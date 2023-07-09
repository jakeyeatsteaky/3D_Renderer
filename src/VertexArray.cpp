#include "GL/glew.h"
#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vaoIdx);
	glBindVertexArray(m_vaoIdx);
}

VertexArray::VertexArray(const VertexArray& copy) : m_vaoIdx(copy.m_vaoIdx)
{
	glBindVertexArray(m_vaoIdx);
}

VertexArray::VertexArray(const VertexArray&& move) noexcept : m_vaoIdx(move.m_vaoIdx)
{
	glBindVertexArray(m_vaoIdx);
}
 
VertexArray::~VertexArray()
{
	Destroy();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_vaoIdx);
}

unsigned int VertexArray::GetIdx()
{
	return m_vaoIdx;
}

void VertexArray::Destroy()
{
	// 
}

void VertexArray::ClearFromBinding()
{
	glBindVertexArray(0);
}
