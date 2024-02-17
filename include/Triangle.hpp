#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : Shape
{
public:
	Triangle();
	Triangle(uint32_t color);

	~Triangle() override;

	virtual void drawShape() const override;

private:

};


#endif // end TRIANGLE_hpp