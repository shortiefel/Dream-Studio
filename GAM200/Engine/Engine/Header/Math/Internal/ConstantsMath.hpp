/* Start Header**********************************************************************************/
/*
@file    ConstantsMath.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu 100%
@date    14/09/2021
\brief
This file contains epsilon and pi constants


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef CONSTANTS_MATH_HPP
#define CONSTANTS_MATH_HPP

#include <limits>
#include <iostream>
namespace Engine {
    namespace DreamMath {
        template <typename T>
        inline T epsilon() {
            return std::numeric_limits<T>::epsilon();
        }

        /*
        * Return true if its almost 0
        */
        template <typename T>
        bool EpsilonCheck(const T& target, const T& val2 = T{ 0 }) {
            return (target >= val2 - std::numeric_limits<T>::epsilon() && target <= val2 + std::numeric_limits<T>::epsilon());
        }

        template <typename T>
        inline T pi() {
            return static_cast<T>(3.141592653589793238462643383279502884197169399375105820974944);
        }

        
    }
}
#endif