#pragma once

#include <cmath>


// TODO Use glm instead
namespace cyclone
{
	/**
	 * Holds a vector in 3 dimensions. Four data members are allocated
	 * to ensure alignment in an array.
	 *
	 * @note This class contains a lot of inline methods for basic
	 * mathematics. The implementations are included in the header
	 * file.
	 */
	class Vector3
	{
	public:
		/** Holds the value along the x axis. */
		double x = 0.f;

		/** Holds the value along the y axis. */
		double y = 0.f;

		/** Holds the value along the z axis. */
		double z = 0.f;

	private:
		/** Padding to ensure 4 word alignment. */
		// TODO Why
		double pad = 0.f;

	public:
		/** The default constructor creates a zero vector. */
		Vector3() = default;

		Vector3(double v)
			: x(v), y(v), z(v) {}

		/**
		 * The explicit constructor creates a vector with the given
		 * components.
		 */
		Vector3(const double x, const double y, const double z)
			: x(x), y(y), z(z) {}

		const static Vector3 GRAVITY;
		const static Vector3 UP;

		double operator[](unsigned i) const
		{
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		double& operator[](unsigned i)
		{
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		/** Adds the given vector to this. */
		void operator+=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		/**
		 * Returns the value of the given vector added to this.
		 */
		Vector3 operator+(const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		/** Subtracts the given vector from this. */
		void operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		/**
		 * Returns the value of the given vector subtracted from this.
		 */
		Vector3 operator-(const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		/** Multiplies this vector by the given scalar. */
		void operator*=(const double value)
		{
			x *= value;
			y *= value;
			z *= value;
		}

		/** Returns a copy of this vector scaled the given value. */
		Vector3 operator*(const double value) const
		{
			return Vector3(x * value, y * value, z * value);
		}

		/**
		 * Calculates and returns a component-wise product of this
		 * vector with the given vector.
		 */
		Vector3 componentProduct(const Vector3& vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		/**
		 * Performs a component-wise product with the given vector and
		 * sets this vector to its result.
		 */
		void componentProductUpdate(const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		/**
		 * Calculates and returns the vector product of this vector
		 * with the given vector.
		 */
		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}

		/**
		 * Updates this vector to be the vector product of its current
		 * value and the given vector.
		 */
		void operator %=(const Vector3& vector)
		{
			*this = vectorProduct(vector);
		}

		/**
		 * Calculates and returns the vector product of this vector
		 * with the given vector.
		 */
		Vector3 operator%(const Vector3& vector) const
		{
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}

		/**
		 * Calculates and returns the scalar product of this vector
		 * with the given vector.
		 */
		double scalarProduct(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/**
		 * Calculates and returns the scalar product of this vector
		 * with the given vector.
		 */
		double operator *(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/**
		 * Adds the given vector to this, scaled by the given amount.
		 */
		void addScaledVector(const Vector3& vector, double scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/** Gets the magnitude of this vector. */
		double magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		/** Gets the squared magnitude of this vector. */
		double squareMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		/** Limits the size of the vector to the given maximum. */
		void trim(double size)
		{
			if (squareMagnitude() > size * size)
			{
				normalise();
				x *= size;
				y *= size;
				z *= size;
			}
		}

		/** Turns a non-zero vector into a vector of unit length. */
		Vector3& normalise()
		{
			double l = magnitude();
			if (l > 0)
			{
				(*this) *= ((double)1) / l;
			}
			return *this;
		}

		/** Returns the normalised version of a vector. */
		Vector3 unit() const
		{
			Vector3 result = *this;
			result.normalise();
			return result;
		}

		/** Checks if the two vectors have identical components. */
		bool operator==(const Vector3& other) const
		{
			return x == other.x &&
				y == other.y &&
				z == other.z;
		}

		/** Checks if the two vectors have non-identical components. */
		bool operator!=(const Vector3& other) const
		{
			return !(*this == other);
		}

		/**
		 * Checks if this vector is component-by-component less than
		 * the other.
		 *
		 * @note This does not behave like a single-value comparison:
		 * !(a < b) does not imply (b >= a).
		 */
		bool operator<(const Vector3& other) const
		{
			return x < other.x && y < other.y && z < other.z;
		}

		/**
		 * Checks if this vector is component-by-component less than
		 * the other.
		 *
		 * @note This does not behave like a single-value comparison:
		 * !(a < b) does not imply (b >= a).
		 */
		bool operator>(const Vector3& other) const
		{
			return x > other.x && y > other.y && z > other.z;
		}

		/**
		 * Checks if this vector is component-by-component less than
		 * the other.
		 *
		 * @note This does not behave like a single-value comparison:
		 * !(a <= b) does not imply (b > a).
		 */
		bool operator<=(const Vector3& other) const
		{
			return x <= other.x && y <= other.y && z <= other.z;
		}

		/**
		 * Checks if this vector is component-by-component less than
		 * the other.
		 *
		 * @note This does not behave like a single-value comparison:
		 * !(a <= b) does not imply (b > a).
		 */
		bool operator>=(const Vector3& other) const
		{
			return x >= other.x && y >= other.y && z >= other.z;
		}

		/** Zero all the components of the vector. */
		void clear()
		{
			x = y = z = 0;
		}

		/** Flips all the components of the vector. */
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}
	};
}