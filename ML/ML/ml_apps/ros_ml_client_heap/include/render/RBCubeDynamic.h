#ifndef RBCUBE_H
#define RBCUBE_H

#include "core/platform_includes.h"
#include "core/glm_include.h"

class Shader;

class RBCube {
public:
  RBCube();
  ~RBCube();

public:
  void SetPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); }
  glm::vec3 GetPosition() { return _position; }
  void SetRotation(float x, float y, float z) { _rotation = glm::vec3(x, y, z); }
  glm::vec3 GetRotation() { return _rotation; }
  void SetScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); }
  glm::vec3 GetScale() { return _scale; }
  void SetColor(glm::vec3 color) { _color = color; }
  glm::vec3 GetColor() { return _color; }

  void ApplyShader(Shader& shader);
  void Render(glm::mat4 projectionMatrix);

  void Dump();
private:
  GLuint _progId;
  GLuint _vaoId;
  unsigned int _vboId;
  unsigned int _iboId;

  // const int a = 0.02;
  float _vertices[24] = {
     0.02,  0.02, -0.02,
     0.02,  0.02,  0.02,
    -0.02,  0.02,  0.02,
    -0.02,  0.02, -0.02,

     0.02, -0.02,  0.02,
    -0.02, -0.02,  0.02,
     0.02, -0.02, -0.02,

    -0.02, -0.02, -0.02
  };

  unsigned int _indices[36] = {  // note that we start from 0!
  // X clockwise
  0, 1, 3, 1, 2, 2,
  6, 0, 7, 0, 3, 7,
  4, 6, 5, 6, 7, 5,
  1, 4, 2, 4, 5, 2,
  
  // Y clockwise
  0, 6, 1, 6, 4, 1,
  2, 5, 3, 5, 7, 3
  };

  GLuint _projId;
  GLuint _colorId;
  glm::vec3 _color;
  int _steps = 0;
  int _verts = 0;

  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;

  // Part 3: Added to support laserpointer
  glm::mat4 _transform;

  int _indices_n;
};
#endif