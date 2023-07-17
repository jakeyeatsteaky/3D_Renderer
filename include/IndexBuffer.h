#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include "GL/glew.h"
#include <vector>

class IndexBuffer
{
public:
	IndexBuffer(const std::vector<unsigned>& indices);
	~IndexBuffer();

	void Bind(const unsigned int* indices, GLsizeiptr indexBufferSize);
	void Bind() const;
	unsigned int GetIdx();
	void ClearFromBinding();
	void Destroy();

private:
	unsigned int m_iboIdx;
	unsigned int* m_indices;
	GLsizeiptr m_indicesSize;
};


#endif