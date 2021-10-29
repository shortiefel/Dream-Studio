/* Start Header**********************************************************************************/
/*
@file    ScriptClass.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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
	/*-----------------------------------------------------------------------------------------------------------------------------------
	Script classes
	-----------------------------------------------------------------------------------------------------------------------------------*/
	struct CSClass {
		std::string fullName = std::string{};
		std::string namespaceName = std::string{};
		std::string className = std::string{};

		CSClass() = default;
		CSClass(std::string cn) : fullName{ cn } {
			if (fullName.find('.') != std::string::npos) {
				namespaceName = fullName.substr(0, fullName.find_last_of('.'));
				className = fullName.substr(fullName.find_last_of('.') + 1);
			}
			else {
				className = fullName;
			}
		}

		MonoObject* object = nullptr;
		MonoClass* klass = nullptr;

		MonoMethod* ConstructorFunc = nullptr;
		MonoMethod* InitFunc = nullptr;
		MonoMethod* UpdateFunc = nullptr;
		MonoMethod* DestroyFunc = nullptr;
		MonoMethod* OnCollisionEnter = nullptr;
		MonoMethod* OnCollisionStay = nullptr;
		MonoMethod* OnCollisionExit = nullptr;
		MonoMethod* OnTriggerEnter = nullptr;
		MonoMethod* OnTriggerStay = nullptr;
		MonoMethod* OnTriggerExit = nullptr;
		MonoMethod* OnMouseEnter = nullptr;
		MonoMethod* OnMouseClick = nullptr;
		MonoMethod* OnMouseOver = nullptr;
		MonoMethod* OnMouseExit = nullptr;
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
		bool isActive = true;

		CSScriptInstance(std::string cn = "", bool active = true) : csClass(cn), isActive{active}{}

		CSScriptInstance(CSScriptInstance&& rhs) noexcept {
			csClass = std::move(rhs.csClass);
			csVariableMap = std::move(rhs.csVariableMap);
		}
		CSScriptInstance&  operator=(CSScriptInstance&& rhs) noexcept {
			if (this == &rhs) return *this;
			std::swap(csClass, rhs.csClass);
			std::swap(csVariableMap, rhs.csVariableMap);
			return *this;
		}
		CSScriptInstance(const CSScriptInstance&) = delete;
	};

	//Map of string(Class name) and CSScriptInstance
	using CSClassInstance = std::unordered_map<std::string, CSScriptInstance>;
}

#endif