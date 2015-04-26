#include "../headers/EuroGrooveLine.h"

template<typename T>
EuroGrooveLine<T>::EuroGrooveLine(Point p1, Point p2, int side, unsigned char color[]) :GenericLine<T>(p1, p2, side, color)
{
}

template<typename T>
void EuroGrooveLine<T>::Draw(cimg_library::CImg<T> img)
{
	int distance = 8;
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

	int skipped = 0;
	int drawed = 0;
	int current = 0;
	for (int x = (int)x3; x < maxX; x++)
	{
		if (current != drawed){

			if (steep)
			{
				DrawwingCuttingPlans::Geometry::StandardEquationLine _ln = DrawwingCuttingPlans::Geometry::getPerpendicularToLineAtPoint(line, Point(y, x));
				Point _p = DrawwingCuttingPlans::Geometry::getDistantPointFromPointAtGenericLine(_ln, Point(y, x), distance, this->_side);
				img.draw_line(y, x, _p.x(), _p.y(), this->_color, 1);
			}
			else
			{
				DrawwingCuttingPlans::Geometry::StandardEquationLine _ln = DrawwingCuttingPlans::Geometry::getPerpendicularToLineAtPoint(line, Point(x, y));
				Point _p = DrawwingCuttingPlans::Geometry::getDistantPointFromPointAtGenericLine(_ln, Point(x, y), distance, this->_side);
				img.draw_line(x, y, _p.x(), _p.y(), this->_color, 1);
			}
			drawed = current;
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