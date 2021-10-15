/* Start Header**********************************************************************************/
/*
@file    ConstantsMath.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
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


namespace Engine {
    namespace DreamMath {
        namespace MathImplementation {
            constexpr double EPSILON = 0.0001;
            constexpr double PI = 3.14159265358;
        }

        template <typename T>
        inline T epsilon() {
            return static_cast<T>(MathImplementation::EPSILON);
        }

        template <typename T>
        inline T pi() {
            return static_cast<T>(MathImplementation::PI);
        }
    }
}
#endif