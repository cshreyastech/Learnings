#pragma once

#include <app_framework/application.h>
#include <app_framework/convert.h>
#include <app_framework/ml_macros.h>
#include <app_framework/toolset.h>

#include <gflags/gflags.h>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <ml_eye_tracking.h>
#include <ml_head_tracking.h>
#include <ml_logging.h>
#include <ml_perception.h>

class GLEyeTrackingApp : public ml::app_framework::Application {
public:
  GLEyeTrackingApp(int argc = 0, char **argv = nullptr) : ml::app_framework::Application(argc, argv) {}

  void OnStart() override;

  void OnStop() override;

  void OnUpdate(float) override;

private:
  std::shared_ptr<ml::app_framework::Node> fixation_node_;
  std::shared_ptr<ml::app_framework::Node> left_center_node_;
  std::shared_ptr<ml::app_framework::Node> right_center_node_;
  std::shared_ptr<ml::app_framework::Node> left_gaze_node_;
  std::shared_ptr<ml::app_framework::Node> right_gaze_node_;
  std::shared_ptr<ml::app_framework::Node> left_gaze_point_node_;
  std::shared_ptr<ml::app_framework::Node> right_gaze_point_node_;

  MLHandle head_tracker_ = ML_INVALID_HANDLE;
  MLHeadTrackingStaticData head_static_data_ = {};
  MLHandle eye_tracker_ = ML_INVALID_HANDLE;
  MLEyeTrackingStaticData eye_static_data_ = {};
};


