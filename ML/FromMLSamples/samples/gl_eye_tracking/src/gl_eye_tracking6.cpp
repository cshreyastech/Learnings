#include "gl_eye_tracking/gl_eye_tracking6.hpp"

DEFINE_bool(draw_fixation_point, true, "Draw the fixation point.");
DEFINE_bool(draw_eye_centers, true, "Draw the eye centers.");
DEFINE_bool(draw_gaze_left, false, "Draw left gaze vector.");
DEFINE_bool(draw_gaze_right, false, "Draw right gaze vector.");
DEFINE_bool(eye_centers_origin, true,
            "If true, eye centers are drawn relative to the origin; otherwise, the world space position is used.");

const glm::vec3 kCubeScale = glm::vec3(0.01f, 0.01f, 0.01f);
const glm::vec3 kEyeCenterScale = glm::vec3(0.02f, 0.02f, 0.02f);
void GLEyeTrackingApp::OnStart()
{
    UNWRAP_MLRESULT(MLHeadTrackingCreate(&head_tracker_));
    UNWRAP_MLRESULT(MLHeadTrackingGetStaticData(head_tracker_, &head_static_data_));

    UNWRAP_MLRESULT(MLEyeTrackingCreate(&eye_tracker_));
    UNWRAP_MLRESULT_FATAL(MLEyeTrackingGetStaticData(eye_tracker_, &eye_static_data_));

    fixation_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    left_center_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    right_center_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    left_gaze_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Line);
    right_gaze_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Line);
    left_gaze_point_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    right_gaze_point_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);

    top_left_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    top_right_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    bottom_right_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
    bottom_left_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);

    GetRoot()->AddChild(fixation_node_);
    GetRoot()->AddChild(left_center_node_);
    GetRoot()->AddChild(right_center_node_);
    GetRoot()->AddChild(left_gaze_node_);
    GetRoot()->AddChild(right_gaze_node_);
    GetRoot()->AddChild(left_gaze_point_node_);
    GetRoot()->AddChild(right_gaze_point_node_);

    GetRoot()->AddChild(top_left_node_);
    GetRoot()->AddChild(top_right_node_);
    GetRoot()->AddChild(bottom_right_node_);
    GetRoot()->AddChild(bottom_left_node_);

    fixation_node_->SetLocalScale(kCubeScale);
    left_center_node_->SetLocalScale(kEyeCenterScale);
    right_center_node_->SetLocalScale(kEyeCenterScale);
    left_gaze_point_node_->SetLocalScale(kEyeCenterScale);
    right_gaze_point_node_->SetLocalScale(kEyeCenterScale);

    top_left_node_->SetLocalScale(kEyeCenterScale);
    top_right_node_->SetLocalScale(kEyeCenterScale);
    bottom_right_node_->SetLocalScale(kEyeCenterScale);
    bottom_left_node_->SetLocalScale(kEyeCenterScale);
    
}

void GLEyeTrackingApp::OnStop()
{
  ML_LOG(Info, "OnStop()");

    UNWRAP_MLRESULT(MLHeadTrackingDestroy(head_tracker_));
    UNWRAP_MLRESULT(MLEyeTrackingDestroy(eye_tracker_));
}

void GLEyeTrackingApp::OnUpdate(float)
{
    MLSnapshot *snapshot = nullptr;
    UNWRAP_MLRESULT(MLPerceptionGetSnapshot(&snapshot));

    MLTransform T_W_R = {};
    MLTransform T_P_fixation = {};
    MLTransform T_W_fixation = {};
    MLTransform left_eye_center = {};
    MLTransform right_eye_center = {};
    MLTransform T_W_head = {};


    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &head_static_data_.coord_frame_head, &T_W_head));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.fixation, &T_P_fixation));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.left_center, &left_eye_center));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.right_center, &right_eye_center));
    UNWRAP_MLRESULT(MLPerceptionReleaseSnapshot(snapshot));

    // T_W_R.rotation = ml::app_framework::to_ml(GetRoot()->GetWorldRotation());
    // T_W_R.position = ml::app_framework::to_ml(GetRoot()->GetWorldTranslation());

    // ML_LOG(Info, "T_W_ROOT(%f, %f, %f, %f), (%f, %f, %f)", 
    //     T_W_R.rotation.w, T_W_R.rotation.x, T_W_R.rotation.y, T_W_R.rotation.z, 
    //     T_W_R.position.x, T_W_R.position.y, T_W_R.position.z);

    // ML_LOG(Info, "T_W_head(%f, %f, %f, %f), (%f, %f, %f)", 
    //     T_W_head.rotation.w, T_W_head.rotation.x, T_W_head.rotation.y, T_W_head.rotation.z, 
    //     T_W_head.position.x, T_W_head.position.y, T_W_head.position.z);

    // T_P_fixation.rotation.w = 1.0f;
    // T_P_fixation.rotation.x = 0.0f;
    // T_P_fixation.rotation.y = 0.0f;
    // T_P_fixation.rotation.z = 0.0f;
    
    // T_P_fixation.position.x = 0.167184f;
    // T_P_fixation.position.y = -0.093600f;
    // T_P_fixation.position.z = -1.244016f;

    // ML_LOG(Info, "T_P_fixation(%f, %f, %f, %f), (%f, %f, %f)", 
    //     T_P_fixation.rotation.w, T_P_fixation.rotation.x, T_P_fixation.rotation.y, T_P_fixation.rotation.z, 
    //     T_P_fixation.position.x, T_P_fixation.position.y, T_P_fixation.position.z);

    // if (FLAGS_draw_fixation_point) {
    //   fixation_node_->SetWorldRotation(ml::app_framework::to_glm(T_P_fixation.rotation));
    //   fixation_node_->SetWorldTranslation(ml::app_framework::to_glm(T_P_fixation.position));
    // }

    // T_W_fixation.rotation = ml::app_framework::to_ml(fixation_node_->GetWorldRotation());
    // T_W_fixation.position = ml::app_framework::to_ml(fixation_node_->GetWorldTranslation());

    // ML_LOG(Info, "T_W_fixation(%f, %f, %f, %f), (%f, %f, %f)", 
    //   T_W_fixation.rotation.w, T_W_fixation.rotation.x, T_W_fixation.rotation.y, T_W_fixation.rotation.z, 
    //   T_W_fixation.position.x, T_W_fixation.position.y, T_W_fixation.position.z);


    MLTransform T_W_top_left = {};
    MLTransform T_W_top_right = {};
    MLTransform T_W_bottom_right = {};
    MLTransform T_W_bottom_left = {};
    

    T_W_top_left.rotation.w = 1.0f;
    T_W_top_left.rotation.x = 0.0f;
    T_W_top_left.rotation.y = 0.0f;
    T_W_top_left.rotation.z = 0.0f;

    float x = 0.0f, y = 0.0f, z = -0.5f;

    T_W_bottom_left.position.x = x;
    T_W_bottom_left.position.y = y;
    T_W_bottom_left.position.z = z;

    T_W_bottom_right.position.x = x + 0.45f;
    T_W_bottom_right.position.y = y;
    T_W_bottom_right.position.z = z;

    T_W_top_right.position.x = x + 0.45f;
    T_W_top_right.position.y = y + 0.3f;
    T_W_top_right.position.z = z;

    T_W_top_left.position.x = x;
    T_W_top_left.position.y = y + 0.3f;
    T_W_top_left.position.z = z;

    bottom_left_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_top_left.rotation));
    bottom_left_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_bottom_left.position));

    bottom_right_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_top_left.rotation));
    bottom_right_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_bottom_right.position));

    top_right_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_top_left.rotation));
    top_right_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_top_right.position));

    top_left_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_top_left.rotation));
    top_left_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_top_left.position));

    ML_LOG(Info, "----------------------");
}

int main(int argc, char **argv) {
  GLEyeTrackingApp app(argc, argv);
  app.SetUseGfx(true);
  app.RunApp();
  return 0;
}
