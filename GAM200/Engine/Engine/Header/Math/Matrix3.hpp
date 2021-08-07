/* Start Header**********************************************************************************/
/*
@file    Matrix3.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This matrix implementation is column major
Eg: To initialize a matrix
0 1 2
3 4 5
6 7 8

MathD::Mat3 matrix3 (0, 3, 6, 1, 4, 7, 2, 5, 8);
Note: MathD::Mat3 is a type name done in matrix.hpp
namespace MathImplementation is to prevent accidental usage


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef MATRIX_3_HPP
#define MATRIX_3_HPP

//#include "Debug Tools/Logging.hpp"
#include <iostream> // for operator<< 
#include "Engine/Header/Math/Vector.hpp"

namespace Engine {
#define EPSILON		0.0001f
#define PI 3.14159265358f

	namespace MathD {
		namespace MathImplementation {
			template <typename T>
			class Matrix3 {
			public:
				T m[9];

				//identity matrix as default
				Matrix3() : m{ T(1), T{}, T{}, T{}, T(1), T{}, T{}, T{}, T(1) } {}
				Matrix3(Vector3D<T> v1, Vector3D<T> v2, Vector3D<T> v3) : m{
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z } {}
				Matrix3(float _00, float _01, float _02,
					float _10, float _11, float _12,
					float _20, float _21, float _22) :
					m{ _00, _01, _02, _10, _11, _12, _20, _21, _22 } {}

				Matrix3<T>& operator=(const Matrix3<T>& rhs) {
					for (int i{ 0 }; i < 9; ++i) {
						m[i] = rhs.m[i];
					}

					return *this;
				}

				// Assignment operators
				Matrix3<T>& operator *= (const Matrix3<T>& rhs) {
					Matrix3<T> result;
					for (int i{ 0 }; i < 3; ++i) {
						for (int o{ 0 }; o < 3; ++o) {
							int index1 = i * 3;
							result.m[(i * 3) + o] = (rhs.m[index1] * m[o]) + (rhs.m[index1 + 1] * m[o + 3]) + (rhs.m[index1 + 2] * m[o + 6]);
						}
					}

					*this = result;
					return *this;
				}

				friend std::ostream& operator<<(std::ostream& os, const Matrix3<T>& rhs) {
					for (int i{ 0 }; i < 9; ++i) {
						switch (i) {
						case 0:
						case 3:
						case 6:
							os << "(";
							break;
						default:
							break;
						}
						os << rhs.m[i];
						switch (i) {
						case 2:
						case 5:
						case 8:
							os << ") ";
							break;
						default:
							os << ", ";
							break;
						}

					}
					return os;
				}

				/**************************************************************************/
				/*!
				This function return ptr to matrix in column major
				*/
				/**************************************************************************/
				T* GetPtr() {
					return m;
				}
			};

			template <typename T>
			Matrix3<T> operator* (const Matrix3<T>& lhs, const Matrix3<T>& rhs) {
				Matrix3<T> result{ lhs };
				result *= rhs;
				return result;
			}

			/*************************************************************************
			This operator multiplies the matrix pMtx with the vector rhs
			and returns the result as a vector
			0 3 6
			1 4 7
			2 5 8
			*************************************************************************/
			template <typename T>
			Vector2D<T>  operator * (const Matrix3<T>& pMtx, const Vector2D<T>& rhs) {
				Vector2D<T> result;
				result.x = (pMtx.m[0] * rhs.x) + (pMtx.m[3] * rhs.y) + pMtx.m[6];
				result.y = (pMtx.m[1] * rhs.x) + (pMtx.m[4] * rhs.y) + pMtx.m[7];
				return result;
			}

			/**************************************************************************/
			/*!
			This function sets the matrix pResult to the identity matrix
			*/
			/**************************************************************************/
			template <typename T>
			void Identity(Matrix3<T>& pResult) {
				for (int i{ 0 }; i < 9; ++i) {
					pResult.m[i] = 0;
					if (!(i % 4)) pResult.m[i] = 1;
				}
			}

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
			void Translate(Matrix3<T>& pResult, float x, float y) {
				Identity(pResult);
				pResult.m[6] = x;
				pResult.m[7] = y;
			}

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
			void Scale(Matrix3<T>& pResult, float x, float y) {
				Identity(pResult);
				pResult.m[0] = x;
				pResult.m[4] = y;
			}

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
			void RotRad(Matrix3<T>& pResult, float angle) {
				Identity(pResult);
				pResult.m[0] = pResult.m[4] = (float)cos(angle);
				pResult.m[1] = pResult.m[3] = (float)sin(angle);
				pResult.m[3] = -pResult.m[3];
			}

			/**************************************************************************/
			/*!
				This matrix creates a rotation matrix from "angle" whose value
				is in degree. Save the resultant matrix in pResult.
			 */
			 /**************************************************************************/
			template <typename T>
			void RotDeg(Matrix3<T>& pResult, float angle) {
				Identity(pResult);
				RotRad(pResult, PI / 180.f * angle);
			}

			/**************************************************************************/
			/*!
				This functions calculated the transpose matrix of pMtx
				and saves it in pResult
			 */
			 /**************************************************************************/
			template <typename T>
			void Transpose(Matrix3<T>& pResult, const Matrix3<T>& pMtx) {
				int i{ 0 }, j{ 0 };
				for (; i * j != 4;) {
					pResult.m[i + (j * 3)] = pMtx.m[j + (i * 3)];
					if (j == 2) {
						j = 0;
						++i;
					}
					else ++j;
				}
			}

			/**************************************************************************/
			/*!
				This function calculates the inverse matrix of pMtx and saves the
				result in pResult. If the matrix inversion fails, pResult
				would be set to identity matrix.
			*/
			/**************************************************************************/
			template <typename T>
			void Inverse(Matrix3<T>& pResult, float& determinant, const Matrix3<T>& pMtx) {
				determinant = pMtx.m[0] * (pMtx.m[4] * pMtx.m[8] - pMtx.m[5] * pMtx.m[7])
					- pMtx.m[1] * (pMtx.m[3] * pMtx.m[8] - pMtx.m[5] * pMtx.m[6])
					+ pMtx.m[2] * (pMtx.m[3] * pMtx.m[7] - pMtx.m[4] * pMtx.m[6]);

				if (determinant > -EPSILON && determinant < EPSILON) { Identity(pResult); return; }

				Matrix3<T> tem;
				tem.m[0] = pMtx.m[4] * pMtx.m[8] - pMtx.m[5] * pMtx.m[7];
				tem.m[1] = -(pMtx.m[1] * pMtx.m[8] - pMtx.m[2] * pMtx.m[7]);
				tem.m[2] = pMtx.m[1] * pMtx.m[5] - pMtx.m[2] * pMtx.m[4];

				tem.m[3] = -(pMtx.m[3] * pMtx.m[8] - pMtx.m[5] * pMtx.m[6]);
				tem.m[4] = pMtx.m[0] * pMtx.m[8] - pMtx.m[2] * pMtx.m[6];
				tem.m[5] = -(pMtx.m[0] * pMtx.m[5] - pMtx.m[2] * pMtx.m[3]);

				tem.m[6] = pMtx.m[3] * pMtx.m[7] - pMtx.m[4] * pMtx.m[6];
				tem.m[7] = -(pMtx.m[0] * pMtx.m[7] - pMtx.m[1] * pMtx.m[6]);
				tem.m[8] = pMtx.m[0] * pMtx.m[4] - pMtx.m[1] * pMtx.m[3];

				for (int i{ 0 }; i < 9; ++i) {
					pResult.m[i] = tem.m[i] / determinant;
					//Prevent -0 from appearing
					//if (pResult.m[i] > -EPSILON && pResult.m[i] < EPSILON) pResult.m[i] = 0;
				}
			}
		}
	}
}

#endif