/* Start Header**********************************************************************************/
/*
@file    ComponentsInternalCall.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/ComponentsInternalCall.hpp"
This file contain the declaration of ComponentsInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	namespace InternalCall {
		/*-----------------------------------------------------
		Called in ScriptingInternalCall
		-----------------------------------------------------*/
		void RegisterComponentsInternalCall();

		//Set the function that will be called for ScreenToWorldPoint in c#
		void SetGetViewportInternalFunc(Math::mat3(*fp)());
	}
}