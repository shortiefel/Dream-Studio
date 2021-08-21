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
#include <string>
#include <memory>

namespace Engine {
	namespace ScriptEmbed {
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
			-Initialize object
		-----------------------------------------------------*/
		void ReloadObject(std::shared_ptr<MonoObject*>& object, std::string& className);
		/*-----------------------------------------------------
			Call a specific virtual function
			E.g: Init, Update
		-----------------------------------------------------*/
		void CallFunction(std::shared_ptr<MonoObject*>& object, std::string& className, std::string& func);
	}
}

#endif