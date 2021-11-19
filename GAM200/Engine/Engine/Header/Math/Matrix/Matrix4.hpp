/* Start Header**********************************************************************************/
/*
@file    Matrix4.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    02/10/2021
\brief
This matrix implementation is column major

namespace MathImplementation is to prevent accidental usage


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef MATRIX_4_HPP
#define MATRIX_4_HPP

//#include "Debug Tools/Logging.hpp"
#include <iostream> // for operator<< 
//#include "Engine/Header/Math/Vector/Vector.hpp"
#include "Engine/Header/Math/Internal/ConstantsMath.hpp"

namespace Engine {
	namespace DreamMath {
		namespace MathImplementation {
			template <typename T>
			class Matrix4 {
			public:
				T m[16];

				//identity matrix as default
				Matrix4() : m{ 
					T(1), T{}, T{}, T{}, 
					T{}, T(1), T{}, T{},
					T{}, T{}, T(1), T{},
					T{}, T{}, T{}, T(1) } {}
				/*Matrix4(Vector3D<T> v1, Vector3D<T> v2, Vector3D<T> v3) : m{
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z } {}*/
				Matrix4(float _00, float _01, float _02, float _03,
					float _10, float _11, float _12, float _13,
					float _20, float _21, float _22, float _23,
					float _30, float _31, float _32, float _33) :
					m{ 
					_00, _01, _02, _03, 
					_10, _11, _12, _13, 
					_20, _21, _22, _23, 
					_30, _31, _32, _33 } {}

				Matrix4<T>& operator=(const Matrix4<T>& rhs) {
					for (int i{ 0 }; i < 16; ++i) {
						m[i] = rhs.m[i];
					}

					return *this;
				}

				// Assignment operators
				Matrix4<T>& operator *= (const Matrix4<T>& rhs) {
					Matrix4<T> result;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							int num = 0;
							for (int k = 0; k < 4; k++) {
								num += m[i][k] * rhs.m[k][j];
							}
							result[i][j] = num;
						}
					}

					*this = result;
					return *this;
				}

				friend std::ostream& operator<<(std::ostream& os, const Matrix4<T>& rhs) {
					for (int i{ 0 }; i < 16; ++i) {
						switch (i) {
						case 0:
						case 4:
						case 8:
						case 12:
							os << "(";
							break;
						default:
							break;
						}
						os << rhs.m[i];
						switch (i) {
						case 3:
						case 7:
						case 11:
						case 15:
							os << ") ";
							break;
						default:
							os << ", ";
							break;
						}

					}
					return os;
				}

				///**************************************************************************/
				///*!
				//This function return ptr to matrix in column major
				//*/
				///**************************************************************************/
				//const T* GetPtr() {
				//	return m;
				//}
			};

			template <typename T>
			Matrix4<T> operator* (const Matrix4<T>& lhs, const Matrix4<T>& rhs) {
				Matrix4<T> result{ lhs };
				result *= rhs;
				return result;
			}

			/*************************************************************************
			This operator multiplies the matrix pMtx with the vector rhs
			and returns the result as a vector
			0 4 8  12
			1 5 9  13
			2 6 10 14
			3 7 11 15
			*************************************************************************/
			/*template <typename T>
			Vector4D<T>  operator * (const Matrix4<T>& pMtx, const Vector4D<T>& rhs) {
				Vector4D<T> result;
				result.x = (pMtx.m[0] * rhs.x) + (pMtx.m[4] * rhs.y) + (pMtx.m[8] * rhs.z) + (pMtx.m[12] * rhs.w);
				result.y = (pMtx.m[1] * rhs.x) + (pMtx.m[5] * rhs.y) + (pMtx.m[9] * rhs.z) + (pMtx.m[13] * rhs.w);
				result.z = (pMtx.m[2] * rhs.x) + (pMtx.m[6] * rhs.y) + (pMtx.m[10] * rhs.z) + (pMtx.m[14] * rhs.w);
				result.w = (pMtx.m[3] * rhs.x) + (pMtx.m[7] * rhs.y) + (pMtx.m[11] * rhs.z) + (pMtx.m[15] * rhs.w);
				return result;
			}*/

			///**************************************************************************/
			///*!
			//This function sets the matrix pResult to the identity matrix
			//*/
			///**************************************************************************/
			//template <typename T>
			//void Identity(Matrix4<T>& pResult) {
			//	for (int i{ 0 }; i < 16; ++i) {
			//		pResult.m[i] = 0;
			//		if (!(i % 5)) pResult.m[i] = 1;
			//	}
			//}

			///**************************************************************************/
			///*!
			//	This function creates a translation matrix from x & y
			//	and saves it in pResult
			//	0 4 8  12
			//	1 5 9  13
			//	2 6 10 14
			//	3 7 11 15
			// */
			// /**************************************************************************/
			//template <typename T>
			//void Translate(Matrix4<T>& pResult, float x, float y, float z) {
			//	Identity(pResult);
			//	pResult.m[12] = x;
			//	pResult.m[13] = y;
			//	pResult.m[14] = z;
			//}

			///**************************************************************************/
			///*!
			//	This function creates a scaling matrix from x & y
			//	and saves it in pResult
			//	0 4 8  12
			//	1 5 9  13
			//	2 6 10 14
			//	3 7 11 15
			// */
			// /**************************************************************************/
			//template <typename T>
			//void Scale(Matrix4<T>& pResult, float x, float y, float z) {
			//	Identity(pResult);
			//	pResult.m[0] = x;
			//	pResult.m[5] = y;
			//	pResult.m[10] = y;
			//}

			///**************************************************************************/
			///*!
			//	This matrix creates a rotation matrix from "angle" whose value
			//	is in radian. Save the resultant matrix in pResult.
			//	Rotate X axis
			//	0 4 8  12
			//	1 5 9  13
			//	2 6 10 14
			//	3 7 11 15
			// */
			// /**************************************************************************/
			//template <typename T>
			//void RotRadX(Matrix4<T>& pResult, float angle) {
			//	Identity(pResult);
			//	pResult.m[5] = pResult.m[10] = (float)cos(angle);
			//	pResult.m[6] = pResult.m[9] = (float)sin(angle);
			//	pResult.m[9] = -pResult.m[9];
			//}

			///**************************************************************************/
			///*!
			//	This matrix creates a rotation matrix from "angle" whose value
			//	is in radian. Save the resultant matrix in pResult.
			//	Rotate Y axis
			//	0 4 8  12
			//	1 5 9  13
			//	2 6 10 14
			//	3 7 11 15
			// */
			// /**************************************************************************/
			//template <typename T>
			//void RotRadY(Matrix4<T>& pResult, float angle) {
			//	Identity(pResult);
			//	pResult.m[0] = pResult.m[10] = (float)cos(angle);
			//	pResult.m[2] = pResult.m[8] = (float)sin(angle);
			//	pResult.m[2] = -pResult.m[2];
			//}

			///**************************************************************************/
			///*!
			//	This matrix creates a rotation matrix from "angle" whose value
			//	is in radian. Save the resultant matrix in pResult.
			//	Rotate Z axis
			//	0 4 8  12
			//	1 5 9  13
			//	2 6 10 14
			//	3 7 11 15
			// */
			// /**************************************************************************/
			//template <typename T>
			//void RotRadZ(Matrix4<T>& pResult, float angle) {
			//	Identity(pResult);
			//	pResult.m[0] = pResult.m[5] = (float)cos(angle);
			//	pResult.m[1] = pResult.m[4] = (float)sin(angle);
			//	pResult.m[4] = -pResult.m[4];
			//}

			///**************************************************************************/
			///*!
			//	This matrix creates a rotation matrix from "angle" whose value
			//	is in degree. Save the resultant matrix in pResult.
			//	Rotate X axis
			// */
			// /**************************************************************************/
			//template <typename T>
			//void RotDegX(Matrix4<T>& pResult, float angle) {
			//	Identity(pResult);
			//	RotRadX(pResult, static_cast<float>(PI) / 180.f * angle);
			//}

			///**************************************************************************/
			///*!
			//	This matrix creates a rotation matrix from "angle" whose value
			//	is in degree. Save the resultant matrix in pResult.
			//	Rotate Y axis
			// */
			// /**************************************************************************/
			//template <typename T>
			//void RotDegY(Matrix4<T>& pResult, float angle) {
			//	Identity(pResult);
			//	RotRadY(pResult, static_cast<float>(PI) / 180.f * angle);
			//}

			///**************************************************************************/
			///*!
			//	This matrix creates a rotation matrix from "angle" whose value
			//	is in degree. Save the resultant matrix in pResult.
			//	Rotate Z axis
			// */
			// /**************************************************************************/
			//template <typename T>
			//void RotDegZ(Matrix4<T>& pResult, float angle) {
			//	Identity(pResult);
			//	RotRadZ(pResult, static_cast<float>(PI) / 180.f * angle);
			//}

			///**************************************************************************/
			///*!
			//	This functions calculated the transpose matrix of pMtx
			//	and saves it in pResult
			//	0 4 8  12      0  1  2  3  
			//	1 5 9  13  to  4  5  6  7  
			//	2 6 10 14      8  9  10 11  
			//	3 7 11 15      12 13 14 15  
			// */
			// /**************************************************************************/
			//template <typename T>
			//void Transpose(Matrix4<T>& pResult, const Matrix4<T>& pMtx) {
			//	int i{ 0 }, j{ 0 };
			//	for (; i * j <= 9;) {
			//		pResult.m[i + (j * 4)] = pMtx.m[j + (i * 4)];
			//		if (j == 3) {
			//			if (i == 3) break;
			//			j = 0;
			//			++i;
			//		}
			//		else ++j;
			//	}
			//}

			///**************************************************************************/
			///*!
			//	This function calculates the inverse matrix of pMtx and saves the
			//	result in pResult. If the matrix inversion fails, pResult
			//	would be set to identity matrix.
			//*/
			///**************************************************************************/
			//template <typename T>
			//void Inverse(Matrix4<T>& pResult, float& determinant, const Matrix4<T>& pMtx) {

			//	pResult.m[0] = pMtx.m[5] *  pMtx.m[10] * pMtx.m[15] -
			//			 pMtx.m[5] *  pMtx.m[11] * pMtx.m[14] -
			//			 pMtx.m[9] *  pMtx.m[6] *  pMtx.m[15] +
			//			 pMtx.m[9] *  pMtx.m[7] *  pMtx.m[14] +
			//			 pMtx.m[13] * pMtx.m[6] *  pMtx.m[11] -
			//			 pMtx.m[13] * pMtx.m[7] *  pMtx.m[10];

			//	pResult.m[4] = -pMtx.m[4] *  pMtx.m[10] * pMtx.m[15] +
			//			  pMtx.m[4] *  pMtx.m[11] * pMtx.m[14] +
			//			  pMtx.m[8] *  pMtx.m[6] *  pMtx.m[15] -
			//			  pMtx.m[8] *  pMtx.m[7] *  pMtx.m[14] -
			//			  pMtx.m[12] * pMtx.m[6] *  pMtx.m[11] +
			//			  pMtx.m[12] * pMtx.m[7] *  pMtx.m[10];

			//	pResult.m[8] = pMtx.m[4] *  pMtx.m[9] *  pMtx.m[15] -
			//			 pMtx.m[4] *  pMtx.m[11] * pMtx.m[13] -
			//			 pMtx.m[8] *  pMtx.m[5] *  pMtx.m[15] +
			//			 pMtx.m[8] *  pMtx.m[7] *  pMtx.m[13] +
			//			 pMtx.m[12] * pMtx.m[5] *  pMtx.m[11] -
			//			 pMtx.m[12] * pMtx.m[7] *  pMtx.m[9];

			//	pResult.m[12] = -pMtx.m[4] *  pMtx.m[9] *  pMtx.m[14] +
			//			   pMtx.m[4] *  pMtx.m[10] * pMtx.m[13] +
			//			   pMtx.m[8] *  pMtx.m[5] *  pMtx.m[14] -
			//			   pMtx.m[8] *  pMtx.m[6] *  pMtx.m[13] -
			//			   pMtx.m[12] * pMtx.m[5] *  pMtx.m[10] +
			//			   pMtx.m[12] * pMtx.m[6] *  pMtx.m[9];

			//	determinant = pMtx.m[0] * pResult.m[0] + pMtx.m[1] * pResult.m[4] + pMtx.m[2] * pResult.m[8] + pMtx.m[3] * pResult.m[12];

			//	if (determinant > static_cast<float>(-EPSILON) && determinant < static_cast<float>(EPSILON)) { Identity(pResult); return; }

			//	determinant = 1 / determinant;

			//	pResult.m[1] = -pMtx.m[1] * pMtx.m[10] * pMtx.m[15] +
			//		pMtx.m[1] * pMtx.m[11] * pMtx.m[14] +
			//		pMtx.m[9] * pMtx.m[2] * pMtx.m[15] -
			//		pMtx.m[9] * pMtx.m[3] * pMtx.m[14] -
			//		pMtx.m[13] * pMtx.m[2] * pMtx.m[11] +
			//		pMtx.m[13] * pMtx.m[3] * pMtx.m[10];

			//	pResult.m[5] = pMtx.m[0] * pMtx.m[10] * pMtx.m[15] -
			//		pMtx.m[0] * pMtx.m[11] * pMtx.m[14] -
			//		pMtx.m[8] * pMtx.m[2] * pMtx.m[15] +
			//		pMtx.m[8] * pMtx.m[3] * pMtx.m[14] +
			//		pMtx.m[12] * pMtx.m[2] * pMtx.m[11] -
			//		pMtx.m[12] * pMtx.m[3] * pMtx.m[10];

			//	pResult.m[9] = -pMtx.m[0] * pMtx.m[9] * pMtx.m[15] +
			//		pMtx.m[0] * pMtx.m[11] * pMtx.m[13] +
			//		pMtx.m[8] * pMtx.m[1] * pMtx.m[15] -
			//		pMtx.m[8] * pMtx.m[3] * pMtx.m[13] -
			//		pMtx.m[12] * pMtx.m[1] * pMtx.m[11] +
			//		pMtx.m[12] * pMtx.m[3] * pMtx.m[9];

			//	pResult.m[13] = pMtx.m[0] * pMtx.m[9] * pMtx.m[14] -
			//		pMtx.m[0] * pMtx.m[10] * pMtx.m[13] -
			//		pMtx.m[8] * pMtx.m[1] * pMtx.m[14] +
			//		pMtx.m[8] * pMtx.m[2] * pMtx.m[13] +
			//		pMtx.m[12] * pMtx.m[1] * pMtx.m[10] -
			//		pMtx.m[12] * pMtx.m[2] * pMtx.m[9];

			//	pResult.m[2] = pMtx.m[1] * pMtx.m[6] * pMtx.m[15] -
			//		pMtx.m[1] * pMtx.m[7] * pMtx.m[14] -
			//		pMtx.m[5] * pMtx.m[2] * pMtx.m[15] +
			//		pMtx.m[5] * pMtx.m[3] * pMtx.m[14] +
			//		pMtx.m[13] * pMtx.m[2] * pMtx.m[7] -
			//		pMtx.m[13] * pMtx.m[3] * pMtx.m[6];

			//	pResult.m[6] = -pMtx.m[0] * pMtx.m[6] * pMtx.m[15] +
			//		pMtx.m[0] * pMtx.m[7] * pMtx.m[14] +
			//		pMtx.m[4] * pMtx.m[2] * pMtx.m[15] -
			//		pMtx.m[4] * pMtx.m[3] * pMtx.m[14] -
			//		pMtx.m[12] * pMtx.m[2] * pMtx.m[7] +
			//		pMtx.m[12] * pMtx.m[3] * pMtx.m[6];

			//	pResult.m[10] = pMtx.m[0] * pMtx.m[5] * pMtx.m[15] -
			//		pMtx.m[0] * pMtx.m[7] * pMtx.m[13] -
			//		pMtx.m[4] * pMtx.m[1] * pMtx.m[15] +
			//		pMtx.m[4] * pMtx.m[3] * pMtx.m[13] +
			//		pMtx.m[12] * pMtx.m[1] * pMtx.m[7] -
			//		pMtx.m[12] * pMtx.m[3] * pMtx.m[5];

			//	pResult.m[14] = -pMtx.m[0] * pMtx.m[5] * pMtx.m[14] +
			//		pMtx.m[0] * pMtx.m[6] * pMtx.m[13] +
			//		pMtx.m[4] * pMtx.m[1] * pMtx.m[14] -
			//		pMtx.m[4] * pMtx.m[2] * pMtx.m[13] -
			//		pMtx.m[12] * pMtx.m[1] * pMtx.m[6] +
			//		pMtx.m[12] * pMtx.m[2] * pMtx.m[5];

			//	pResult.m[3] = -pMtx.m[1] * pMtx.m[6] * pMtx.m[11] +
			//		pMtx.m[1] * pMtx.m[7] * pMtx.m[10] +
			//		pMtx.m[5] * pMtx.m[2] * pMtx.m[11] -
			//		pMtx.m[5] * pMtx.m[3] * pMtx.m[10] -
			//		pMtx.m[9] * pMtx.m[2] * pMtx.m[7] +
			//		pMtx.m[9] * pMtx.m[3] * pMtx.m[6];

			//	pResult.m[7] = pMtx.m[0] * pMtx.m[6] * pMtx.m[11] -
			//		pMtx.m[0] * pMtx.m[7] * pMtx.m[10] -
			//		pMtx.m[4] * pMtx.m[2] * pMtx.m[11] +
			//		pMtx.m[4] * pMtx.m[3] * pMtx.m[10] +
			//		pMtx.m[8] * pMtx.m[2] * pMtx.m[7] -
			//		pMtx.m[8] * pMtx.m[3] * pMtx.m[6];

			//	pResult.m[11] = -pMtx.m[0] * pMtx.m[5] * pMtx.m[11] +
			//		pMtx.m[0] * pMtx.m[7] * pMtx.m[9] +
			//		pMtx.m[4] * pMtx.m[1] * pMtx.m[11] -
			//		pMtx.m[4] * pMtx.m[3] * pMtx.m[9] -
			//		pMtx.m[8] * pMtx.m[1] * pMtx.m[7] +
			//		pMtx.m[8] * pMtx.m[3] * pMtx.m[5];

			//	pResult.m[15] = pMtx.m[0] * pMtx.m[5] * pMtx.m[10] -
			//		pMtx.m[0] * pMtx.m[6] * pMtx.m[9] -
			//		pMtx.m[4] * pMtx.m[1] * pMtx.m[10] +
			//		pMtx.m[4] * pMtx.m[2] * pMtx.m[9] +
			//		pMtx.m[8] * pMtx.m[1] * pMtx.m[6] -
			//		pMtx.m[8] * pMtx.m[2] * pMtx.m[5];

			//	

			//	pResult.m[0] *= determinant;
			//	pResult.m[4] *= determinant; 
			//	pResult.m[8] *= determinant; 
			//	pResult.m[12] *= determinant;
			//	pResult.m[1] *= determinant; 
			//	pResult.m[5] *= determinant; 
			//	pResult.m[9] *= determinant; 
			//	pResult.m[13] *= determinant;
			//	pResult.m[2] *= determinant; 
			//	pResult.m[6] *= determinant; 
			//	pResult.m[10] *= determinant; 
			//	pResult.m[14] *= determinant;
			//	pResult.m[3] *= determinant;
			//	pResult.m[7] *= determinant; 
			//	pResult.m[11] *= determinant; 
			//	pResult.m[15] *= determinant;
			//}
		}
	}
}

#endif