#include "Gradient.h"



namespace Optimization
{
	namespace OptimizationClasses
	{
		Gradient::Gradient(const Function<double>& func, size_t size, double h)
		{
			for (size_t i = 0; i < size; i++)
				_derivates.push_back(Derivate(func, i, size, h));
		}

		Vector Gradient::Calculate(const double* x) const
		{
			Vector result(_derivates.size());

			for (size_t i = 0; i < _derivates.size(); i++)
				result[i] = _derivates[i](x);

			return result;
		}
	}
}
