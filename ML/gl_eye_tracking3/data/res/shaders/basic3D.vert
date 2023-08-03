#version 330 core

in vec3 coord3D;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 gl_Color;

uniform mat4 projFrom3D;

void main(void) {	
	gl_Position =  projFrom3D * vec4(coord3D, 1);
	gl_Color = aColor;
}
