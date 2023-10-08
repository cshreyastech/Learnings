#include "render/RBPointDynamic.h"
#include "render/RBShader.h"

#define BOTTOM_RADIUS 0.5
#define TOP_RADIUS 0.5


RBPoint::RBPoint()
{
}

void RBPoint::SetShader(Shader& shader)
{
  vertices_size_ = N_POINTS * 6 * sizeof(float);

  _position = glm::vec3(0);
  _rotation = glm::vec3(0);
  _scale = glm::vec3(0.25);

  _progId = shader.GetProgramID();
  glUseProgram(_progId);

  _projId = glGetUniformLocation(_progId, "projFrom3D");
  GLuint _location = glGetAttribLocation(_progId, "coord3D");

  glGenVertexArrays(1, &_vaoId);
  glGenBuffers(1, &_vbo);
  
  glBindVertexArray(_vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices_size_, nullptr, GL_DYNAMIC_DRAW);


  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (const void*)offsetof(Point, Position));
  glEnableVertexAttribArray(_location);

  // Color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (const void*)offsetof(Point, Color));
  glEnableVertexAttribArray(1);


  glBindVertexArray(_vaoId);

  glBindVertexArray(0);
  glUseProgram(0);

  ML_LOG_TAG(Debug, APP_TAG, "Uniform location (%d, %d, %d), program %d", _colorId, _projId, _location, _progId);
}

RBPoint::~RBPoint() {
}

void RBPoint::Render(glm::mat4 projectionMatrix, const Point point_cloud[]) {
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size_, point_cloud);

	glUseProgram(_progId);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 scale = glm::scale(_scale);
	glm::mat4 transform = projectionMatrix * translate * scale;

	glBindVertexArray(_vaoId);
	glUniformMatrix4fv(_projId, 1, GL_FALSE, &transform[0][0]);
  glDrawArrays(GL_POINTS, 0, N_POINTS);
	glBindVertexArray(0);

	glUseProgram(0);
}