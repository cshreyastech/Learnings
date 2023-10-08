#ifndef RBDYNAMICPOINT_H
#define RBDYNAMICPOINT_H

#include "core/platform_includes.h"
#include "core/glm_include.h"
#include "common/ros_ml_common.h"

class Shader;

class RBPoint {
public:
  RBPoint();
	~RBPoint();

public:
	void SetPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); }
	glm::vec3 GetPosition() { return _position; }
	void SetRotation(float x, float y, float z) { _rotation = glm::vec3(x, y, z); }
	glm::vec3 GetRotation() { return _rotation; }
	void SetScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); }
	glm::vec3 GetScale() { return _scale; }
	void SetColor(glm::vec3 color) { _color = color; }
	glm::vec3 GetColor() { return _color; }

  void SetShader(Shader& shader);
	
  void Render(glm::mat4 projectionMatrix, const Point point_cloud[]);

private:
	GLuint _progId;
	GLuint _vaoId;
	GLuint _projId;
	GLuint _colorId;
	glm::vec3 _color;
  GLuint _vbo;
	int _steps = 0;
	// int _verts = 0;

	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
  GLuint _location;

  // int n_points_{0};
  int vertices_size_{0};

	// Part 3: Added to support laserpointer
	glm::mat4 _transform;
};

#endif