/* Start Header**********************************************************************************/
/*
@file    ScriptClass.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    26/06/2021
\brief
This file contain definition for Script class


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Script/ScriptClass.hpp"
#include "Engine/Header/Script/Scripting.hpp"

namespace Engine {
	/*-----------------------------------------------------------------------------------------------------------------------------------
	Script classes
	-----------------------------------------------------------------------------------------------------------------------------------*/

	CSClass::CSClass(std::string cn) : fullName{ cn } {
			if (fullName.find('.') != std::string::npos) {
				namespaceName = fullName.substr(0, fullName.find_last_of('.'));
				className = fullName.substr(fullName.find_last_of('.') + 1);
			}
			else {
				className = fullName;
			}
		}

	CSClass::CSClass(const CSClass& rhs) : fullName{ rhs.fullName }, namespaceName{ rhs.namespaceName }, className{ rhs.className } {}

	CSClass& CSClass::operator=(const CSClass& rhs) {
		fullName = rhs.fullName; namespaceName = rhs.namespaceName; className = rhs.className; return *this;
	}

	CSClass::CSClass(CSClass&& rhs) noexcept {
		*this = std::move(rhs);
	}
	CSClass& CSClass::operator=(CSClass&& rhs) noexcept {
		fullName = rhs.fullName;
		namespaceName = rhs.namespaceName;
		className = rhs.className;

		rhs.fullName = "";
		rhs.namespaceName = "";
		rhs.className = "";

		gc_handle = rhs.gc_handle;

		object = rhs.object;
		klass = rhs.klass;

		AwakeFunc = rhs.AwakeFunc;
		ConstructorFunc = rhs.ConstructorFunc;
		InitFunc = rhs.InitFunc;
		UpdateFunc = rhs.UpdateFunc;
		FixedUpdateFunc = rhs.FixedUpdateFunc;
		DestroyFunc = rhs.DestroyFunc;
		OnEnable = rhs.OnEnable;
		OnDisable = rhs.OnDisable;
		OnCollisionEnter = rhs.OnCollisionEnter;
		OnCollisionStay = rhs.OnCollisionStay;
		OnCollisionExit = rhs.OnCollisionExit;
		OnTriggerEnter = rhs.OnTriggerEnter;
		OnTriggerStay = rhs.OnTriggerStay;
		OnTriggerExit = rhs.OnTriggerExit;
		OnMouseEnter = rhs.OnMouseEnter;
		OnMouseOver = rhs.OnMouseOver;
		OnMouseExit = rhs.OnMouseExit;

		rhs.gc_handle = 0;

		rhs.object = nullptr;
		rhs.klass = nullptr;

		rhs.AwakeFunc = nullptr;
		rhs.ConstructorFunc = nullptr;
		rhs.InitFunc = nullptr;
		rhs.UpdateFunc = nullptr;
		rhs.FixedUpdateFunc = nullptr;
		rhs.DestroyFunc = nullptr;
		rhs.OnEnable = nullptr;
		rhs.OnDisable = nullptr;
		rhs.OnCollisionEnter = nullptr;
		rhs.OnCollisionStay = nullptr;
		rhs.OnCollisionExit = nullptr;
		rhs.OnTriggerEnter = nullptr;
		rhs.OnTriggerStay = nullptr;
		rhs.OnTriggerExit = nullptr;
		rhs.OnMouseEnter = nullptr;
		rhs.OnMouseOver = nullptr;
		rhs.OnMouseExit = nullptr;

		return *this;
	}

	CSClass::~CSClass() {
		mono_gchandle_free(gc_handle);
	}



	/*-----------------------------------------------------------------------------------------------------------------------------------
	Instance of a script object
	-CS class to call update/destroy function
	-Access to CS script public variable
	-----------------------------------------------------------------------------------------------------------------------------------*/

	CSScriptInstance::CSScriptInstance(std::string cn, bool active) : csClass(cn), isActive{ active }{}

	CSScriptInstance::CSScriptInstance(CSScriptInstance&& rhs) noexcept : csClass(std::move(rhs.csClass)) {

		//csVariableMap = std::move(rhs.csVariableMap);
	}
	CSScriptInstance& CSScriptInstance::operator=(CSScriptInstance&& rhs) noexcept {
		if (this == &rhs) return *this;
		std::swap(csClass, rhs.csClass);
		//std::swap(csVariableMap, rhs.csVariableMap);
		return *this;
	}

	CSScriptInstance::CSScriptInstance(const CSScriptInstance& rhs) {
		*this = rhs;
	}
	CSScriptInstance& CSScriptInstance::operator=(const CSScriptInstance& rhs) {
		csClass = rhs.csClass;
		Scripting::InitCSClass(*this);

		return *this;
	}

}
