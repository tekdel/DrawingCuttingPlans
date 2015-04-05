#include <iostream>

class GenericLineEq
{
private:
	float avalue;
	float bvalue;
	float cvalue;
public:
	GenericLineEq() : GenericLineEq(0, 0, 0){ };
	GenericLineEq(float a, float b, float c) : avalue(a), bvalue(b), cvalue(c) { };
	~GenericLineEq();

	float a();
	float b();
	float c();

	void a(float value);
	void b(float value);
	void c(float value);

	GenericLineEq& operator=(const GenericLineEq& arg);

	friend std::ostream &operator<<(std::ostream &out, GenericLineEq arg);
};

float GenericLineEq::a(){
	return avalue;
}

float GenericLineEq::b(){
	return bvalue;
}

float GenericLineEq::c(){
	return cvalue;
}

void GenericLineEq::a(float value){
	avalue = value;
}

void GenericLineEq::b(float value){
	bvalue = value;
}

void GenericLineEq::c(float value){
	cvalue = value;
}

GenericLineEq::~GenericLineEq()
{
}

GenericLineEq& GenericLineEq::operator=(const GenericLineEq& arg){
	avalue = arg.avalue;
	bvalue = arg.bvalue;
	cvalue = arg.cvalue;

	return *this;
}

std::ostream &operator<<(std::ostream &out, GenericLineEq arg){
	char* signB = arg.b() > 0 ? "+" : "";
	char* signC = arg.c() > 0 ? "+" : "";
	out << "Equation Ax + By + C = 0;  " << arg.a() << "x " << signB << arg.b() << "y " << signC << arg.c() << std::endl;
	return out;
}