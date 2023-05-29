#ifndef STRUCT_DECLARATIONS_HPP
#define STRUCT_DECLARATIONS_HPP

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

struct Transformation
{
  int i;
  float f;
  glm::vec4 t;
};


struct Transformation1
{
  int i;
};

struct Transformation3
{
  glm::quat q_w_eye;
  glm::vec3 p_w_eye;
};

#endif