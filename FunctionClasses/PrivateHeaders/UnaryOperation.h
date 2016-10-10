#pragma once
#include <functional>
#include "Function.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		using UnaryOperator = function<double(double)>;

		class UnaryOperation : public Function
		{
			Function *_left;
			UnaryOperator _operation;
			string _opStr;

		public:
			UnaryOperation(Function *left, UnaryOperator op, string opStr);
			~UnaryOperation();

			double Calculate(const Vector& x) const override sealed;
			string ToString() const override sealed;
			size_t CountVariables() const override sealed;
		};
	}
}
