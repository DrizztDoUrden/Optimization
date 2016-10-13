#include "Parser.h"
#include <sstream>
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
		double Neg(double x) { return -x; };

		ParsedFunction* ParseOperation(Lexer& lexer, vector<Token*> &stack);
		ParsedFunction* ParseOperandOrPower(Lexer& lexer, vector<Token*> &stack);

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

		ParsedFunction* ParseOperand(Lexer& lexer, vector<Token*> &stack)
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

				switch (type)
				{
				case Operators::Sin: {
					delete Pop(lexer, stack);
					CheckForUnexpectedEnd(lexer);
					return new UnaryOperation(ParseOperand(lexer, stack), Sin, "sin ");
				}
				case Operators::Cos: {
					delete Pop(lexer, stack);
					CheckForUnexpectedEnd(lexer);
					return new UnaryOperation(ParseOperand(lexer, stack), Cos, "cos ");
				}
				case Operators::Log: {
					delete Pop(lexer, stack);
					CheckForUnexpectedEnd(lexer);
					return new UnaryOperation(ParseOperand(lexer, stack), Log, "log ");
				}
				case Operators::Exp: {
					delete Pop(lexer, stack);
					CheckForUnexpectedEnd(lexer);
					return new UnaryOperation(ParseOperand(lexer, stack), Exp, "exp ");
				}
				default: {
					stringstream ss;
					ss << "Unknown operator at " << start->GetPosition() << ".";
					throw exception(ss.str().c_str());
				}
				}
			}
			case '(': {
				delete Pop(lexer, stack);
				auto t = ParseOperation(lexer, stack);

				if (lexer.Finished() || !Match(lexer, stack, ')'))
				{
					stringstream ss;
					ss << "Expected ) at " << lexer.GetPosition() << ".";
					throw exception(ss.str().c_str());
				}

				return t;
			}
			case '-': {
				delete Pop(lexer, stack);
				auto t = ParseOperandOrPower(lexer, stack);
				return new UnaryOperation(t, Neg, "-");
			}
			default: {
				stringstream ss;
				ss << "Unknown token at " << start->GetPosition() << ".";
				throw exception(ss.str().c_str());
			}
			}
		}

		ParsedFunction* ParseRightOperand(Lexer& lexer, vector<Token*> &stack, ParsedFunction* left, int priority, BinaryOperator leftOp, string leftOpStr)
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

		ParsedFunction* ParseOperandOrPower(Lexer& lexer, vector<Token*> &stack)
		{
			auto op = ParseOperand(lexer, stack);
			auto oper = Peek(lexer, stack);

			if (oper->GetId() != '^')
				return op;

			delete Pop(lexer, stack);
			return ParseRightOperand(lexer, stack, op, 30, Pow, "^");
		}

		ParsedFunction* ParseOperation(Lexer& lexer, vector<Token*> &stack)
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

		ParsedFunction* Parser::Parse() const
		{
			vector<Token*> stack;
			Lexer lexer(_input);

			if (lexer.Finished())
				throw exception("Input is already finished.");

			auto t = ParseOperation(lexer, stack);

			if (!lexer.Finished())
			{
				stringstream ss;
				ss << "Unexpected token at " << lexer.GetPosition() << ".";
				throw exception(ss.str().c_str());
			}

			return t;
		}
	}
}
