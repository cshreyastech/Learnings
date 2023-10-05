#include "render/RBPointDynamic.h"
#include "render/RBShader.h"

#define BOTTOM_RADIUS 0.5
#define TOP_RADIUS 0.5


RBPoint::RBPoint()
// RBPoint::RBPoint(Shader& shader, const int n_points)
//   : _verts(n_points), vertices_size_(n_points * 6 * sizeof(float))
{



}

void RBPoint::SetShader(Shader& shader, const int n_points)
{
  // n_points is defined in common.h so this need not be passed over network
  n_points_ = n_points;

  vertices_size_ = n_points_ * 6 * sizeof(float);

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

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(_location);

  // The color attribute starts after the position data so the offset is 3 * sizeof(float) 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(_vaoId);

  glBindVertexArray(0);
  glUseProgram(0);

  ML_LOG_TAG(Debug, APP_TAG, "Uniform location (%d, %d, %d), program %d", _colorId, _projId, _location, _progId);
}

RBPoint::~RBPoint() {
}

// void RBPoint::Render(glm::mat4 projectionMatrix, float vertices[]) {
void RBPoint::Render(glm::mat4 projectionMatrix, PointCloud &point_cloud) {
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  // glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, vertices);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size_, point_cloud.points);

	glUseProgram(_progId);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 scale = glm::scale(_scale);
	glm::mat4 transform = projectionMatrix * translate * scale;

	glBindVertexArray(_vaoId);
	glUniformMatrix4fv(_projId, 1, GL_FALSE, &transform[0][0]);
	// glDrawArrays(GL_POINTS, 0, _verts);
  glDrawArrays(GL_POINTS, 0, n_points_);
	glBindVertexArray(0);

	glUseProgram(0);
}

// void RBPoint::Dump() {
// 	ML_LOG_TAG(Debug, APP_TAG, "---------------- Dump of Point ----------------");
// 	ML_LOG_TAG(Debug, APP_TAG, "Prog ID:  %d", _progId);
// 	ML_LOG_TAG(Debug, APP_TAG, "VAO ID:   %d", _vaoId);
// 	ML_LOG_TAG(Debug, APP_TAG, "Proj ID:  %d", _projId);
// 	ML_LOG_TAG(Debug, APP_TAG, "Color ID: %d", _colorId);
// 	ML_LOG_TAG(Debug, APP_TAG, "Steps:    %d",    _steps);
// 	ML_LOG_TAG(Debug, APP_TAG, "Verts:    %d",    _verts);
// 	ML_LOG_TAG(Debug, APP_TAG, "Color:    %f,%f,%f", _color[0], _color[1], _color[2]);
// 	ML_LOG_TAG(Debug, APP_TAG, "Position: %f,%f,%f", _position.x, _position.y, _position.z);
// 	ML_LOG_TAG(Debug, APP_TAG, "Rotation: %f,%f,%f", _rotation.x, _rotation.y, _rotation.z);
// 	ML_LOG_TAG(Debug, APP_TAG, "Scale:    %f,%f,%f", _scale.x, _scale.y, _scale.z);
// 	ML_LOG_TAG(Debug, APP_TAG, "--------------------------------------------------");
// }