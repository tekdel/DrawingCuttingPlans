#include "Point.h"
#include "Drawable.h"

#pragma once
template<typename T>
class GenericArc : public Drawable<T>
{
protected:
	Point _p;
	int _r;
	float _f0, _f1;
	unsigned char _color[3];
public:
	GenericArc(Point p, int r, float f0, float f1, unsigned char color[]);
	virtual void Draw(cimg_library::CImg<T> img);
};