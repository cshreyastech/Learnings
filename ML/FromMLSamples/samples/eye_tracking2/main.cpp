// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2018 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Creator Agreement, located
// here: https://id.magicleap.com/creator-terms
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%
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

DEFINE_bool(draw_fixation_point, true, "Draw the fixation point.");
DEFINE_bool(draw_eye_centers, true, "Draw the eye centers.");
DEFINE_bool(draw_gaze_left, true, "Draw left gaze vector.");
DEFINE_bool(draw_gaze_right, true, "Draw right gaze vector.");
DEFINE_bool(eye_centers_origin, false,
            "If true, eye centers are drawn relative to the origin; otherwise, the world space position is used.");

const glm::vec3 kCubeScale = glm::vec3(0.01f, 0.01f, 0.01f);
const glm::vec3 kEyeCenterScale = glm::vec3(0.02f, 0.02f, 0.02f);

class EyeTrackingApp : public ml::app_framework::Application {
public:
  EyeTrackingApp(int argc = 0, char **argv = nullptr) : ml::app_framework::Application(argc, argv) {}

  void OnStart() override {
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
    reference_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);

    GetRoot()->SetName("RootNode");
    fixation_node_->SetName("fixation_node");
    left_center_node_->SetName("left_center_node");
    reference_node_->SetName("reference_node");

    GetRoot()->AddChild(fixation_node_);
    GetRoot()->AddChild(left_center_node_);
    GetRoot()->AddChild(right_center_node_);
    GetRoot()->AddChild(left_gaze_node_);
    GetRoot()->AddChild(right_gaze_node_);
    GetRoot()->AddChild(left_gaze_point_node_);
    GetRoot()->AddChild(right_gaze_point_node_);
    GetRoot()->AddChild(reference_node_);

    fixation_node_->SetLocalScale(kCubeScale);
    left_center_node_->SetLocalScale(kEyeCenterScale);
    right_center_node_->SetLocalScale(kEyeCenterScale);
    left_gaze_point_node_->SetLocalScale(kEyeCenterScale);
    right_gaze_point_node_->SetLocalScale(kEyeCenterScale);
    reference_node_->SetLocalScale(kEyeCenterScale);

    // ML_LOG(Info, "T_W_fixationOrigin(%f, %f, %f, %f), (%f, %f, %f)", 
    //   Q_W_fixationOrigin.w, Q_W_fixationOrigin.x, Q_W_fixationOrigin.y, Q_W_fixationOrigin.z, 
    //   P_W_fixationOrigin.x, P_W_fixationOrigin.y, P_W_fixationOrigin.z);

    // const glm::mat4 T_W_fixationOrigin = ToTransformation(Q_W_fixationOrigin, P_W_fixationOrigin);

    // ML_LOG(Info, 
    //   "T_W_fixationOrigin(%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f)",
    //  T_W_fixationOrigin[0][0], T_W_fixationOrigin[0][1], T_W_fixationOrigin[0][2], T_W_fixationOrigin[0][3],
    //  T_W_fixationOrigin[1][0], T_W_fixationOrigin[1][1], T_W_fixationOrigin[1][2], T_W_fixationOrigin[1][3],
    //  T_W_fixationOrigin[2][0], T_W_fixationOrigin[2][1], T_W_fixationOrigin[2][2], T_W_fixationOrigin[2][3],
    //  T_W_fixationOrigin[3][0], T_W_fixationOrigin[3][1], T_W_fixationOrigin[3][2], T_W_fixationOrigin[3][3]);

    // glm::quat Q_W_fixationOrigin2;
    // glm::vec3 P_W_fixationOrigin2;
    // FromTransformation(T_W_fixationOrigin, Q_W_fixationOrigin2, P_W_fixationOrigin2);

    // ML_LOG(Info, "T_W_fixationOrigin2(%f, %f, %f, %f), (%f, %f, %f)", 
    //     Q_W_fixationOrigin2.w, Q_W_fixationOrigin2.x, Q_W_fixationOrigin2.y, Q_W_fixationOrigin2.z, 
    //     P_W_fixationOrigin2.x, P_W_fixationOrigin2.y, P_W_fixationOrigin2.z);

    // T_fixationOrigin_W_ = glm::inverse(T_W_fixationOrigin);

    // ML_LOG(Info, 
    //   "T_fixationOrigin_W_(%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f)",
    //  T_fixationOrigin_W_[0][0], T_fixationOrigin_W_[0][1], T_fixationOrigin_W_[0][2], T_fixationOrigin_W_[0][3],
    //  T_fixationOrigin_W_[1][0], T_fixationOrigin_W_[1][1], T_fixationOrigin_W_[1][2], T_fixationOrigin_W_[1][3],
    //  T_fixationOrigin_W_[2][0], T_fixationOrigin_W_[2][1], T_fixationOrigin_W_[2][2], T_fixationOrigin_W_[2][3],
    //  T_fixationOrigin_W_[3][0], T_fixationOrigin_W_[3][1], T_fixationOrigin_W_[3][2], T_fixationOrigin_W_[3][3]);
  }

  void OnStop() override {
    UNWRAP_MLRESULT(MLHeadTrackingDestroy(head_tracker_));
    UNWRAP_MLRESULT(MLEyeTrackingDestroy(eye_tracker_));
  }

  void OnUpdate(float) override {
    MLSnapshot *snapshot = nullptr;
    UNWRAP_MLRESULT(MLPerceptionGetSnapshot(&snapshot));

    MLTransform T_W_Root = {};
    MLTransform T_W_fixation = {};
    MLTransform T_W_left_eye_center = {};
    MLTransform T_W_right_eye_center = {};
    MLTransform T_W_head = {};
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &head_static_data_.coord_frame_head, &T_W_head));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.fixation, &T_W_fixation));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.left_center, &T_W_left_eye_center));
    UNWRAP_MLRESULT(MLSnapshotGetTransform(snapshot, &eye_static_data_.right_center, &T_W_right_eye_center));
    UNWRAP_MLRESULT(MLPerceptionReleaseSnapshot(snapshot));

    const glm::quat Q_W_fixation = ml::app_framework::to_glm(T_W_fixation.rotation);
    const glm::vec3 P_W_fixation = ml::app_framework::to_glm(T_W_fixation.position);


    // const glm::mat4 T_W_fixation_glm = ToTransformation(Q_W_fixation, P_W_fixation);

    // const glm::mat4 T_fixationOrigin_fixation = T_fixationOrigin_W_ * T_W_fixation_glm;
    // glm::quat Q_fixationOrigin_fixation;
    // glm::vec3 P_fixationOrigin_fixation;
    // FromTransformation(T_fixationOrigin_fixation, Q_fixationOrigin_fixation, P_fixationOrigin_fixation);

    const glm::vec3 target = glm::vec3(0.0f, 0.0f, -0.5f);
    reference_node_->SetWorldRotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
    reference_node_->SetWorldTranslation(target);
    if (FLAGS_draw_fixation_point) {
      fixation_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_fixation.rotation));
      fixation_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_fixation.position));
    }



    // MLTransform T_P_fixation = {};
    // T_P_fixation.rotation = ml::app_framework::to_ml(fixation_node_->GetLocalRotation());
    // T_P_fixation.position = ml::app_framework::to_ml(fixation_node_->GetLocalTranslation());

    // ML_LOG(Info, "T_P_fixation(%f, %f, %f, %f), (%f, %f, %f)", 
    //   T_P_fixation.rotation.w, T_P_fixation.rotation.x, T_P_fixation.rotation.y, T_P_fixation.rotation.z, 
    //   T_P_fixation.position.x, T_P_fixation.position.y, T_P_fixation.position.z);

    // if (FLAGS_eye_centers_origin) {
    //   //
    //   // This case draws the eye centers relative to the
    //   // origin. When running on device this would allow you to move
    //   // back from the origin and see the eye centers versus them
    //   // being within your head and not able to see them.
    //   //
    //   left_center_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_left_eye_center.rotation));
    //   left_center_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_left_eye_center.position) 
    //     - ml::app_framework::to_glm(T_W_head.position));
    //   right_center_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_right_eye_center.rotation));
    //   right_center_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_right_eye_center.position) 
    //     - ml::app_framework::to_glm(T_W_head.position));


    // } else {
    //   //
    //   // This case is more useful on MLRemote where you could change
    //   // the world space position of the eye centers independently
    //   // of the headpose.  This would also be useful on device if
    //   // you wanted to log these positions to make sure that the eye
    //   // center values are correct.
    //   //
    //   left_center_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_left_eye_center.rotation));
    //   left_center_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_left_eye_center.position));
    //   right_center_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_right_eye_center.rotation));
    //   right_center_node_->SetWorldTranslation(ml::app_framework::to_glm(T_W_right_eye_center.position));
    // }

    // if (FLAGS_draw_gaze_left) {
    //   auto left_origin = ml::app_framework::to_glm(T_W_left_eye_center.position);
    //   auto left_direction = ml::app_framework::to_glm(T_W_left_eye_center.rotation) * glm::vec3(0, 0, -1);
    //   glm::vec3 left_gaze_line[] = {
    //     left_origin,
    //     left_origin + left_direction
    //   };
    //   auto left_line_renderable = left_gaze_node_->GetComponent<ml::app_framework::RenderableComponent>();
    //   left_line_renderable->GetMesh()->SetPrimitiveType(GL_LINES);
    //   left_line_renderable->GetMesh()->UpdateMesh(left_gaze_line, nullptr, sizeof(left_gaze_line)/sizeof(glm::vec3), nullptr, 0);
    //   auto left_line_material = std::static_pointer_cast<ml::app_framework::FlatMaterial>(left_line_renderable->GetMaterial());
    //   left_line_material->SetColor(glm::vec4(.0f, .0f, 1.0f, 1.0f));

    //   left_gaze_point_node_->SetWorldTranslation(left_origin + left_direction);
    //   left_gaze_point_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_left_eye_center.rotation));
    // }

    // if (FLAGS_draw_gaze_right) {
    //   auto right_origin = ml::app_framework::to_glm(T_W_right_eye_center.position);
    //   auto right_direction = ml::app_framework::to_glm(T_W_right_eye_center.rotation) * glm::vec3(0, 0, -1);
    //   glm::vec3 right_gaze_line[] = {
    //     right_origin,
    //     right_origin + right_direction
    //   };
    //   auto right_line_renderable = right_gaze_node_->GetComponent<ml::app_framework::RenderableComponent>();
    //   right_line_renderable->GetMesh()->SetPrimitiveType(GL_LINES);
    //   right_line_renderable->GetMesh()->UpdateMesh(right_gaze_line, nullptr, sizeof(right_gaze_line)/sizeof(glm::vec3), nullptr, 0);
    //   auto right_line_material = std::static_pointer_cast<ml::app_framework::FlatMaterial>(right_line_renderable->GetMaterial());
    //   right_line_material->SetColor(glm::vec4(.0f, .0f, 1.0f, 1.0f));

    //   right_gaze_point_node_->SetWorldTranslation(right_origin + right_direction);
    //   right_gaze_point_node_->SetWorldRotation(ml::app_framework::to_glm(T_W_right_eye_center.rotation));
    // }

    const glm::quat Q_W_head = ml::app_framework::to_glm(T_W_head.rotation);
    const glm::vec3 P_W_head = ml::app_framework::to_glm(T_W_head.position);
    // ML_LOG(Info, "T_W_head(%f, %f, %f, %f), (%f, %f, %f)", 
    //   Q_W_head.w, Q_W_head.x, Q_W_head.y, Q_W_head.z, 
    //   P_W_head.x, P_W_head.y, P_W_head.z);

    // ML_LOG(Info, "T_W_fixation(%f, %f, %f, %f), (%f, %f, %f)", 
    //   Q_W_fixation.w, Q_W_fixation.x, Q_W_fixation.y, Q_W_fixation.z, 
    //   P_W_fixation.x, P_W_fixation.y, P_W_fixation.z);

    ML_LOG(Info, "P_W_head(%f, %f, %f)", 
      P_W_head.x, P_W_head.y, P_W_head.z);

    ML_LOG(Info, "P_W_fixation(%f, %f, %f)", 
      P_W_fixation.x, P_W_fixation.y, P_W_fixation.z);


    const glm::vec3 P_head_fixation = P_W_head - P_W_fixation;
    ML_LOG(Info, "P_head_fixation(%f, %f, %f)", 
      P_head_fixation.x, P_head_fixation.y, P_head_fixation.z);

    // ML_LOG(Info, 
    //   "T_fixationOrigin_fixation(%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f)",
    //  T_fixationOrigin_fixation[0][0], T_fixationOrigin_fixation[0][1], T_fixationOrigin_fixation[0][2], T_fixationOrigin_fixation[0][3],
    //  T_fixationOrigin_fixation[1][0], T_fixationOrigin_fixation[1][1], T_fixationOrigin_fixation[1][2], T_fixationOrigin_fixation[1][3],
    //  T_fixationOrigin_fixation[2][0], T_fixationOrigin_fixation[2][1], T_fixationOrigin_fixation[2][2], T_fixationOrigin_fixation[2][3],
    //  T_fixationOrigin_fixation[3][0], T_fixationOrigin_fixation[3][1], T_fixationOrigin_fixation[3][2], T_fixationOrigin_fixation[3][3]);

    // ML_LOG(Info, "T_fixationOrigin_fixation(%f, %f, %f, %f), (%f, %f, %f)", 
    //     Q_fixationOrigin_fixation.w, Q_fixationOrigin_fixation.x, Q_fixationOrigin_fixation.y, Q_fixationOrigin_fixation.z, 
    //     P_fixationOrigin_fixation.x, P_fixationOrigin_fixation.y, P_fixationOrigin_fixation.z);


    // ML_LOG(Info, "P_fixationOrigin_fixation(%f, %f, %f)", 
    //   P_fixationOrigin_fixation.x, P_fixationOrigin_fixation.y, P_fixationOrigin_fixation.z);


    ML_LOG(Info, "----------------------");
    float error = 0.01;
    float lower_bound = target.z - error;
    float upper_bound = target.z + error;
    ML_LOG(Info, "lower_bound: %f, upper_bound: %f", lower_bound, upper_bound);

    if((P_W_fixation.z >= lower_bound) && (P_W_fixation.z <= upper_bound))
    {
      ML_LOG(Info, "Calling exit");     
      exit(0);
    }
  }

  glm::mat4 ToTransformation(const glm::quat &Q, const glm::vec3 &P)
  {
    glm::mat4 R = glm::toMat4(Q);
    const glm::mat4 P_temp = glm::translate(glm::mat4(1.0f), P);
    const glm::mat4 T = P_temp * R;

    return T;
  }

  void FromTransformation(const glm::mat4 &T, glm::quat &Q, glm::vec3 &P)
  {
    Q = glm::toQuat(T);
    P = T[3];
  }

// const glm::quat Q_W_fixationOrigin2 = glm::toQuat(T_W_fixationOrigin);
//     const glm::vec3 P_W_fixationOrigin2 = T_W_fixationOrigin[3];
private:
  std::shared_ptr<ml::app_framework::Node> fixation_node_;
  std::shared_ptr<ml::app_framework::Node> left_center_node_;
  std::shared_ptr<ml::app_framework::Node> right_center_node_;
  std::shared_ptr<ml::app_framework::Node> left_gaze_node_;
  std::shared_ptr<ml::app_framework::Node> right_gaze_node_;
  std::shared_ptr<ml::app_framework::Node> left_gaze_point_node_;
  std::shared_ptr<ml::app_framework::Node> right_gaze_point_node_;
  std::shared_ptr<ml::app_framework::Node> reference_node_;


  MLHandle head_tracker_ = ML_INVALID_HANDLE;
  MLHeadTrackingStaticData head_static_data_ = {};
  MLHandle eye_tracker_ = ML_INVALID_HANDLE;
  MLEyeTrackingStaticData eye_static_data_ = {};

  // Fix Origin
  const glm::quat Q_W_fixationOrigin = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
  const glm::vec3 P_W_fixationOrigin = glm::vec3(0.0f, 2.0f, -1.5f);
  glm::mat4 T_fixationOrigin_W_;
};

int main(int argc, char **argv) {
  EyeTrackingApp app(argc, argv);
  app.RunApp();
  return 0;
}
