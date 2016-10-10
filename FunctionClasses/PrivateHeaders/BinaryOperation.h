#pragma once
#include <functional>
#include "Function.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		using BinaryOperator = function<double(double, double)>;

		class BinaryOperation : public Function
		{
			Function *_left, *_right;
			BinaryOperator _operation;
			string _opStr;

		public:
			BinaryOperation(Function *left, Function *right, BinaryOperator op, string opStr);
			~BinaryOperation();

			double Calculate(const Vector& x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
