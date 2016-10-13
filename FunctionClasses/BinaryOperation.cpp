#include "BinaryOperation.h"
#include <algorithm>
#include <sstream>



namespace Optimization
{
	namespace FunctionClasses
	{
		BinaryOperation::BinaryOperation(ParsedFunction *left, ParsedFunction *right, BinaryOperator op, string opStr)
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

		double BinaryOperation::Calculate(const double* x) const
		{
			return _operation(_left->Calculate(x), _right->Calculate(x));
		}

		string BinaryOperation::ToString() const
		{
			stringstream ss;

			ss << "(" << _left->ToString() << _opStr << _right->ToString() << ")";

			return ss.str();
		}

		size_t BinaryOperation::CountVariables() const
		{
			return max(_left->CountVariables(), _right->CountVariables());
		}
	}
}
