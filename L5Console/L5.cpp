// L4.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "Parser.h"
#include "Vector.h"


using namespace Optimization::OptimizationClasses;
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



double TestFunction(const double* x)
{
	auto x1 = x[0];
	auto x2 = x[1];

	return -pow(x2 - pow(x1, 2), 2) + 100 * pow(1 - pow(x1, 2), 2);
}

void Build(string input)
{
	Parser p(input);
	auto f = p.Parse();

	cout << "Input:" << input << endl;
	cout << "Output: " << f->ToString() << endl;
	cout << "Variables: " << f->CountVariables() << endl;

	delete f;
}

int main(int argsc, char** args)
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

	if (argsc > 1)
	{
		string arg1(args[1]);

		if (arg1 == "-build")

		return 0;
	}

	string input("-(x2 - x1^2)^2 + 100*(1 - x1^2)^2");
	const auto testStart = -5.;
	const auto testEnd = 5.;
	const auto stepPart = .01;
	const auto step = (testEnd - testStart) * stepPart;
	const auto eps = pow(10, -10);

	Parser p(input);

	double x[2];
	auto f = p.Parse();
	auto valid = true;

	cout << "Input:" << input << endl;
	cout << "Output: " << f->ToString() << endl;
	cout << "Variables: " << f->CountVariables() << endl;

	for (x[0] = testStart; valid && x[0] < testEnd; x[0] += step)
		for (x[1] = testStart; valid && x[1] < testEnd; x[1] += step)
			if ((valid = (abs((*f)(x) - TestFunction(x)) > eps)))
				cout << "Error at: " << Vector(x, 2).ToString(0) << " - \t" << (*f)(x) << " != " << TestFunction(x) << endl;

	cout << "All tests valid on (" << testStart << ".." << testEnd << ";" << testStart << ".." << testEnd << ")." << endl;

	delete f;

    return 0;
}
