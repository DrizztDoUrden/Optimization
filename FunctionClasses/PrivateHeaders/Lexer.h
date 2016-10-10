#pragma once
#include <string>
#include "Token.h"



using namespace std;



namespace Optimization
{
	namespace FunctionClasses
	{
		class Lexer
		{
			string _input;
			size_t _position;

			__inline char Peek() const { return _input[_position]; }
			__inline char Pop() { return _input[_position++]; }

			bool Match(char c);
			bool Match(const string& s);

			void SkipSpaces();
			Token* ParseDouble(int start, size_t startPos);
			Token* ParseNumber();
			Token* ParseVar();
			Token* ParseOp();
			Token* ParseRest();

		public:
			explicit Lexer(string input);

			bool Finished();

			Token* Scan();
		};
	}
}
