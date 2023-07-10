#pragma once
// #include "glad/glad.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define GLM_ENABLE_EXPERIMENTAL 1
#include "../glm/gtx/quaternion.hpp"

#include "../glm/glm.hpp"
#include "../glm/ext.hpp"
#include "../glm/gtx/vector_angle.hpp"
#include "../glm/gtx/transform.hpp" 
#include "../glm/gtc/matrix_transform.hpp"

#ifndef EGL_EGLEXT_PROTOTYPES
	#define EGL_EGLEXT_PROTOTYPES
#endif

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#define ASIO_STANDLONE

#include <vector>