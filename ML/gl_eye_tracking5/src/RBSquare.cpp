#include "RBSquare.h"
#include "RBShader.h"

#include <iostream>

#define GLM_FORCE_RADIANS
#include "../glm/gtc/matrix_transform.hpp"

const char APP_TAG[] = "C-ENGINE-CYL";
#include <ml_logging.h>

#define BOTTOM_RADIUS 0.5
#define TOP_RADIUS 0.5

Square::Square(int steps) {
	// _steps = steps;
	// _verts = (_steps + 1) * 2; 

	_position = glm::vec3(0);
	_rotation = glm::vec3(0);
	_scale = glm::vec3(0.25);
}

Square::~Square() {
}

void Square::ApplyShader(Shader& shader) {
	_progId = shader.GetProgramID();
	glUseProgram(_progId);

	_colorId = glGetUniformLocation(_progId, "color");
	_projId = glGetUniformLocation(_progId, "projFrom3D");
	GLuint location = glGetAttribLocation(_progId, "coord3D");


  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  }; 


  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };

  const int dimention = 3;
  int _verts = sizeof(vertices) / sizeof(vertices[0]);
  const int sides_n = _verts / dimention;

  _indices_n = sizeof(indices) / sizeof(indices[0]);
  unsigned int VBO;
  // 1. bind Vertex Array Object
  glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);


  glGenBuffers(1, &VBO);

  // 2. copy our vertices array in a vertex buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 3. copy our index array in a element buffer for OpenGL to use
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  unsigned int stride = sizeof(float) * dimention; 
  // std::cout << "stride: " << stride << std::endl;

  // layout (location = 0)
  glVertexAttribPointer(0, dimention, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glUseProgram(0);

	ML_LOG_TAG(Debug, APP_TAG, "Uniform location (%d, %d, %d), program %d", _colorId, _projId, location, _progId);
}

void Square::Render(glm::mat4 projectionMatrix) {
	glUseProgram(_progId);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 scale = glm::scale(_scale);
	glm::mat4 transform = projectionMatrix * translate * scale;

  glBindVertexArray(_vaoId);
  glUniformMatrix4fv(_projId, 1, GL_FALSE, &transform[0][0]);
	glUniform3f(_colorId, _color[0], _color[1], _color[2]);
  glDrawElements(GL_TRIANGLES, _indices_n, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

	glUseProgram(0);
}

void Square::Dump() {
	ML_LOG_TAG(Debug, APP_TAG, "---------------- Dump of Square ----------------");
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