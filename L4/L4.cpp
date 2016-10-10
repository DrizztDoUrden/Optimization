// L4.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "TestFunctions3.h"
#include "Methods.h"
#include "Utilities.h"
#include "Counters.h"



const unsigned int OpsLimit = 1000;



void ExecuteL4(MinimizationMethod method, NonlinearFunction function, double start[], double min[], double eps, size_t size)
{
	auto ops = 0u;

	try
	{
		auto result = method(function, start, eps, size, OpsLimit, ops);

		cout << "\tParallel tangents: (";

		for (size_t i = 0; i < size; i++)
		{
			if (i > 0)
				cout << ";";

			cout << result[i];
		}

		cout << ") in " << ops << " ops with " << GetFunctionCallsResetting() << " func calls.\t";

		if (size < 3)
			cout << "\t";

		ValidateResult(function, result.data(), min, eps, size);
	}
	catch (int)
	{
		cout << "Partan\t\tstopped in " << ops << " ops with " << GetFunctionCallsResetting() << " func calls.\t\t>>Error<<";
	}

	cout << endl;
}



int main()
{
	auto partanByPauel = PrepareParallelTangents(Pauel);

	for (size_t i = 0; i < NumberOfFunctions3; i++)
	{
		cout << "F" << NumberOffset3 + i + 1 << ".";
		
		for (size_t j = 0; j < startsNumbers3[i]; j++)
		{
			cout << "\tS" << j << ".";
			ExecuteL4(partanByPauel, functions3[i], starts3[i][j], mins3[i], epss3[i], dims3[i]);
		}
	}

    return 0;
}
