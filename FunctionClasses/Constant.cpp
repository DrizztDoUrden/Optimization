#include "Constant.h"
#include <string>


namespace Optimization
{
	namespace FunctionClasses
	{
		Constant::Constant(double value)
			: _value(value)
		{
			
		}


		double Constant::Calculate(const double* x) const
		{
			return _value;
		}

		string Constant::ToString() const
		{
			char temp[32];
			sprintf_s(temp, "%.0f", _value);
			return temp;
		}

		size_t Constant::CountVariables() const
		{
			return 0;
		}
	}
}
