#include "VertexBuffer.h"
#include <string>
#include <cstring>

VertexBuffer::VertexBuffer(const float* vertices, const GLsizeiptr VertexBufferSize) :
	m_vertices(new float[VertexBufferSize]),
	m_verticesSize(VertexBufferSize)
{	
	memcpy(m_vertices, vertices, (size_t)VertexBufferSize);

	glGenBuffers(1, &m_vboIdx);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboIdx);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize, m_vertices, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const VertexBuffer& other): 
	m_vboIdx(other.m_vboIdx),
	m_vertices(other.m_vertices),
	m_verticesSize(other.m_verticesSize)
{
	// TODO: Implement copy constructure when use case arises
	printf("COPY CONSTRUCTOR NOT IMPLEMENTED VERTEXBUFFFER\n");
}

VertexBuffer::~VertexBuffer()
{
	Destroy();
}

void VertexBuffer::Bind(const float* vertices, const GLsizeiptr VertexBufferSize)
{
	m_vertices = new float[VertexBufferSize];
	m_verticesSize = VertexBufferSize;
	memcpy(m_vertices, vertices, (size_t)VertexBufferSize);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboIdx);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize, m_vertices, GL_STATIC_DRAW);

}

unsigned int VertexBuffer::GetIdx() 
{
	return m_vboIdx;
}


void VertexBuffer::ClearFromBinding()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Destroy() 
{
	delete[] m_vertices;
}