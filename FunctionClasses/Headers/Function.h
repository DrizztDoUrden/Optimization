#pragma once
#include <string>



using namespace std;



namespace Optimization
{
	namespace FunctionClasses
	{
		class Function
		{
		public:
			Function();
			virtual ~Function();

			virtual double Calculate(const double* x) const abstract;
			virtual string ToString() const abstract;
			virtual size_t CountVariables() const abstract;

			__inline double operator()(const double* x) const { return Calculate(x); }
		};
	}
}
