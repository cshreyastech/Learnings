#pragma once

#include <app_framework/application.h>
#include <app_framework/convert.h>
#include <app_framework/ml_macros.h>
#include <app_framework/toolset.h>

#include <gflags/gflags.h>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <ml_controller.h>
#include <ml_head_tracking.h>
#include <ml_input.h>
#include <ml_perception.h>

#include <array>
#include <cstdlib>
#include <sstream>

class GLEyeTrackingApp : public ml::app_framework::Application {
public:
  GLEyeTrackingApp(int argc = 0, char **argv = nullptr) : ml::app_framework::Application(argc, argv) {}

  void OnStart() override;

  void OnStop() override;

  void OnUpdate(float) override;

private:
  struct ControllerVisual {
    std::shared_ptr<ml::app_framework::Node> controller;
    std::shared_ptr<ml::app_framework::Node> touch;
    std::shared_ptr<ml::app_framework::Node> text;
  };
  std::array<ControllerVisual, MLInput_MaxControllers> input_nodes_;
  MLHandle input_tracker_ = ML_INVALID_HANDLE;
  MLHandle head_tracker_ = ML_INVALID_HANDLE;
  MLHeadTrackingStaticData head_static_data_ = {};

  void UpdateText(const MLInputControllerState &controller_state, ml::app_framework::TextComponent &text_comp);
};


