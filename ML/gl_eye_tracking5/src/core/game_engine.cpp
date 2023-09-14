#include "core/game_engine.h"
#include "core/ml_utilities.h"

namespace olc
{
  GameEngine::GameEngine()
  {

  }

  GameEngine::~GameEngine()
  {
    ML_LOG_TAG(Debug, APP_TAG, "inside GameEngine::~GameEngine()");
    // delete[] vertices;
  }

  olc::rcode GameEngine::Construct(int32_t screen_w, int32_t screen_h)
  {
    ML_LOG_TAG(Debug, APP_TAG, "inside GameEngine::Construct()");
  // glfw: initialize and configure
  // ------------------------------


    return olc::rcode::OK;
  }

  bool GameEngine::OnUserCreate()
  {
    ML_LOG_TAG(Debug, APP_TAG, "inside GameEngine::Create()");
    return false;
  }

  bool GameEngine::OnUserUpdate(float fElaspedTime)
  {
    ML_LOG_TAG(Debug, APP_TAG, "inside GameEngine::OnUserUpdate()");
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
    ML_LOG_TAG(Debug, APP_TAG, "inside GameEngine::OnUserDestroy()");
		return true;
	}

  olc::rcode GameEngine::Start()
  {
    ML_LOG_TAG(Debug, APP_TAG, "inside GameEngine::Start()");
    OnUserCreate();

    while(true)
      OnUserUpdate(0.0f);
    return olc::rcode::OK;
  }

} // namespace olc
