#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <memory>

#include "Shader.h"
#include "server/socket_server.hpp"
#include "server/struct_declarations.hpp"

#include <vector>

#include <cassert>
#include <fstream>
#include <string>
#include <chrono>

#include "snappy-internal.h"
#include "snappy-sinksource.h"
#include "snappy.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void deserialize(const char* data, float vertices[], const int vertices_length);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  // glfw: initialize and configure
  // ------------------------------
//   glfwInit();
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//   // glfw window creation
//   // --------------------
//   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//   if (window == NULL)
//   {
//     std::cout << "Failed to create GLFW window" << std::endl;
//     glfwTerminate();
//     return -1;
//   }
//   glfwMakeContextCurrent(window);
//   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//   // glad: load all OpenGL function pointers
//   // ---------------------------------------
//   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//   {
//     std::cout << "Failed to initialize GLAD" << std::endl;
//     return -1;
//   }

//   // build and compile our shader program
//   // ------------------------------------
//   Shader ourShader("../../networking/server/res/shaders/pointcloud.shader.vs", 
//                    "../../networking/server/res/shaders/pointcloud.shader.fs");

  std::unique_ptr<SocketServer> server_ptr(new SocketServer(8080));
  server_ptr->ConnectToNetwork();

  const int n_points = server_ptr->ReceiveInt();
  std::cout << "n_points: " << n_points << std::endl;

  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);

  const int p_vertices_compressed_size = server_ptr->ReceiveInt();
  std::cout << "p_vertices_compressed_size: " << p_vertices_compressed_size << std::endl;

  char* p_vertices_compressed = 
    // (char*)malloc(p_vertices_compressed_size);
    new char[p_vertices_compressed_size];

  for(int i = 0; i < 1; i++)
  {
    auto receive_cloud_start = std::chrono::high_resolution_clock::now();
    
    server_ptr->ReceiveCloud(&p_vertices_compressed, p_vertices_compressed_size);

    auto receive_cloud_end = std::chrono::high_resolution_clock::now();
    long long receive_cloud_duration = 
      std::chrono::duration_cast<std::chrono::microseconds>(receive_cloud_end - receive_cloud_start).count();
    printf("Server - snappy - receivecloud(mircosec): %lld\n", receive_cloud_duration);
  }

  char* p_vertices_uncompressed = 
    // (char*)malloc(vertices_size);
    new char[vertices_size];

  auto uncompression_start = std::chrono::high_resolution_clock::now();
  bool raw_uncompress = snappy::RawUncompress(p_vertices_compressed, p_vertices_compressed_size,
                     p_vertices_uncompressed);
  auto uncompression_end = std::chrono::high_resolution_clock::now();
  long long uncompression_duration = 
    std::chrono::duration_cast<std::chrono::microseconds>(uncompression_end - uncompression_start).count();
  printf("Server - snappy - RawUncompression(mircosec): %lld\n", uncompression_duration);

  delete[] p_vertices_compressed;

  float* vertices = new float[vertices_length];
  deserialize(p_vertices_uncompressed, vertices, vertices_length);

  delete[] p_vertices_uncompressed;

  // Validation beginning
  std::ifstream file_handler("/home/shreyas/Downloads/cloud_data/induvidual_rows/depth_data_0.txt");
  float vertices_check[vertices_length];
  // float* vertices_check = new float[vertices_length];
  std::string each_value_str;
  int n_values_read_from_file  = 0;
  while(file_handler >> each_value_str)
  {
    std::string each_value_clean_str = 
      each_value_str.substr(0, each_value_str.find("f", 0));

    float value_float = std::stof(each_value_clean_str);

    vertices_check[n_values_read_from_file] = value_float;
    n_values_read_from_file++;
  }
  assert(n_points == (n_values_read_from_file)/6);

  for(int i = 0; i < vertices_length; i++)
  {
    // printf("vertices[%d]:%f, vertices_check[%d]:%f\n", i, vertices[i], i, vertices_check[i]);
    assert(vertices[i] == vertices_check[i]);
  }
  file_handler.close();
  delete[] vertices;

  std::cout << "Cloud value matches\n";
  // Validation end






















  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

  // unsigned int VBO, VAO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  // glBindVertexArray(VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // // position
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);

  // // The color attribute starts after the position data so the offset is 3 * sizeof(float) 
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  // glEnableVertexAttribArray(1);

  // glBindVertexArray(VAO);
  
  // // render loop
  // // -----------
  // while (!glfwWindowShouldClose(window))
  // {
  //   // input
  //   // -----
  //   processInput(window);

  //   // render
  //   // ------
  //   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //   glClear(GL_COLOR_BUFFER_BIT);

  //   // render the triangle
  //   ourShader.use();
  //   glBindVertexArray(VAO);
  //   glPointSize(5);
  //   glDrawArrays(GL_POINTS, 0, n_points);

  //   // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  //   // -------------------------------------------------------------------------------
  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }

  // // optional: de-allocate all resources once they've outlived their purpose:
  // // ------------------------------------------------------------------------
  // // delete[] vertices;

  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);

  // // glfw: terminate, clearing all previously allocated GLFW resources.
  // // ------------------------------------------------------------------
  // glfwTerminate();


  // Stats
  // p_vertices_compressed_size: 3962497
  // Server - snappy - receivecloud(mircosec): 2926
  // Server - snappy - RawUncompression(mircosec): 24644

  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void deserialize(const char* data, float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}