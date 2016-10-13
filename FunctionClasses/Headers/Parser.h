#pragma once
#include <vector>
#include "ParsedFunction.h"



using namespace std;



namespace Optimization
{
	namespace FunctionClasses
	{
		class Parser
		{
			string _input;

		public:
			explicit Parser(string input);

			ParsedFunction* Parse() const;
		};
	}
}
