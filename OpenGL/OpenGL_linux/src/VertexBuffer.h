#ifndef _VERTEXBUFFER_
#define _VERTEXBUFFER_

class VertexBuffer
{
private:
  unsigned int m_RendererID;
public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};

#endif