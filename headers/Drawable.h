#include "..\include\CImg.h"

#pragma once
template<typename T>
class Drawable
{
public:
	virtual void Draw(cimg_library::CImg<T> img) = 0;
};