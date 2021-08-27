/* Start Header**********************************************************************************/
/*
@file    ScriptClass.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain declaration for Script class


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_CLASS
#define SCRIPT_CLASS

#include <unordered_map>
#include <mono/metadata/threads.h>

#include "Engine/Header/Script/ScriptClassVariable.hpp"

namespace Engine {
	namespace Scripting {
		/*-----------------------------------------------------------------------------------------------------------------------------------
		Script classes
		-----------------------------------------------------------------------------------------------------------------------------------*/
		struct CSClass {
			std::string className = std::string{};

			//CSClass() = default;
			CSClass(std::string cn) : className{ cn } {}

			MonoObject* object = nullptr;

			MonoMethod* UpdateFunc = nullptr;
			MonoMethod* DestroyFunc = nullptr;
		};


		/*-----------------------------------------------------------------------------------------------------------------------------------
		Instance of a script object
		-CS class to call update/destroy function
		-Access to CS script public variable
		-----------------------------------------------------------------------------------------------------------------------------------*/
		struct CSScriptInstance {
			CSClass csClass;
			//map(variableName, variableData)
			std::unordered_map<std::string, CSPublicVariable> csVariableMap;

			CSScriptInstance(std::string cn) : csClass(cn) {}
		};

		//Map of string(Class name) and CSScriptInstance
		using CSClassInstance = std::unordered_map<std::string, CSScriptInstance>;
	}
}

#endif