#include "../include/CImg.h"
#include "Attributes.h"

#pragma once
template <typename T>
class ArchAttributes : Attributes<T>
{
public:
	ArchAttributes();
	~ArchAttributes();
};


template <typename T>
ArchAttributes<T>::ArchAttributes()
{
}

template <typename T>
ArchAttributes<T>::~ArchAttributes()
{
}
template <typename T>
ArchAttributes<T>:: void draw_curve_saws(const cimg_library::CImg<T>* img){
	float fi0, float fi1,
		const tc *const color, const float opacity,
		const unsigned int pattern) {
		cimg::unused(pattern);
		if (is_empty()) return *this;
		if (!color)
			throw CImgArgumentException(_cimg_instance
			"draw_circle(): Specified color is (null).",
			cimg_instance);
		if (radius < 0 || x0 - radius >= width() || y0 + radius < 0 || y0 - radius >= height()) return *this;
		if (!radius) return draw_point(x0, y0, color, opacity);
		if (radius == 1) return *this;

		int k = 17;
		float d = k * cimg::abs(fi1 - fi0) / radius;
		std::cout << " d " << d << std::endl;
		int x, y;
		for (float fi = fi0; fi < fi1; fi += d) {
			for (float alpha = fi; alpha < fi + d / 2 && alpha < fi1; alpha += 0.01)
			{
				x = x0 + (radius - 5) * std::cos(alpha);
				y = y0 + (radius - 5) * std::sin(alpha);
				img.draw_point(x, y, color, opacity);
			}
		}
		return *this;
}

template <typename T>
ArchAttributes<T>:: void draw_euro_groove(const cimg_library::CImg<T>* img){
	float fi0, float fi1,
		const tc *const color, const float opacity,
		const unsigned int pattern) {
		cimg::unused(pattern);
		if (is_empty()) return *this;
		if (!color)
			throw CImgArgumentException(_cimg_instance
			"draw_circle(): Specified color is (null).",
			cimg_instance);
		if (radius < 0 || x0 - radius >= width() || y0 + radius < 0 || y0 - radius >= height()) return *this;
		if (!radius) return draw_point(x0, y0, color, opacity);
		if (radius == 1) return *this;

		int k = 7;
		float d = k * cimg::abs(fi1 - fi0) / radius;
		int x1, y1, x2, y2;
		for (float fi = fi0; fi < fi1; fi += d) {
			x1 = x0 + radius * std::cos(fi);
			y1 = y0 + radius * std::sin(fi);
			x2 = x0 + (radius - 4) * std::cos(fi);
			y2 = y0 + (radius - 4) * std::sin(fi);
			img.draw_line(x1, y1, x2, y2, color);
		}
		return *this;
}

