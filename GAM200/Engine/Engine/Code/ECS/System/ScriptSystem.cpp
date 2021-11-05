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

#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"

#include <iostream>

namespace Engine {

	bool CallOverlapFunc(const OverlapColliderEvent& e); //To be registered to Event
	bool CallMouseOverlapFunc(const MouseOverlapColliderEvent& e);

	bool ScriptSystem::CompileCS(bool play) {
		PROFILER_START("Scripting");

		return Scripting::CompileCSInternal(play);
	}

	void ScriptSystem::PlayInit() {
		PROFILER_START("Scripting");
		
		const auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
		for (auto& csScript : entScriptArray) {
			const Entity_id& entity_id = csScript.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			auto& classScriptInstances = csScript.klassInstance;
			
			//Calls all constructor first and then initialize all
			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				void* param[] = { (void*)&entity_id };
				//std::cout << "class: " << className << "\n";
				if (csScriptInstance.isActive && csScriptInstance.csClass.ConstructorFunc != nullptr) {
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::CONSTRUCTOR, param);
				}
			}

			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.InitFunc != nullptr) {
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::INIT);
				}
			}
			
		}
	}

	void ScriptSystem::PlayRunTime() {
		PROFILER_START("Scripting");

		const auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
		for (auto& csScript : entScriptArray) {
			if (EntityId_Check(csScript.GetEntityId())) break;

			auto& classScriptInstances = csScript.klassInstance;
			//const auto& entityId = csScript.GetEntity();

			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.UpdateFunc != nullptr) {
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::UPDATE);
				}
			}
		}
	}

	void ScriptSystem::Create() {
		Scripting::Setup();
		RegisterInternalCall();
		OverlapColliderEvent::RegisterFunction(CallOverlapFunc);
		MouseOverlapColliderEvent::RegisterFunction(CallMouseOverlapFunc);
		LOG_INSTANCE("Script System created");
	}

	void ScriptSystem::Destroy() {
		Scripting::Cleanup();
		LOG_INSTANCE("Graphic System destroyed");
	}

	bool CallOverlapFunc(const OverlapColliderEvent& e) {
		PROFILER_START("Scripting");
		
		ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(e.self);
		if (!csScript) return false;
		for (auto& [className, csScriptInstance] : csScript->klassInstance) {
			Scripting::Mono_Runtime_Invoke(csScriptInstance, e.type);
		}
		return true;
	}

	bool CallMouseOverlapFunc(const MouseOverlapColliderEvent& e) {
		PROFILER_START("Scripting");

		ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(e.other);
		if (!csScript) return false;
		std::cout << e.other << " over lap \n";
		for (auto& [className, csScriptInstance] : csScript->klassInstance) {
			std::cout << className << " " << (int)e.type << " over lap \n";
			Scripting::Mono_Runtime_Invoke(csScriptInstance, e.type);
		}
		return true;
	}

	void ScriptSystem::UpdateMapData() {
		PROFILER_START("Scripting");

		Scripting::ReloadMono();
		Scripting::InitAllCSClass();
		Scripting::InitAllPublicVariable();
	}
}