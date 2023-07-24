#include "VertexLayout.h"
#include "GL/glew.h"

void VertexLayout::SetLayout(size_t index, size_t size, size_t stride, size_t offset, bool intType)
{
	if(intType)
		glVertexAttribPointer((GLuint)index, (GLuint)size, GL_FLOAT, GL_FALSE, (GLuint)stride * sizeof(int), (void*)((GLuint)offset * sizeof(int)));
	else
		glVertexAttribPointer((GLuint)index, (GLuint)size, GL_FLOAT, GL_FALSE, (GLuint)stride * sizeof(float), (void*)((GLuint)offset * sizeof(float)));
	
	glEnableVertexAttribArray((GLuint)index);
}

void VertexLayout::SetLayouts()
{
	switch(m_layoutType)
	{
		case Layout_Type_Pos:
		{
			SetLayout(0, 3, 3, 0);
			break;
		}

		case Layout_Type_PosCol:
		{
			SetLayout(0, 3, 6, 0);
			SetLayout(1, 3, 6, 3);
			break;
		}

		case Layout_Type_PosTex:
		{
			SetLayout(0, 3, 5, 0);
			SetLayout(1, 2, 5, 3, true);
			break;
		}

		case Layout_Type_PosColTex:
		{
			SetLayout(0, 3, 8, 0);
			SetLayout(1, 3, 8, 3);
			SetLayout(2, 2, 8, 6, true);
			break;
		}
	}
}
