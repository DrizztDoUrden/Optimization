#pragma once
#include "Vector.h"



using namespace Optimization::OptimizationClasses;



namespace Optimization
{
	namespace FunctionClasses
	{
		class Function
		{
		public:
			Function();
			virtual ~Function();

			virtual double Calculate(const Vector& x) const abstract;
			virtual string ToString() const abstract;
			virtual size_t CountVariables() const abstract;

			double operator()(const Vector& x) const;
		};
	}
}
