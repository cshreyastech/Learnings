#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <memory>

#include "Shader.h"
#include "server/socket_server.hpp"
#include "server/struct_declarations.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // build and compile our shader program
  // ------------------------------------
  Shader ourShader("../../networking/server/res/shaders/pointcloud.shader.vs", 
                   "../../networking/server/res/shaders/pointcloud.shader.fs");

  std::unique_ptr<SocketServer> server_ptr(new SocketServer(8080));
  server_ptr->ConnectToNetwork();

  // const int n_vertices = server_ptr->ReceiveInt();

  const int n_vertices = 1;
  const int vertices_size = n_vertices * 6;

  float vertices[vertices_size];
  server_ptr->ReceiveCloud(vertices, vertices_size);

  // printf("vertices[%d]:%f\n", vertices_size - 1, vertices[vertices_size - 1]);
  // printf("vertices[%d]:%f\n", vertices_size - 23, vertices[vertices_size - 23]);
  // printf("vertices[%d]:%f\n", vertices_size - 1239, vertices[vertices_size - 1239]);
  // for(int i = 0; i < vertices_size; i++)
  // {
  //   printf("vertices[%d]:%f\n", i, vertices[i]);
  // }




//   const int n_vertices = 5;
//   // set up vertex data (and buffer(s)) and configure vertex attributes
//   // ------------------------------------------------------------------
//   float vertices[n_vertices * 6] = {
//     // positions         // colors
//     //  0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
//     // -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom left
//     //  0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f    // top 

// -0.524111f, -0.392878f, -0.931184f, 0.635294f, 0.635294f, 0.635294f, 
// -0.522476f, -0.392882f, -0.931193f, 0.635294f, 0.635294f, 0.635294f, 
// -0.520837f, -0.392883f, -0.931197f, 0.635294f, 0.635294f, 0.635294f, 
// -0.519204f, -0.392889f, -0.931210f, 0.635294f, 0.635294f, 0.635294f, 
// -0.517565f, -0.392890f, -0.931213f, 0.635294f, 0.635294f, 0.635294f, 
//   };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // The color attribute starts after the position data so the offset is 3 * sizeof(float) 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(VAO);


  // float offset = 0.5f; //Exercise 3.2
  
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render the triangle
    // ourShader.setFloat("xOffset", offset); //Exercise 3.2
    ourShader.use();
    glBindVertexArray(VAO);
    glPointSize(5);
    glDrawArrays(GL_POINTS, 0, n_vertices);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // glDeleteProgram(ourShader);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
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