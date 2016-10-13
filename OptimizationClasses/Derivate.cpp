#include "Derivate.h"
#include "Vector.h"



namespace Optimization
{
	namespace OptimizationClasses
	{
		Derivate::Derivate(const Function<double>& func, size_t coord, size_t size, double h)
			: _func(func)
			, _coord(coord)
			, _size(size)
			, _h(h)
		{
		}

		double Derivate::Calculate(const double* x) const
		{
			Vector t(x, _size);
			auto result = 0.;

			t[_coord] -= 2 * _h;
			result += _func(t);

			t[_coord] += _h;
			result -= 8 * _func(t);

			t[_coord] += 2 * _h;
			result += 8 * _func(t);

			t[_coord] += _h;
			result = _func(t);

			return result / 12 / _h;
		}
	}
}
