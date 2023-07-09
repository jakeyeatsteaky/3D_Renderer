#include "VertexLayout.h"
#include "GL/glew.h"

void VertexLayout::SetLayout(size_t index, size_t size, size_t stride, size_t offset)
{
	if (m_attributeCount < m_numAttributes)
	{
		glVertexAttribPointer((GLuint)index, (GLuint)size, GL_FLOAT, GL_FALSE, (GLuint)stride * sizeof(float), (void*)((GLuint)offset * sizeof(float)));
		glEnableVertexAttribArray((GLuint)index);

		m_attributeCount++;
		if (m_attributeCount == m_numAttributes)
			m_readyForUse = true;
	}
}

bool VertexLayout::ReadyForUse()
{
	return m_readyForUse;
}