// L3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Methods.h"
#include "TestFunctions2.h"
#include "Utilities.h"
#include "Counters.h"



const unsigned int OperationsLimit = 1000;



void ExecuteL3(NonlinearFunction function, double start[], double direction[], double eps, double min[], size_t size)
{
	auto function1d = LinearizeFunction(function, start, direction, size);
	auto svenOps = 0u;
	auto bolcOps = 0u;
	auto davidOps = 0u;
	double intStart;
	double intEnd;

	Sven(function1d, 0, eps, intStart, intEnd, OperationsLimit, svenOps);
	cout << "\tSven\t\t[" << intStart << ";" << intEnd << "] in " << svenOps << " ops with " << GetFunctionCallsResetting() << " func calls. " << endl << "\t";

	try
	{
		auto result = Bolcano(function1d, intStart, intEnd, eps, OperationsLimit, bolcOps);
		auto delinResult = DelinearizeCoordinate(start, direction, Dims2, result);

		cout << "Bolcano\t\t(" << delinResult[0] << ";" << delinResult[1] << ") in " << bolcOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t";
		ValidateResult(function, delinResult.data(), min, eps, size);
	}
	catch (int)
	{
		cout << "Bolcano\t\tstopped in " << bolcOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t\t>>Error<<";
	}

	cout << endl << "\t";

	try
	{
		auto result = Davidon(function1d, intStart, intEnd, eps, OperationsLimit, davidOps);
		auto delinResult = DelinearizeCoordinate(start, direction, Dims2, result);

		cout << "Davidon\t\t(" << delinResult[0] << ";" << delinResult[1] << ") in " << davidOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t";
		ValidateResult(function, delinResult.data(), min, eps, size);
	}
	catch (...)
	{
		cout << "Davidon\t\tstopped in " << davidOps << " ops with " << GetFunctionCallsResetting() << " func calls.\t\t>>Error<<";
	}

	cout << endl;
}



int main()
{
	for (size_t i = 0; i < NumberOfFunctions2; i++)
	{
		cout << "F" << NumberOffset2 + i + 1;
		ExecuteL3(functions2[i], starts2[i], directions2[i], epss2[i], mins2[i], Dims2);
	}

    return 0;
}
