#include "../headers/Point.h"

Point::Point() : Point(0, 0)
{
}

Point::Point(int x, int y){
	this->xval = x;
	this->yval = y;
}

Point::~Point()
{
}

int Point::x(){
	return this->xval;
}

int Point::y(){
	return yval;
}

void Point::x(int value){
	this->xval = value;
}

void Point::y(int value){
	yval = value;
}

Point& Point::operator=(const Point& arg){
	xval = arg.xval;
	yval = arg.yval;
	return *this;
}

std::ostream &operator<<(std::ostream &out, Point& arg){
	out << "Point(x,y) = ( " << arg.x() << " , " << arg.y() << " )" << std::endl;
	return out;
}