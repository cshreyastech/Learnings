#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H


#include<string>
#include <iostream>

#include "core/ml_graphics_context.h"

#include "common/ros_ml_common.h"
#include "render/RBShader.h"
#include "render/RBCubeDynamic.h"
#include "render/RBPointDynamic.h"
#include <memory>


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

  void PublishCloud(const Point point_cloud[]);

  public: // Branding
    std::string sAppName;

  private:
    graphics_context_t graphics_context_;
    MLResult result_;
    MLHandle opengl_context_;
    MLHandle graphics_client_ = ML_INVALID_HANDLE;

    MLHandle ml_head_tracker_ = ML_INVALID_HANDLE;
    MLHeadTrackingStaticData ml_head_static_data_ = {};
    
    MLHandle ml_eye_tracker_ = ML_INVALID_HANDLE;
    MLEyeTrackingStaticData ml_eye_static_data_ = {};

    RBCube fixation_;
    RBPoint render_point_cloud_;

  }; 

}
#endif