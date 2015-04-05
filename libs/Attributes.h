#include "../include/CImg.h"

#pragma once
template <typename T>
class Attributes<T>
{
public:
	Attributes();
	~Attributes();

	virtual void draw_curve_saws(const cimg_library::CImg<T>* img);
	virtual void draw_euro_groove(const cimg_library::CImg<T>* img);
	virtual void draw_hem(const cimg_library::CImg<T>* img);
};


template <typename T>
Attributes<T>::Attributes()
{
}

template <typename T>
Attributes<T>::~Attributes()
{
}


