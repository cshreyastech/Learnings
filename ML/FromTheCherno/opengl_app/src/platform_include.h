#pragma once

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define GLM_ENABLE_EXPERIMENTAL 1
#include "glm/gtx/quaternion.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/transform.hpp" 
#include "glm/gtc/matrix_transform.hpp"

#ifndef EGL_EGLEXT_PROTOTYPES
	#define EGL_EGLEXT_PROTOTYPES
#endif

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cmath>

#include <ml_logging.h>
#include <ml_graphics.h>
#include <ml_lifecycle.h>
#include <ml_perception.h>
#include <ml_head_tracking.h>
#include <ml_input.h>
#include <fstream>
#include <string>
#include <sstream>

const char APP_TAG[] = "MAIN";