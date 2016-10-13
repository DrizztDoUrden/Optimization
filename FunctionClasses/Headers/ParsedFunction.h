#pragma once
#include "Function.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		class ParsedFunction abstract : public Function<double>
		{
		public:
			virtual string ToString() const abstract;
			virtual size_t CountVariables() const abstract;
		};
	}
}
