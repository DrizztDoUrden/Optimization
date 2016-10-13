#pragma once
#include <string>



using namespace std;



namespace Optimization
{
	namespace FunctionClasses
	{
		template<typename TResult>
		class Function abstract
		{
		public:
			Function()
			{
			}

			virtual ~Function()
			{
			}

			virtual TResult Calculate(const double* x) const abstract;
			__inline TResult operator()(const double* x) const { return Calculate(x); }
		};
	}
}
