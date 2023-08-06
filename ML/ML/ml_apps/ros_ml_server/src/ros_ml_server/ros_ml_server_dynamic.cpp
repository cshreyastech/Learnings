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

#include "app_framework/support_functions.h"
#include "app_framework/graphics_context.h"

#include "core/RBShader.h"
#include "render/RBCube.h"
#include "render/RBPoint.h"

#include "ros_ml_server/socket_server.hpp"
#include "ros_ml_server/zlib_compression.hpp"

#include <cassert>
#include <fstream>
#include <string>
#include <chrono>

#include <fstream>
#include <cassert>

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

void deserialize(std::vector<uint8_t>& data, float vertices[], const int vertices_length);
void ParseCloudFromFile(const std::string file_path, float vertices[], const int n_points);

int main() {
  std::unique_ptr<SocketServer> server_ptr(new SocketServer(8080));
  server_ptr->ConnectToNetwork();

  const int n_points = server_ptr->ReceiveInt();
  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);
  ML_LOG_TAG(Error, APP_TAG, "n_points:%d ", n_points);
  
  // Receive Cloud data
  // std::vector<uint8_t> p_vertices_vec;
  // server_ptr->ReceiveCloud(p_vertices_vec, vertices_size);
  // assert(p_vertices_vec.size() == vertices_size);
  // ML_LOG_TAG(Error, APP_TAG, "p_vertices_vec.size():%lu ", p_vertices_vec.size());
  
  // // convert it to float array
  // float* vertices = (float*)malloc(vertices_size);
  // deserialize(p_vertices_vec, vertices, vertices_length);

  // ML_LOG_TAG(Info, APP_TAG, "Starting Cloud data validation");
  // float* vertices_0_check = (float*)malloc(vertices_size);
  // ParseCloudFromFile("data/res/cloud/depth_data_0.txt", vertices_0_check, n_points);
  // for(int i = 0; i < vertices_length; i++)
  //   assert(vertices_0_check[i] == vertices[i]);

  // delete[] vertices;
  // delete[] vertices_0_check;
  // ML_LOG_TAG(Info, APP_TAG, "Cloud data matches");

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
	

	// Cube left_eye = Cube();
	// left_eye.ApplyShader(shader3D);
	// left_eye.SetColor(COLOR_RED);
	// left_eye.SetPosition(-0.1f, 0.0f, 0.0f);

	Cube fixation = Cube();
	fixation.ApplyShader(shader3D);
	fixation.SetColor(COLOR_GREEN);
	fixation.SetPosition(0.0f, 0.0f, 0.0f);


	// Cube right_eye = Cube();
	// right_eye.ApplyShader(shader3D);
	// right_eye.SetColor(COLOR_BLUE);
	// right_eye.SetPosition(0.1f, 0.0f, 0.0f);

  Point cloud = Point(pointShader3D, n_points, vertices_size);


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
    std::vector<uint8_t> p_vertices_vec;

    auto ReceiveCloudStart = std::chrono::high_resolution_clock::now();
    server_ptr->ReceiveCloud(p_vertices_vec, vertices_size);
    auto ReceiveCloudEnd = std::chrono::high_resolution_clock::now();
    // assert(p_vertices_vec.size() == vertices_size);

  
    auto deserializeStart = std::chrono::high_resolution_clock::now();
    // convert it to float array
    float* vertices = (float*)malloc(vertices_size);
    deserialize(p_vertices_vec, vertices, vertices_length);
    auto deserializeEnd = std::chrono::high_resolution_clock::now();

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

				
				// left_eye.Render(projectionMatrix);
				fixation.Render(projectionMatrix);
				// right_eye.Render(projectionMatrix);
				// point.Render(projectionMatrix);
				// cloud.Render(projectionMatrix);

        auto renderStart = std::chrono::high_resolution_clock::now();
        cloud.Render(projectionMatrix, vertices, vertices_size);
        auto renderEnd = std::chrono::high_resolution_clock::now();

				// Bind the frame buffer
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				MLGraphicsSignalSyncObjectGL(graphics_client, virtual_camera_array.virtual_cameras[camera].sync_object);

        long long ReceiveCloudDuration = 
          std::chrono::duration_cast<std::chrono::microseconds>(ReceiveCloudEnd - ReceiveCloudStart).count();

        long long deserializeDuration = 
          std::chrono::duration_cast<std::chrono::microseconds>(deserializeEnd - deserializeStart).count();

        long long renderDuration = 
          std::chrono::duration_cast<std::chrono::microseconds>(renderEnd - renderStart).count();

          ML_LOG_TAG(Info, APP_TAG, "ReceiveCloudDuration: %lld", ReceiveCloudDuration);
          ML_LOG_TAG(Info, APP_TAG, " deserializeDuration: %lld", deserializeDuration);
          ML_LOG_TAG(Info, APP_TAG, "      renderDuration: %lld", renderDuration);
          ML_LOG_TAG(Info, APP_TAG, "---------------------------------------");
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
    delete[] vertices;
	}

	// End of game loop, clean app and exit
	ML_LOG_TAG(Debug, APP_TAG, "End application loop");

	graphics_context.unmakeCurrent();
	glDeleteFramebuffers(1, &graphics_context.framebuffer_id);
	MLGraphicsDestroyClient(&graphics_client);
	MLPerceptionShutdown();
	ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");

  // clean up system
  // delete[] vertices;
  MLHeadTrackingDestroy(ml_head_tracker_);
  MLEyeTrackingDestroy(ml_eye_tracker_);

	return 0;
}


void deserialize(std::vector<uint8_t>& data, float vertices[], const int vertices_length)
{
  std::vector<uint8_t>::iterator it = data.begin();

  float *q = (float*)&(*it);

  // std::cout << "OOM: " << 51619 * sizeof(float) << std::endl;

  // vertices[51620] = *q; q++;
  // vertices[vertices_length - 1] = 0.0012f;
  for(int i = 0; i < vertices_length + 1; i++)
  {
    vertices[i] = *q; q++; 
  }
}

void ParseCloudFromFile(const std::string file_path, float vertices[], const int n_points)
{
  std::ifstream file_handler(file_path);
  ML_LOG_TAG(Debug, APP_TAG, "file_path: %s", file_path.c_str());

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

  file_handler.close();
  assert(n_points == (n_values_read_from_file / 6));
}