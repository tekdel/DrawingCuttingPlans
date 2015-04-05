#include <iostream>

class Point
{
private:
	int xval;
	int yval;
public:
	Point() : Point(0, 0){};
	Point(int x, int y) : xval(x), yval(y) {};
	~Point();
	int x();
	int y();
	void x(int value);
	void y(int value);

	Point& operator=(const Point& arg);
	friend std::ostream &operator<<(std::ostream &out, Point& arg);
};

Point::~Point()
{
}

int Point::x(){
	return xval;
}

int Point::y(){
	return yval;
}

void Point::x(int value){
	xval = value;
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

