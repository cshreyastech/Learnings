#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H


#include<string>
#include <iostream>

// #include <ml_logging.h>

const char APP_TAG[] = "MAIN";

namespace olc
{
  enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };
  class GameEngine
  {
  public:
    GameEngine();
    virtual ~GameEngine();
  public:
    olc::rcode Construct();
    olc::rcode Start();

  public: // User override interface
  // Called once on application startup, use to load your resources
  virtual bool OnUserCreate();
  // // Called every frame, and provides with a time per frame value
  virtual bool OnUserUpdate(float fElaspedTime);
  // Called once an application termination, used for clearing resources
  virtual bool OnUserDestroy();

  olc::rcode PublishCloud(float vertices[]);

  public: // Branding
		std::string sAppName;
		int n_points;
    float* vertices;

  private:
    // graphics_context_t graphics_context_;
    // GLFWwindow* window_;
  }; 

}
#endif