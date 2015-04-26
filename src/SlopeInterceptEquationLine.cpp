#include "../headers/SlopeInterceptEquationLine.h"


DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::SlopeInterceptEquationLine() : SlopeInterceptEquationLine(0, 0)
{
}

DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::SlopeInterceptEquationLine(float k, float b)
{
	this->kvalue = k;
	this->bvalue = b;
}


DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::~SlopeInterceptEquationLine()
{
}


float DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::k(){
	return this->kvalue;
}

float DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::b(){
	return bvalue;
}

void DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::k(float value){
	kvalue = value;
}

void DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::b(float value){
	bvalue = value;
}

DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine& DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::operator = (DrawwingCuttingPlans::Geometry::StandardEquationLine arg){
	if (arg.b() == 0){
		throw "Zero division";
	}

	kvalue = -1 * (arg.a() / arg.b());
	bvalue = -1 * (arg.c() / arg.b());
	return *this;
}

DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine& DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine::operator=(const DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine& arg){
	kvalue = arg.kvalue;
	bvalue = arg.bvalue;
	return *this;
}

std::ostream &operator<<(std::ostream &out, DrawwingCuttingPlans::Geometry::SlopeInterceptEquationLine arg){
	char* sign = arg.b() > 0 ? "+" : "";
	out << "Equation y = kx + b;  " << arg.k() << "x " << sign << arg.b() << std::endl;
	return out;
}