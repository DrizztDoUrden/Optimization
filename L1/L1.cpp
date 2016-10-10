// L1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Methods.h"
#include "TestFunctions1.h"
#include "Utilities.h"
#include "Counters.h"



using namespace std;



const unsigned int OperationsLimit = 1000;



void ExecuteL1(LinearFunction function, double start, double eps, double min)
{
	auto svenOps = 0u;
	auto fibOps = 0u;
	double intStart;
	double intEnd;

	Sven(function, start, eps, intStart, intEnd, OperationsLimit, svenOps);
	cout << "\tSven\t\t[" << intStart << ";" << intEnd  << "] in " << svenOps << " ops with " << GetFunctionCallsResetting() << " func calls." << endl;
	auto result = Fibonachi(function, intStart, intEnd, eps, OperationsLimit, fibOps);
	cout << "\tFibonachi\t" << result << " in " << fibOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t";
	ValidateResult(function, result, min, eps);
	cout << endl;
}

int main()
{
	for (size_t i = 0; i < NumberOfFunctions1; i++)
	{
		cout << "F" << i + 1 + NumberOffset1 << ".";
		ExecuteL1(functions1[i], starts1[i], epss1[i], mins1[i]);
	}

	return 0;
}
