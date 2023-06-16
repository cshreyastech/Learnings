#include "gl_eye_tracking/gl_eye_tracking5.hpp"

const glm::vec3 kCubeScale = glm::vec3(0.01f, 0.01f, 0.01f);

void GLEyeTrackingApp::OnStart()
{
  ML_LOG(Info, "OnStart()");

  cube_node1_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node2_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node3_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node4_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node5_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node6_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node7_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  cube_node8_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);

  GetRoot()->AddChild(cube_node1_);
  GetRoot()->AddChild(cube_node2_);
  GetRoot()->AddChild(cube_node3_);
  GetRoot()->AddChild(cube_node4_);
  GetRoot()->AddChild(cube_node5_);
  GetRoot()->AddChild(cube_node6_);
  GetRoot()->AddChild(cube_node7_);
  GetRoot()->AddChild(cube_node8_);

  cube_node1_->SetLocalScale(kCubeScale);
  cube_node2_->SetLocalScale(kCubeScale);
  cube_node3_->SetLocalScale(kCubeScale);
  cube_node4_->SetLocalScale(kCubeScale);
  cube_node5_->SetLocalScale(kCubeScale);
  cube_node6_->SetLocalScale(kCubeScale);
  cube_node7_->SetLocalScale(kCubeScale);
  cube_node8_->SetLocalScale(kCubeScale);
}

void GLEyeTrackingApp::OnStop()
{
  ML_LOG(Info, "OnStop()");
}

void GLEyeTrackingApp::OnUpdate(float)
{
  const glm::quat Q_W(-0.0, 0.0, -0.0, 1.0);

  cube_node1_->SetWorldRotation(Q_W);
  cube_node2_->SetWorldRotation(Q_W);
  cube_node3_->SetWorldRotation(Q_W);
  cube_node4_->SetWorldRotation(Q_W);
  cube_node5_->SetWorldRotation(Q_W);
  cube_node6_->SetWorldRotation(Q_W);
  cube_node7_->SetWorldRotation(Q_W);
  cube_node8_->SetWorldRotation(Q_W);

  float d = 1.0f;
  cube_node1_->SetWorldTranslation(glm::vec3(-0.0, -0.0, -0.5));
  
  cube_node2_->SetWorldTranslation(glm::vec3(-0.0, -0.0, -d));
  
  cube_node3_->SetWorldTranslation(glm::vec3(-d, -0.0, -d));
  cube_node4_->SetWorldTranslation(glm::vec3( d, -0.0, -d));
  
  cube_node5_->SetWorldTranslation(glm::vec3( 0.0, -d, -d));
  cube_node6_->SetWorldTranslation(glm::vec3( 0.0,  d, -d));

  cube_node7_->SetWorldTranslation(glm::vec3( d,  d, -d));
  cube_node8_->SetWorldTranslation(glm::vec3(-d, -d, -d));
}

int main(int argc, char **argv) {
  GLEyeTrackingApp app(argc, argv);
  app.SetUseGfx(true);
  app.RunApp();
  return 0;
}
