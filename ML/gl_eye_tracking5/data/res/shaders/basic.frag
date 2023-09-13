#version 330 core

out vec4 fragColor;

in vec3 gl_Color;

void main(void) {
	fragColor = vec4(gl_Color, 1);
}
