#include "VertexBuffer.h"
#include <string>
#include <cstring>

VertexBuffer::VertexBuffer(const std::vector<float>& vertices) :
	m_vertices(new float[vertices.size()]),
	m_verticesSize(vertices.size() * sizeof(float))
{	
	memcpy(m_vertices, vertices.data(), m_verticesSize);

	glGenBuffers(1, &m_vboIdx);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboIdx);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize, m_vertices, GL_STATIC_DRAW);
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

void VertexBuffer::Bind() const
{
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