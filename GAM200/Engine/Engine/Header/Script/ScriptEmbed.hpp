/* Start Header**********************************************************************************/
/*
@file    ScriptEmbed.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    28/06/2021
\brief
This file has the function declaration for ScriptEmbed


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_EMBED_HPP
#define SCRIPT_EMBED_HPP

#include <mono/metadata/assembly.h>
#include "Engine/Header/ECS/Component/Script/ScriptComponent.hpp"
#include <string>
#include <memory>

namespace Engine {
	namespace Scripting {
		/*-----------------------------------------------------
			Set up mono
		-----------------------------------------------------*/
		void Create();
		/*-----------------------------------------------------
			Clean up mono
		-----------------------------------------------------*/
		void Destroy();
		/*-----------------------------------------------------
			Called when play button is pressed
			-Serialize
			-Stop child domain
			-Create child domain
			-Load assemblies
		-----------------------------------------------------*/
		void ReloadMono();
		/*-----------------------------------------------------
			Called when play button is pressed (After ReloadMono)
			-Load objects
			-Deserialize
			-Call Constructor
			-Call init object
		-----------------------------------------------------*/
		void ReloadObject(MonoObject*& object, CSharpScript& cSharpScript, void** param);
		/*-----------------------------------------------------
			Call a specific virtual function
			E.g: Init, Update
		-----------------------------------------------------*/
		void CallFunction(MonoObject*& object, std::string& className, std::string& func);

		void CallFunction(MonoObject*& object, MonoMethod*& method, void** param = nullptr);
	}
}

#endif