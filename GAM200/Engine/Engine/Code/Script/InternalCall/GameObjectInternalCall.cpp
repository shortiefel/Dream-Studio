/* Start Header**********************************************************************************/
/*
@file    GameObjectInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/GameObjectInternalCall.hpp"
This file contain the definition of GameObjectInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/Script/InternalCall/GameObjectInternalCall.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

#include "Engine/Header/Script/Scripting.hpp"

#include <mono/jit/jit.h>



namespace Engine {
	namespace InternalCall {
		void CreateEntity_Engine(unsigned int* entityId, MonoString* str);
		void FindEntity_Engine(int* entityId, MonoString* str);

		//bool AddComponent_Scripts_Engine(unsigned int entityId, MonoString* name);
		//bool AddComponent_Transform_Engine(unsigned int entityId);
		//bool AddComponent_Collider_Engine(unsigned int entityId);
		//bool AddComponent_Camera_Engine(unsigned int entityId);

		void SetActive_GameObject_Engine(unsigned int entityId, bool state);

		/*-----------------------------------------------------
		Called in ScriptingInternalCall
		-----------------------------------------------------*/
		void RegisterGameObjectInternalCall() {
			mono_add_internal_call("GameObject::CreateEntity_Engine", CreateEntity_Engine);
			mono_add_internal_call("GameObject::FindEntity_Engine", FindEntity_Engine);

			//mono_add_internal_call("GameObject::AddComponent_Scripts_Engine", AddComponent_Scripts_Engine);
			//mono_add_internal_call("GameObject::AddComponent_Transform_Engine", AddComponent_Transform_Engine);
			//mono_add_internal_call("GameObject::AddComponent_Collider_Engine", AddComponent_Collider_Engine);
			//mono_add_internal_call("GameObject::AddComponent_Camera_Engine", AddComponent_Camera_Engine);

			mono_add_internal_call("GameObject::SetActive_GameObject_Engine", SetActive_GameObject_Engine);
		}

		void CreateEntity_Engine(unsigned int* entityId, MonoString* str) {
			char* text = mono_string_to_utf8(str);
			std::string entityName = text;
			mono_free(text);
			if (entityName.empty()) entityName = "Entity";
			const Entity entity = dreamECSGame->CreateEntity(entityName.c_str());
			*entityId = entity.id;
		}

		void FindEntity_Engine(int* entityId, MonoString* str) {
			const auto& entityMap = dreamECSGame->GetUsedEntityMap();
			char* text = mono_string_to_utf8(str);
			std::string entityName = text;
			mono_free(text);
			if (entityName.empty()) {
				*entityId = -1;
				return;
			}
			for (const auto& [entId, entity] : entityMap) {
				if (entityName.compare(entity.name) == 0) {
					*entityId = entId;
					return;
				}
			}
			//Cant find
			*entityId = -1;
		}

		//bool AddComponent_Scripts_Engine(unsigned int entityId, MonoString* name) {
		//	//return false;
		//	char* text = mono_string_to_utf8(name);
		//	bool result = dreamECSGame->AddComponent<ScriptComponent>(ScriptComponent{ entityId, text });
		//	mono_free(text);
		//	return result;
		//}

		//bool AddComponent_Transform_Engine(unsigned int entityId) {
		//	return dreamECSGame->AddComponent<TransformComponent>(TransformComponent{ entityId });
		//}
		//
		//bool AddComponent_Collider_Engine(unsigned int entityId) {
		//	return dreamECSGame->AddComponent<ColliderComponent>(ColliderComponent{ entityId });
		//}
		//
		//bool AddComponent_Camera_Engine(unsigned int entityId) {
		//	return dreamECSGame->AddComponent<CameraComponent>(CameraComponent{ entityId });
		//}

		void SetActive_GameObject_Engine(unsigned int entityId, bool state) {
			SetEngineType(entityId, TransformComponent, isActive, state);
			ScriptComponent* scriptType = dreamECSGame->GetComponentPTR<ScriptComponent>(entityId);
			if (scriptType != nullptr) {
				auto& klassInt = scriptType->klassInstance;
				for (auto& [className, scriptInstance] : klassInt) {
					scriptInstance.isActive = state;
					if (state) Scripting::Mono_Runtime_Invoke(scriptInstance, MonoFunctionType::On_Enable);
					else Scripting::Mono_Runtime_Invoke(scriptInstance, MonoFunctionType::On_Disable);
				}
			}

		}
	}
}
