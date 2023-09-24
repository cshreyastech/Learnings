#ifndef ML_GRAPHICS_CONTEXT_H
#define ML_GRAPHICS_CONTEXT_H

#include "core/platform_includes.h"
// 1. Types and definitions

// const char APP_TAG[] = "MAIN";

struct graphics_context_t {
  EGLDisplay egl_display;
  EGLContext egl_context;
  GLuint framebuffer_id;

  graphics_context_t();
  ~graphics_context_t();

  void makeCurrent();
  void unmakeCurrent();
};

// -----------------------------------------------------------------------------
// 3. App Lifecycle callback functions

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



#define COLOR_RED glm::vec3(1,0,0)
#define COLOR_GREEN glm::vec3(0,1,0)
#define COLOR_BLUE glm::vec3(0,0,1)

// -----------------------------------------------------------------------------
// Part 2: ML helper functions

#define CHECK(c) do { \
  auto result = (c); \
  if (result != MLResult_Ok) { \
    ML_LOG_TAG(Error, APP_TAG, "%s failed (%d).", #c, (int)result); \
    return -1; \
  } \
} while (0)



#endif