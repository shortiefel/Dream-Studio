/* Start Header**********************************************************************************/
/*
@file    Matrix.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file SHOULD be included to use Matrix3 and its functions
Usage:
	#include "Matrix.hpp"
	This matrix implementation is column major
	Eg: To initialize a matrix
	0 1 2
	3 4 5
	6 7 8

	MathD::Mat3 matrix3 (0, 3, 6, 1, 4, 7, 2, 5, 8);

	MathD namespace is to prevent name clash with other library
	This file has other types of Matrix3 in case it is needed
	Do add more here if other types is needed

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Math/Matrix3.hpp"

namespace MathD {
	//float matrix3
	using Mat3 = MathImplementation::Matrix3<float>;
	//int matrix3
	using iMat3 = MathImplementation::Matrix3<int>;
}

#endif