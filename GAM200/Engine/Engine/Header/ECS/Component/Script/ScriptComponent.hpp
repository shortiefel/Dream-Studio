/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain the Script component


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

//#include "Engine/Header/Script/Script.hpp"

#include <string>
#include <mono/metadata/threads.h>

namespace Engine {
	//using Custom_Script = std::shared_ptr<Script>;

	struct CSharpScript {
		std::string className = std::string{};

		CSharpScript() = default;
		CSharpScript(std::string cn) : className{ cn } {}

		MonoObject* object = nullptr;

		MonoMethod* UpdateFunc = nullptr;
		MonoMethod* DestroyFunc = nullptr;
	};
}

#endif