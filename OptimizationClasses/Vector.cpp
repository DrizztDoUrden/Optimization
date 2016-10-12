#include "Vector.h"
#include <string>
#include <sstream>



namespace Optimization
{
	namespace OptimizationClasses
	{
		Vector::Vector()
		{
		}

		Vector::Vector(const char* s)
		{
			while (true)
			{
				char* t;
				auto d = strtod(s, &t);

				if (s != t)
					_coordinates.push_back(d);

				if (*t == '\0')
					break;

				if (*t != ';')
					throw exception("Wrong vector");

				s = t + 1;
			}
		}

		Vector::Vector(vector<double>& coordinates)
			: _coordinates(coordinates)
		{
		}

		Vector::Vector(const double* coordinates, size_t size)
			: _coordinates(size)
		{
			for (size_t i = 0; i < size; i++)
				_coordinates[i] = coordinates[i];
		}

		Vector::Vector(size_t size)
			: _coordinates(size)
		{
		}

		Vector::Vector(const Vector& other)
			: _coordinates(other._coordinates)
		{
		}

		Vector::~Vector()
		{
		}

		Vector Vector::operator=(const Vector& other)
		{
			for (size_t i = 0; i < _coordinates.size(); i++)
				_coordinates[i] = other[i];

			return Vector(_coordinates);
		}

		Vector Vector::operator+(const Vector& other) const
		{
			vector<double> coords(_coordinates.size());

			for (size_t i = 0; i < _coordinates.size(); i++)
				coords[i] = _coordinates[i] + other[i];

			return Vector(coords);
		}

		Vector Vector::operator-(const Vector& other) const
		{
			vector<double> coords(_coordinates.size());

			for (size_t i = 0; i < _coordinates.size(); i++)
				coords[i] = _coordinates[i] - other[i];

			return Vector(coords);
		}

		Vector Vector::operator*(double other) const
		{
			vector<double> coords(_coordinates.size());

			for (size_t i = 0; i < _coordinates.size(); i++)
				coords[i] = _coordinates[i] * other;

			return Vector(coords);
		}

		double Vector::operator*(const Vector& other) const
		{
			auto result = .0;

			for (size_t i = 0; i < _coordinates.size(); i++)
				result += _coordinates[i] * other[i];

			return result;
		}

		Vector Vector::operator/(double other) const
		{
			vector<double> coords(_coordinates.size());

			for (size_t i = 0; i < _coordinates.size(); i++)
				coords[i] = _coordinates[i] / other;

			return Vector(coords);
		}

		void Vector::Normalize()
		{
			auto length = Absolute();

			for (size_t i = 0; i < _coordinates.size(); i++)
				_coordinates[i] /= length;
		}

		string Vector::ToString() const
		{
			stringstream ss;

			ss << "(";

			for (size_t i = 0; i < _coordinates.size(); i++)
			{
				if (i > 0)
					ss << ";";

				ss << _coordinates[i];
			}

			ss << ")";

			return ss.str();
		}
	}
}
