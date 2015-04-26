#include "Point.h"
#include "Drawable.h"

#pragma once
template<typename T>
class GenericLine : public Drawable<T>
{
protected:
	Point _p1;
	Point _p2;
	int _side;
	unsigned char _color[3];
public:
	GenericLine(Point p1, Point p2, int side, unsigned char color[]);
	virtual void Draw(cimg_library::CImg<T> img);
};