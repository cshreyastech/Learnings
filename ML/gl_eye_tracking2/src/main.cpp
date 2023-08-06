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

#include "RBShader.h"
#include "RBCylinder.h"
#include "RBSquare.h"
#include "RBCube.h"
#include "RBPoint.h"
#include <fstream>
#include <cassert>

// -----------------------------------------------------------------------------
// Part 2: Define a color

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

	// Part 2: Instantiate the shader 
	Shader shader3D = Shader();
	shader3D.Load("data/res/shaders/standard3D.vert", "data/res/shaders/standard.frag");

	Shader pointShader3D = Shader();
	pointShader3D.Load("data/res/shaders/basic3D.vert", "data/res/shaders/basic.frag");
	
	// Shader shader_square = Shader();
	// shader_square.Load("data/res/shaders/standard3D.vert", "data/res/shaders/standard.frag");

	// Part 2: Instantiate the objec(s) here 
	// Cylinder cylinder = Cylinder(16);
	// cylinder.ApplyShader(shader3D);
	// cylinder.SetColor(COLOR_RED);

	// Square square = Square(16);
	// square.ApplyShader(shader_square);
	// square.SetColor(COLOR_RED);



	Cube left_eye = Cube();
	left_eye.ApplyShader(shader3D);
	left_eye.SetColor(COLOR_RED);
	// glm::vec3 pos = left_eye.GetPosition();
	left_eye.SetPosition(-0.1f, 0.0f, 0.0f);


	Cube fixation = Cube();
	fixation.ApplyShader(shader3D);
	fixation.SetColor(COLOR_GREEN);
	// glm::vec3 pos = fixation.GetPosition();
	fixation.SetPosition(0.0f, 0.0f, 0.0f);

	// Point point = Point(16);
	// point.ApplyShader(shader3D);
	// point.SetColor(COLOR_GREEN);
	// point.SetPosition(0.0f, 0.0f, 0.0f);

	Cube right_eye = Cube();
	right_eye.ApplyShader(shader3D);
	right_eye.SetColor(COLOR_BLUE);
	// glm::vec3 pos = left_eye.GetPosition();
	right_eye.SetPosition(0.1f, 0.0f, 0.0f);


  std::ifstream file_handler("data/res/cloud/depth_data.txt");
  const int n_points = 307200;
  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);

  float* vertices = (float*)malloc(vertices_size);

  std::string each_value_str;
  int n_values_read_from_file  = 0;
  while(file_handler >> each_value_str)
  {
    std::string each_value_clean_str = 
      each_value_str.substr(0, each_value_str.find("f", 0));

    float value_float = std::stof(each_value_clean_str);

    vertices[n_values_read_from_file] = value_float;
    n_values_read_from_file++;
  }
  assert(n_points == (n_values_read_from_file)/6);

	Point cloud = Point();
	cloud.ApplyShader(pointShader3D, vertices, n_points, vertices_size);
  delete[] vertices;

  MLHandle ml_head_tracker_ = ML_INVALID_HANDLE;
  MLHeadTrackingStaticData ml_head_static_data_ = {};
  MLHandle ml_eye_tracker_ = ML_INVALID_HANDLE;
  MLEyeTrackingStaticData ml_eye_static_data_ = {};

  MLHeadTrackingCreate(&ml_head_tracker_);
  MLHeadTrackingGetStaticData(ml_head_tracker_, &ml_head_static_data_);

  MLEyeTrackingCreate(&ml_eye_tracker_);
  MLEyeTrackingGetStaticData(ml_eye_tracker_, &ml_eye_static_data_);

	// The main/game loop
	ML_LOG_TAG(Debug, APP_TAG, "Enter main loop");
	while (true) {
		// Part 2: Get state of the Controller
		MLInputControllerState input_states[MLInput_MaxControllers];
      CHECK(MLInputGetControllerState(input, input_states));

    MLSnapshot *snapshot = nullptr;
    MLPerceptionGetSnapshot(&snapshot);

    MLTransform ml_fixation = {};
    MLTransform ml_left_eye_center = {};
    MLTransform ml_right_eye_center = {};
    MLTransform ml_head = {};
    MLSnapshotGetTransform(snapshot, &ml_head_static_data_.coord_frame_head, &ml_head);
    MLSnapshotGetTransform(snapshot, &ml_eye_static_data_.fixation, &ml_fixation);
    // MLSnapshotGetTransform(snapshot, &ml_eye_static_data_.left_center, &ml_left_eye_center);
    // MLSnapshotGetTransform(snapshot, &eye_static_data_.right_center, &right_eye_center);
    // MLPerceptionReleaseSnapshot(snapshot);
		fixation.SetPosition(ml_fixation.position.x, ml_fixation.position.y, ml_fixation.position.z);
		// ML_LOG_TAG(Info, APP_TAG, "ml_head(%f, %f, %f)", 
		// 	ml_head.position.x, ml_head.position.y, ml_head.position.z);
		// ML_LOG_TAG(Info, APP_TAG, "ml_left_eye_center(%f, %f, %f)", 
		// 	ml_left_eye_center.position.x, ml_left_eye_center.position.y, ml_left_eye_center.position.z);




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

				// glm::vec4 left_eye_center(ml_left_eye_center.position.x, 
				// ml_left_eye_center.position.y,
				// ml_left_eye_center.position.z, 1.0);
				// left_eye_center = rb_camera_matrix(current_camera) * left_eye_center;

				// left_eye.SetPosition(ml_left_eye_center.position.x, 
				// 	ml_left_eye_center.position.y,
				// 	ml_left_eye_center.position.z);


				// Part 2: Render the object
				// cylinder.Render(projectionMatrix);
				// square.Render(projectionMatrix);
				
				// left_eye.Render(projectionMatrix);
				fixation.Render(projectionMatrix);
				// right_eye.Render(projectionMatrix);
				// point.Render(projectionMatrix);
				cloud.Render(projectionMatrix);
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
	MLPerceptionShutdown();
	ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");


  // clean up system
  MLHeadTrackingDestroy(ml_head_tracker_);
  MLEyeTrackingDestroy(ml_eye_tracker_);
  
  // UNWRAP_MLRESULT(MLGraphicsDestroyClient(&graphics_client));
  // UNWRAP_MLRESULT(MLPerceptionShutdown());



	return 0;
}
