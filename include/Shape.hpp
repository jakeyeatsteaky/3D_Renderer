#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <stdint.h>

class Shape
{
public:
	Shape():color(0xFFFFFFFF) {}
	Shape(uint32_t color) : color(color) {};

	virtual ~Shape() = 0;

	virtual void drawShape() const = 0;

private:

protected:
	uint32_t color;
};


#endif // end shape_hpp