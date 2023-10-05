#include "render/RBCubeDynamic.h"
#include "render/RBShader.h"


#define BOTTOM_RADIUS 0.5
#define TOP_RADIUS 0.5

RBCube::RBCube() {
  _position = glm::vec3(0);
  _rotation = glm::vec3(0);
  _scale = glm::vec3(0.25);
}

RBCube::~RBCube() {
  glDeleteVertexArrays(1, &_vaoId);
}

void RBCube::ApplyShader(Shader& shader) {
  _progId = shader.GetProgramID();
  glUseProgram(_progId);

  _colorId = glGetUniformLocation(_progId, "color");
  _projId = glGetUniformLocation(_progId, "projFrom3D");
  GLuint location = glGetAttribLocation(_progId, "coord3D");

  const int dimention = 3;
  int _verts = sizeof(_vertices) / sizeof(_vertices[0]);
  const int sides_n = _verts / dimention;

  _indices_n = sizeof(_indices) / sizeof(_indices[0]);
  // unsigned int VBO;
  // 1. bind Vertex Array Object
  glGenVertexArrays(1, &_vaoId);
  glBindVertexArray(_vaoId);


  glGenBuffers(1, &_vboId);

  // 2. copy our vertices array in a vertex buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, _vboId);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), nullptr, GL_DYNAMIC_DRAW);

  // 3. copy our index array in a element buffer for OpenGL to use
  unsigned int stride = sizeof(float) * dimention; 
  // glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
  glVertexAttribPointer(0, dimention, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);


  glGenBuffers(1, &_iboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_DYNAMIC_DRAW);

  
  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0); 

  glBindVertexArray(0);
  glUseProgram(0);

  ML_LOG_TAG(Debug, APP_TAG, "Uniform location (%d, %d, %d), program %d", _colorId, _projId, location, _progId);
}

void RBCube::Render(glm::mat4 projectionMatrix) {
  glBindBuffer(GL_ARRAY_BUFFER, _vboId);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_vertices), _vertices);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(_indices), _indices);

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




  // glUseProgram(_progId);

  // glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
  // glm::mat4 scale = glm::scale(_scale);
  // glm::mat4 transform = projectionMatrix * translate * scale;

  // glBindVertexArray(_vaoId);
  // glUniformMatrix4fv(_projId, 1, GL_FALSE, &transform[0][0]);
  // glDrawArrays(GL_POINTS, 0, _verts);
  // glBindVertexArray(0);

  // glUseProgram(0);
}


void RBCube::Dump() {
  ML_LOG_TAG(Debug, APP_TAG, "---------------- Dump of RBCube ----------------");
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