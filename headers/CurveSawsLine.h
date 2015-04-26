#include "Point.h"
#include "GenericLine.h"

#pragma once
template<typename T>
class CurveSawsLine : public GenericLine<T>
{
public:
	CurveSawsLine(Point p1, Point p2, int side, unsigned char color[]);
	void Draw(cimg_library::CImg<T> img);
};
