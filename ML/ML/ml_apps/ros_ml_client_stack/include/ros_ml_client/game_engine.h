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
    // olc::rcode Construct();
    bool Construct();
    // olc::rcode Start();
    bool Start();

    void PublishCoud(float vertices[], const int n_points);

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
    int n_points{0};
    // int vertices_length{0};
    // int vertices_size{0};

  private:
    graphics_context_t graphics_context_;
    MLResult result_;
    MLHandle opengl_context_;
    MLHandle graphics_client_ = ML_INVALID_HANDLE;

    MLHandle ml_head_tracker_ = ML_INVALID_HANDLE;
    MLHeadTrackingStaticData ml_head_static_data_ = {};
    
    MLHandle ml_eye_tracker_ = ML_INVALID_HANDLE;
    MLEyeTrackingStaticData ml_eye_static_data_ = {};

    // TBD: Change them to unique pointers.
    // TBD: Modify Cube to dynamic rendering
    Cube* fixation_ = nullptr;
    Point* cloud_ = nullptr;

  }; 

}
#endif