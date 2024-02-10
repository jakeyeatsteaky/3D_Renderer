#ifndef VERTEX_LAYOUT_HPP
#define VERTEX_LAYOUT_HPP
#include <cstdlib>
#include "enumerations.h"

class VertexLayout
{
public:
    VertexLayout(Layout_Type vertexLayout) : m_layoutType(vertexLayout){}
    ~VertexLayout() = default;

    void SetLayouts();
    void SetLayout(size_t index, size_t size, size_t stride, size_t offset, bool intType = false);
    bool ReadyForUse();

private:
    Layout_Type m_layoutType;
};



#endif

