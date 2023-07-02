// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2018 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Creator Agreement, located
// here: https://id.magicleap.com/creator-terms
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%
#include <app_framework/graphics_context.h>
#include <app_framework/ml_macros.h>

#include <glad/glad.h>

#include <ml_graphics.h>
#include <ml_head_tracking.h>
#include <ml_lifecycle.h>
#include <ml_logging.h>
#include <ml_perception.h>

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <cmath>
// #include <GLFW/glfw3.h>
#include <chrono>

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "out vec3 ourColor;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos, 1.0);\n"
  "   ourColor = aColor;\n"
  "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 ourColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(ourColor, 1.0);\n"
  "}\n\0";



enum class AppStatus { Stopped, Paused, Running };

// Callbacks
static void OnStop(void *application_context) {
  auto status = reinterpret_cast<std::atomic<AppStatus> *>(application_context);
  *status = AppStatus::Stopped;
  ML_LOG(Info, "On stop called.");
}

static void OnPause(void *application_context) {
  auto status = reinterpret_cast<std::atomic<AppStatus> *>(application_context);
  *status = AppStatus::Paused;
  ML_LOG(Info, "On pause called.");
}

static void OnResume(void *application_context) {
  auto status = reinterpret_cast<std::atomic<AppStatus> *>(application_context);
  *status = AppStatus::Running;
  ML_LOG(Info, "On resume called.");
}

int main() {
  // set up host-specific graphics surface
  ml::app_framework::GraphicsContext graphics_context;
  graphics_context.MakeCurrent();
  if (!gladLoadGLLoader((GLADloadproc)ml::app_framework::GraphicsContext::GetProcAddress)) {
    ML_LOG(Fatal, "gladLoadGLLoader() failed");
  }

  // let system know our app has started
  MLLifecycleCallbacksEx lifecycle_callbacks = {};
  MLLifecycleCallbacksExInit(&lifecycle_callbacks);
  lifecycle_callbacks.on_stop = OnStop;
  lifecycle_callbacks.on_pause = OnPause;
  lifecycle_callbacks.on_resume = OnResume;

  std::atomic<AppStatus> status(AppStatus::Running);

  UNWRAP_MLRESULT(MLLifecycleInitEx(&lifecycle_callbacks, (void *)&status));

  // initialize perception system
  MLPerceptionSettings perception_settings;
  UNWRAP_MLRESULT(MLPerceptionInitSettings(&perception_settings));

  UNWRAP_MLRESULT(MLPerceptionStartup(&perception_settings));


  MLGraphicsOptions graphics_options = {0, MLSurfaceFormat_RGBA8UNorm, MLSurfaceFormat_D32Float};
  MLHandle graphics_client = ML_INVALID_HANDLE;
  UNWRAP_MLRESULT(MLGraphicsCreateClientGL(&graphics_options, graphics_context.GetContextHandle(), &graphics_client));

  // Now that graphics is connected, the app is ready to go
  UNWRAP_MLRESULT(MLLifecycleSetReadyIndication());

  MLHandle head_tracker;
  UNWRAP_MLRESULT(MLHeadTrackingCreate(&head_tracker));
  MLHeadTrackingStaticData head_static_data;
  UNWRAP_MLRESULT(MLHeadTrackingGetStaticData(head_tracker, &head_static_data));
  //----------------------------------------------//
  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    ML_LOG(Info, "ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s", infoLog);
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    ML_LOG(Info, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s", infoLog);
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    ML_LOG(Info, "ERROR::SHADER::PROGRAM::LINKING_FAILED: %s", infoLog);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

// set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
  };

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

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //----------------------------------------------//
  ML_LOG(Info, "Start loop.");

  auto start = std::chrono::steady_clock::now();

  // Get ready to connect our GL context to the MLSDK graphics API
  GLuint framebuffer_id = 0;
  glGenFramebuffers(1, &framebuffer_id);

  while (AppStatus::Stopped != status) {
    if (AppStatus::Paused == status) {
      continue;
    }

    MLGraphicsFrameParamsEx frame_params;
    MLGraphicsFrameParamsExInit(&frame_params);

    MLHandle frame_handle;
    MLGraphicsFrameInfo frame_info = {};
    MLGraphicsFrameInfoInit(&frame_info);
    MLResult out_result = MLGraphicsBeginFrameEx(graphics_client, &frame_params, &frame_info);
    if (MLResult_Ok != out_result) {
      if (MLResult_Pending == out_result || MLResult_Timeout == out_result) {
        continue;
      } else {
        UNWRAP_MLRESULT(out_result);
      }
    }

    frame_handle = frame_info.handle;
    // auto msRuntime =
    // std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    auto current_time = std::chrono::system_clock::now();
    auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());
    double timeValue = duration_in_seconds.count();


    for (int camera = 0; camera < 2; ++camera) {
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
      glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, frame_info.color_id, 0, camera);
      glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, frame_info.depth_id, 0, camera);

      const MLRectf &viewport = frame_info.viewport;
      
      glViewport((GLint)viewport.x, (GLint)viewport.y, (GLsizei)viewport.w, (GLsizei)viewport.h);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      //---------Insert rendering code below---------//
      // update shader uniform
      // be sure to activate the shader before any calls to glUniform
      glUseProgram(shaderProgram);

      // render the triangle
      glDrawArrays(GL_TRIANGLES, 0, 3);
      

      //---------Insert rendering code above---------//
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      UNWRAP_MLRESULT(
          MLGraphicsSignalSyncObjectGL(graphics_client, frame_info.virtual_cameras[camera].sync_object));
    }
    UNWRAP_MLRESULT(MLGraphicsEndFrame(graphics_client, frame_handle));

    graphics_context.SwapBuffers();
  }

  ML_LOG(Info, "End loop.");
  // ---------------------------------------------------
  graphics_context.UnMakeCurrent();

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  

  glDeleteFramebuffers(1, &framebuffer_id);
  // clean up system
  UNWRAP_MLRESULT(MLGraphicsDestroyClient(&graphics_client));
  UNWRAP_MLRESULT(MLPerceptionShutdown());

  return 0;
}