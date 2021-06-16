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
}

#endif