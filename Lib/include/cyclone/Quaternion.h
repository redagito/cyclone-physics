#pragma once

// TODO Use glm instead
namespace cyclone
{
	/**
	 * Holds a three degree of freedom orientation.
	 *
	 * Quaternions have
	 * several mathematical properties that make them useful for
	 * representing orientations, but require four items of data to
	 * hold the three degrees of freedom. These four items of data can
	 * be viewed as the coefficients of a complex number with three
	 * imaginary parts. The mathematics of the quaternion is then
	 * defined and is roughly correspondent to the math of 3D
	 * rotations. A quaternion is only a valid rotation if it is
	 * normalised: i.e. it has a length of 1.
	 *
	 * @note Angular velocity and acceleration can be correctly
	 * represented as vectors. Quaternions are only needed for
	 * orientation.
	 */
	class Quaternion
	{
	public:
		union u {
			struct s {
				/**
				 * Holds the real component of the quaternion.
				 */
				real r;

				/**
				 * Holds the first complex component of the
				 * quaternion.
				 */
				real i;

				/**
				 * Holds the second complex component of the
				 * quaternion.
				 */
				real j;

				/**
				 * Holds the third complex component of the
				 * quaternion.
				 */
				real k;
			} sd;

			/**
			 * Holds the quaternion data in array form.
			 */
			real data[4];
		} ud;

		// ... other Quaternion code as before ...

		/**
		 * The default constructor creates a quaternion representing
		 * a zero rotation.
		 */
		Quaternion()
		{
			ud.sd.r = 1;
			ud.sd.i = 0;
			ud.sd.j = 0;
			ud.sd.k = 0;
		}

		/**
		 * The explicit constructor creates a quaternion with the given
		 * components.
		 *
		 * @param r The real component of the rigid body's orientation
		 * quaternion.
		 *
		 * @param i The first complex component of the rigid body's
		 * orientation quaternion.
		 *
		 * @param j The second complex component of the rigid body's
		 * orientation quaternion.
		 *
		 * @param k The third complex component of the rigid body's
		 * orientation quaternion.
		 *
		 * @note The given orientation does not need to be normalised,
		 * and can be zero. This function will not alter the given
		 * values, or normalise the quaternion. To normalise the
		 * quaternion (and make a zero quaternion a legal rotation),
		 * use the normalise function.
		 *
		 * @see normalise
		 */
		Quaternion(const real r, const real i, const real j, const real k)
		{
			ud.sd.r = r;
			ud.sd.i = i;
			ud.sd.j = j;
			ud.sd.k = k;
		}

		/**
		 * Normalises the quaternion to unit length, making it a valid
		 * orientation quaternion.
		 */
		void normalise()
		{
			real d = ud.sd.r * ud.sd.r + ud.sd.i * ud.sd.i + ud.sd.j * ud.sd.j + ud.sd.k * ud.sd.k;

			// Check for zero length quaternion, and use the no-rotation
			// quaternion in that case.
			if (d < real_epsilon) {
				ud.sd.r = 1;
				return;
			}

			d = ((real)1.0) / real_sqrt(d);
			ud.sd.r *= d;
			ud.sd.i *= d;
			ud.sd.j *= d;
			ud.sd.k *= d;
		}

		/**
		 * Multiplies the quaternion by the given quaternion.
		 *
		 * @param multiplier The quaternion by which to multiply.
		 */
		void operator *=(const Quaternion& multiplier)
		{
			Quaternion q = *this;
			ud.sd.r = q.ud.sd.r * multiplier.ud.sd.r - q.ud.sd.i * multiplier.ud.sd.i -
				q.ud.sd.j * multiplier.ud.sd.j - q.ud.sd.k * multiplier.ud.sd.k;
			ud.sd.i = q.ud.sd.r * multiplier.ud.sd.i + q.ud.sd.i * multiplier.ud.sd.r +
				q.ud.sd.j * multiplier.ud.sd.k - q.ud.sd.k * multiplier.ud.sd.j;
			ud.sd.j = q.ud.sd.r * multiplier.ud.sd.j + q.ud.sd.j * multiplier.ud.sd.r +
				q.ud.sd.k * multiplier.ud.sd.i - q.ud.sd.i * multiplier.ud.sd.k;
			ud.sd.k = q.ud.sd.r * multiplier.ud.sd.k + q.ud.sd.k * multiplier.ud.sd.r +
				q.ud.sd.i * multiplier.ud.sd.j - q.ud.sd.j * multiplier.ud.sd.i;
		}

		/**
		 * Adds the given vector to this, scaled by the given amount.
		 * This is used to update the orientation quaternion by a rotation
		 * and time.
		 *
		 * @param vector The vector to add.
		 *
		 * @param scale The amount of the vector to add.
		 */
		void addScaledVector(const Vector3& vector, real scale)
		{
			Quaternion q(0,
				vector.x * scale,
				vector.y * scale,
				vector.z * scale);
			q *= *this;
			ud.sd.r += q.ud.sd.r * ((real)0.5);
			ud.sd.i += q.ud.sd.i * ((real)0.5);
			ud.sd.j += q.ud.sd.j * ((real)0.5);
			ud.sd.k += q.ud.sd.k * ((real)0.5);
		}

		void rotateByVector(const Vector3& vector)
		{
			Quaternion q(0, vector.x, vector.y, vector.z);
			(*this) *= q;
		}
	};
}