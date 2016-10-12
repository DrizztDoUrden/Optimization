#include "Constant.h"
#include <string>
#include <sstream>



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
			stringstream ss;
			
			ss << _value;

			return ss.str();
		}

		size_t Constant::CountVariables() const
		{
			return 0;
		}
	}
}
