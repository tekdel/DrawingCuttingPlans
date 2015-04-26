#include "../headers/CurveSawsArc.h"

template<typename T>
CurveSawsArc<T>::CurveSawsArc(Point p, int r, float f0, float f1, unsigned char color[]) :GenericArc<T>(p, r, f0, f1, color){
}

template<typename T>
void CurveSawsArc<T>::Draw(cimg_library::CImg<T> img){
	int k = 17;
	float d = k * std::abs(this->_f1 - this->_f0) / this->_r;
	int x, y;
	for (float fi = this->_f0; fi < this->_f1; fi += d) {
		for (float alpha = fi; alpha < fi + d / 2 && alpha < this->_f1; alpha += 0.01)
		{
			x = this->_p.x() + (this->_r - 5) * std::cos(alpha);
			y = this->_p.y() + (this->_r - 5) * std::sin(alpha);
			img.draw_point(x, y, this->_color, 1);
		}
	}
}