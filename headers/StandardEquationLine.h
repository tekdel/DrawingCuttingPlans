#include <iostream>

#pragma once
namespace DrawwingCuttingPlans{
	namespace Geometry{
		class StandardEquationLine
		{
		private:
			float avalue;
			float bvalue;
			float cvalue;
		public:
			StandardEquationLine();
			StandardEquationLine(float a, float b, float c);
			~StandardEquationLine();

			float a();
			float b();
			float c();

			void a(float value);
			void b(float value);
			void c(float value);

			StandardEquationLine& operator=(const StandardEquationLine& arg);

			friend std::ostream &operator<<(std::ostream &out, StandardEquationLine arg);
		};
	}
}