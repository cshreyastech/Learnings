#include "core/game_engine.h"


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

    graphics_context_.unmakeCurrent();
    // glDeleteFramebuffers(1, &graphics_context.framebuffer_id);
    // MLGraphicsDestroyClient(&graphics_client);
    MLPerceptionShutdown();
    ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");

    // delete[] vertices_0;
    // clean up system
    // MLHeadTrackingDestroy(ml_head_tracker_);
    // MLEyeTrackingDestroy(ml_eye_tracker_);

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
    MLHandle opengl_context = reinterpret_cast<MLHandle>(graphics_context_.egl_context);
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
      return olc::rcode::NO_FILE;
    }
    else {
      ML_LOG_TAG(Debug, APP_TAG, "Lifecycle system ready");
    }




    return olc::rcode::OK;
  }

  bool GameEngine::OnUserCreate()
  {
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::OnUserCreate()");
    return false;
  }

  bool GameEngine::OnUserUpdate(float fElaspedTime)
  {
    // std::cout << "GameEngine::OnUserUpdate()\n"; 
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::OnUserUpdate()");
    // const int vertices_length = n_points * 6;
    // const int vertices_size = vertices_length * sizeof(float);

    // assert(vertices[vertices_length - 1] == 0.619608f);
    // std::cout << "GameEngine::OnUserUpdate() - validated:" << std::endl;

    // assert(vertices[vertices_length - 1] == 0.619608f);
    // while (!glfwWindowShouldClose(window_))
    // {

    // }

    return false;
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

  olc::rcode GameEngine::PublishCloud(float vertices[])
  {
    // std::cout << "GameEngine::PublishCloud()\n";
    // std::cout << "vertices[10] = 0.133333f: " << vertices[10] << std::endl;

    return olc::rcode::OK;
  }



} // namespace olc
