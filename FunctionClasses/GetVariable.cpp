#include "GetVariable.h"
#include <string>


namespace Optimization
{
	namespace FunctionClasses
	{
		GetVariable::GetVariable(size_t id)
			: _id(id)
		{
		}

		double GetVariable::Calculate(const Vector& x) const
		{
			return x[_id];
		}

		string GetVariable::ToString() const
		{
			return string("x").append(to_string(_id + 1));
		}

		size_t GetVariable::CountVariables() const
		{
			return _id + 1;
		}
	}
}
