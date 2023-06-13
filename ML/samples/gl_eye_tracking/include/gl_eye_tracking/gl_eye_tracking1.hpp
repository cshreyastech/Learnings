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



#include <app_framework/node.h>
#include <app_framework/preset_resource.h>
#include <app_framework/resource_pool.h>
#include <app_framework/components/renderable_component.h>
#include <app_framework/material/pbr_material.h>
#include <app_framework/material/textured_material.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/texture.h>

#include <stb_image.h>


class GLEyeTrackingApp : public ml::app_framework::Application {
public:
  GLEyeTrackingApp(int argc = 0, char **argv = nullptr) : ml::app_framework::Application(argc, argv) {}

  void OnStart() override;

  void OnStop() override;

  void OnUpdate(float) override;

private:
  std::shared_ptr<ml::app_framework::Node> fixation_node_;
  std::shared_ptr<ml::app_framework::Node> left_gaze_node_;

  std::shared_ptr<ml::app_framework::Node> quad_node_;
  std::shared_ptr<ml::app_framework::Node> tex_node_;
  std::shared_ptr<ml::app_framework::Texture> tex_;
  std::shared_ptr<ml::app_framework::PBRMaterial> mat_;
};


