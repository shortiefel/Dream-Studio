/* Start Header**********************************************************************************/
/*
@file    Scripting.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    21/09/2021
\brief
This file contain the declaration of Scripting


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPTING_HPP
#define SCRIPTING_HPP

#include "Engine/Header/Script/ScriptClass.hpp"
#include "Engine/Header/Script/MonoFunctionType.hpp"

namespace Engine {
	namespace Scripting {
		void Mono_Runtime_Invoke(const CSScriptInstance& _csScriptInstance, MonoFunctionType _type, void** _param = nullptr);

		/*-----------------------------------------------------
		Destroy child domain
		-Check if child domain exist
		-delete if it exist
	-----------------------------------------------------*/
		void DestroyChildDomain();
	}
}

#endif