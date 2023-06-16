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
#include <stb_image.h>

#include <ml_graphics.h>
#include <ml_head_tracking.h>
#include <ml_lifecycle.h>
#include <ml_perception.h>

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <chrono>

#include "gl_eye_tracking/core/shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <app_framework/application.h>
#include <app_framework/convert.h>
#include <app_framework/toolset.h>

#include <gflags/gflags.h>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <ml_eye_tracking.h>
#include <ml_head_tracking.h>
#include <ml_logging.h>

DEFINE_bool(draw_fixation_point, true, "Draw the fixation point.");
DEFINE_bool(draw_eye_centers, true, "Draw the eye centers.");
DEFINE_bool(draw_gaze_left, false, "Draw left gaze vector.");
DEFINE_bool(draw_gaze_right, false, "Draw right gaze vector.");
DEFINE_bool(eye_centers_origin, true,
            "If true, eye centers are drawn relative to the origin; otherwise, the world space position is used.");

const glm::vec3 kCubeScale = glm::vec3(0.01f, 0.01f, 0.01f);
const glm::vec3 kEyeCenterScale = glm::vec3(0.02f, 0.02f, 0.02f);

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
  MLHandle head_tracker_ = ML_INVALID_HANDLE;
  MLHeadTrackingStaticData head_static_data_ = {};
  MLHandle eye_tracker_ = ML_INVALID_HANDLE;
  MLEyeTrackingStaticData eye_static_data_ = {};

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
  
  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);
  // build and compile our shader program
  // ------------------------------------
  Shader ourShader("data/res/shaders/6.4.shader.vs", "data/res/shaders/6.4.shader.fs");
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float a = 1.0f;
  float multiplyer = 0.0002f;

  a *= multiplyer;
  float vertices[] = {
     a,  a, -a,
     a,  a,  a,
    -a,  a,  a,
    -a,  a, -a,

     a, -a,  a,
    -a, -a,  a,
     a, -a, -a,

    -a, -a, -a
  };

  unsigned int indices[] = {  // note that we start from 0!
  // X clockwise
  0, 1, 3, 1, 2, 2,
  6, 0, 7, 0, 3, 7,
  4, 6, 5, 6, 7, 5,
  1, 4, 2, 4, 5, 2,
  
  // Y clockwise
  0, 6, 1, 6, 4, 1,
  2, 5, 3, 5, 7, 3
  };


  const int dimention = 3;
  const int vertices_n = sizeof(vertices) / sizeof(vertices[0]);
  const int sides_n = vertices_n / dimention;

  const int indices_n = sizeof(indices) / sizeof(indices[0]);

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  unsigned int stride = sizeof(float) * dimention;
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);

  UNWRAP_MLRESULT(MLHeadTrackingCreate(&head_tracker_));
  UNWRAP_MLRESULT(MLHeadTrackingGetStaticData(head_tracker_, &head_static_data_));

  UNWRAP_MLRESULT(MLEyeTrackingCreate(&eye_tracker_));
  UNWRAP_MLRESULT_FATAL(MLEyeTrackingGetStaticData(eye_tracker_, &eye_static_data_));

  // uncomment this call to draw in wireframe polygons.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glEnable(GL_PROGRAM_POINT_SIZE);
  // glEnable(GL_DEPTH_TEST);
  // glEnable(GL_FRAMEBUFFER_SRGB);
  //----------------------------------------------//
  ML_LOG(Info, "Start loop.");

  // Get ready to connect our GL context to the MLSDK graphics API
  GLuint framebuffer_id = 0;
  glGenFramebuffers(1, &framebuffer_id);

  auto start = std::chrono::high_resolution_clock::now();
  while (AppStatus::Stopped != status) {
    if (AppStatus::Paused == status) {
      continue;
    }
    MLSnapshot *snapshot = nullptr;
    UNWRAP_MLRESULT(MLPerceptionGetSnapshot(&snapshot));

    MLTransform fixation = {};
    MLTransform left_eye_center = {};
    MLTransform right_eye_center = {};
    MLTransform head = {};
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &head_static_data_.coord_frame_head, &head));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.fixation, &fixation));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.left_center, &left_eye_center));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.right_center, &right_eye_center));
    UNWRAP_MLRESULT(MLPerceptionReleaseSnapshot(snapshot));

    // Render Fixation point
    glm::quat Q_W_FIX = ml::app_framework::to_glm(fixation.rotation);
    glm::quat P_W_FIX = ml::app_framework::to_glm(fixation.position);

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

    for (int camera = 0; camera < 2; ++camera) {
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
      glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, frame_info.color_id, 0, camera);
      glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, frame_info.depth_id, 0, camera);

      const MLRectf &viewport = frame_info.viewport;
      
      // 0, 0, 1280, 960
      glViewport((GLint)viewport.x, (GLint)viewport.y, (GLsizei)viewport.w, (GLsizei)viewport.h);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

      //---------Insert rendering code below---------//
      auto end = std::chrono::high_resolution_clock::now();
      auto dur = end - start;
      auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(dur);

      // activate shader
      ourShader.use();

      // create transformations
      glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
      glm::mat4 view          = glm::mat4(1.0f);
      glm::mat4 projection    = glm::mat4(1.0f);
      model = glm::rotate(model, f_secs.count(), glm::vec3(0.5f, 1.0f, 0.0f));
      view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.5f));
      float aspect_ratio = (viewport.w / viewport.h);
      projection = glm::perspective(glm::radians(5.0f), aspect_ratio, 0.1f, 100.0f);
      // retrieve the matrix uniform locations
      unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
      unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
      // pass them to the shaders (3 different ways)
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
      // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
      ourShader.setMat4("projection", projection);

      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, indices_n, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
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
  glDeleteBuffers(1, &EBO);

  glDeleteFramebuffers(1, &framebuffer_id);

  // clean up system
  UNWRAP_MLRESULT(MLHeadTrackingDestroy(head_tracker_));
  UNWRAP_MLRESULT(MLEyeTrackingDestroy(eye_tracker_));
  
  UNWRAP_MLRESULT(MLGraphicsDestroyClient(&graphics_client));
  UNWRAP_MLRESULT(MLPerceptionShutdown());

  return 0;
}
