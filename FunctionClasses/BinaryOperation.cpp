#include "BinaryOperation.h"
#include <algorithm>



namespace Optimization
{
	namespace FunctionClasses
	{
		BinaryOperation::BinaryOperation(Function *left, Function *right, BinaryOperator op, string opStr)
			: _left(left)
			, _right(right)
			, _operation(op)
			, _opStr(opStr)
		{

		}

		BinaryOperation::~BinaryOperation()
		{
			delete _left;
			delete _right;
		}

		double BinaryOperation::Calculate(const Vector& x) const
		{
			return _operation(_left->Calculate(x), _right->Calculate(x));
		}

		string BinaryOperation::ToString() const
		{
			return string("(").append(_left->ToString()).append(_opStr).append(_right->ToString()).append(")");
		}

		size_t BinaryOperation::CountVariables() const
		{
			return max(_left->CountVariables(), _right->CountVariables());
		}
	}
}
