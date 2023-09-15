#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H


#include<string>
#include <iostream>

#include "core/ml_graphics_context.h"

#include "render/RBShader.h"
#include "render/RBCube.h"
#include "render/RBPointDynamic.h"

namespace olc
{
  enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };
  class GameEngine
  {
  public:
    GameEngine();
    virtual ~GameEngine();
  public:
    olc::rcode Construct(int32_t screen_w, int32_t screen_h);
    olc::rcode Start();

  public: // User override interface
  // Called once on application startup, use to load your resources
  virtual bool OnUserCreate();
  // // Called every frame, and provides with a time per frame value
  virtual bool OnUserUpdate(float fElaspedTime);
  // Called once an application termination, used for clearing resources
  virtual bool OnUserDestroy();

  olc::rcode PublishCloud(float vertices[]);
  // public: // DRAWING ROUTINES
  //   // Draws a single Pixel
  //   // To be filled later

  public: // Branding
    std::string sAppName;
    int n_points;
    float* vertices;

  private:
    void RequestPrivileges();

  private:
    // GLFWwindow* window_;
  }; 

}
#endif