#include "../headers/StandardEquationLine.h"

DrawwingCuttingPlans::Geometry::StandardEquationLine::StandardEquationLine() : StandardEquationLine(0, 0, 0)
{
}

DrawwingCuttingPlans::Geometry::StandardEquationLine::StandardEquationLine(float a, float b, float c)
{
	this->avalue = a;
	this->bvalue = b;
	this->cvalue = c;
}

DrawwingCuttingPlans::Geometry::StandardEquationLine::~StandardEquationLine()
{
}


float DrawwingCuttingPlans::Geometry::StandardEquationLine::a(){
	return avalue;
}

float DrawwingCuttingPlans::Geometry::StandardEquationLine::b(){
	return bvalue;
}

float DrawwingCuttingPlans::Geometry::StandardEquationLine::c(){
	return cvalue;
}

void DrawwingCuttingPlans::Geometry::StandardEquationLine::a(float value){
	avalue = value;
}

void DrawwingCuttingPlans::Geometry::StandardEquationLine::b(float value){
	bvalue = value;
}

void DrawwingCuttingPlans::Geometry::StandardEquationLine::c(float value){
	cvalue = value;
}

DrawwingCuttingPlans::Geometry::StandardEquationLine& DrawwingCuttingPlans::Geometry::StandardEquationLine::operator=(const DrawwingCuttingPlans::Geometry::StandardEquationLine& arg){
	avalue = arg.avalue;
	bvalue = arg.bvalue;
	cvalue = arg.cvalue;

	return *this;
}

std::ostream &operator<<(std::ostream &out, DrawwingCuttingPlans::Geometry::StandardEquationLine arg){
	char* signB = arg.b() > 0 ? "+" : "";
	char* signC = arg.c() > 0 ? "+" : "";
	out << "Equation Ax + By + C = 0;  " << arg.a() << "x " << signB << arg.b() << "y " << signC << arg.c() << std::endl;
	return out;
}
