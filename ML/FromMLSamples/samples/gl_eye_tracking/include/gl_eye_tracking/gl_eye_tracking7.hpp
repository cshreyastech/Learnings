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
#include "gl_eye_tracking/core/shader.hpp"
#include <stb_image.h>

class GLEyeTrackingApp : public ml::app_framework::Application {
public:
  GLEyeTrackingApp(int argc = 0, char **argv = nullptr) : ml::app_framework::Application(argc, argv) {}

  void OnStart() override;

  void OnStop() override;

  void OnUpdate(float) override;

private:
  unsigned int texture;
  unsigned int VBO, VAO, EBO;
  Shader* ourShader{nullptr};

};


