#pragma once
#include "Function.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		class Constant : public Function
		{
			double _value;

		public:
			explicit Constant(double value);
			double Calculate(const Vector& x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
