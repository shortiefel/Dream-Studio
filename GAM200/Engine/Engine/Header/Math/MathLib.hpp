/* Start Header**********************************************************************************/
/*
@file    MathLib.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file contains Matrix and Vector header file and 
a degree to radian function


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MATH_LIB_HPP
#define MATH_LIB_HPP

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace MathD {
    template <typename T>
    inline T radians(T deg) {
        return deg * PI / 180;
    }

    template <typename T>
    inline T degrees(T rad) {
        return rad * 180 / PI;
    }

    template <typename T>
    inline T* value_ptr(MathImplementation::Matrix3<T>& mat) {
        return mat.GetPtr();
    }

    template <typename T>
    inline T getLength(T n1, T n2) {
        return sqrt(pow(n1, 2) + pow(n2, 2));
    }

    template <typename T>
    inline T getSqLength(T n1, T n2) {
        return pow(n1, 2) + pow(n2, 2);
    }
}

#endif