#include "../headers/GenericArc.h"

template<typename T>
GenericArc<T>::GenericArc(Point p, int r, float f0, float f1, unsigned char color[]){
	this->_p = p;
	this->_r = r;
	this->_f0 = f0;
	this->_f1 = f1;
	this->_color[0] = color[0];
	this->_color[1] = color[1];
	this->_color[2] = color[2];
}

template<typename T>
void GenericArc<T>::Draw(cimg_library::CImg<T> img){
	int x, y;
	for (float fi = this->_f0; fi < this->_f1; fi += 0.01) {
		x = _p.x() + _r * std::cos(fi);
		y = _p.y() + _r * std::sin(fi);
		img.draw_point(x, y, _color, 1);
	}
}