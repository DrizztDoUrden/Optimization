#include "Function.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		Function::Function()
		{
		}

		Function::~Function()
		{
		}

		double Function::operator()(const Vector& x) const
		{
			return Calculate(x);
		}
	}
}
