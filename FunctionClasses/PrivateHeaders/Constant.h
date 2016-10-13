#pragma once
#include "ParsedFunction.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		class Constant : public ParsedFunction
		{
			double _value;

		public:
			explicit Constant(double value);
			double Calculate(const double* x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
