#pragma once

#include "cyclone/Vector3.h"
#include "cyclone/Quaternion.h"

namespace cyclone {
    
	/**
	 * Holds an inertia tensor, consisting of a 3x3 row-major matrix.
	 * This matrix is not padding to produce an aligned structure, since
	 * it is most commonly used with a mass (single real) and two
	 * damping coefficients to make the 12-element characteristics array
	 * of a rigid body.
	 */
	class Matrix3
	{
	public:
		/**
		 * Holds the tensor matrix data in array form.
		 */
		real data[9];

		// ... Other Matrix3 code as before ...

		/**
		 * Creates a new matrix.
		 */
		Matrix3()
		{
			data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
				data[6] = data[7] = data[8] = 0;
		}

		/**
		 * Creates a new matrix with the given three vectors making
		 * up its columns.
		 */
		Matrix3(const Vector3& compOne, const Vector3& compTwo,
			const Vector3& compThree)
		{
			setComponents(compOne, compTwo, compThree);
		}

		/**
		 * Creates a new matrix with explicit coefficients.
		 */
		Matrix3(real c0, real c1, real c2, real c3, real c4, real c5,
			real c6, real c7, real c8)
		{
			data[0] = c0; data[1] = c1; data[2] = c2;
			data[3] = c3; data[4] = c4; data[5] = c5;
			data[6] = c6; data[7] = c7; data[8] = c8;
		}

		/**
		 * Sets the matrix to be a diagonal matrix with the given
		 * values along the leading diagonal.
		 */
		void setDiagonal(real a, real b, real c)
		{
			setInertiaTensorCoeffs(a, b, c);
		}

		/**
		 * Sets the value of the matrix from inertia tensor values.
		 */
		void setInertiaTensorCoeffs(real ix, real iy, real iz,
			real ixy = 0, real ixz = 0, real iyz = 0)
		{
			data[0] = ix;
			data[1] = data[3] = -ixy;
			data[2] = data[6] = -ixz;
			data[4] = iy;
			data[5] = data[7] = -iyz;
			data[8] = iz;
		}

		/**
		 * Sets the value of the matrix as an inertia tensor of
		 * a rectangular block aligned with the body's coordinate
		 * system with the given axis half-sizes and mass.
		 */
		void setBlockInertiaTensor(const Vector3& halfSizes, real mass)
		{
			Vector3 squares = halfSizes.componentProduct(halfSizes);
			setInertiaTensorCoeffs(0.3f * mass * (squares.y + squares.z),
				0.3f * mass * (squares.x + squares.z),
				0.3f * mass * (squares.x + squares.y));
		}

		/**
		 * Sets the matrix to be a skew symmetric matrix based on
		 * the given vector. The skew symmetric matrix is the equivalent
		 * of the vector product. So if a,b are vectors. a x b = A_s b
		 * where A_s is the skew symmetric form of a.
		 */
		void setSkewSymmetric(const Vector3 vector)
		{
			data[0] = data[4] = data[8] = 0;
			data[1] = -vector.z;
			data[2] = vector.y;
			data[3] = vector.z;
			data[5] = -vector.x;
			data[6] = -vector.y;
			data[7] = vector.x;
		}

		/**
		 * Sets the matrix values from the given three vector components.
		 * These are arranged as the three columns of the vector.
		 */
		void setComponents(const Vector3& compOne, const Vector3& compTwo,
			const Vector3& compThree)
		{
			data[0] = compOne.x;
			data[1] = compTwo.x;
			data[2] = compThree.x;
			data[3] = compOne.y;
			data[4] = compTwo.y;
			data[5] = compThree.y;
			data[6] = compOne.z;
			data[7] = compTwo.z;
			data[8] = compThree.z;

		}

		/**
		 * Transform the given vector by this matrix.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 operator*(const Vector3& vector) const
		{
			return Vector3(
				vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
				vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
				vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
			);
		}

		/**
		 * Transform the given vector by this matrix.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 transform(const Vector3& vector) const
		{
			return (*this) * vector;
		}

		/**
		 * Transform the given vector by the transpose of this matrix.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 transformTranspose(const Vector3& vector) const
		{
			return Vector3(
				vector.x * data[0] + vector.y * data[3] + vector.z * data[6],
				vector.x * data[1] + vector.y * data[4] + vector.z * data[7],
				vector.x * data[2] + vector.y * data[5] + vector.z * data[8]
			);
		}

		/**
		 * Gets a vector representing one row in the matrix.
		 *
		 * @param i The row to return.
		 */
		Vector3 getRowVector(int i) const
		{
			return Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
		}

		/**
		 * Gets a vector representing one axis (i.e. one column) in the matrix.
		 *
		 * @param i The row to return.
		 *
		 * @return The vector.
		 */
		Vector3 getAxisVector(int i) const
		{
			return Vector3(data[i], data[i + 3], data[i + 6]);
		}

		/**
		 * Sets the matrix to be the inverse of the given matrix.
		 *
		 * @param m The matrix to invert and use to set this.
		 */
		void setInverse(const Matrix3& m)
		{
			real t4 = m.data[0] * m.data[4];
			real t6 = m.data[0] * m.data[5];
			real t8 = m.data[1] * m.data[3];
			real t10 = m.data[2] * m.data[3];
			real t12 = m.data[1] * m.data[6];
			real t14 = m.data[2] * m.data[6];

			// Calculate the determinant
			real t16 = (t4 * m.data[8] - t6 * m.data[7] - t8 * m.data[8] +
				t10 * m.data[7] + t12 * m.data[5] - t14 * m.data[4]);

			// Make sure the determinant is non-zero.
			if (t16 == (real)0.0f) return;
			real t17 = 1 / t16;

			data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7]) * t17;
			data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7]) * t17;
			data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4]) * t17;
			data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6]) * t17;
			data[4] = (m.data[0] * m.data[8] - t14) * t17;
			data[5] = -(t6 - t10) * t17;
			data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6]) * t17;
			data[7] = -(m.data[0] * m.data[7] - t12) * t17;
			data[8] = (t4 - t8) * t17;
		}

		/** Returns a new matrix containing the inverse of this matrix. */
		Matrix3 inverse() const
		{
			Matrix3 result;
			result.setInverse(*this);
			return result;
		}

		/**
		 * Inverts the matrix.
		 */
		void invert()
		{
			setInverse(*this);
		}

		/**
		 * Sets the matrix to be the transpose of the given matrix.
		 *
		 * @param m The matrix to transpose and use to set this.
		 */
		void setTranspose(const Matrix3& m)
		{
			data[0] = m.data[0];
			data[1] = m.data[3];
			data[2] = m.data[6];
			data[3] = m.data[1];
			data[4] = m.data[4];
			data[5] = m.data[7];
			data[6] = m.data[2];
			data[7] = m.data[5];
			data[8] = m.data[8];
		}

		/** Returns a new matrix containing the transpose of this matrix. */
		Matrix3 transpose() const
		{
			Matrix3 result;
			result.setTranspose(*this);
			return result;
		}

		/**
		 * Returns a matrix which is this matrix multiplied by the given
		 * other matrix.
		 */
		Matrix3 operator*(const Matrix3& o) const
		{
			return Matrix3(
				data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
				data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
				data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],

				data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
				data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
				data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],

				data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
				data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
				data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
			);
		}

		/**
		 * Multiplies this matrix in place by the given other matrix.
		 */
		void operator*=(const Matrix3& o)
		{
			real t1;
			real t2;
			real t3;

			t1 = data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6];
			t2 = data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7];
			t3 = data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8];
			data[0] = t1;
			data[1] = t2;
			data[2] = t3;

			t1 = data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6];
			t2 = data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7];
			t3 = data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8];
			data[3] = t1;
			data[4] = t2;
			data[5] = t3;

			t1 = data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6];
			t2 = data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7];
			t3 = data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8];
			data[6] = t1;
			data[7] = t2;
			data[8] = t3;
		}

		/**
		 * Multiplies this matrix in place by the given scalar.
		 */
		void operator*=(const real scalar)
		{
			data[0] *= scalar; data[1] *= scalar; data[2] *= scalar;
			data[3] *= scalar; data[4] *= scalar; data[5] *= scalar;
			data[6] *= scalar; data[7] *= scalar; data[8] *= scalar;
		}

		/**
		 * Does a component-wise addition of this matrix and the given
		 * matrix.
		 */
		void operator+=(const Matrix3& o)
		{
			data[0] += o.data[0]; data[1] += o.data[1]; data[2] += o.data[2];
			data[3] += o.data[3]; data[4] += o.data[4]; data[5] += o.data[5];
			data[6] += o.data[6]; data[7] += o.data[7]; data[8] += o.data[8];
		}

		/**
		 * Sets this matrix to be the rotation matrix corresponding to
		 * the given quaternion.
		 */
		void setOrientation(const Quaternion& q)
		{
			data[0] = 1 - (2 * q.ud.sd.j * q.ud.sd.j + 2 * q.ud.sd.k * q.ud.sd.k);
			data[1] = 2 * q.ud.sd.i * q.ud.sd.j + 2 * q.ud.sd.k * q.ud.sd.r;
			data[2] = 2 * q.ud.sd.i * q.ud.sd.k - 2 * q.ud.sd.j * q.ud.sd.r;
			data[3] = 2 * q.ud.sd.i * q.ud.sd.j - 2 * q.ud.sd.k * q.ud.sd.r;
			data[4] = 1 - (2 * q.ud.sd.i * q.ud.sd.i + 2 * q.ud.sd.k * q.ud.sd.k);
			data[5] = 2 * q.ud.sd.j * q.ud.sd.k + 2 * q.ud.sd.i * q.ud.sd.r;
			data[6] = 2 * q.ud.sd.i * q.ud.sd.k + 2 * q.ud.sd.j * q.ud.sd.r;
			data[7] = 2 * q.ud.sd.j * q.ud.sd.k - 2 * q.ud.sd.i * q.ud.sd.r;
			data[8] = 1 - (2 * q.ud.sd.i * q.ud.sd.i + 2 * q.ud.sd.j * q.ud.sd.j);
		}

		/**
		 * Interpolates a couple of matrices.
		 */
		static Matrix3 linearInterpolate(const Matrix3& a, const Matrix3& b, real prop);
	};
}