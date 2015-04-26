#include <iostream>

#pragma once
class Point
{
private:
	int xval;
	int yval;
public:
	Point();
	Point(int x, int y);
	~Point();
	int x();
	int y();
	void x(int value);
	void y(int value);

	Point& operator=(const Point& arg);
	friend std::ostream &operator<<(std::ostream &out, Point& arg);
};