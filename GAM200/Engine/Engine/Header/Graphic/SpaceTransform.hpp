/* Start Header**********************************************************************************/
/*
@file    SpaceTransform.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    30/10/2021
\brief
#include "Engine/Header/Graphic/SpaceTransform.hpp"
This file contain the SpaceTransform declaration
This file provides functionality to switch between screen and world position


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SPACE_TRANSFORM_HPP
#define SPACE_TRANSFORM_HPP

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	/*
	_viewportTransform is inverse(viewport to NDC)
	_camTransform is inverse(NDC to world)
	order: invCam * invViewport * Position*/
	Math::vec3 ScreenToWorldPoint(const Math::vec3& _screenPosition, const Math::mat3& _invCamTransform, const Math::mat3& _invViewportTransform);
	/*
	_viewportTransform is normal (NDC to viewport)
	_camTransform is normal (World to NDC)
	order: Viewport * Cam * Position*/
	Math::vec3 WorldToScreenPoint(const Math::vec3& _screenPosition, const Math::mat3& _camTransform, const Math::mat3& _viewportTransform);
}

#endif