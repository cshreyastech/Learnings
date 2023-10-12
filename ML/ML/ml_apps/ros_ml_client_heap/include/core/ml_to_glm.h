#ifndef ML_TO_GLM_H
#define ML_TO_GLM_H

#include "core/glm_include.h"
#include <ml_graphics.h>
// -----------------------------------------------------------------------------
// Part 2: glm helper functions

glm::mat4 rb_convert_ml_to_glm(const MLTransform &ml) {
  glm::quat q;
  q.w = ml.rotation.w;
  q.x = ml.rotation.x;
  q.y = ml.rotation.y;
  q.z = ml.rotation.z;

  return glm::translate(glm::mat4(), glm::vec3(ml.position.x, ml.position.y, ml.position.z)) * glm::toMat4(q);
}

glm::mat4 rb_projection_matrix(MLGraphicsVirtualCameraInfo &camera) {
  return (glm::make_mat4(camera.projection.matrix_colmajor));
}

glm::mat4 rb_camera_matrix(MLGraphicsVirtualCameraInfo &camera) {
  glm::mat4 proj = glm::make_mat4(camera.projection.matrix_colmajor);
  glm::vec3 trans = glm::make_vec3(camera.transform.position.values);
  glm::mat4 rotMat = glm::mat4_cast(glm::make_quat(camera.transform.rotation.values));
  glm::mat4 transMat = glm::translate(glm::mat4(1.0f), trans);
  glm::mat4 worldFromCamera = transMat * rotMat;

  return (glm::inverse(worldFromCamera));
}

static glm::quat quat_ml_to_glm(const MLTransform &ml) {
  glm::quat q;

  q.w = ml.rotation.w;
  q.x = ml.rotation.x;
  q.y = ml.rotation.y;
  q.z = ml.rotation.z;

  return q;
}

static glm::vec3 vec_ml_to_glm(const MLTransform &ml) {
  glm::vec3 v;
  v.x = ml.position.x;
  v.y = ml.position.y;
  v.z = ml.position.z;

  return v;
}

#endif