#include "GetVariable.h"
#include <string>
#include <sstream>



namespace Optimization
{
	namespace FunctionClasses
	{
		GetVariable::GetVariable(size_t id)
			: _id(id)
		{
		}

		double GetVariable::Calculate(const double* x) const
		{
			return x[_id];
		}

		string GetVariable::ToString() const
		{
			stringstream ss;

			ss << "x" << _id + 1;

			return ss.str();
		}

		size_t GetVariable::CountVariables() const
		{
			return _id + 1;
		}
	}
}
