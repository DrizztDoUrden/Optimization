#include "Counters.h"



size_t functionCalls = 0;

void FunctionCalled()
{
	functionCalls++;
}

void ResetCounters()
{
	functionCalls = 0;
}

size_t GetFunctionCallsResetting()
{
	auto t = functionCalls;
	ResetCounters();
	return t;
}
