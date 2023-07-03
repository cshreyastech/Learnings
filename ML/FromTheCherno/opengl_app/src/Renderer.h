#pragma once

#include "platform_include.h"

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
