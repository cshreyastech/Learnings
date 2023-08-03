#include "RBPoint.h"
#include "RBShader.h"

#include <iostream>
#define GLM_FORCE_RADIANS
#include "../glm/gtc/matrix_transform.hpp"

const char APP_TAG[] = "C-ENGINE-CYL";
#include <ml_logging.h>

#define BOTTOM_RADIUS 0.5
#define TOP_RADIUS 0.5

Point::Point() {

	_position = glm::vec3(0);
	_rotation = glm::vec3(0);
	_scale = glm::vec3(0.25);
}

Point::~Point() {
}

void Point::ApplyShader(Shader& shader, float vertex[], const int n_points, const int vertex_size) {
	_progId = shader.GetProgramID();
	glUseProgram(_progId);

	_projId = glGetUniformLocation(_progId, "projFrom3D");
	GLuint location = glGetAttribLocation(_progId, "coord3D");

	

	// GLfloat pointVertexData[_verts * 3];
	// MakePoint(pointVertexData, _steps);

	// _verts = 3;
  // float pointVertexData[] = {
  //   // positions         // colors
  //    0.5f, -0.5f, -0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
  //   -0.5f, -0.5f, -0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
  //    0.0f,  0.5f, -0.0f,  0.0f, 0.0f, 1.0f    // top 
  // };

	// _verts = 307200;
	_verts = n_points;
 
  // float pointVertexData[] = {
  //   // positions         // colors

  // };



	GLuint vbo;
	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(_vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertexData), pointVertexData, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_size), vertex, GL_STATIC_DRAW);

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(location);

  // The color attribute starts after the position data so the offset is 3 * sizeof(float) 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(_vaoId);

	glBindVertexArray(0);
	glUseProgram(0);

	ML_LOG_TAG(Debug, APP_TAG, "Uniform location (%d, %d, %d), program %d", _colorId, _projId, location, _progId);
}

void Point::Render(glm::mat4 projectionMatrix) {
	glUseProgram(_progId);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 scale = glm::scale(_scale);
	glm::mat4 transform = projectionMatrix * translate * scale;

	glBindVertexArray(_vaoId);
	glUniformMatrix4fv(_projId, 1, GL_FALSE, &transform[0][0]);
	// glUniform3f(_colorId, _color[0], _color[1], _color[2]);
	// GLfloat size = 5.0f;
	// glPointSize(5); 
	
	// glDrawArrays(GL_POINTS, 0, _verts);
	glDrawArrays(GL_POINTS, 0, _verts);
	glBindVertexArray(0);

	glUseProgram(0);
}

void Point::Dump() {
	ML_LOG_TAG(Debug, APP_TAG, "---------------- Dump of Point ----------------");
	ML_LOG_TAG(Debug, APP_TAG, "Prog ID:  %d", _progId);
	ML_LOG_TAG(Debug, APP_TAG, "VAO ID:   %d", _vaoId);
	ML_LOG_TAG(Debug, APP_TAG, "Proj ID:  %d", _projId);
	ML_LOG_TAG(Debug, APP_TAG, "Color ID: %d", _colorId);
	ML_LOG_TAG(Debug, APP_TAG, "Steps:    %d",    _steps);
	ML_LOG_TAG(Debug, APP_TAG, "Verts:    %d",    _verts);
	ML_LOG_TAG(Debug, APP_TAG, "Color:    %f,%f,%f", _color[0], _color[1], _color[2]);
	ML_LOG_TAG(Debug, APP_TAG, "Position: %f,%f,%f", _position.x, _position.y, _position.z);
	ML_LOG_TAG(Debug, APP_TAG, "Rotation: %f,%f,%f", _rotation.x, _rotation.y, _rotation.z);
	ML_LOG_TAG(Debug, APP_TAG, "Scale:    %f,%f,%f", _scale.x, _scale.y, _scale.z);
	ML_LOG_TAG(Debug, APP_TAG, "--------------------------------------------------");
}