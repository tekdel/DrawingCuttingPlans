#include "../headers/GenericLine.h"

template<typename T>
GenericLine<T>::GenericLine(Point p1, Point p2, int side, unsigned char color[]){
	this->_p1 = p1;
	this->_p2 = p2;
	this->_side = side;
	this->_color[0] = color[0];
	this->_color[1] = color[1];
	this->_color[2] = color[2];
}

template<typename T>
void GenericLine<T>::Draw(cimg_library::CImg<T> img){
	img.draw_line(this->_p1.x(), this->_p1.y(), this->_p2.x(), this->_p2.y(), this->_color, 1);
}