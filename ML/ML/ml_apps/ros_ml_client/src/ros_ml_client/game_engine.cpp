#include "ros_ml_client/game_engine.h"



namespace olc
{
  GameEngine::GameEngine()
  {
    ML_LOG_TAG(Info, APP_TAG, "GameEngine::GameEngine()");
  }

  GameEngine::~GameEngine()
  {
    ML_LOG_TAG(Info, APP_TAG, "Inside ~GameEngine()");
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::~GameEngine()");

    delete fixation_;
    delete cloud_;

    graphics_context_.unmakeCurrent();
    glDeleteFramebuffers(1, &graphics_context_.framebuffer_id);
    MLGraphicsDestroyClient(&graphics_client_);
    MLPerceptionShutdown();
    ML_LOG_TAG(Debug, APP_TAG, "System cleanup done");

    
    // clean up system
    MLHeadTrackingDestroy(ml_head_tracker_);
    MLEyeTrackingDestroy(ml_eye_tracker_);

    delete[] vertices;
  }

  olc::rcode GameEngine::Construct()
  {
  // glfw: initialize and configure
  // ------------------------------


    return olc::rcode::OK;
  }

  bool GameEngine::OnUserCreate()
  {
    return false;
  }

  bool GameEngine::OnUserUpdate(float fElaspedTime)
  {
    // ML_LOG_TAG(Info, APP_TAG, "GameEngine::OnUserUpdate()");

    // const int vertices_length = n_points * 6;
    // const int vertices_size = vertices_length * sizeof(float);

    assert(vertices[vertices_length - 1] == 0.619608f);
    // std::cout << "GameEngine::OnUserUpdate() - validated:" << std::endl;

    // assert(vertices[vertices_length - 1] == 0.619608f);
    // while (!glfwWindowShouldClose(window_))
    // {

    // }

    return false;
  }

  bool GameEngine::OnUserDestroy()
  {

    ML_LOG_TAG(Info, APP_TAG, "Inside OnUserDestroy()");    
    delete[] vertices;

    return true;
  }

  olc::rcode GameEngine::Start()
  {
    OnUserCreate();

    while(true)
      OnUserUpdate(0.0f);
    return olc::rcode::OK;
  }

  olc::rcode GameEngine::PublishCloud(float vertices[])
  {
    std::cout << "Inside GameEngine::PublishCloud()\n";
    std::cout << "vertices[10] = 0.133333f: " << vertices[10] << std::endl;

    return olc::rcode::OK;
  }

} // namespace olc
