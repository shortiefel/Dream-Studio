/* Start Header**********************************************************************************/
/*
@file    ScriptEngine.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/08/2021
\brief
This file contain the definition of ScriptEngine


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Script/ScriptEngine.hpp"

#include "Engine/Header/Script/ScriptEmbed.hpp"

/*-------------------------------------
Terminology

CSPublicVariable
-Class containing the data and description of a variable in CS

CSClass
-Store the name and some functions of a CS class (update/destroy)

CSScriptInstance
-CSClass and Map of string(Variable name) and CSPublicVariable

CSClassInstance
-Map of string(Class name) and CSScriptInstance

CSEntityClassInstance
-Map of entity id and CSClassInstance
-------------------------------------*/
#include <iostream>
namespace Engine {
	namespace Scripting {
		CSEntityClassInstance ScriptEngine::csEntityClassInstance;


		void ScriptEngine::Play() {
			std::cout << "play \n";
			Scripting::ReloadMono();
			
			//Entity and map of classScript
			for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
				//Single class and (class and CS public variable)
				for (auto& [className, csScriptInstance] : classScriptInstances) {
					//Store obj---------------------------------------------------------
					void* param[] = { (void*)&entityId }; //Change to entity.id for the future
					Scripting::ReloadObject(csScriptInstance.csClass.object, csScriptInstance.csClass, param);
				}
			}
		}
	}
}