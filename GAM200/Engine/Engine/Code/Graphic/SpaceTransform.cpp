/* Start Header**********************************************************************************/
/*
@file    SpaceTransform.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    30/10/2021
\brief
#include "Engine/Header/Graphic/SpaceTransform.hpp"
This file contain the SpaceTransform definition
This file provides functionality to switch between screen and world position


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/SpaceTransform.hpp"

namespace Engine {
	Math::vec3 ScreenToWorldPoint(const Math::vec3& _screenPosition, const Math::mat3& _invCamTransform, const Math::mat3& _invViewportTransform) {
		return _invCamTransform * _invViewportTransform * _screenPosition;
	}

	Math::vec3 WorldToScreenPoint(const Math::vec3& _screenPosition, const Math::mat3& _camTransform, const Math::mat3& _viewportTransform) {
		return _viewportTransform *_camTransform * _screenPosition;
	}
}