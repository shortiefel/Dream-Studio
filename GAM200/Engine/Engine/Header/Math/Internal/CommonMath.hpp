/* Start Header**********************************************************************************/
/*
@file    CommonMath.hpp
@@author  tan wei ling felicia	weilingfelicia.tan@digipen.edu  100%
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
            return deg * pi<T>() / 180;
        }

        template <typename T>
        inline T degrees(T rad) {
            return rad * 180 / pi<T>();
        }

        /*template <typename T>
        inline T* value_ptr(const MathImplementation::Vector3D<T>& rhs) {
            return &(rhs.m[0]);
        }

        template <typename T>
        inline T* value_ptr(const MathImplementation::Vector4D<T>& rhs) {
            return &(rhs.m[0]);
        }*/

        template <typename T>
        inline const T* value_ptr(const MathImplementation::Matrix3<T>& rhs) {
            return &(rhs.m[0]);
        }

        template <typename T>
        inline  T* value_ptr(MathImplementation::Matrix3<T>& rhs) {
            return &(rhs.m[0]);
        }

        template <typename T>
        inline const T* value_ptr(const MathImplementation::Matrix4<T>& rhs) {
            return &(rhs.m[0]);

        }
        template <typename T>
        inline T* value_ptr(MathImplementation::Matrix4<T>& rhs) {
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

        /*-------------------------------------------------------------------------------------------------------------------
        Min Max checks
        -------------------------------------------------------------------------------------------------------------------*/
        template <typename T, typename U>
        inline T Min(T num1, U num2) {
            return (std::min)((num1), static_cast<T>(num2));    
        }

        template <typename T, typename U>
        inline T Max(T num1, U num2) {
            return (std::max)((num1), static_cast<T>(num2));
        }
	}
}

#endif