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
    // delete[] vertices;
  }

  olc::rcode GameEngine::Construct()
  {
    // std::cout << "GameEngine::Construct()\n"; 
    ML_LOG_TAG(Debug, APP_TAG, "GameEngine::Construct()");
  // glfw: initialize and configure
  // ------------------------------


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
