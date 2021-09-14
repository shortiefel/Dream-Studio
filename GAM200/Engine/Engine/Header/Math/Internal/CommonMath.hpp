/* Start Header**********************************************************************************/
/*
@file    CommonMath.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    14/09/2021
\brief

Common math like to radian/degree


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef COMMON_MATH_H
#define COMMON_MATH_H



namespace Engine {
	namespace DreamMath {
		/*-------------------------------------------------------------------------------------------------------------------
		Trigo
		-------------------------------------------------------------------------------------------------------------------*/
        template <typename T>
        inline T sin(T deg) {
            return static_cast<T>(std::sin(static_cast<double>(deg)));
        }

        template <typename T>
        inline T cos(T deg) {
            return static_cast<T>(std::cos(static_cast<double>(deg)));
        }

        template <typename T>
        inline T radians(T deg) {
            return deg * static_cast<T>(MathImplementation::PI) / 180;
        }

        template <typename T>
        inline T degrees(T rad) {
            return rad * 180 / static_cast<T>(MathImplementation::PI);
        }

        template <typename T>
        inline const T* value_ptr(const MathImplementation::Matrix3<T>& rhs) {
            return &(rhs.m[0]);
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
}

#endif