#include <iostream>
#include "StandardEquationLine.h"

#pragma once

namespace DrawwingCuttingPlans{
	namespace Geometry{
		class SlopeInterceptEquationLine
		{
		private:
			float kvalue;
			float bvalue;
		public:
			SlopeInterceptEquationLine();
			SlopeInterceptEquationLine(float k, float b);
			~SlopeInterceptEquationLine();

			float k();
			float b();

			void k(float value);
			void b(float value);

			explicit SlopeInterceptEquationLine(DrawwingCuttingPlans::Geometry::StandardEquationLine arg){
				if (arg.b() == 0){
					throw "Zero division";
				}

				kvalue = -1 * (arg.a() / arg.b());
				bvalue = -1 * (arg.c() / arg.b());
			}

			SlopeInterceptEquationLine& operator= (DrawwingCuttingPlans::Geometry::StandardEquationLine arg);
			SlopeInterceptEquationLine& operator=(const SlopeInterceptEquationLine& arg);

			friend std::ostream &operator<<(std::ostream &out, SlopeInterceptEquationLine arg);
		};
	}
}