// L4.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "Parser.h"



using namespace Optimization::FunctionClasses;



const unsigned int OpsLimit = 1000;



/*void ExecuteL4(MinimizationMethod method, NonlinearFunction function, double start[], double min[], double eps, size_t size)
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

		cout << ") in " << ops << " ops\t";

		if (size < 3)
			cout << "\t";

		ValidateResult(function, result.data(), min, eps, size);
	}
	catch (int)
	{
		cout << "Partan\t\tstopped in " << ops << " ops.\t\t>>Error<<";
	}

	cout << endl;
}*/



double TestFunction(const Vector& x)
{
	auto x1 = x[0];
	auto x2 = x[1];

	return pow(x2 - pow(x1, 2), 2) + 100 * pow(1 - pow(x1, 2), 2);
}

int main()
{
	/*auto partanByPauel = PrepareParallelTangents(Pauel);

	for (size_t i = 0; i < NumberOfFunctions3; i++)
	{
		cout << "F" << NumberOffset3 + i + 1 << ".";

		for (size_t j = 0; j < startsNumbers3[i]; j++)
		{
			cout << "\tS" << j << ".";
			ExecuteL4(partanByPauel, functions3[i], starts3[i][j], mins3[i], epss3[i], dims3[i]);
		}
	}*/

	string input("(x2 - x1^2)^2 + 100*(1 - x1^2)^2");
	Parser p(input);

	auto f = p.Parse();

	cout << "Input:" << input << endl;
	cout << "Output: " << f->ToString() << endl;
	cout << "Variables: " << f->CountVariables() << endl;

	for (double x0 = -5; x0 < 5; x0 += .01)
		for (double x1 = -5; x1 < 5; x1 += .01)
		{
			Vector x(2);

			x[0] = x0;
			x[1] = x1;

			if (abs((*f)(x) - TestFunction(x)) > pow(10, -10))
				cout << "Error at: " << x.ToString(0) << " - \t" << (*f)(x) << " != " << TestFunction(x) << endl;
		}

	cout << "All tests valid on (-5 - 5;-5 - 5)." << endl;

	delete f;

    return 0;
}
