#include "Vector.h"
#include <string>


namespace Optimization
{
	namespace OptimizationClasses
	{
		Vector::Vector(vector<double>& coordinates)
			: _coordinates(coordinates)
		{
		}

		Vector::Vector(vector<double>& coordinates, size_t size)
			: _coordinates(coordinates)
		{
			_coordinates.resize(size);
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
			string result("(");

			for (size_t i = 0; i < _coordinates.size(); i++)
			{
				if (i > 0)
					result = result.append(";");

				result = result.append(to_string(_coordinates[i]));
			}

			return result.append(")");
		}

		string Vector::ToString(size_t digitsAfterZero) const
		{
			string result("(");
			auto format = string("%.").append(to_string(digitsAfterZero)).append("f");

			for (size_t i = 0; i < _coordinates.size(); i++)
			{
				if (i > 0)
					result = result.append(";");

				char buffer[32];
				sprintf_s(buffer, format.c_str(), _coordinates[i]);
				result = result.append(buffer);
			}

			return result.append(")");
		}
	}
}
