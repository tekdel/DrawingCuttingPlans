#include "Part.h"

Part::Part()
{
}

Part::Part(int _x0, int _y0, int _width, int _height, std::string _comment)
{
	x0 = _x0;
	y0 = _y0;
	width = _width;
	height = _height;
	comment = _comment;
}


Part::~Part()
{
}
