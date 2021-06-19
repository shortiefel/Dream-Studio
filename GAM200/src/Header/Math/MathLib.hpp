/* Start Header**********************************************************************************/
/*
@file    MathLib.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file contains Matrix and Vector header file and 
a degree to radian function

*/
/* End Header **********************************************************************************/

#ifndef MATH_LIB_HPP
#define MATH_LIB_HPP

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace MathD {
    template <typename T>
    T radians(T deg) {
        deg = deg * PI / 180;
        return deg;
    }

    template <typename T>
    T* value_ptr(MathImplementation::Matrix3<T>& mat) {
        return mat.GetPtr();
    }
}

#endif