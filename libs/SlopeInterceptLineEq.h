#include <iostream>

class SlopeInterceptLineEq
{
private:
	float kvalue;
	float bvalue;
public:
	SlopeInterceptLineEq() : SlopeInterceptLineEq(0, 0){ };
	SlopeInterceptLineEq(float k, float b) : kvalue(k), bvalue(b) { };
	~SlopeInterceptLineEq();

	float k();
	float b();

	void k(float value);
	void b(float value);

	explicit SlopeInterceptLineEq(GenericLineEq arg){
		if (arg.b() == 0){
			throw "Zero division";
		}

		kvalue = -1 * (arg.a() / arg.b());
		bvalue = -1 * (arg.c() / arg.b());
	}

	SlopeInterceptLineEq& operator= (GenericLineEq arg);
	SlopeInterceptLineEq& operator=(const SlopeInterceptLineEq& arg);

	friend std::ostream &operator<<(std::ostream &out, SlopeInterceptLineEq arg);
};

float SlopeInterceptLineEq::k(){
	return kvalue;
}

float SlopeInterceptLineEq::b(){
	return bvalue;
}

void SlopeInterceptLineEq::k(float value){
	kvalue = value;
}

void SlopeInterceptLineEq::b(float value){
	bvalue = value;
}

SlopeInterceptLineEq::~SlopeInterceptLineEq()
{
}

SlopeInterceptLineEq& SlopeInterceptLineEq::operator = (GenericLineEq arg){
	if (arg.b() == 0){
		throw "Zero division";
	}

	kvalue = -1 * (arg.a() / arg.b());
	bvalue = -1 * (arg.c() / arg.b());
	return *this;
}

SlopeInterceptLineEq& SlopeInterceptLineEq::operator=(const SlopeInterceptLineEq& arg){
	kvalue = arg.kvalue;
	bvalue = arg.bvalue;
	return *this;
}

std::ostream &operator<<(std::ostream &out, SlopeInterceptLineEq arg){
	char* sign = arg.b() > 0 ? "+" : "";
	out << "Equation y = kx + b;  " << arg.k() << "x " << sign << arg.b() << std::endl;
	return out;
}