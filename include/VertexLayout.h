#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H
#include <cstdlib>

class VertexLayout
{
public:
    VertexLayout(size_t numAttributes) : m_numAttributes(numAttributes), m_attributeCount(0), m_readyForUse(false) {}
    ~VertexLayout() = default;

    void SetLayout(size_t index, size_t size, size_t stride, size_t offset);
    bool ReadyForUse();

private:
    size_t m_numAttributes;
    size_t m_attributeCount;
    bool m_readyForUse;
};



#endif

