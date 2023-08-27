// #ifndef _RENDERER_
// #define _RENDERER_

#include <GL/glew.h>
#include <signal.h>
// #include "vendor/glad/glad.h"

#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
