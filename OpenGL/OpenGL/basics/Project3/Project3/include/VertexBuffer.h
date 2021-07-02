#pragma once

class VertexBuffer
{
private:
	unsigned int n_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};