#include "../headers/EuroGrooveArc.h"

template<typename T>
EuroGrooveArc<T>::EuroGrooveArc(Point p, int r, float f0, float f1, unsigned char color[]) :GenericArc<T>(p, r, f0, f1, color){
}

template<typename T>
void EuroGrooveArc<T>::Draw(cimg_library::CImg<T> img){
	int k = 7;
	float d = k * std::abs(this->_f1 - this->_f0) / this->_r;
	int x1, y1, x2, y2;
	for (float fi = this->_f0; fi < this->_f1; fi += d) {
		x1 = this->_p.x() + this->_r * std::cos(fi);
		y1 = this->_p.y() + this->_r * std::sin(fi);
		x2 = this->_p.x() + (this->_r - 4) * std::cos(fi);
		y2 = this->_p.y() + (this->_r - 4) * std::sin(fi);
		img.draw_line(x1, y1, x2, y2, this->_color, 1);
	}
}