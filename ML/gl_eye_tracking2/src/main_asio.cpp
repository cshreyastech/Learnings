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
// #include "RBTexture.h"
#include "RBPoint.h"

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

	// Start asio code
	asio::error_code ec;

	// Create a "context" - essentially the platform specific interface
	asio::io_context context;

	// Get the address of somewhere we wis to connect to
	// asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("142.251.32.36", ec), 80);

	// Create a socket, the contet will deliver the implementation
	asio::ip::tcp::socket socket(context);

	// Tell socket to try and connect
	socket.connect(endpoint, ec);

	if (!ec)
	{
		ML_LOG_TAG(Debug, APP_TAG, "Connected!");
	}
	else
	{
		// std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
		ML_LOG_TAG(Debug, APP_TAG, "Failed to connect to address %s", ec.message().c_str());
	}

	if (socket.is_open())
	{
		std::string sRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		// Send as much as data as possible from server
		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

		// Wait until response
		socket.wait(socket.wait_read);

		// Read available data in socket
		size_t bytes = socket.available();

		if (bytes > 0)
		{
			std::vector<char> vBuffer(bytes);
			socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

			for (auto c : vBuffer)
				ML_LOG_TAG(Debug, APP_TAG, "%c", c);
		}
	}

	// End asio code





	// Part 2: Instantiate the shader 
	// Shader shader3D = Shader();
	// shader3D.Load("data/res/shaders/standard3D.vert", "data/res/shaders/standard.frag");

	// Shader pointShader3D = Shader();
	// pointShader3D.Load("data/res/shaders/basic3D.vert", "data/res/shaders/basic.frag");
	
	// Shader shader_square = Shader();
	// shader_square.Load("data/res/shaders/standard3D.vert", "data/res/shaders/standard.frag");

	// Cube right_eye = Cube();
	// right_eye.ApplyShader(shader3D);
	// right_eye.SetColor(COLOR_BLUE);
	// // glm::vec3 pos = left_eye.GetPosition();
	// right_eye.SetPosition(0.1f, 0.0f, 0.0f);

	// Point cloud = Point();
	// cloud.ApplyShader(pointShader3D);

	// The main/game loop
	ML_LOG_TAG(Debug, APP_TAG, "Enter main loop");
	while (true) {
		// Part 2: Get state of the Controller
		MLInputControllerState input_states[MLInput_MaxControllers];
      CHECK(MLInputGetControllerState(input, input_states));

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

				glClearColor(0.001, 0.001, 0.001, 0.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Part 2: Get the projection matrix
				MLGraphicsVirtualCameraInfo &current_camera = virtual_camera_array.virtual_cameras[camera];
				glm::mat4 projectionMatrix = rb_projection_matrix(current_camera) * rb_camera_matrix(current_camera);

				// Part 2: Render the object
				// cylinder.Render(projectionMatrix);
				// square.Render(projectionMatrix);
				
				// left_eye.Render(projectionMatrix);
				// fixation.Render(projectionMatrix);
				// right_eye.Render(projectionMatrix);
				// point.Render(projectionMatrix);
				// cloud.Render(projectionMatrix);
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


  // // clean up system
  // UNWRAP_MLRESULT(MLHeadTrackingDestroy(head_tracker_));
  // UNWRAP_MLRESULT(MLEyeTrackingDestroy(eye_tracker_));
  
  // UNWRAP_MLRESULT(MLGraphicsDestroyClient(&graphics_client));
  // UNWRAP_MLRESULT(MLPerceptionShutdown());



	return 0;
}
