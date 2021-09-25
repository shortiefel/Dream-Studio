/* Start Header**********************************************************************************/
/*
@file    ScriptSystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    26/08/2021
\brief
This file contain the definition of ScriptSystem

find assembly with mono_domain_assembly_open and
get class inside file (class should be same name as filename)
c++ code will find method and call it (method like: update, init)

Steps to test
4. combine 2 files into 1 dll

When entering play mode
Compiles
Serialize
Stop child domain
Create child domain
Load assemblies
Load objects
Deserialize
Initialize object


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


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#include "Engine/Header/Script/ScriptInternalCall.hpp"
#include "Engine/Header/Script/Scripting.hpp"

#include "Engine/Header/Event/OverlapColliderEvent.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/debug-helpers.h> //MonoMethodDesc
#include <mono/metadata/attrdefs.h> //Attribute

#include <cstdlib> //For file to be run by cmd (std::system)


#include <iostream>

namespace Engine {

	bool CallOverlapFunc(const OverlapColliderEvent& e); //To be registered to Event

	bool ScriptSystem::CompileCS() {
		return Scripting::CompileCSInternal();
	}

	void ScriptSystem::PlayInit() {
		const auto& entScriptArray = DreamECS::GetInstance().GetComponentArrayData<CSScript>();
		for (auto& csScript : entScriptArray) {
			if (Entity_Check(csScript.GetEntityId())) break;

			auto& classScriptInstances = csScript.klassInstance;
			const auto& entityId = csScript.GetEntityId();

			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				void* param[] = { (void*)&entityId }; //Change to entity.id after ECS rework
				std::cout << "class: " << className << " " << entityId << "\n";
				if (csScriptInstance.isActive && csScriptInstance.csClass.ConstructorFunc != nullptr)
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::CONSTRUCTOR, param);
				if (csScriptInstance.isActive && csScriptInstance.csClass.InitFunc != nullptr)
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::INIT);
			}
		}
	}

	void ScriptSystem::PlayRunTime() {

		const auto& entScriptArray = DreamECS::GetInstance().GetComponentArrayData<CSScript>();
		for (auto& csScript : entScriptArray) {
			if (Entity_Check(csScript.GetEntityId())) break;

			auto& classScriptInstances = csScript.klassInstance;
			//const auto& entityId = csScript.GetEntityId();

			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.UpdateFunc != nullptr)
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::UPDATE);
			}
		}
	}

	void ScriptSystem::Create() {
		Scripting::Setup();
		RegisterInternalCall();
		OverlapColliderEvent::RegisterFunction(CallOverlapFunc);
		LOG_INSTANCE("Script System created");
	}

	void ScriptSystem::Destroy() {
		Scripting::Cleanup();
		LOG_INSTANCE("Graphic System destroyed");
	}

	bool CallOverlapFunc(const OverlapColliderEvent& e) {
		CSScript* csScript = DreamECS::GetInstance().GetComponentTest<CSScript>(e.self);
		if (!csScript) return false;
		for (auto& [className, csScriptInstance] : csScript->klassInstance) {
			Scripting::Mono_Runtime_Invoke(csScriptInstance, e.type);
		}
		return true;
	}

	void ScriptSystem::UpdateMapData() {
		Scripting::ReloadMono();
		Scripting::InitAllCSClass();
		Scripting::InitAllPublicVariable();
	}
}