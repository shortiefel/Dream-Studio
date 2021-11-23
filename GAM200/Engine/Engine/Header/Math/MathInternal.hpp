/* Start Header**********************************************************************************/
/*
@file    MathInternal.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu  100%
@date    16/06/2021
\brief
This file contains math internal include


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MATH_INTERNAL_HPP
#define MATH_INTERNAL_HPP

#include "Engine/Header/Math/Internal/VectorMath.hpp"
#include "Engine/Header/Math/Internal/MatrixMath.hpp"
#include "Engine/Header/Math/Internal/CommonMath.hpp"
#include "Engine/Header/Math/Internal/ConstantsMath.hpp"

namespace Engine {
    namespace DreamMath {
        template <typename T>
        bool EpsilonCheck(DreamMath::MathImplementation::Vector2D<T> target) {
            if (target.x >= -epsilon<T>() && target.x <= epsilon<T>() &&
                target.y >= -epsilon<T>() && target.y <= epsilon<T>())
                return true;
            return false;
        }

        /*
        * Return true if its almost 0
        */
        template <typename T>
        bool EpsilonCheck(T target) {
            if (target >= -epsilon<T>() && target <= epsilon<T>())
                return true;
            return false;
        }

        template <typename T>
        bool EpsilonCheck(DreamMath::MathImplementation::Vector2D<T> target, DreamMath::MathImplementation::Vector2D<T> target2) {
            const auto& xPos = target.x - target2.x;
            const auto& yPos = target.y - target2.y;
            if (xPos >= -epsilon<T>() && xPos <= epsilon<T>() &&
                yPos >= -epsilon<T>() && yPos <= epsilon<T>())
                return true;
            return false;
        }
    }
}


#endif