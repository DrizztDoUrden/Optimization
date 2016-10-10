#include "UnaryOperation.h"



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
			return string("(").append(_opStr).append(_left->ToString()).append(")");
		}

		size_t UnaryOperation::CountVariables() const
		{
			return _left->CountVariables();
		}
	}
}
