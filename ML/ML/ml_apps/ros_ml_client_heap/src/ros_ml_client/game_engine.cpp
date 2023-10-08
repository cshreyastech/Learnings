#include "ros_ml_client/game_engine.h"
#include "core/ml_to_glm.h"



namespace olc
{
  GameEngine::GameEngine()
  {
    // std::cout << "GameEngine::GameEngine()\n";
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::GameEngine()");
  }

  GameEngine::~GameEngine()
  {
    // std::cout << "GameEngine::~GameEngine()\n"; 
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::~GameEngine()");

    // delete fixation_;
    // delete cloud_;

    graphics_context_.unmakeCurrent();
    glDeleteFramebuffers(1, &graphics_context_.framebuffer_id);
    MLGraphicsDestroyClient(&graphics_client_);
    MLPerceptionShutdown();
    ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");

    
    // clean up system
    MLHeadTrackingDestroy(ml_head_tracker_);
    MLEyeTrackingDestroy(ml_eye_tracker_);


    // delete[] vertices;
  }

  olc::rcode GameEngine::Construct()
  {
    // std::cout << "GameEngine::Construct()\n"; 
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::Construct()");
  // glfw: initialize and configure
  // ------------------------------
    MLLoggingEnableLogLevel(MLLogLevel_Debug);


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
      return olc::rcode::NO_FILE;
    }

    if (MLResult_Ok != MLPerceptionStartup(&perception_settings)) {
      ML_LOG_TAG(Error, APP_TAG, "Failed to startup perception");
      return olc::rcode::NO_FILE;
    }


    // Create OpenGL context and create framebuffer
    graphics_context_.makeCurrent();
    glGenFramebuffers(1, &graphics_context_.framebuffer_id);

    MLGraphicsOptions graphics_options = { 0, MLSurfaceFormat_RGBA8UNorm, MLSurfaceFormat_D32Float };
    opengl_context_ = reinterpret_cast<MLHandle>(graphics_context_.egl_context);

    MLGraphicsCreateClientGL(&graphics_options, opengl_context_, &graphics_client_);

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
      return olc::rcode::NO_FILE;
    }
    else {
      ML_LOG_TAG(Debug, APP_TAG, "Lifecycle system ready");
    }

    // Part 2: Instantiate the shader 
    Shader shader3D = Shader();
    shader3D.Load("data/res/shaders/standard3D.vert", "data/res/shaders/standard.frag");

    Shader pointShader3D = Shader();
    pointShader3D.Load("data/res/shaders/basic3D.vert", "data/res/shaders/basic.frag");

    render_point_cloud_.SetShader(pointShader3D);

    fixation_.ApplyShader(shader3D);
    fixation_.SetColor(COLOR_GREEN);
    fixation_.SetPosition(0.0f, 0.0f, 0.0f);

    MLHeadTrackingCreate(&ml_head_tracker_);
    MLHeadTrackingGetStaticData(ml_head_tracker_, &ml_head_static_data_);

    MLEyeTrackingCreate(&ml_eye_tracker_);
    MLEyeTrackingGetStaticData(ml_eye_tracker_, &ml_eye_static_data_);

    // The main/game loop
    ML_LOG_TAG(Debug, APP_TAG, "Enter main loop");

    return olc::rcode::OK;
  }

  bool GameEngine::OnUserCreate()
  {
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::OnUserCreate()");
    return false;
  }


  bool GameEngine::OnUserUpdate(float fElaspedTime)
  {
    return false;
  }

  void GameEngine::PublishCloud(const Point point_cloud[])
  {
    MLSnapshot *snapshot = nullptr;
    MLPerceptionGetSnapshot(&snapshot);

    MLTransform ml_fixation = {};
    MLTransform ml_left_eye_center = {};
    MLTransform ml_right_eye_center = {};
    MLTransform ml_head = {};
    MLSnapshotGetTransform(snapshot, &ml_head_static_data_.coord_frame_head, &ml_head);
    MLSnapshotGetTransform(snapshot, &ml_eye_static_data_.fixation, &ml_fixation);

    fixation_.SetPosition(ml_fixation.position.x, ml_fixation.position.y, ml_fixation.position.z);

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
    MLResult frame_result = MLGraphicsBeginFrameEx(graphics_client_, &frame_params, &frame_info);

    frame_handle = frame_info.handle;


    if (frame_result == MLResult_Ok) {
      // Prepare rendering for each camera/eye
      for (int camera = 0; camera < 2; ++camera) {
        glBindFramebuffer(GL_FRAMEBUFFER, graphics_context_.framebuffer_id);
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

        fixation_.Render(projectionMatrix);

        render_point_cloud_.Render(projectionMatrix, point_cloud);
        
        // Bind the frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        MLGraphicsSignalSyncObjectGL(graphics_client_, frame_info.virtual_cameras[camera].sync_object);
      }

      // Finish the frame
      result_ = MLGraphicsEndFrame(graphics_client_, frame_handle);

      if (MLResult_Ok != result_) {
        ML_LOG_TAG(Error, APP_TAG, "MLGraphicsEndFrame() error: %d", result_);
      }
    }
    else if (frame_result != MLResult_Timeout) {
      // Sometimes it fails with timeout when device is busy
      ML_LOG_TAG(Error, APP_TAG, "MLGraphicsBeginFrame() error: %d", frame_result);
    }
  }

  bool GameEngine::OnUserDestroy()
  {
    // std::cout << "GameEngine::OnUserDestroy()\n"; 
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::OnUserDestroy()");
    return true;
  }

  olc::rcode GameEngine::Start()
  {
    // std::cout << "GameEngine::OnuserStart()\n"; 
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::Start()");
    OnUserCreate();

    while(true)
      OnUserUpdate(0.0f);
    return olc::rcode::OK;
  }



} // namespace olc
