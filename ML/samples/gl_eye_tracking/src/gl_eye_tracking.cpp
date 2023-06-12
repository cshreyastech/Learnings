#include "gl_eye_tracking/gl_eye_tracking.hpp"


static bool ValidateDof(const char *flagname, gflags::int32 value) {
  if (0 == value || 3 == value || 6 == value) {
    return true;
  }

  ML_LOG(Error, "%s cannot be %d. It must be 0, 3, or 6.", flagname, value);
  return false;
}

DEFINE_int32(dof0, 6, "Desired degrees-of-freedom mode of controller 0. Can be 0, 3, or 6.");
DEFINE_validator(dof0, &ValidateDof);
DEFINE_int32(dof1, 6, "Desired degrees-of-freedom mode of controller 1. Can be 0, 3, or 6.");
DEFINE_validator(dof1, &ValidateDof);

void GLEyeTrackingApp::OnStart() {
  using namespace ml::app_framework;
  for (auto &node : input_nodes_) {
    node.controller = std::make_shared<ml::app_framework::Node>();

    auto model = Registry::GetInstance()->GetResourcePool()->LoadAsset("data/Controller.fbx");
    model->SetLocalRotation(glm::quat{glm::vec3{0.f, glm::pi<float>(), 0.f}});
    model->SetLocalScale(glm::vec3(0.01f));
    node.controller->AddChild(model);

    auto touchpad_offset = std::make_shared<ml::app_framework::Node>();
    touchpad_offset->SetLocalRotation(glm::quat{glm::vec3{glm::radians(-90.f + 18.f), 0.f, 0.f}});
    node.controller->AddChild(touchpad_offset);
    node.touch = Registry::GetInstance()->GetResourcePool()->LoadAsset("data/Touchpad_arrow.fbx");
    node.touch->SetLocalScale(glm::vec3(0.02f));
    node.touch->SetLocalRotation(glm::quat{glm::vec3{0.f, glm::pi<float>(), 0.f}});
    touchpad_offset->AddChild(node.touch);

    // node.text = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Text);
    // node.text->SetLocalTranslation(glm::vec3(0.f, 0.f, -0.5f));
    // node.controller->AddChild(node.text);
  }

  UNWRAP_MLRESULT(MLHeadTrackingCreate(&head_tracker_));
  UNWRAP_MLRESULT(MLHeadTrackingGetStaticData(head_tracker_, &head_static_data_));

  MLInputConfiguration input_config = {};
  input_config.dof[0] = static_cast<MLInputControllerDof>(FLAGS_dof0 / 3);
  input_config.dof[1] = static_cast<MLInputControllerDof>(FLAGS_dof1 / 3);
  UNWRAP_MLRESULT(MLInputCreate(&input_config, &input_tracker_));
}

void GLEyeTrackingApp::OnStop() {
  UNWRAP_MLRESULT(MLInputDestroy(input_tracker_));
  UNWRAP_MLRESULT(MLHeadTrackingDestroy(head_tracker_));
}

void GLEyeTrackingApp::OnUpdate(float) {
  MLInputControllerState controller_states[MLInput_MaxControllers];
  UNWRAP_MLRESULT(MLInputGetControllerState(input_tracker_, controller_states));
  for (size_t i = 0; i < input_nodes_.size(); ++i) {
    if (controller_states[i].is_connected) {
      GetRoot()->AddChild(input_nodes_[i].controller);
      auto controller_transform = glm::translate(ml::app_framework::to_glm(controller_states[i].position)) *
                                  glm::mat4_cast(ml::app_framework::to_glm(controller_states[i].orientation));
      input_nodes_[i].controller->SetWorldTranslation(ml::app_framework::to_glm(controller_states[i].position));
      input_nodes_[i].controller->SetWorldRotation(ml::app_framework::to_glm(controller_states[i].orientation));
      input_nodes_[i].touch->SetLocalTranslation(
          0.02f * ml::app_framework::to_glm(controller_states[i].touch_pos_and_force[0]));
    } else {
      GetRoot()->RemoveChild(input_nodes_[i].controller);
    }
    // UpdateText(controller_states[i], *input_nodes_[i].text->GetComponent<ml::app_framework::TextComponent>());
  }
}

void GLEyeTrackingApp::UpdateText(const MLInputControllerState &controller_state, ml::app_framework::TextComponent &text_comp) {
  std::stringstream ss;
  ss << "orientation = " << glm::to_string(ml::app_framework::to_glm(controller_state.orientation)) << std::endl;
  ss << "position = " << glm::to_string(ml::app_framework::to_glm(controller_state.position)) << std::endl;
  ss << "touch_pos_and_force 0 = "
     << glm::to_string(ml::app_framework::to_glm(controller_state.touch_pos_and_force[0])) << std::endl;
  ss << "touch_pos_and_force 1 = "
     << glm::to_string(ml::app_framework::to_glm(controller_state.touch_pos_and_force[1])) << std::endl;
  ss << "trigger_normalized = " << controller_state.trigger_normalized << std::endl;
  ss << "button_state[MLInputControllerButton_Bumper] = "
     << controller_state.button_state[MLInputControllerButton_Bumper] << std::endl;
  ss << "is_touch_active 0 = " << controller_state.is_touch_active[0] << std::endl;
  ss << "is_touch_active 1 = " << controller_state.is_touch_active[1] << std::endl;
  ss << "is_connected = " << controller_state.is_connected << std::endl;
  ss << "type = " << controller_state.type << std::endl;
  ss << "dof = " << controller_state.dof << std::endl;
  ss << "hardware_index = " << static_cast<uint32_t>(controller_state.hardware_index) << std::endl;
  text_comp.SetText(ss.str().c_str(), 0.5, 0.5);
}
