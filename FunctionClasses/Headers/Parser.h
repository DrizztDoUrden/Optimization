#pragma once
#include <vector>
#include "Function.h"



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

			Function* Parse() const;
		};
	}
}
