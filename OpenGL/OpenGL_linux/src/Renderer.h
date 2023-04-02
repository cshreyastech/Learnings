// #pragma once
#include <GL/glew.h>
#include <signal.h>

#define ASSERT(x) if(!(x)) RaiseDebugError();
#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void RaiseDebugError();
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);