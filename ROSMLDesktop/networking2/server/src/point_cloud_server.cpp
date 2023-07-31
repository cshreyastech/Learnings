#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <memory>

#include "Shader.h"
#include "server/socket_server.hpp"
#include "server/struct_declarations.hpp"

#include "server/zlib_compression.hpp"
#include <vector>

#include <cassert>
#include <fstream>
#include <string>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void deserialize(std::vector<uint8_t>& data, float vertices[], const int vertices_length);
void deserialize(uint8_t const* data, float vertices[], const int vertices_length);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
//   // glfw: initialize and configure
//   // ------------------------------
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
  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);

  
  const int zlibData_size = server_ptr->ReceiveInt();
  std::cout << "zlibData_size: " << zlibData_size << std::endl;

  std::vector<uint8_t> zlibData_vec;
  server_ptr->ReceiveCloud(zlibData_size, zlibData_vec);
  uint8_t* zlibData_array = (uint8_t*)malloc(zlibData_vec.size());
  std::copy(zlibData_vec.begin(), zlibData_vec.end(), zlibData_array);

  ZlibCompression zlib;
  std::vector<uint8_t> plainData = zlib.Decompress(zlibData_array, zlibData_vec.size());

  // convert it to float array
  float* vertices = (float*)malloc(vertices_size);
  deserialize(plainData, vertices, vertices_length);

  // for(int i = 0; i < vertices_length; i++)
  //   assert(vertices_client[i] == vertices_server[i]);

  

  // server_ptr->ReceiveCloud(zlibData_size);

  // uint8_t* zlibData;
  // uint8_t* zlibData = (uint8_t*)malloc(2969600 + 100000000);
  // uint8_t* zlibData = new uint8_t[5969600];

  // server_ptr->ReceiveCloud(&zlibData, zlibData_size);
  // delete[] zlibData;
  // ZlibCompression zlib;
  // std::vector<uint8_t> data_server = zlib.decompress(zlibData_array, zlibData_client.size());
  // std::vector<uint8_t> plainData = decompressor->decompress(zlibData);


  // float* vertices = (float*)malloc(vertices_size);
  // // DeserializeFloatArray(vertices, vertices_length, plainData);
  // deserialize(plainData, vertices, vertices_length);



  // Validation beginning
  std::ifstream file_handler("/home/cs20/Downloads/cloud_data_tbd/induvidual_rows/depth_data.txt");
  // float vertices_check[vertices_length];
  float* vertices_check = new float[vertices_length];
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
    // printf("vertices_check[%d]:%f\n", i, vertices_check[i]);
    assert(vertices[i] == vertices_check[i]);
  }
  file_handler.close();
  delete[] vertices_check;
  delete[] vertices;
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

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  // delete[] vertices;

  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);

  // // glfw: terminate, clearing all previously allocated GLFW resources.
  // // ------------------------------------------------------------------
  // glfwTerminate();
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

void deserialize(std::vector<uint8_t>& data, float vertices[], const int vertices_length)
{
  std::vector<uint8_t>::iterator it = data.begin();

  float *q = (float*)&(*it);

  // std::cout << "OOM: " << 51619 * sizeof(float) << std::endl;

  // vertices[51620] = *q; q++;
  // vertices[vertices_length - 1] = 0.0012f;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++; 
  }
}

void deserialize(uint8_t const* data, float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}