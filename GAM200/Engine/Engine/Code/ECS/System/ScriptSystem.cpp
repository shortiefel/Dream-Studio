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
#include "Engine/Header/Event/FixedUpdateEvent.hpp"

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
	bool CallFixedUpdate(const FixedUpdateEvent& e);

	bool ScriptSystem::CompileCS() {
		PROFILER_START("Scripting");

		return Scripting::CompileCSInternal();
	}

	void ScriptSystem::PlayInit() {
		PROFILER_START("Scripting");

		InternalCall::InitializeSavedData();

		auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
		const auto& entMap = dreamECSGame->GetUsedConstEntityMap();

		for (auto& csScript : entScriptArray) {
			const Entity_id& entity_id = csScript.GetEntityId();
			
			if (EntityId_Check(entity_id)) break;
			if (entMap.find(entity_id) == entMap.end()) continue;

			auto& classScriptInstances = csScript.klassInstance;

			//Calls all constructor first and then initialize all
			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				void* param[] = { (void*)&entity_id };
				//std::cout << "class: " << className << "\n";
				if (csScriptInstance.isActive && csScriptInstance.csClass.ConstructorFunc != nullptr) {
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::Constructor, param);
				}
			}
		}

		for (auto& csScript : entScriptArray) {
			const Entity_id& entity_id = csScript.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (entMap.find(entity_id) == entMap.end()) continue;

			auto& classScriptInstances = csScript.klassInstance;

			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.AwakeFunc != nullptr) {
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::Awake);
				}
			}

		}

		for (auto& csScript : entScriptArray) {
			const Entity_id& entity_id = csScript.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (entMap.find(entity_id) == entMap.end()) continue;

			auto& classScriptInstances = csScript.klassInstance;

			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.InitFunc != nullptr) {
					//std::cout << "init function \n";
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::Init);
				}
			}

		}
	}

	void ScriptSystem::PlayRunTime() {
		PROFILER_START("Scripting");

		auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
		const auto& entMap = dreamECSGame->GetUsedConstEntityMap();

		for (auto& csScript : entScriptArray) {
			const Entity_id& entity_id = csScript.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (entMap.find(entity_id) == entMap.end()) continue;

			auto& classScriptInstances = csScript.klassInstance;
			//const auto& entityId = csScript.GetEntity();

			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.UpdateFunc != nullptr) {
					//std::cout << className << "\n";
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::Update);
				}
			}
		}
	}

	void ScriptSystem::DestroyChildDomain() {
		Scripting::DestroyChildDomain();
	}

	void ScriptSystem::Create() {
		Scripting::Setup();
		InternalCall::RegisterInternalCall();
		OverlapColliderEvent::RegisterFunction(CallOverlapFunc);
		MouseOverlapColliderEvent::RegisterFunction(CallMouseOverlapFunc);
		FixedUpdateEvent::RegisterFunction(CallFixedUpdate);
		LOG_INSTANCE("Script System created");
	}

	void ScriptSystem::Destroy() {
		Scripting::Cleanup();
		LOG_INSTANCE("Graphic System destroyed");
	}

	bool CallOverlapFunc(const OverlapColliderEvent& e) {
		PROFILER_START("Scripting");
		if (!GameState::GetInstance().GetPlaying()) return false;

		ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(e.self);
		if (!csScript) return false;
		void* param[] = { (void*)&(e.other) };
		for (auto& [className, csScriptInstance] : csScript->klassInstance) {
			Scripting::Mono_Runtime_Invoke(csScriptInstance, e.type, param);
		}
		return true;
	}

	bool CallMouseOverlapFunc(const MouseOverlapColliderEvent& e) {
		PROFILER_START("Scripting");
		if (!GameState::GetInstance().GetPlaying()) return false;

		ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(e.other);
		if (!csScript) return false;

		for (auto& [className, csScriptInstance] : csScript->klassInstance) {
			if(csScriptInstance.isActive)
				Scripting::Mono_Runtime_Invoke(csScriptInstance, e.type);
		}
		return true;
	}

	bool CallFixedUpdate(const FixedUpdateEvent&) {
		PROFILER_START("Scripting");

		auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
		for (auto& csScript : entScriptArray) {
			if (EntityId_Check(csScript.GetEntityId())) break;

			auto& classScriptInstances = csScript.klassInstance;

			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.isActive && csScriptInstance.csClass.FixedUpdateFunc != nullptr) {
					Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::Fixed_Update);
				}
			}
		}

		return true;
	}

	void ScriptSystem::UpdateMapData() {
		PROFILER_START("Scripting");

		Scripting::ReloadMono();
		Scripting::InitAllCSClass();
		Scripting::InitAllPublicVariable();
	}

	void ScriptSystem::SaveCSData() {
		InternalCall::StoreSavedData();
	}
}