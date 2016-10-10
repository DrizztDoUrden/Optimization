#include "Parser.h"
#include "Constant.h"
#include "UnaryOperation.h"
#include "BinaryOperation.h"
#include "GetVariable.h"
#include "Lexer.h"



namespace Optimization
{
	namespace FunctionClasses
	{
		double Add(double left, double right) { return left + right; }
		double Sub(double left, double right) { return left - right; }
		double Mul(double left, double right) { return left * right; }
		double Div(double left, double right) { return left / right; }
		double Pow(double left, double right) { return pow(left, right); }
		double Sin(double x) { return sin(x); };
		double Cos(double x) { return cos(x); };
		double Log(double x) { return log(x); };
		double Exp(double x) { return exp(x); };

		Function* ParseOperation(Lexer& lexer, vector<Token*> &stack);

		void CheckForUnexpectedEnd(Lexer& lexer)
		{
			if (lexer.Finished())
				throw exception("Unexpected end of expression.");
		}

		Token* Peek(Lexer& lexer, vector<Token*> &stack)
		{
			if (!stack.empty())
				return stack[stack.size() - 1];

			auto t = lexer.Scan();
			stack.push_back(t);
			return t;
		}

		Token* Pop(Lexer& lexer, vector<Token*> &stack)
		{
			if (stack.empty())
				return lexer.Scan();

			auto t = stack[stack.size() - 1];
			stack.pop_back();
			return t;
		}

		bool Match(Lexer& lexer, vector<Token*> &stack, int id)
		{
			if (Peek(lexer, stack)->GetId() != id)
				return false;

			delete Pop(lexer, stack);

			return true;
		}

		Function* ParseOperand(Lexer& lexer, vector<Token*> &stack)
		{
			CheckForUnexpectedEnd(lexer);

			auto start = Peek(lexer, stack);

			switch (start->GetId())
			{
			case static_cast<int>(TokenIds::Number) : {
				auto n = static_cast<Number*>(start)->GetValue();
				delete Pop(lexer, stack);
				return new Constant(n);
			}
			case static_cast<int>(TokenIds::Double) : {
				auto n = static_cast<RealNumber*>(start)->GetValue();
				delete Pop(lexer, stack);
				return new Constant(n);
			}
			case static_cast<int>(TokenIds::Variable) : {
				auto n = static_cast<Variable*>(start)->GetValue();
				delete Pop(lexer, stack);
				return new GetVariable(n - 1);
			}
			case static_cast<int>(TokenIds::Operator) : {
				auto type = static_cast<Operator*>(start)->GetValue();
				delete Pop(lexer, stack);

				CheckForUnexpectedEnd(lexer);

				switch (type)
				{
				case Operators::Sin: return new UnaryOperation(ParseOperand(lexer, stack), Sin, "sin");
				case Operators::Cos: return new UnaryOperation(ParseOperand(lexer, stack), Cos, "cos");
				case Operators::Log: return new UnaryOperation(ParseOperand(lexer, stack), Log, "log");
				case Operators::Exp: return new UnaryOperation(ParseOperand(lexer, stack), Exp, "exp");
				default: throw exception("Unknown operator.");
				}
			}
			case '(': {
				delete Pop(lexer, stack);
				auto t = ParseOperation(lexer, stack);

				if (lexer.Finished() || !Match(lexer, stack, ')'))
					throw exception("Expected ).");

				return t;
			}
			default: throw exception("Unknown token.");
			}
		}

		Function* ParseRightOperand(Lexer& lexer, vector<Token*> &stack, Function* left, int priority, BinaryOperator leftOp, string leftOpStr)
		{
			CheckForUnexpectedEnd(lexer);

			auto rOp = ParseOperand(lexer, stack);

			if (lexer.Finished())
				return new BinaryOperation(left, rOp, leftOp, leftOpStr);

			auto op = Peek(lexer, stack);

			if (priority < 30)
			{
				if (op->GetId() == '^')
				{
					delete Pop(lexer, stack);
					return new BinaryOperation(left, ParseRightOperand(lexer, stack, rOp, 30, Pow, "^"), leftOp, leftOpStr);
				}
			}
			if (priority < 20)
			{
				if (op->GetId() == '*')
				{
					delete Pop(lexer, stack);
					return new BinaryOperation(left, ParseRightOperand(lexer, stack, rOp, 20, Mul, "*"), leftOp, leftOpStr);
				}
				if (op->GetId() == '/')
				{
					delete Pop(lexer, stack);
					return new BinaryOperation(left, ParseRightOperand(lexer, stack, rOp, 20, Div, "/"), leftOp, leftOpStr);
				}
			}

			return new BinaryOperation(left, rOp, leftOp, leftOpStr);
		}

		Function* ParseOperation(Lexer& lexer, vector<Token*> &stack)
		{
			auto left = ParseOperand(lexer, stack);

			while (!lexer.Finished())
			{
				auto op = Peek(lexer, stack);

				switch (op->GetId())
				{
				case '+':
					delete Pop(lexer, stack);
					left = ParseRightOperand(lexer, stack, left, 10, Add, "+");
					break;
				case '-':
					delete Pop(lexer, stack);
					left = ParseRightOperand(lexer, stack, left, 10, Sub, "-");
					break;
				case '*':
					delete Pop(lexer, stack);
					left = ParseRightOperand(lexer, stack, left, 20, Mul, "*");
					break;
				case '/':
					delete Pop(lexer, stack);
					left = ParseRightOperand(lexer, stack, left, 20, Div, "/");
					break;
				case '^':
					delete Pop(lexer, stack);
					left = ParseRightOperand(lexer, stack, left, 30, Pow, "^");
					break;
				default:
					return left;
				}
			}
			
			return left;
		}

		Parser::Parser(string input)
			: _input(input)
		{
		}

		Function* Parser::Parse() const
		{
			vector<Token*> stack;
			Lexer lexer(_input);

			if (lexer.Finished())
				throw exception("Input is already finished.");

			auto t = ParseOperation(lexer, stack);

			if (!lexer.Finished())
				throw exception("Unexpected token.");

			return t;
		}
	}
}
