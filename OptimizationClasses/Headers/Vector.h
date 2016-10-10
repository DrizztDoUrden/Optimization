#pragma once
#include <vector>

using namespace std;



namespace Optimization
{
	namespace OptimizationClasses
	{
		class Vector
		{
			vector<double> _coordinates;

		public:
			Vector(vector<double>&);
			Vector(vector<double>& coordinates, size_t size);
			explicit Vector(size_t size);
			Vector(const Vector&);
			~Vector();
			Vector operator=(const Vector&);

			__inline double Absolute() const { return *this * *this; }
			__inline Vector Norm() const { return *this / Absolute(); }
			__inline size_t Size() const { return _coordinates.size(); }
			__inline explicit operator double*() { return _coordinates.data(); }
			__inline explicit operator const double*() const { return _coordinates.data(); }
			__inline double& operator[](size_t index) { return _coordinates[index]; }
			__inline double operator[](size_t index) const { return _coordinates[index]; }

			Vector operator+(const Vector&) const;
			Vector operator-(const Vector&) const;
			Vector operator*(const double) const;
			double operator*(const Vector&) const;
			Vector operator/(double) const;

			void Normalize();

			string ToString() const;
			string ToString(size_t digitsAfterZero) const;
		};
	}
}
