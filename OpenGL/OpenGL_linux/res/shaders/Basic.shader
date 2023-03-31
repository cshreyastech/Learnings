#shader vertex
#version 410 core

layout(location = 0) in vec4 position;

void main()
{
  gl_Position = position;
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

void main()
{
  color = vec4(2.0, 0.3, 0.8, 1.0);
};
