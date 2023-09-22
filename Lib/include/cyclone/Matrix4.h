#pragma once

#include "cyclone/precision.h"
#include "cyclone/Vector3.h"
#include "cyclone/Quaternion.h"

namespace cyclone
{
    
	/**
	 * Holds a transform matrix, consisting of a rotation matrix and
	 * a position. The matrix has 12 elements, it is assumed that the
	 * remaining four are (0,0,0,1); producing a homogenous matrix.
	 */
	class Matrix4
	{
	public:
		/**
		 * Holds the transform matrix data in array form.
		 */
		real data[12];

		// ... Other Matrix4 code as before ...


		/**
		 * Creates an identity matrix.
		 */
		Matrix4()
		{
			data[1] = data[2] = data[3] = data[4] = data[6] =
				data[7] = data[8] = data[9] = data[11] = 0;
			data[0] = data[5] = data[10] = 1;
		}

		/**
		 * Sets the matrix to be a diagonal matrix with the given coefficients.
		 */
		void setDiagonal(real a, real b, real c)
		{
			data[0] = a;
			data[5] = b;
			data[10] = c;
		}

		/**
		 * Returns a matrix which is this matrix multiplied by the given
		 * other matrix.
		 */
		Matrix4 operator*(const Matrix4& o) const
		{
			Matrix4 result;
			result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) + (o.data[8] * data[2]);
			result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) + (o.data[8] * data[6]);
			result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) + (o.data[8] * data[10]);

			result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) + (o.data[9] * data[2]);
			result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) + (o.data[9] * data[6]);
			result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) + (o.data[9] * data[10]);

			result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) + (o.data[10] * data[2]);
			result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) + (o.data[10] * data[6]);
			result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) + (o.data[10] * data[10]);

			result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) + (o.data[11] * data[2]) + data[3];
			result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) + (o.data[11] * data[6]) + data[7];
			result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) + (o.data[11] * data[10]) + data[11];

			return result;
		}

		/**
		 * Transform the given vector by this matrix.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 operator*(const Vector3& vector) const
		{
			return Vector3(
				vector.x * data[0] +
				vector.y * data[1] +
				vector.z * data[2] + data[3],

				vector.x * data[4] +
				vector.y * data[5] +
				vector.z * data[6] + data[7],

				vector.x * data[8] +
				vector.y * data[9] +
				vector.z * data[10] + data[11]
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
		 * Returns the determinant of the matrix.
		 */
		real getDeterminant() const;

		/**
		 * Sets the matrix to be the inverse of the given matrix.
		 *
		 * @param m The matrix to invert and use to set this.
		 */
		void setInverse(const Matrix4& m);

		/** Returns a new matrix containing the inverse of this matrix. */
		Matrix4 inverse() const
		{
			Matrix4 result;
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
		 * Transform the given direction vector by this matrix.
		 *
		 * @note When a direction is converted between frames of
		 * reference, there is no translation required.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 transformDirection(const Vector3& vector) const
		{
			return Vector3(
				vector.x * data[0] +
				vector.y * data[1] +
				vector.z * data[2],

				vector.x * data[4] +
				vector.y * data[5] +
				vector.z * data[6],

				vector.x * data[8] +
				vector.y * data[9] +
				vector.z * data[10]
			);
		}

		/**
		 * Transform the given direction vector by the
		 * transformational inverse of this matrix.
		 *
		 * @note This function relies on the fact that the inverse of
		 * a pure rotation matrix is its transpose. It separates the
		 * translational and rotation components, transposes the
		 * rotation, and multiplies out. If the matrix is not a
		 * scale and shear free transform matrix, then this function
		 * will not give correct results.
		 *
		 * @note When a direction is converted between frames of
		 * reference, there is no translation required.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 transformInverseDirection(const Vector3& vector) const
		{
			return Vector3(
				vector.x * data[0] +
				vector.y * data[4] +
				vector.z * data[8],

				vector.x * data[1] +
				vector.y * data[5] +
				vector.z * data[9],

				vector.x * data[2] +
				vector.y * data[6] +
				vector.z * data[10]
			);
		}

		/**
		 * Transform the given vector by the transformational inverse
		 * of this matrix.
		 *
		 * @note This function relies on the fact that the inverse of
		 * a pure rotation matrix is its transpose. It separates the
		 * translational and rotation components, transposes the
		 * rotation, and multiplies out. If the matrix is not a
		 * scale and shear free transform matrix, then this function
		 * will not give correct results.
		 *
		 * @param vector The vector to transform.
		 */
		Vector3 transformInverse(const Vector3& vector) const
		{
			Vector3 tmp = vector;
			tmp.x -= data[3];
			tmp.y -= data[7];
			tmp.z -= data[11];
			return Vector3(
				tmp.x * data[0] +
				tmp.y * data[4] +
				tmp.z * data[8],

				tmp.x * data[1] +
				tmp.y * data[5] +
				tmp.z * data[9],

				tmp.x * data[2] +
				tmp.y * data[6] +
				tmp.z * data[10]
			);
		}

		/**
		 * Gets a vector representing one axis (i.e. one column) in the matrix.
		 *
		 * @param i The row to return. Row 3 corresponds to the position
		 * of the transform matrix.
		 *
		 * @return The vector.
		 */
		Vector3 getAxisVector(int i) const
		{
			return Vector3(data[i], data[i + 4], data[i + 8]);
		}

		/**
		 * Sets this matrix to be the rotation matrix corresponding to
		 * the given quaternion.
		 */
		void setOrientationAndPos(const Quaternion& q, const Vector3& pos)
		{
			data[0] = 1 - (2 * q.ud.sd.j * q.ud.sd.j + 2 * q.ud.sd.k * q.ud.sd.k);
			data[1] = 2 * q.ud.sd.i * q.ud.sd.j + 2 * q.ud.sd.k * q.ud.sd.r;
			data[2] = 2 * q.ud.sd.i * q.ud.sd.k - 2 * q.ud.sd.j * q.ud.sd.r;
			data[3] = pos.x;

			data[4] = 2 * q.ud.sd.i * q.ud.sd.j - 2 * q.ud.sd.k * q.ud.sd.r;
			data[5] = 1 - (2 * q.ud.sd.i * q.ud.sd.i + 2 * q.ud.sd.k * q.ud.sd.k);
			data[6] = 2 * q.ud.sd.j * q.ud.sd.k + 2 * q.ud.sd.i * q.ud.sd.r;
			data[7] = pos.y;

			data[8] = 2 * q.ud.sd.i * q.ud.sd.k + 2 * q.ud.sd.j * q.ud.sd.r;
			data[9] = 2 * q.ud.sd.j * q.ud.sd.k - 2 * q.ud.sd.i * q.ud.sd.r;
			data[10] = 1 - (2 * q.ud.sd.i * q.ud.sd.i + 2 * q.ud.sd.j * q.ud.sd.j);
			data[11] = pos.z;
		}

		/**
		 * Fills the given array with this transform matrix, so it is
		 * usable as an open-gl transform matrix. OpenGL uses a column
		 * major format, so that the values are transposed as they are
		 * written.
		 */
		void fillGLArray(float array[16]) const
		{
			array[0] = (float)data[0];
			array[1] = (float)data[4];
			array[2] = (float)data[8];
			array[3] = (float)0;

			array[4] = (float)data[1];
			array[5] = (float)data[5];
			array[6] = (float)data[9];
			array[7] = (float)0;

			array[8] = (float)data[2];
			array[9] = (float)data[6];
			array[10] = (float)data[10];
			array[11] = (float)0;

			array[12] = (float)data[3];
			array[13] = (float)data[7];
			array[14] = (float)data[11];
			array[15] = (float)1;
		}
	};
}