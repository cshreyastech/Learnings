#define MLSDK20

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cmath>

#include <ml_logging.h>
#include <ml_graphics.h>
#include <ml_lifecycle.h>
#include <ml_perception.h>
#include <ml_head_tracking.h>
#include <ml_input.h>
#include <fstream>
#include <string>
#include <sstream>

#include "platform_include.h"

// -----------------------------------------------------------------------------
// Part 2: Define a color

#define COLOR_RED glm::vec3(1,0,0)
#define COLOR_GREEN glm::vec3(0,1,0)

// -----------------------------------------------------------------------------
// Part 2: ML helper functions

#define CHECK(c) do { \
    auto result = (c); \
    if (result != MLResult_Ok) { \
        ML_LOG_TAG(Error, APP_TAG, "%s failed (%d).", #c, (int)result); \
        return -1; \
    } \
} while (0)

// -----------------------------------------------------------------------------
// Part 2: glm helper functions

glm::mat4 rb_convert_ml_to_glm(const MLTransform &ml) {
    glm::quat q;
    q.w = ml.rotation.w;
    q.x = ml.rotation.x;
    q.y = ml.rotation.y;
    q.z = ml.rotation.z;

    return glm::translate(glm::mat4(), glm::vec3(ml.position.x, ml.position.y, ml.position.z)) * glm::toMat4(q);
}

glm::mat4 rb_projection_matrix(MLGraphicsVirtualCameraInfo &camera) {
  return (glm::make_mat4(camera.projection.matrix_colmajor));
}

glm::mat4 rb_camera_matrix(MLGraphicsVirtualCameraInfo &camera) {
  glm::mat4 proj = glm::make_mat4(camera.projection.matrix_colmajor);
  glm::vec3 trans = glm::make_vec3(camera.transform.position.values);
  glm::mat4 rotMat = glm::mat4_cast(glm::make_quat(camera.transform.rotation.values));
  glm::mat4 transMat = glm::translate(glm::mat4(1.0f), trans);
  glm::mat4 worldFromCamera = transMat * rotMat;

  return (glm::inverse(worldFromCamera));
}

// -----------------------------------------------------------------------------
// 1. Types and definitions

const char APP_TAG[] = "MAIN";

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
// 2. OpenGL context functions

graphics_context_t::graphics_context_t() {
  egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  EGLint major = 4;
  EGLint minor = 0;
  eglInitialize(egl_display, &major, &minor);
  eglBindAPI(EGL_OPENGL_API);

  EGLint config_attribs[] = {
    EGL_RED_SIZE, 5,
    EGL_GREEN_SIZE, 6,
    EGL_BLUE_SIZE, 5,
    EGL_ALPHA_SIZE, 0,
    EGL_DEPTH_SIZE, 24,
    EGL_STENCIL_SIZE, 8,
    EGL_NONE
  };

  EGLConfig egl_config = nullptr;
  EGLint config_size = 0;
  eglChooseConfig(egl_display, config_attribs, &egl_config, 1, &config_size);

  EGLint context_attribs[] = {
    EGL_CONTEXT_MAJOR_VERSION_KHR, 3,
    EGL_CONTEXT_MINOR_VERSION_KHR, 0,
    EGL_NONE
  };

  egl_context = eglCreateContext(egl_display, egl_config, EGL_NO_CONTEXT, context_attribs);
}

void graphics_context_t::makeCurrent() {
  eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, egl_context);
}

void graphics_context_t::unmakeCurrent() {
  eglMakeCurrent(NULL, EGL_NO_SURFACE, EGL_NO_SURFACE, NULL);
}

graphics_context_t::~graphics_context_t() {
  eglDestroyContext(egl_display, egl_context);
  eglTerminate(egl_display);
}

// -----------------------------------------------------------------------------
// 3. App Lifecycle callback functions

static void on_stop(void* user_data) {
  ML_LOG_TAG(Info, APP_TAG, "Lifecycle call on_stop()");
}

static void on_pause(void* user_data) {
  ML_LOG_TAG(Info, APP_TAG, "Lifecycle call on_pause()");
}

static void on_resume(void* user_data) {
  ML_LOG_TAG(Info, APP_TAG, "Lifecycle call on_resume()");
}


// -----------------------------------------------------------------------------
struct ShaderProgramSource
{
  std::string VertexSource;
  std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
  std::ifstream stream(filepath);

  enum class ShaderType
  {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while (getline(stream, line))
  {
    if (line.find("#shader") != std::string::npos)
    {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    }
    else
      ss[(int)type] << line << '\n';
  }

  return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    // Stack side allocation of dynamic memory
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    // std::cout << "Failed to compile " <<
    //   (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" <<
    //   std::endl;
    // std::cout << message << std::endl;

    ML_LOG_TAG(Error, "Failed to compile %s shader!", 
      (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));

    glDeleteShader(id);
    return 0;

  }
  return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

// -----------------------------------------------------------------------------
// 4. Main

int main() {
  graphics_context_t graphics_context;

  MLLoggingEnableLogLevel(MLLogLevel_Debug);

  // Assign call application lifecycle callback functions
  MLLifecycleCallbacks lifecycle_callbacks = {};
  lifecycle_callbacks.on_stop = on_stop;
  lifecycle_callbacks.on_pause = on_pause;
  lifecycle_callbacks.on_resume = on_resume;

  // Initialize application lifecycle
  MLResult result = MLLifecycleInit(&lifecycle_callbacks, nullptr);

  if (result != MLResult_Ok) {
    ML_LOG_TAG(Error, APP_TAG, "Failed to initialize lifecycle system");
    return -1;
  }
  else {
    ML_LOG_TAG(Debug, APP_TAG, "Lifecycle system started");
  }

  // Initialize perception system
  MLPerceptionSettings perception_settings;
  if (MLResult_Ok != MLPerceptionInitSettings(&perception_settings)) {
    ML_LOG_TAG(Error, APP_TAG, "Failed to initialize perception");
    return -1;
  }

  if (MLResult_Ok != MLPerceptionStartup(&perception_settings)) {
    ML_LOG_TAG(Error, APP_TAG, "Failed to startup perception");
    return -1;
  }

  // Create OpenGL context and create framebuffer
  graphics_context.makeCurrent();
  glGenFramebuffers(1, &graphics_context.framebuffer_id);

  MLGraphicsOptions graphics_options = { 0, MLSurfaceFormat_RGBA8UNorm, MLSurfaceFormat_D32Float };
  MLHandle opengl_context = reinterpret_cast<MLHandle>(graphics_context.egl_context);
  MLHandle graphics_client = ML_INVALID_HANDLE;
  MLGraphicsCreateClientGL(&graphics_options, opengl_context, &graphics_client);

  // Part 2: Set up the head tracker
  MLHandle head_tracker;
  MLResult head_track_result = MLHeadTrackingCreate(&head_tracker);
  MLHeadTrackingStaticData head_static_data;

  if (MLResult_Ok == head_track_result && MLHandleIsValid(head_tracker)) {
    MLHeadTrackingGetStaticData(head_tracker, &head_static_data);
  }
  else {
    ML_LOG_TAG(Error, APP_TAG, "Failed to create head tracker");
  }

  // Ready for application lifecycle
  if (MLLifecycleSetReadyIndication() != MLResult_Ok) {
    ML_LOG_TAG(Error, APP_TAG, "Failed to indicate lifecycle readyness");
    return -1;
  }
  else {
    ML_LOG_TAG(Debug, APP_TAG, "Lifecycle system ready");
  }

  // Part 2: Create the input handler
  ML_LOG_TAG(Debug, APP_TAG, "Create input system (controller)");
  MLHandle input;
  CHECK(MLInputCreate(NULL, &input));

  // Opengl Code
  ML_LOG_TAG(Info, APP_TAG, "GL Version %s", glGetString(GL_VERSION));
  float positions[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
  

  unsigned int ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
  
  unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
  glUseProgram(shader);

  // The main/game loop
  ML_LOG_TAG(Debug, APP_TAG, "Enter main loop");
  while (true) {      
    // Initialize a frame
    MLGraphicsFrameParams frame_params;
    result = MLGraphicsInitFrameParams(&frame_params);

    if (MLResult_Ok != result) {
      ML_LOG_TAG(Error, APP_TAG, "MLGraphicsInitFrameParams() error: %d", result);
    }

    frame_params.surface_scale = 1.0f;
    frame_params.projection_type = MLGraphicsProjectionType_ReversedInfiniteZ;
    frame_params.near_clip = 0.38;
    frame_params.focus_distance = 1.0f;

    MLHandle frame_handle;
    MLGraphicsVirtualCameraInfoArray virtual_camera_array;

    // Begin the frame
    MLResult frame_result = MLGraphicsBeginFrame(graphics_client, &frame_params, &frame_handle, &virtual_camera_array);

    if (frame_result == MLResult_Ok) {
      // Prepare rendering for each camera/eye
      for (int camera = 0; camera < 2; ++camera) {
        glBindFramebuffer(GL_FRAMEBUFFER, graphics_context.framebuffer_id);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, virtual_camera_array.color_id, 0, camera);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, virtual_camera_array.depth_id, 0, camera);

        const MLRectf& viewport = virtual_camera_array.viewport;
        glViewport((GLint)viewport.x, (GLint)viewport.y, (GLsizei)viewport.w, (GLsizei)viewport.h);

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Part 2: Get the projection matrix
        MLGraphicsVirtualCameraInfo &current_camera = virtual_camera_array.virtual_cameras[camera];
        glm::mat4 projectionMatrix = rb_projection_matrix(current_camera) * rb_camera_matrix(current_camera);

        // Part 2: Render the object
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Bind the frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        MLGraphicsSignalSyncObjectGL(graphics_client, virtual_camera_array.virtual_cameras[camera].sync_object);
      }

      // Finish the frame
      result = MLGraphicsEndFrame(graphics_client, frame_handle);

      if (MLResult_Ok != result) {
        ML_LOG_TAG(Error, APP_TAG, "MLGraphicsEndFrame() error: %d", result);
      }
    }
    else if (frame_result != MLResult_Timeout) {
      // Sometimes it fails with timeout when device is busy
      ML_LOG_TAG(Error, APP_TAG, "MLGraphicsBeginFrame() error: %d", frame_result);
    }
  }

  // End of game loop, clean app and exit
  ML_LOG_TAG(Debug, APP_TAG, "End application loop");

  graphics_context.unmakeCurrent();

  glDeleteFramebuffers(1, &graphics_context.framebuffer_id);

  MLGraphicsDestroyClient(&graphics_client);

  ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");

  return 0;
}
