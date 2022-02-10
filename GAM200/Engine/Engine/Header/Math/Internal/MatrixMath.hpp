/* Start Header**********************************************************************************/
/*
@file    MatrixMath.hpp
@author  tan wei ling felicia	weilingfelicia.tan@digipen.edu	100%
@date    02/10/2021
\brief

Math to be used with Matrix as parameter

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "Engine/Header/Math/Matrix/Matrix3.hpp"
#include "Engine/Header/Math/Matrix/Matrix4.hpp"

#include "Engine/Header/Math/Internal/ConstantsMath.hpp"

namespace Engine {
	namespace DreamMath {
		namespace MI = MathImplementation;

		/*-------------------------------------------------------------------------------------------------------------------
		Identity Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
		This function sets the matrix pResult to the identity matrix
		*/
		/**************************************************************************/
		template <typename T>
		void Identity(MI::Matrix3<T>& pResult) {
			for (int i{ 0 }; i < 9; ++i) {
				pResult.m[i] = 0;
				if (!(i % 4)) pResult.m[i] = 1;
			}
		}
		/**************************************************************************/
		/*!
		This function sets the matrix pResult to the identity matrix
		*/
		/**************************************************************************/
		template <typename T>
		void Identity(MI::Matrix4<T>& pResult) {
			for (int i{ 0 }; i < 16; ++i) {
				pResult.m[i] = 0;
				if (!(i % 5)) pResult.m[i] = 1;
			}
		}

		
		/*-------------------------------------------------------------------------------------------------------------------
		Translation Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
			This function creates a translation matrix from x & y
			and saves it in pResult
			0 3 6
			1 4 7
			2 5 8
		 */
		 /**************************************************************************/
		template <typename T>
		void Translate(MI::Matrix3<T>& pResult, float x, float y) {
			Identity(pResult);
			pResult.m[6] = x;
			pResult.m[7] = y;
		}

		/**************************************************************************/
		/*!
			This function creates a translation matrix from x & y
			and saves it in pResult
			0 4 8  12
			1 5 9  13
			2 6 10 14
			3 7 11 15
		 */
		 /**************************************************************************/
		template <typename T>
		void Translate(MI::Matrix4<T>& pResult, float x, float y, float z) {
			Identity(pResult);
			pResult.m[12] = x;
			pResult.m[13] = y;
			pResult.m[14] = z;
		}


		/*-------------------------------------------------------------------------------------------------------------------
		Scaling Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
			This function creates a scaling matrix from x & y
			and saves it in pResult
			0 3 6
			1 4 7
			2 5 8
		 */
		 /**************************************************************************/
		template <typename T>
		void Scale(MI::Matrix3<T>& pResult, float x, float y) {
			Identity(pResult);
			pResult.m[0] = x;
			pResult.m[4] = y;
		}

		/**************************************************************************/
		/*!
			This function creates a scaling matrix from x & y
			and saves it in pResult
			0 4 8  12
			1 5 9  13
			2 6 10 14
			3 7 11 15
		 */
		 /**************************************************************************/
		template <typename T>
		void Scale(MI::Matrix4<T>& pResult, float x, float y, float z) {
			Identity(pResult);
			pResult.m[0] = x;
			pResult.m[5] = y;
			pResult.m[10] = z;
		}

		
		/*-------------------------------------------------------------------------------------------------------------------
		Rotation radian Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in radian. Save the resultant matrix in pResult.
			0 3 6
			1 4 7
			2 5 8
		 */
		 /**************************************************************************/
		template <typename T>
		void RotRad(MI::Matrix3<T>& pResult, float angle) {
			Identity(pResult);
			pResult.m[0] = pResult.m[4] = (float)cos(angle);
			pResult.m[1] = pResult.m[3] = (float)sin(angle);
			pResult.m[3] = -pResult.m[3];
		}

		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in radian. Save the resultant matrix in pResult.
			Rotate X axis
			0 4 8  12
			1 5 9  13
			2 6 10 14
			3 7 11 15
		 */
		 /**************************************************************************/
		template <typename T>
		void RotRadX(MI::Matrix4<T>& pResult, float angle) {
			Identity(pResult);
			pResult.m[5] = pResult.m[10] = (float)cos(angle);
			pResult.m[6] = pResult.m[9] = (float)sin(angle);
			pResult.m[9] = -pResult.m[9];
		}

		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in radian. Save the resultant matrix in pResult.
			Rotate Y axis
			0 4 8  12
			1 5 9  13
			2 6 10 14
			3 7 11 15
		 */
		 /**************************************************************************/
		template <typename T>
		void RotRadY(MI::Matrix4<T>& pResult, float angle) {
			Identity(pResult);
			pResult.m[0] = pResult.m[10] = (float)cos(angle);
			pResult.m[2] = pResult.m[8] = (float)sin(angle);
			pResult.m[2] = -pResult.m[2];
		}

		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in radian. Save the resultant matrix in pResult.
			Rotate Z axis
			0 4 8  12
			1 5 9  13
			2 6 10 14
			3 7 11 15
		 */
		 /**************************************************************************/
		template <typename T>
		void RotRadZ(MI::Matrix4<T>& pResult, float angle) {
			Identity(pResult);
			pResult.m[0] = pResult.m[5] = (float)cos(angle);
			pResult.m[1] = pResult.m[4] = (float)sin(angle);
			pResult.m[4] = -pResult.m[4];
		}

		
		/*-------------------------------------------------------------------------------------------------------------------
		Rotation degree Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in degree. Save the resultant matrix in pResult.
		 */
		 /**************************************************************************/
		template <typename T>
		void RotDeg(MI::Matrix3<T>& pResult, float angle) {
			Identity(pResult);
			RotRad(pResult, pi<T>() / 180.f * angle);
		}

		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in degree. Save the resultant matrix in pResult.
			Rotate X axis
		 */
		 /**************************************************************************/
		template <typename T>
		void RotDegX(MI::Matrix4<T>& pResult, float angle) {
			Identity(pResult);
			RotRadX(pResult, pi<T>() / 180.f * angle);
		}

		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in degree. Save the resultant matrix in pResult.
			Rotate Y axis
		 */
		 /**************************************************************************/
		template <typename T>
		void RotDegY(MI::Matrix4<T>& pResult, float angle) {
			Identity(pResult);
			RotRadY(pResult, pi<T>() / 180.f * angle);
		}

		/**************************************************************************/
		/*!
			This matrix creates a rotation matrix from "angle" whose value
			is in degree. Save the resultant matrix in pResult.
			Rotate Z axis
		 */
		 /**************************************************************************/
		template <typename T>
		void RotDegZ(MI::Matrix4<T>& pResult, float angle) {
			Identity(pResult);
			RotRadZ(pResult, pi<T>() / 180.f * angle);
		}

		
		/*-------------------------------------------------------------------------------------------------------------------
		Transpose Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
			This functions calculated the transpose matrix of pMtx
			and saves it in pResult
		 */
		 /**************************************************************************/
		template <typename T>
		void Transpose(MI::Matrix3<T>& pResult, const MI::Matrix3<T>& pMtx) {
			int i{ 0 }, j{ 0 };
			for (; i * j <= 4;) {
				pResult.m[i + (j * 3)] = pMtx.m[j + (i * 3)];
				if (j == 2) {
					if (i == 2) break;
					j = 0;
					++i;
				}
				else ++j;
			}
		}

		/**************************************************************************/
		/*!
			This functions calculated the transpose matrix of pMtx
			and saves it in pResult
			0 4 8  12      0  1  2  3
			1 5 9  13  to  4  5  6  7
			2 6 10 14      8  9  10 11
			3 7 11 15      12 13 14 15
		 */
		 /**************************************************************************/
		template <typename T>
		void Transpose(MI::Matrix4<T>& pResult, const MI::Matrix4<T>& pMtx) {
			int i{ 0 }, j{ 0 };
			for (; i * j <= 9;) {
				pResult.m[i + (j * 4)] = pMtx.m[j + (i * 4)];
				if (j == 3) {
					if (i == 3) break;
					j = 0;
					++i;
				}
				else ++j;
			}
		}

		/*-------------------------------------------------------------------------------------------------------------------
		Inverse Matrix
		-------------------------------------------------------------------------------------------------------------------*/
		/**************************************************************************/
		/*!
			This function calculates the inverse matrix of pMtx and saves the
			result in pResult. If the matrix inversion fails, pResult
			would be set to identity matrix.
			0 3 6
			1 4 7
			2 5 8
		*/
		/**************************************************************************/
		template <typename T>
		MI::Matrix3<T> Inverse(const MI::Matrix3<T>& pMtx) {
			float determinant =
				pMtx.m[0] * (pMtx.m[4] * pMtx.m[8] - pMtx.m[7] * pMtx.m[5])
				- pMtx.m[3] * (pMtx.m[1] * pMtx.m[8] - pMtx.m[7] * pMtx.m[2])
				+ pMtx.m[6] * (pMtx.m[1] * pMtx.m[5] - pMtx.m[4] * pMtx.m[2]);

			MI::Matrix3<T> pResult;
			if (determinant > -epsilon<T>() && determinant < epsilon<T>()) { Identity(pResult); return pResult; }

			determinant = 1.f / determinant;
			
			pResult.m[0] = +(pMtx.m[4] * pMtx.m[8] - pMtx.m[7] * pMtx.m[5]) * determinant;
			pResult.m[1] = -(pMtx.m[1] * pMtx.m[8] - pMtx.m[7] * pMtx.m[2]) * determinant;
			pResult.m[2] = +(pMtx.m[1] * pMtx.m[5] - pMtx.m[4] * pMtx.m[2]) * determinant;

			pResult.m[3] = -(pMtx.m[3] * pMtx.m[8] - pMtx.m[6] * pMtx.m[5]) * determinant;
			pResult.m[4] = +(pMtx.m[0] * pMtx.m[8] - pMtx.m[6] * pMtx.m[2]) * determinant;
			pResult.m[5] = -(pMtx.m[0] * pMtx.m[5] - pMtx.m[3] * pMtx.m[2]) * determinant;

			pResult.m[6] = +(pMtx.m[3] * pMtx.m[7] - pMtx.m[6] * pMtx.m[4]) * determinant;
			pResult.m[7] = -(pMtx.m[0] * pMtx.m[7] - pMtx.m[6] * pMtx.m[1]) * determinant;
			pResult.m[8] = +(pMtx.m[0] * pMtx.m[4] - pMtx.m[3] * pMtx.m[1]) * determinant;

			return pResult;
		}

		/**************************************************************************/
		/*!
			This function calculates the inverse matrix of pMtx and saves the
			result in pResult. If the matrix inversion fails, pResult
			would be set to identity matrix.
		*/
		/**************************************************************************/
		template <typename T>
		MI::Matrix4<T> Inverse(const MI::Matrix4<T>& pMtx) {
			float determinant;
			MI::Matrix4<T> pResult;
			pResult.m[0] = pMtx.m[5] * pMtx.m[10] * pMtx.m[15] -
				pMtx.m[5] * pMtx.m[11] * pMtx.m[14] -
				pMtx.m[9] * pMtx.m[6] * pMtx.m[15] +
				pMtx.m[9] * pMtx.m[7] * pMtx.m[14] +
				pMtx.m[13] * pMtx.m[6] * pMtx.m[11] -
				pMtx.m[13] * pMtx.m[7] * pMtx.m[10];

			pResult.m[4] = -pMtx.m[4] * pMtx.m[10] * pMtx.m[15] +
				pMtx.m[4] * pMtx.m[11] * pMtx.m[14] +
				pMtx.m[8] * pMtx.m[6] * pMtx.m[15] -
				pMtx.m[8] * pMtx.m[7] * pMtx.m[14] -
				pMtx.m[12] * pMtx.m[6] * pMtx.m[11] +
				pMtx.m[12] * pMtx.m[7] * pMtx.m[10];

			pResult.m[8] = pMtx.m[4] * pMtx.m[9] * pMtx.m[15] -
				pMtx.m[4] * pMtx.m[11] * pMtx.m[13] -
				pMtx.m[8] * pMtx.m[5] * pMtx.m[15] +
				pMtx.m[8] * pMtx.m[7] * pMtx.m[13] +
				pMtx.m[12] * pMtx.m[5] * pMtx.m[11] -
				pMtx.m[12] * pMtx.m[7] * pMtx.m[9];

			pResult.m[12] = -pMtx.m[4] * pMtx.m[9] * pMtx.m[14] +
				pMtx.m[4] * pMtx.m[10] * pMtx.m[13] +
				pMtx.m[8] * pMtx.m[5] * pMtx.m[14] -
				pMtx.m[8] * pMtx.m[6] * pMtx.m[13] -
				pMtx.m[12] * pMtx.m[5] * pMtx.m[10] +
				pMtx.m[12] * pMtx.m[6] * pMtx.m[9];

			determinant = pMtx.m[0] * pResult.m[0] + pMtx.m[1] * pResult.m[4] + pMtx.m[2] * pResult.m[8] + pMtx.m[3] * pResult.m[12];

			if (determinant > -epsilon<T>() && determinant < epsilon<T>()) { Identity(pResult); return MI::Matrix4<T>{}; }

			determinant = 1 / determinant;

			pResult.m[1] = -pMtx.m[1] * pMtx.m[10] * pMtx.m[15] +
				pMtx.m[1] * pMtx.m[11] * pMtx.m[14] +
				pMtx.m[9] * pMtx.m[2] * pMtx.m[15] -
				pMtx.m[9] * pMtx.m[3] * pMtx.m[14] -
				pMtx.m[13] * pMtx.m[2] * pMtx.m[11] +
				pMtx.m[13] * pMtx.m[3] * pMtx.m[10];

			pResult.m[5] = pMtx.m[0] * pMtx.m[10] * pMtx.m[15] -
				pMtx.m[0] * pMtx.m[11] * pMtx.m[14] -
				pMtx.m[8] * pMtx.m[2] * pMtx.m[15] +
				pMtx.m[8] * pMtx.m[3] * pMtx.m[14] +
				pMtx.m[12] * pMtx.m[2] * pMtx.m[11] -
				pMtx.m[12] * pMtx.m[3] * pMtx.m[10];

			pResult.m[9] = -pMtx.m[0] * pMtx.m[9] * pMtx.m[15] +
				pMtx.m[0] * pMtx.m[11] * pMtx.m[13] +
				pMtx.m[8] * pMtx.m[1] * pMtx.m[15] -
				pMtx.m[8] * pMtx.m[3] * pMtx.m[13] -
				pMtx.m[12] * pMtx.m[1] * pMtx.m[11] +
				pMtx.m[12] * pMtx.m[3] * pMtx.m[9];

			pResult.m[13] = pMtx.m[0] * pMtx.m[9] * pMtx.m[14] -
				pMtx.m[0] * pMtx.m[10] * pMtx.m[13] -
				pMtx.m[8] * pMtx.m[1] * pMtx.m[14] +
				pMtx.m[8] * pMtx.m[2] * pMtx.m[13] +
				pMtx.m[12] * pMtx.m[1] * pMtx.m[10] -
				pMtx.m[12] * pMtx.m[2] * pMtx.m[9];

			pResult.m[2] = pMtx.m[1] * pMtx.m[6] * pMtx.m[15] -
				pMtx.m[1] * pMtx.m[7] * pMtx.m[14] -
				pMtx.m[5] * pMtx.m[2] * pMtx.m[15] +
				pMtx.m[5] * pMtx.m[3] * pMtx.m[14] +
				pMtx.m[13] * pMtx.m[2] * pMtx.m[7] -
				pMtx.m[13] * pMtx.m[3] * pMtx.m[6];

			pResult.m[6] = -pMtx.m[0] * pMtx.m[6] * pMtx.m[15] +
				pMtx.m[0] * pMtx.m[7] * pMtx.m[14] +
				pMtx.m[4] * pMtx.m[2] * pMtx.m[15] -
				pMtx.m[4] * pMtx.m[3] * pMtx.m[14] -
				pMtx.m[12] * pMtx.m[2] * pMtx.m[7] +
				pMtx.m[12] * pMtx.m[3] * pMtx.m[6];

			pResult.m[10] = pMtx.m[0] * pMtx.m[5] * pMtx.m[15] -
				pMtx.m[0] * pMtx.m[7] * pMtx.m[13] -
				pMtx.m[4] * pMtx.m[1] * pMtx.m[15] +
				pMtx.m[4] * pMtx.m[3] * pMtx.m[13] +
				pMtx.m[12] * pMtx.m[1] * pMtx.m[7] -
				pMtx.m[12] * pMtx.m[3] * pMtx.m[5];

			pResult.m[14] = -pMtx.m[0] * pMtx.m[5] * pMtx.m[14] +
				pMtx.m[0] * pMtx.m[6] * pMtx.m[13] +
				pMtx.m[4] * pMtx.m[1] * pMtx.m[14] -
				pMtx.m[4] * pMtx.m[2] * pMtx.m[13] -
				pMtx.m[12] * pMtx.m[1] * pMtx.m[6] +
				pMtx.m[12] * pMtx.m[2] * pMtx.m[5];

			pResult.m[3] = -pMtx.m[1] * pMtx.m[6] * pMtx.m[11] +
				pMtx.m[1] * pMtx.m[7] * pMtx.m[10] +
				pMtx.m[5] * pMtx.m[2] * pMtx.m[11] -
				pMtx.m[5] * pMtx.m[3] * pMtx.m[10] -
				pMtx.m[9] * pMtx.m[2] * pMtx.m[7] +
				pMtx.m[9] * pMtx.m[3] * pMtx.m[6];

			pResult.m[7] = pMtx.m[0] * pMtx.m[6] * pMtx.m[11] -
				pMtx.m[0] * pMtx.m[7] * pMtx.m[10] -
				pMtx.m[4] * pMtx.m[2] * pMtx.m[11] +
				pMtx.m[4] * pMtx.m[3] * pMtx.m[10] +
				pMtx.m[8] * pMtx.m[2] * pMtx.m[7] -
				pMtx.m[8] * pMtx.m[3] * pMtx.m[6];

			pResult.m[11] = -pMtx.m[0] * pMtx.m[5] * pMtx.m[11] +
				pMtx.m[0] * pMtx.m[7] * pMtx.m[9] +
				pMtx.m[4] * pMtx.m[1] * pMtx.m[11] -
				pMtx.m[4] * pMtx.m[3] * pMtx.m[9] -
				pMtx.m[8] * pMtx.m[1] * pMtx.m[7] +
				pMtx.m[8] * pMtx.m[3] * pMtx.m[5];

			pResult.m[15] = pMtx.m[0] * pMtx.m[5] * pMtx.m[10] -
				pMtx.m[0] * pMtx.m[6] * pMtx.m[9] -
				pMtx.m[4] * pMtx.m[1] * pMtx.m[10] +
				pMtx.m[4] * pMtx.m[2] * pMtx.m[9] +
				pMtx.m[8] * pMtx.m[1] * pMtx.m[6] -
				pMtx.m[8] * pMtx.m[2] * pMtx.m[5];



			pResult.m[0] *= determinant;
			pResult.m[4] *= determinant;
			pResult.m[8] *= determinant;
			pResult.m[12] *= determinant;
			pResult.m[1] *= determinant;
			pResult.m[5] *= determinant;
			pResult.m[9] *= determinant;
			pResult.m[13] *= determinant;
			pResult.m[2] *= determinant;
			pResult.m[6] *= determinant;
			pResult.m[10] *= determinant;
			pResult.m[14] *= determinant;
			pResult.m[3] *= determinant;
			pResult.m[7] *= determinant;
			pResult.m[11] *= determinant;
			pResult.m[15] *= determinant;

			return pResult;
		}

		/**************************************************************************/
		/*!
			This function calculates the Orthographic projection matrix
		*/
		/**************************************************************************/
		template <typename T>
		MI::Matrix4<T> OrthoGraphic(T l, T r, T b, T t, T zn, T zf)
		{
			MI::Matrix4<T> pResult;
			pResult.m[0] = 2 / (r - l);
			pResult.m[1] = T{};
			pResult.m[2] = T{};
			pResult.m[3] = T{};
			pResult.m[4] = T{};
			pResult.m[5] = 2 / (t - b);
			pResult.m[6] = T{};
			pResult.m[7] = T{};
			pResult.m[8] = T{};
			pResult.m[9] = T{};
			pResult.m[10] = -2.0f / (zf - zn);
			pResult.m[11] = T{};
			pResult.m[12] = (l + r) / (l - r);
			pResult.m[13] = (t + b) / (b - t);
			pResult.m[14] = (zn + zf) / (zn - zf);
			pResult.m[15] = 1.0f;

			return pResult;
		}

		/**************************************************************************/
		/*!
			This function calculates the LookAt projection matrix
		*/
		/**************************************************************************/
		template <typename T>
		MI::Matrix4<T> LookAt(MI::Vector3D<T> eye, MI::Vector3D<T> at, MI::Vector3D<T> up)
		{
			MI::Vector3D<T> tmp = eye - at;
			MI::Vector3D<T> zaxis = DreamMath::normalize(tmp);
			MI::Vector3D<T> yaxis = DreamMath::normalize(up);

			tmp = DreamMath::cross(yaxis, zaxis);
			MI::Vector3D<T> xaxis = DreamMath::normalize(tmp);

			tmp = DreamMath::cross(zaxis, xaxis);
			yaxis = DreamMath::normalize(tmp);

			MI::Matrix4<T> mat;

			mat.m[0]  = xaxis.x;
			mat.m[1]  = yaxis.x;
			mat.m[2]  = zaxis.x;
			mat.m[3]  = T{};
			mat.m[4]  = xaxis.y;
			mat.m[5]  = yaxis.y;
			mat.m[6]  = zaxis.y;
			mat.m[7]  = T{};
			mat.m[8]  = xaxis.z;
			mat.m[9]  = yaxis.z;
			mat.m[10] = zaxis.z;
			mat.m[11] = T{};
			mat.m[12] = -DreamMath::dot(xaxis, eye);
			mat.m[13] = -DreamMath::dot(yaxis, eye);
			mat.m[14] = -DreamMath::dot(zaxis, eye);
			mat.m[15] = 1.0f;

			return mat;
		}
	}
}
#endif