#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "IndexBuffer.hpp"


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