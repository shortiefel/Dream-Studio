/* Start Header**********************************************************************************/
/*
@file    MathLib.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    12/09/2021
\brief
This file contains access/switch to either glm library and custom math library
For easy switching to test whether custom math library is working properly


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MATH_LIB_HPP
#define MATH_LIB_HPP

//#include "Engine/Header/Math/MathLib.hpp"

#ifdef CUSTOM_MATH
#include "Engine/Header/Math/MathInternal.hpp"
namespace Math = MathD;
#else
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Math = glm;
#endif

#endif
