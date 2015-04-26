#include <iostream>
#include <algorithm>  
#include "../stdafx.h"
#include "StandardEquationLine.h"
#include "SlopeInterceptEquationLine.h"
#include "Point.h"

#pragma once
namespace DrawwingCuttingPlans{
	namespace Geometry{
		StandardEquationLine getEquationByTwoPoints(Point a, Point b){
			StandardEquationLine eq;
			eq.a(a.y() - b.y());
			eq.b(b.x() - a.x());
			eq.c(a.x()* b.y() - b.x() * a.y());
			return eq;
		}

		SlopeInterceptEquationLine getPerpendicularToLineAtPoint(SlopeInterceptEquationLine line, Point a){
			SlopeInterceptEquationLine eq;
			if (line.k() == 0){
				eq.b(a.y());
			}
			else{
				eq.k(-1 / line.k());
				eq.b(a.x() / line.k() + a.y());
			}
			return eq;
		}

		StandardEquationLine getPerpendicularToLineAtPoint(StandardEquationLine line, Point a){
			StandardEquationLine eq;
			//A(y - y1) - B(x - x1) = 0
			eq.a(-line.b());
			eq.b(line.a());
			eq.c(-a.y() * line.a() + line.b() * a.x());
			return eq;
		}

		int getDistancePoints(Point a, Point b){
			return std::sqrt(std::pow(b.x() - a.x(), 2) + std::pow(b.y() - a.y(), 2));
		}

		Point getDistantPointFromPointAtLine(SlopeInterceptEquationLine line, Point a, int distance, int side = 0){
			float _b = -2 * a.x() - 2 * line.k() * (a.y() - line.b());
			float _a = 1 + line.k() * line.k();

			float D = std::pow(_b, 2) - 4 * _a * (a.x() * a.x() + line.b() * line.b() + a.y() *a.y() - distance * distance - 2 * a.y() * line.b());

			int _x1 = (-_b + std::sqrt(D)) / (2 * _a);
			int _x2 = (-_b - std::sqrt(D)) / (2 * _a);

			int p = _b > 0 ? 1 : 6;

			int x = side == 1 ? max(_x1, _x2) : min(_x1, _x2);
			int y = line.k() * x + line.b();

			return Point(x, y);
		}

		Point getDistantPointFromPointAtGenericLine(StandardEquationLine line, Point a, int distance, int side = 0){
			if (line.a() != 0 && line.b() != 0){
				return getDistantPointFromPointAtLine(SlopeInterceptEquationLine(line), a, distance, side);
			}
			else if (line.b() == 0){
				return side == 0 ? Point(a.x(), a.y() - distance) : Point(a.x(), a.y() + distance);
			}
			else{
				return side == 0 ? Point(a.x() - distance, a.y()) : Point(a.x() + distance, a.y());
			}
		}

		Point getDistantPointFromPointAtPerpendicularLine(StandardEquationLine line, Point a, int distance, int side = 0){
			if (line.a() == 0){
				return side == 0 ? Point(a.x(), a.y() - distance) : Point(a.x(), a.y() + distance);
			}
			else if (line.b() == 0){
				return side == 0 ? Point(a.x() - distance, a.y()) : Point(a.x() + distance, a.y());
			}
			else{
				SlopeInterceptEquationLine eq(line);
				eq = getPerpendicularToLineAtPoint(eq, a);
				return getDistantPointFromPointAtLine(eq, a, distance, side);
			}
		}
	}
}