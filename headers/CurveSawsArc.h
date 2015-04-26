#include "Point.h"
#include "GenericArc.h"

#pragma once
template<typename T>
class CurveSawsArc : public GenericArc<T>
{
public:
	CurveSawsArc(Point p, int r, float f0, float f1, unsigned char color[]);
	void Draw(cimg_library::CImg<T> img);
};