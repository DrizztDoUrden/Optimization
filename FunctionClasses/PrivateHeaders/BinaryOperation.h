#pragma once
#include <functional>
#include "ParsedFunction.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		using BinaryOperator = function<double(double, double)>;

		class BinaryOperation : public ParsedFunction
		{
			ParsedFunction *_left, *_right;
			BinaryOperator _operation;
			string _opStr;

		public:
			BinaryOperation(ParsedFunction *left, ParsedFunction *right, BinaryOperator op, string opStr);
			~BinaryOperation();

			double Calculate(const double* x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
