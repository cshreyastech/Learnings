#define MLSDK20

#include "ros_ml_server/ros_ml_server.hpp"


int main() {
	graphics_context_t graphics_context;

	MLLoggingEnableLogLevel(MLLogLevel_Debug);

	// Assign call application lifecycle callback functions
	MLResult result;


  MLLifecycleCallbacksEx lifecycle_callbacks = {};
  MLLifecycleCallbacksExInit(&lifecycle_callbacks);
  lifecycle_callbacks.on_stop = OnStop;
  lifecycle_callbacks.on_pause = OnPause;
  lifecycle_callbacks.on_resume = OnResume;

  std::atomic<AppStatus> status(AppStatus::Running);

  MLLifecycleInitEx(&lifecycle_callbacks, (void *)&status);


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
	

	Cube left_eye = Cube();
	left_eye.ApplyShader(shader3D);
	left_eye.SetColor(COLOR_RED);
	// glm::vec3 pos = left_eye.GetPosition();
	left_eye.SetPosition(-0.1f, 0.0f, 0.0f);


	Cube fixation = Cube();
	fixation.ApplyShader(shader3D);
	fixation.SetColor(COLOR_GREEN);
	fixation.SetPosition(0.0f, 0.0f, 0.0f);

	Cube right_eye = Cube();
	right_eye.ApplyShader(shader3D);
	right_eye.SetColor(COLOR_BLUE);
	// glm::vec3 pos = left_eye.GetPosition();
	right_eye.SetPosition(0.1f, 0.0f, 0.0f);


  std::unique_ptr<SocketServer> server_ptr(new SocketServer(8080));
  server_ptr->ConnectToNetwork();

  const int n_points = server_ptr->ReceiveInt();
  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);


  const int p_vertices_compressed_size = server_ptr->ReceiveInt();
  ML_LOG_TAG(Info, APP_TAG, "p_vertices_compressed_size: %d\n", p_vertices_compressed_size);


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
    ML_LOG_TAG(Info, APP_TAG, "Server - snappy - receivecloud(mircosec): %lld\n", receive_cloud_duration);
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
  ML_LOG_TAG(Info, APP_TAG, "Server - snappy - RawUncompression(mircosec): %lld\n", uncompression_duration);

  delete[] p_vertices_compressed;

  float* vertices = new float[vertices_length];
  deserialize(p_vertices_uncompressed, vertices, vertices_length);

  delete[] p_vertices_uncompressed;


	// 08-28 12:55:37.592  2202     1 I MAIN    : p_vertices_compressed_size: 3962497
	// 08-28 12:55:37.806  2202     1 I MAIN    : Server - snappy - receivecloud(mircosec): 213901
	// 08-28 12:55:37.891  2202     1 I MAIN    : Server - snappy - RawUncompression(mircosec): 85082

  // float* vertices_0 = (float*)malloc(vertices_size);


 // Validation beginning
  std::ifstream file_handler("data/res/cloud/depth_data_0.txt");
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

  ML_LOG_TAG(Info, APP_TAG, "Cloud data matches");
  ////////////////////

  MLHandle ml_head_tracker_ = ML_INVALID_HANDLE;
  MLHeadTrackingStaticData ml_head_static_data_ = {};
  MLHandle ml_eye_tracker_ = ML_INVALID_HANDLE;
  MLEyeTrackingStaticData ml_eye_static_data_ = {};

  MLHeadTrackingCreate(&ml_head_tracker_);
  MLHeadTrackingGetStaticData(ml_head_tracker_, &ml_head_static_data_);

  MLEyeTrackingCreate(&ml_eye_tracker_);
  MLEyeTrackingGetStaticData(ml_eye_tracker_, &ml_eye_static_data_);

  Point cloud = Point(pointShader3D, n_points, vertices_size);
  
  int vertices_id = 0;
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

    fixation.SetPosition(ml_fixation.position.x, ml_fixation.position.y, ml_fixation.position.z);

    // Initialize a frame
    MLGraphicsFrameParamsEx frame_params;
    MLGraphicsFrameParamsExInit(&frame_params);

    frame_params.surface_scale = 1.0f;
    frame_params.projection_type = MLGraphicsProjectionType_ReversedInfiniteZ;
    frame_params.near_clip = 0.38;
    frame_params.focus_distance = 1.0f;

    MLHandle frame_handle;



    // MLGraphicsVirtualCameraInfoArray virtual_camera_array;
    MLGraphicsFrameInfo frame_info = {};
    MLGraphicsFrameInfoInit(&frame_info);

    // Begin the frame
    MLResult frame_result = MLGraphicsBeginFrameEx(graphics_client, &frame_params, &frame_info);

    frame_handle = frame_info.handle;


    if (frame_result == MLResult_Ok) {
      // Prepare rendering for each camera/eye
      for (int camera = 0; camera < 2; ++camera) {
        glBindFramebuffer(GL_FRAMEBUFFER, graphics_context.framebuffer_id);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, frame_info.color_id, 0, camera);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, frame_info.depth_id, 0, camera);

        const MLRectf& viewport = frame_info.viewport;
        glViewport((GLint)viewport.x, (GLint)viewport.y, (GLsizei)viewport.w, (GLsizei)viewport.h);

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Part 2: Get the projection matrix
        MLGraphicsVirtualCameraInfo &current_camera = frame_info.virtual_cameras[camera];
        glm::mat4 projectionMatrix = rb_projection_matrix(current_camera) * rb_camera_matrix(current_camera);

        // Part 2: Render the object

        fixation.Render(projectionMatrix);
        cloud.Render(projectionMatrix, vertices, vertices_size);
        // Bind the frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        MLGraphicsSignalSyncObjectGL(graphics_client, frame_info.virtual_cameras[camera].sync_object);
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
  delete[] vertices;
	graphics_context.unmakeCurrent();
	glDeleteFramebuffers(1, &graphics_context.framebuffer_id);
	MLGraphicsDestroyClient(&graphics_client);
	MLPerceptionShutdown();
	ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");

  // clean up system
  MLHeadTrackingDestroy(ml_head_tracker_);
  MLEyeTrackingDestroy(ml_eye_tracker_);
  
	return 0;
}