#pragma once
#include <functional>
#include "ParsedFunction.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		using UnaryOperator = function<double(double)>;

		class UnaryOperation : public ParsedFunction
		{
			ParsedFunction *_left;
			UnaryOperator _operation;
			string _opStr;

		public:
			UnaryOperation(ParsedFunction *left, UnaryOperator op, string opStr);
			~UnaryOperation();

			double Calculate(const double* x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
