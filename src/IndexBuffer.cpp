#include "IndexBuffer.h"
#include <string>
#include <cstring>

IndexBuffer::IndexBuffer(const std::vector<unsigned>& indices) :
	m_indices(new unsigned[indices.size()]),
	m_indicesSize(indices.size() * sizeof(unsigned))
{
	memcpy(m_indices, indices.data(), m_indicesSize);

	glGenBuffers(1, &m_iboIdx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboIdx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize, m_indices, GL_STATIC_DRAW);
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

void IndexBuffer::Bind() const
{
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
