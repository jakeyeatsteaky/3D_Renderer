#include "IndexBuffer.h"
#include <string>
#include <cstring>

IndexBuffer::IndexBuffer(const unsigned int* indices, const GLsizeiptr indexBufferSize) :
	m_indices(new unsigned int[indexBufferSize]),
	m_indicesSize(indexBufferSize)
{
	memcpy(m_indices, indices, (size_t)indexBufferSize);

	glGenBuffers(1, &m_iboIdx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboIdx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize, m_indices, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(const IndexBuffer& other) :
	m_iboIdx(other.m_iboIdx),
	m_indices(other.m_indices),
	m_indicesSize(other.m_indicesSize)
{
	// TODO: Implement copy constructure when use case arises
	printf("COPY CONSTRUCTOR NOT IMPLEMENTED INDEX BUFFFER\n");
}

IndexBuffer::~IndexBuffer()
{
	Destroy();
}

void IndexBuffer::Bind(const unsigned int* indices, const GLsizeiptr indexBufferSize)
{
	memcpy(m_indices, indices, (size_t)indexBufferSize);

	glGenBuffers(1, &m_iboIdx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboIdx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize, m_indices, GL_STATIC_DRAW);

}

unsigned int IndexBuffer::GetIdx()
{
	return m_iboIdx;
}


void IndexBuffer::ClearFromBinding()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Destroy()
{
	delete[] m_indices;
}
