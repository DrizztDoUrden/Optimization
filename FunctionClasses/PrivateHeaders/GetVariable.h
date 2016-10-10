#pragma once
#include "Function.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		class GetVariable : public Function
		{
			size_t _id;

		public:
			explicit GetVariable(size_t id);

			double Calculate(const double* x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
