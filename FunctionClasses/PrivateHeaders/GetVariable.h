#pragma once
#include "Function.h"
#include "Vector.h"



using namespace Optimization::OptimizationClasses;



namespace Optimization
{
	namespace FunctionClasses
	{
		class GetVariable : public Function
		{
			size_t _id;

		public:
			explicit GetVariable(size_t id);

			double Calculate(const Vector&) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
