#include "Renderer.h"
// #include <iostream>

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
  while (GLenum error = glGetError())
  {
    ML_LOG_TAG(Error, APP_TAG, "[OpenGL_Error] ( %d ) %s %s:%d", 
      error, function, file, line);
    return false;
  }
  return true;
}