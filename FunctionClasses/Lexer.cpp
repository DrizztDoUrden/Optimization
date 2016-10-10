#include "Lexer.h"



#define ReturnIfNotNull(expr)\
{\
	auto temp = (expr);\
	if (temp != nullptr)\
		return temp;\
}



namespace Optimization
{
	namespace FunctionClasses
	{
		bool Lexer::Match(char c)
		{
			if (Peek() != c)
				return false;

			Pop();

			return true;
		}

		bool Lexer::Match(const string& s)
		{
			if (s.length() >= _input.length() - _position)
				return false;

			for (size_t i = 0; i < s.length(); i++)
			{
				if (!Match(s[i]))
				{
					_position -= i;
					return false;
				}
			}

			return true;
		}

		void Lexer::SkipSpaces()
		{
			while (_input.length() > _position && (Match(' ') || Match('\t')));
		}

		Token* Lexer::ParseDouble(int start, size_t startPos)
		{
			if (Finished() || !Match('.'))
				return nullptr;
			
			double v = 0, p = .1;

			while (!Finished() && Peek() >= '0' && Peek() <= '9')
			{
				v += (Pop() - '0') * p;
				p /= 10;
			}

			return new RealNumber(v + start, startPos);
		}

		Token* Lexer::ParseNumber()
		{
			if (Peek() < '0' || Peek() > '9')
				return nullptr;

			auto v = 0;
			auto startPos = _position;

			while (!Finished() && Peek() >= '0' && Peek() <= '9')
			{
				v = v * 10 + (Pop() - '0');
				ReturnIfNotNull(ParseDouble(v, startPos));
			}

			return new Number(v, startPos);
		}

		Token* Lexer::ParseVar()
		{
			auto startPos = _position;

			if (!Match('x'))
				return nullptr;

			auto v = 0;

			while (!Finished() && Peek() >= '0' && Peek() <= '9')
				v = v * 10 + (Pop() - '0');

			if (v == 0)
				throw exception("Variable number must be not less then 1.");

			return new Variable(v, startPos);
		}

		Token* Lexer::ParseOp()
		{
			auto startPos = _position;

			if (Match("sin")) return new Operator(Operators::Sin, startPos);
			if (Match("cos")) return new Operator(Operators::Cos, startPos);
			if (Match("log")) return new Operator(Operators::Log, startPos);
			if (Match("exp")) return new Operator(Operators::Exp, startPos);

			return nullptr;
		}

		Token* Lexer::ParseRest()
		{
			auto startPos = _position;

			return new Token(Pop(), startPos);
		}

		Lexer::Lexer(string input)
			: _input(input)
			, _position(0)
		{
		}

		bool Lexer::Finished()
		{
			SkipSpaces();
			return _input.length() <= _position;
		}

		Token* Lexer::Scan()
		{
			if (Finished())
				throw exception("Already finished.");

			ReturnIfNotNull(ParseDouble(0, _position));
			ReturnIfNotNull(ParseNumber());
			ReturnIfNotNull(ParseVar());
			ReturnIfNotNull(ParseOp());

			return ParseRest();
		}
	}
}
