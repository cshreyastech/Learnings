#ifndef STRUCT_DECLARATIONS_HPP
#define STRUCT_DECLARATIONS_HPP

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

struct T_W_EYE
{
  glm::quat Q_W_EYE;
  glm::vec3 P_W_EYE;
};

#endif