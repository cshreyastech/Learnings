#include "gl_eye_tracking/gl_eye_tracking.hpp"

const glm::vec3 kCubeScale = glm::vec3(0.01f, 0.01f, 0.01f);

void GLEyeTrackingApp::OnStart()
{
  ML_LOG(Info, "OnStart()");

  fixation_node_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  left_gaze_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Line);
  quad_node_      = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Quad);

  GetRoot()->AddChild(fixation_node_);
  GetRoot()->AddChild(left_gaze_node_);
  GetRoot()->AddChild(quad_node_);

  fixation_node_->SetLocalScale(kCubeScale);
  quad_node_->SetLocalScale(kCubeScale);
}

void GLEyeTrackingApp::OnStop()
{
  ML_LOG(Info, "OnStop()");
}

void GLEyeTrackingApp::OnUpdate(float)
{
  // ML_LOG(Info, "-------------");
  // ML_LOG(Info, "OnUpdate()");


  const glm::quat Q_W(-0.0, 0.0, -0.0, 1.0);
  const glm::vec3 P_W(-0.0, -0.0, -0.5);
  const glm::vec3 left_direction(0.0, 0.0, -1.0);

  fixation_node_->SetWorldRotation(Q_W);
  fixation_node_->SetWorldTranslation(P_W);

  quad_node_->SetWorldRotation(Q_W);
  quad_node_->SetWorldTranslation(P_W);

  glm::vec3 left_gaze_line[] = {
    P_W,
    P_W + left_direction
  };

  auto left_line_renderable = left_gaze_node_->GetComponent<ml::app_framework::RenderableComponent>();
  left_line_renderable->GetMesh()->SetPrimitiveType(GL_LINES);
  left_line_renderable->GetMesh()->UpdateMesh(left_gaze_line, nullptr, sizeof(left_gaze_line)/sizeof(glm::vec3), nullptr, 0);
  auto left_line_material = 
      std::static_pointer_cast<ml::app_framework::FlatMaterial>(left_line_renderable->GetMaterial());
  left_line_material->SetColor(glm::vec4(.0f, .0f, 1.0f, 1.0f));
}