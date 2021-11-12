/* Start Header**********************************************************************************/
/*
@file    ScriptInternalCall.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    25/08/2021
\brief
#include "Engine/Header/Script/ScriptInternalCall.hpp"
This file contain the declaration of ScriptInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_INTERNAL_CALL
#define SCRIPT_INTERNAL_CALL

#include <string>
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	//Register Internal call for C# side to use
	void RegisterInternalCall();

	//Set the function that will be called for Debug.Log in c#
	void SetConsoleWriteFunc(void(*fp)(std::string));
	//Set the function that will be called for ScreenToWorldPoint in c#
	void SetGetViewportFunc(Math::mat3(*fp)());
	//Set the function that will be called for GetMousePosition in c#
	void SetGetMousePositionFunc(Math::vec2(*fp)());
}

#endif