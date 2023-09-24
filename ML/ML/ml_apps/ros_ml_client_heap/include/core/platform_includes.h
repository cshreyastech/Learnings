#ifndef PLATFORM_INCLUDES_H
#define PLATFORM_INCLUDES_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#ifndef EGL_EGLEXT_PROTOTYPES
	#define EGL_EGLEXT_PROTOTYPES
#endif

#include <vector>
#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>
#include <streambuf>
#include <sstream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <fstream>
#include <map>
#include <functional>
#include <algorithm>
#include <array>
#include <cstring>
// #include "glad/glad.h"
// #include <GLFW/glfw3.h>
#include <memory>
#include <cassert>
#include <signal.h>

#include <ml_logging.h>

const char APP_TAG[] = "MAIN";

#include <ml_graphics.h>
#include <ml_lifecycle.h>
#include <ml_perception.h>
#include <ml_head_tracking.h>
#include <ml_input.h>
#include <ml_eye_tracking.h>



#endif