#include "../headers/CurveSawsLine.h"

template<typename T>
CurveSawsLine<T>::CurveSawsLine(Point p1, Point p2, int side, unsigned char color[]) :GenericLine<T>(p1, p2, side, color)
{
}

template<typename T>
void CurveSawsLine<T>::Draw(cimg_library::CImg<T> img)
{
	int distance = 5;
	DrawwingCuttingPlans::Geometry::StandardEquationLine line = DrawwingCuttingPlans::Geometry::getEquationByTwoPoints(this->_p1, this->_p2);
	Point c1 = DrawwingCuttingPlans::Geometry::getDistantPointFromPointAtPerpendicularLine(line, this->_p1, distance, this->_side);
	Point d1 = DrawwingCuttingPlans::Geometry::getDistantPointFromPointAtPerpendicularLine(line, this->_p2, distance, this->_side);
	int x3 = c1.x(), y3 = c1.y(), x4 = d1.x(), y4 = d1.y();

	const bool steep = (std::abs(y4 - y3) > std::abs(x4 - x3));
	if (steep)
	{
		std::swap(x3, y3);
		std::swap(x4, y4);
	}

	if (x3 > x4)
	{
		std::swap(x3, x4);
		std::swap(y3, y4);
	}

	const float dx = x4 - x3;
	const float dy = std::abs(y4 - y3);

	float error = dx / 2.0f;
	const int ystep = (y3 < y4) ? 1 : -1;
	int y = (int)y3;

	const int maxX = (int)x4;

	int current = 0;
	for (int x = (int)x3; x < maxX; x++)
	{
		if (current != 0 && current % 2 == 0){
			if (steep)
			{
				img.draw_point(y, x, this->_color, 1);
			}
			else
			{
				img.draw_point(x, y, this->_color, 1);
			}
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
		current = DrawwingCuttingPlans::Geometry::getDistancePoints(Point(x3, y3), Point(x, y)) / distance;
	}
}
