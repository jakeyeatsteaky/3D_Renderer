#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include "GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const IndexBuffer& other);
	IndexBuffer(const unsigned int* indices, GLsizeiptr indexBufferSize);
	~IndexBuffer();

	void Bind(const unsigned int* indices, GLsizeiptr indexBufferSize);
	unsigned int GetIdx();
	void ClearFromBinding();
	void Destroy();

private:
	unsigned int m_iboIdx;
	unsigned int* m_indices;
	GLsizeiptr m_indicesSize;
};


#endif