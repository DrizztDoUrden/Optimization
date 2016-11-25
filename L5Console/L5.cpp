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

ParsedFunction* Build(const string& input)
{
	return Parser(input).Parse();
}

void ShowHelp()
{
	cout << "Usage:" << endl;
	cout << "L5 [-h[elp]] - show help." << endl;
	cout << "L5 [-f[unction]] <function> [<actions>] - parse function and do actions if any." << endl;
	cout << endl;
	cout << "Actions:" << endl;
	cout << "-mc <point> - preset check for minimum." << endl;
	cout << "-me <number> - preset epsilon for minimum." << endl;
	cout << "-p[oint] <point> - find function value at point." << endl;
	cout << "-m[in[imize]] [-s[tart]] <point> - find function minimum." << endl;
	cout << endl;
	cout << "Points should be in format x1;x2;x3... where x1..xn - numbers." << endl;
}

void Point(size_t argsc, const char** args, size_t offset, streamsize precision, const ParsedFunction& f)
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

	auto fVars = f.CountVariables();

	if (v->Size() < fVars)
	{
		cout << "Point(" << arg << ") size(" << v->Size() << ") is less than function variables count(" << fVars << ")" << endl;

		delete v;
		return;
	}

	cout << "Result at " << v->ToString(precision) << " is " << fixed << f(*v) << defaultfloat << endl;
	delete v;
}

void Minimize(streamsize precision, MinimizationMethod method, const string& methodName, const Function<double>& function, const Vector& start, double eps, const Vector* check)
{
	auto ops = 0u;
	auto calls = 0u;

	try
	{
		auto f = [&function, &calls](const double* x) { calls++; return function(x); };
		auto result = method(f, start, eps, start.Size(), OpsLimit, ops);

		cout << methodName << ": " << Vector(result).ToString(precision) << "\t -> " << fixed << function(result.data()) << defaultfloat << "\tin " << ops << "\tops with " << calls << "\tfunc calls.";

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

void Minimize(size_t argsc, const char** args, size_t offset, streamsize precision, const ParsedFunction& function, const Vector* check = nullptr, double eps = -1)
{
	Vector* start = nullptr;
	string arg(args[offset++]);

	if (arg == "-s" || arg == "-start")
	{
		if (offset == argsc)
		{
			cout << "Wrong usage: start point expected." << endl;
			return;
		}

		arg = args[offset++];
		ToLower(arg);
	}

	try
	{
		start = new Vector(arg.c_str());

		auto fVars = function.CountVariables();

		if (start->Size() < fVars)
		{
			cout << "Point(" << arg << ") size(" << start->Size() << ") is less than function variables count(" << fVars << ")" << endl;

			delete start;
			return;
		}
	}
	catch (const exception& e)
	{
		cout << "Error while parsing start point: " << e.what() << endl;
		return;
	}

	if (eps == -1)
	{
		cout << "Precision must be specified." << endl;
		delete start;
		return;
	}

	Minimize(precision, PrepareParallelTangents(Bolcano), "Partan by Bolcano", function, *start, eps, check);
	delete start;
}

int main(size_t argsc, const char** args)
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

		ParsedFunction* f = nullptr;
		
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

		Vector* minCheck = nullptr;
		auto minEps = -1.;
		streamsize precision = cout.precision();

		while (offset < argsc)
		{
			arg = args[offset++];
			ToLower(arg);
			
			if (arg == "-p" || arg == "-point")
				Point(argsc, args, offset, precision, *f);
			else if (arg == "-m" || arg == "-min" || arg == "-minimize")
				Minimize(argsc, args, offset, precision, *f, minCheck, minEps);
			else if (arg == "-mc")
			{
				if (minCheck != nullptr)
				{
					cout << "Check point has already been specified. New value ignored." << endl;
					continue;
				}

				try
				{
					arg = args[offset++];
					auto tMinCheck = new Vector(arg.c_str());
					auto fVars = f->CountVariables();

					if (tMinCheck->Size() < fVars)
					{
						cout << "Point(" << arg << ") size(" << tMinCheck->Size() << ") is less than function variables count(" << fVars << ")" << endl;
						delete tMinCheck;
					}
					else
						minCheck = tMinCheck;
				}
				catch (const exception& e)
				{
					cout << "Error while parsing check point: " << e.what() << endl;
				}
			}
			else if (arg == "-me")
			{
				char* t;

				arg = args[offset++];
				auto tMinEps = strtol(arg.c_str(), &t, 10);

				if (t == arg.c_str())
					cout << "Precision is not a valid number." << endl;
				else
				{
					precision = tMinEps;
					minEps = pow(10, -tMinEps);
					cout.precision(precision);
				}
			}
		}

		if (minCheck != nullptr) delete minCheck;
		delete f;
		return 0;
	}

	ShowHelp();
    return 0;
}
