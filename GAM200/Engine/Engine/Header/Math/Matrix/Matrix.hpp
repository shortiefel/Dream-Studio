/* Start Header**********************************************************************************/
/*
@file    Matrix.hpp
@author  tan wei ling felicia	weilingfelicia.tan@digipen.edu
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

	Math::mat3 matrix3 (0, 3, 6, 1, 4, 7, 2, 5, 8);

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

#include "Engine/Header/Math/Matrix/Matrix3.hpp"
#include "Engine/Header/Math/Matrix/Matrix4.hpp"

namespace Engine {
	namespace DreamMath {
		//float matrix3
		using mat3 = MathImplementation::Matrix3<float>;
		//int matrix3
		using imat3 = MathImplementation::Matrix3<int>;
		//unsigned int matrix3
		using umat3 = MathImplementation::Matrix3<unsigned int>;

		//float matrix4
		using mat4 = MathImplementation::Matrix4<float>;
		//int matrix4
		using imat4 = MathImplementation::Matrix4<int>;
		//unsigned int matrix4
		using umat4 = MathImplementation::Matrix4<unsigned int>;
	}
}

#endif