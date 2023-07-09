#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const float* vertices, const GLsizeiptr VertexBufferSize);
	VertexBuffer(const VertexBuffer& other);
	~VertexBuffer();

	void Bind(const float* vertices, const GLsizeiptr VertexBufferSize);
	unsigned int GetIdx();
	void ClearFromBinding();
	void Destroy();

private:
	unsigned int m_vboIdx;
	float* m_vertices;
	GLsizeiptr m_verticesSize;
};


#if 0
Some Notes:
	genBuffer, bind and buffer data all happens in the constructor.  The bind method might be able to be used as a change vertices function

#endif

#endif