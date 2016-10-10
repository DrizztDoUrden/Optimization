// L2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Methods.h"
#include "TestFunctions1.h"
#include "Utilities.h"
#include "Counters.h"



const unsigned int OperationsLimit = 1000;



void ExecuteL2(LinearFunction function, double start, double eps, double min)
{
	auto svenOps = 0u;
	auto dichOps = 0u;
	auto pauelOps = 0u;
	double intStart;
	double intEnd;

	Sven(function, 0, eps, intStart, intEnd, OperationsLimit, svenOps);
	cout << "\tSven\t\t[" << intStart << ";" << intEnd << "] in " << svenOps << " ops with " << GetFunctionCallsResetting() << " func calls. " << endl;
	auto result = Dichotomia(function, intStart, intEnd, eps, OperationsLimit, dichOps);
	cout << "\tDich\t\t" << result << " in " << dichOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t\t";
	ValidateResult(function, result, min, eps);
	cout << endl << "\t";

	try
	{
		result = Pauel(function, intStart, intEnd, eps, OperationsLimit, pauelOps);
		cout << "Pauel\t\t" << result << " in " << pauelOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t\t";
		ValidateResult(function, result, min, eps);
	}
	catch (int)
	{
		cout << "Pauel\t\tstopped in " << pauelOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t\t\t>>Error<<";
	}

	cout << endl;
}



int main()
{
	for (size_t i = 0; i < NumberOfFunctions1; i++)
	{
		cout << "F" << i + 1 + NumberOffset1;
		ExecuteL2(functions1[i], starts1[i], epss1[i], mins1[i]);
	}

    return 0;
}
