#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "IndexBuffer.h"


class VertexArray
{
public:
	VertexArray();
	VertexArray(const VertexArray& copy);
	VertexArray(const VertexArray&& move) noexcept;
	~VertexArray();

	unsigned int GetIdx();
	void Bind();
	void ClearFromBinding();
	void Destroy();

private:
	unsigned int m_vaoIdx;
};


#endif