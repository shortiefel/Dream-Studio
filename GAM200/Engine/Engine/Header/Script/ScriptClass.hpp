/* Start Header**********************************************************************************/
/*
@file    ScriptClass.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
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
#include <iostream>
namespace Engine {
	/*-----------------------------------------------------------------------------------------------------------------------------------
	Script classes
	-----------------------------------------------------------------------------------------------------------------------------------*/
	struct CSClass {
		std::string fullName = std::string{};
		std::string namespaceName = std::string{};
		std::string className = std::string{};

		CSClass() = default;
		CSClass(std::string cn);

		CSClass(const CSClass& rhs);
		CSClass& operator=(const CSClass& rhs);

		CSClass(CSClass&& rhs) noexcept;
		CSClass& operator=(CSClass&& rhs) noexcept;

		~CSClass();

		uint32_t gc_handle = 0;

		MonoObject* object = nullptr;
		MonoClass* klass = nullptr;

		MonoMethod* AwakeFunc = nullptr;
		MonoMethod* ConstructorFunc = nullptr;
		MonoMethod* InitFunc = nullptr;
		MonoMethod* UpdateFunc = nullptr;
		MonoMethod* FixedUpdateFunc = nullptr;
		MonoMethod* DestroyFunc = nullptr;
		MonoMethod* OnEnable = nullptr;
		MonoMethod* OnDisable = nullptr;
		MonoMethod* OnCollisionEnter = nullptr;
		MonoMethod* OnCollisionStay = nullptr;
		MonoMethod* OnCollisionExit = nullptr;
		MonoMethod* OnTriggerEnter = nullptr;
		MonoMethod* OnTriggerStay = nullptr;
		MonoMethod* OnTriggerExit = nullptr;
		MonoMethod* OnMouseEnter = nullptr;
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
		//std::unordered_map<std::string, CSPublicVariable> csVariableMap;
		bool isActive = true;

		CSScriptInstance(std::string cn = "", bool active = true);

		CSScriptInstance(CSScriptInstance&& rhs) noexcept;
		CSScriptInstance& operator=(CSScriptInstance&& rhs) noexcept;

		CSScriptInstance(const CSScriptInstance& rhs);
		CSScriptInstance& operator=(const CSScriptInstance& rhs);
	};

	//Map of string(Class name) and CSScriptInstance
	using CSClassInstance = std::unordered_map<std::string, CSScriptInstance>;
}

#endif