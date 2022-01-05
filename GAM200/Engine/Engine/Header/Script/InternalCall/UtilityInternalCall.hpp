/* Start Header**********************************************************************************/
/*
@file    UtilityInternalCall.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/UtilityInternalCall.hpp"
This file contain the declaration of UtilityInternalCall


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
		void RegisterUtilityInternalCall();

		//Set the function that will be called for Debug.Log in c#
		void SetConsoleWriteInternalFunc(void(*fp)(std::string));
		//Set the function that will be called for GetMousePosition in c#
		void SetGetMousePositionInternalFunc(Math::vec2(*fp)());
	}
}

