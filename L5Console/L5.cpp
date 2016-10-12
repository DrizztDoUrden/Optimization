// L4.cpp : Defines the entry point for the console application.
//

#include <algorithm>
#include <iostream>
#include <string>
#include "Parser.h"
#include "Vector.h"
#include "Methods.h"
#include "Utilities.h"


using namespace Optimization::OptimizationClasses;
using namespace Optimization::FunctionClasses;



const unsigned int OpsLimit = 1000;



__inline void ToLower(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
}

double TestFunction(const double* x)
{
	auto x1 = x[0];
	auto x2 = x[1];

	return pow(x2 - pow(x1, 2), 2) + 100 * pow(1 - pow(x1, 2), 2);
}

Function* Build(const string& input)
{
	Parser p(input);
	auto f = p.Parse();

	cout << "Parsed function: " << f->ToString() << endl;
	cout << "Variables: " << f->CountVariables() << endl;

	return  f;
}

void ShowHelp()
{
	cout << "Usage:" << endl;
	cout << "L5 [-h[elp]] - show help." << endl;
	cout << "L5 [-f[unction]] <function> [<actions>] - parse function and do actions if any." << endl;
	cout << endl;
	cout << "Actions:" << endl;
	cout << "-p[oint] <point>" << endl;
	cout << "-m[in[imize]] -s[tart] <point> -e[ps] <eps> [-c[heck] <minimum check point>] - find function minimum." << endl;
	cout << endl;
	cout << "Points should be in format x1;x2;x3... where x1..xn - numbers." << endl;
}

void Point(size_t argsc, char** args, size_t offset, Function* f)
{
	if (argsc == offset)
	{
		cout << "Wrong usage: there must be coordinates of point after -point/-p" << endl;
		return;
	}

	Vector* v;
	auto arg = args[offset++];

	try
	{
		v = new Vector(arg);
	}
	catch (const exception& e)
	{
		cout << "Error while parsing point: " << e.what() << endl;
		return;
	}

	auto fVars = f->CountVariables();

	if (v->Size() < fVars)
	{
		cout << "Point(" << arg << ") size(" << v->Size() << ") is less than function variables count(" << fVars << ")" << endl;

		delete v;
		return;
	}

	cout << "Result at " << v->ToString() << " is " << (*f)(*v) << endl;
	delete v;
}

void Minimize(MinimizationMethod method, const string& methodName, Function* function, const Vector& start, double eps, const Vector* check)
{
	auto ops = 0u;
	auto calls = 0u;

	try
	{
		auto f = [function, &calls](const double* x) { calls++; return (*function)(x); };
		auto result = method(f, start, eps, start.Size(), OpsLimit, ops);

		cout << methodName << ": " << Vector(result).ToString() << " - " << (*function)(result.data()) << " in " << ops << " ops with " << calls << " func calls.";

		if (check != nullptr)
		{
			cout << "\t";
			ValidateResult(f, result.data(), *check, eps, start.Size());
		}
	}
	catch (int)
	{
		cout << methodName << " stopped in " << ops << " ops with " << calls << " func calls.\t\t>>Error<<";
	}

	cout << endl;
}

void Minimize(size_t argsc, char** args, size_t offset, Function* function)
{
	Vector* start = nullptr;
	Vector* check = nullptr;
	auto eps = -1.;

	while (argsc > offset && (start == nullptr || eps == -1. || check == nullptr))
	{
		string arg = args[offset++];

		ToLower(arg);

		if (arg == "-s" || arg == "-start")
		{
			if (start != nullptr)
			{
				cout << "Start point has already been specified." << endl;
				if (check != nullptr) delete check;
				return;
			}

			arg = args[offset++];

			try
			{
				start = new Vector(arg.c_str());
			}
			catch (const exception& e)
			{
				cout << "Error while parsing start point: " << e.what() << endl;
				return;
			}
		}
		else if (arg == "-c" || arg == "-check")
		{
			if (check != nullptr)
			{
				cout << "Check point has already been specified." << endl;
				if (start != nullptr) delete start;
				return;
			}

			arg = args[offset++];

			try
			{
				check = new Vector(arg.c_str());
			}
			catch (const exception& e)
			{
				cout << "Error while parsing check point: " << e.what() << endl;
				return;
			}
		}
		else if (arg == "-e" || arg == "-eps")
		{
			if (eps != -1)
			{
				cout << "Precision has already been specified." << endl;
				if (start != nullptr) delete start;
				if (check != nullptr) delete check;
				return;
			}

			char* t;

			arg = args[offset++];
			eps = strtod(arg.c_str(), &t);

			if (t == arg.c_str())
			{
				cout << "Precision specified." << endl;

				if (start != nullptr)
					delete start;

				return;
			}
		}
		else break;
	}

	if (start == nullptr)
	{
		cout << "Start point must be specified." << endl;
		return;
	}

	if (eps == -1)
	{
		cout << "Precision must be specified." << endl;
		delete start;
		return;
	}

	Minimize(PrepareParallelTangents(Pauel), "Partan by Pauel", function, *start, eps, check);
	if (check != nullptr) delete check;
	delete start;
}

int main(size_t argsc, char** args)
{
	if (argsc > 1)
	{
		size_t offset = 1;
		string arg(args[offset++]);

		ToLower(arg);

		if (arg == "-h" || arg == "-help")
		{
			ShowHelp();
			return 0;
		}

		if (arg == "-f" || arg == "-function")
		{
			if (offset == argsc)
			{
				cout << "Wrong usage: function expected." << endl;
				return 0;
			}

			arg = args[offset++];
			ToLower(arg);
		}

		Function* f = nullptr;

		cout << "Input: " << arg << endl;
		
		try
		{
			f = Build(arg);
		}
		catch (const exception& e)
		{
			cout << "Error while building function: " << e.what() << endl;
			delete f;
			return 0;
		}

		if (offset == argsc)
		{
			delete f;
			return 0;
		}

		while (offset < argsc)
		{
			arg = args[offset++];
			ToLower(arg);
			
			if (arg == "-p" || arg == "-point")
				Point(argsc, args, offset, f);

			if (arg == "-m" || arg == "-min" || arg == "-minimize")
				Minimize(argsc, args, offset, f);
		}

		delete f;
		return 0;
	}

	ShowHelp();
    return 0;
}
