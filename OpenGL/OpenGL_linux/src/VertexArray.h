#ifndef _VERTEXARRAY_
#define _VERTEXARRAY_

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
  unsigned int m_RendererID;

public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

  void Bind() const;
  void Unbind() const;
};

#endif