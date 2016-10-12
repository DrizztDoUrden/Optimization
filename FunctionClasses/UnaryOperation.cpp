#include "UnaryOperation.h"
#include <sstream>



namespace Optimization
{
	namespace FunctionClasses
	{
		UnaryOperation::UnaryOperation(Function *left, UnaryOperator op, string opStr)
			: _left(left)
			, _operation(op)
			, _opStr(opStr)
		{

		}

		UnaryOperation::~UnaryOperation()
		{
			delete _left;
		}

		double UnaryOperation::Calculate(const double* x) const
		{
			return _operation(_left->Calculate(x));
		}

		string UnaryOperation::ToString() const
		{
			stringstream ss;

			ss << _left->ToString() << _opStr;

			return ss.str();
		}

		size_t UnaryOperation::CountVariables() const
		{
			return _left->CountVariables();
		}
	}
}
