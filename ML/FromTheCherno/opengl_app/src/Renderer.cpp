#include "Renderer.h"

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

void Renderer::Clear() const
{
  GLCall(glClearColor(0.0, 0.0, 0.0, 0.0));
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
  shader.Bind();
  va.Bind();
  ib.Bind();

  GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
