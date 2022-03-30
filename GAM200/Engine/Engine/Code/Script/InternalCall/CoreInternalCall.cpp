/* Start Header**********************************************************************************/
/*
@file    CoreInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/CoreInternalCall.hpp"
This file contain the definition of CoreInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/Script/InternalCall/CoreInternalCall.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

#include <mono/jit/jit.h>

#define SetEngineType(ID, type, paramName, param)\
type* ctype = dreamECSGame->GetComponentPTR<type>(ID);\
if (ctype != nullptr) ctype->paramName = param;

#define GET_COMPONENT_PTR(type) type* tem = dreamECSGame->GetComponentPTR<type>(id);\
								return !(tem == nullptr);


namespace Engine {
	namespace InternalCall {
		extern std::unordered_map<MonoType*, std::function<void(Entity_id)>> addComponentFuncs;
		extern std::unordered_map<MonoType*, std::function<bool(Entity_id)>> hasComponentFuncs;

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Check if component exist
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		bool HasComponent_Scripts_Engine(unsigned int id, MonoString* str);
		//bool HasComponent_Transform_Engine(unsigned int id);
		//bool HasComponent_Collider_Engine(unsigned int id);
		//bool HasComponent_Camera_Engine(unsigned int id);
		//bool HasComponent_Rigidbody_Engine(unsigned int id);
		//bool HasComponent_Texture_Engine(unsigned int id);
		//bool HasComponent_Font_Engine(unsigned int id);
		//bool HasComponent_Sound_Engine(unsigned int id);
		//bool HasComponent_UI_Engine(unsigned int id);
		//bool HasComponent_Waypoint_Engine(unsigned int id);


		bool AddComponent_Engine(unsigned int entityId, void* type);
		bool AddComponent_Scripts_Engine(unsigned int entityId, MonoString* name);
		bool HasComponent_Engine(unsigned int entityId, void* type);


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Destroy
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Destroy_Entity_Engine(unsigned int id);
		void Destroy_Transform_Engine(unsigned int id);
		void Destroy_Collider_Engine(unsigned int id);
		void Destroy_Script_Engine(unsigned int id, MonoString* str);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Active
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*void SetTransform_Active_Engine(unsigned int id, bool boolean);
		void GetTransform_Active_Engine(unsigned int id, bool* boolean);
		void SetCollider_Active_Engine(unsigned int id, bool boolean);
		void GetCollider_Active_Engine(unsigned int id, bool* boolean);
		void SetScript_Active_Engine(unsigned int id, bool boolean, MonoString* str);
		void GetScript_Active_Engine(unsigned int id, bool* boolean, MonoString* str);*/

		void Active_Transform_Engine(unsigned int id, bool boolean);
		void Active_Collider_Engine(unsigned int id, bool boolean);
		void Active_Light_Engine(unsigned int id, bool boolean);
		void Active_Text_Engine(unsigned int id, bool boolean);
		void Active_Script_Engine(unsigned int id, bool boolean, MonoString* str);

		/*-----------------------------------------------------
		Called in ScriptingInternalCall
		-----------------------------------------------------*/
		void RegisterCoreInternalCall() {
			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Check if component exist
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("IBehaviour::HasComponent_Scripts_Engine", HasComponent_Scripts_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Transform_Engine", HasComponent_Transform_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Collider_Engine", HasComponent_Collider_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Camera_Engine", HasComponent_Camera_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Rigidbody_Engine", HasComponent_Rigidbody_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Texture_Engine", HasComponent_Texture_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Font_Engine", HasComponent_Font_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Sound_Engine", HasComponent_Sound_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_UI_Engine", HasComponent_UI_Engine);
			//mono_add_internal_call("IBehaviour::HasComponent_Waypoint_Engine", HasComponent_Waypoint_Engine);


			mono_add_internal_call("IBehaviour::AddComponent_Engine", AddComponent_Engine);
			mono_add_internal_call("IBehaviour::AddComponent_Scripts_Engine", AddComponent_Scripts_Engine);
			mono_add_internal_call("IBehaviour::HasComponent_Engine", HasComponent_Engine);
			

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Destroy
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("IBehaviour::Destroy_Entity_Engine", Destroy_Entity_Engine);
			mono_add_internal_call("IBehaviour::Destroy_Transform_Engine", Destroy_Transform_Engine);
			mono_add_internal_call("IBehaviour::Destroy_Collider_Engine", Destroy_Collider_Engine);
			mono_add_internal_call("IBehaviour::Destroy_Script_Engine", Destroy_Script_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Active
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			/*mono_add_internal_call("Transform::SetTransform_Active_Engine", SetTransform_Active_Engine);
			mono_add_internal_call("Transform::GetTransform_Active_Engine", GetTransform_Active_Engine);
			mono_add_internal_call("Collider::SetCollider_Active_Engine", SetCollider_Active_Engine);
			mono_add_internal_call("Collider::GetCollider_Active_Engine", GetCollider_Active_Engine);
			mono_add_internal_call("MonoBehaviour::SetScript_Active_Engine", SetScript_Active_Engine);
			mono_add_internal_call("MonoBehaviour::GetScript_Active_Engine", GetScript_Active_Engine);*/

			mono_add_internal_call("MonoBehaviour::Active_Transform_Engine", Active_Transform_Engine);
			mono_add_internal_call("MonoBehaviour::Active_Collider_Engine", Active_Collider_Engine);
			mono_add_internal_call("MonoBehaviour::Active_Light_Engine", Active_Light_Engine);
			mono_add_internal_call("MonoBehaviour::Active_Text_Engine", Active_Text_Engine);
			mono_add_internal_call("MonoBehaviour::Active_Script_Engine", Active_Script_Engine);
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Check if component exist
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		bool HasComponent_Scripts_Engine(unsigned int id, MonoString* str) {
			ScriptComponent* tem = dreamECSGame->GetComponentPTR<ScriptComponent>(id);
			if (tem == nullptr) return false;
			const auto& scriptComponent = *tem;
			char* text = mono_string_to_utf8(str);
			std::string strName = text;
			mono_free(text);
			for (const auto& [name, klass] : scriptComponent.klassInstance) {
				if (strName.compare(name) == 0) return true;
			}
			return false;
		}

		//bool HasComponent_Transform_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(TransformComponent);
		//}
		//
		//bool HasComponent_Collider_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(ColliderComponent);
		//}
		//
		//bool HasComponent_Camera_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(CameraComponent);
		//}
		//
		//bool HasComponent_Rigidbody_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(RigidBodyComponent);
		//}
		//
		//bool HasComponent_Texture_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(TextureComponent);
		//}
		//
		//bool HasComponent_Font_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(FontComponent);
		//}
		//
		//bool HasComponent_Sound_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(SoundComponent);
		//}
		//
		//bool HasComponent_UI_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(UIComponent);
		//}
		//
		//bool HasComponent_Waypoint_Engine(unsigned int id) {
		//	GET_COMPONENT_PTR(WaypointComponent);
		//}



		bool AddComponent_Engine(unsigned int entityId, void* type) {
			MonoType* mType = mono_reflection_type_get_type((MonoReflectionType*)type);

			if (addComponentFuncs.find(mType) != addComponentFuncs.end()) {
				addComponentFuncs[mType](entityId);
				return true;
			}
			else {
				LOG_WARNING("AddComponent: Type (" + std::string{ mono_type_get_name(mType) } + ") could not be found");
			}
			return false;
		}

		bool AddComponent_Scripts_Engine(unsigned int entityId, MonoString* name) {
			//return false;
			char* text = mono_string_to_utf8(name);
			bool result = dreamECSGame->AddComponent<ScriptComponent>(ScriptComponent{ entityId, text });
			mono_free(text);
			return result;
		}

		bool HasComponent_Engine(unsigned int entityId, void* type) {
			MonoType* mType = mono_reflection_type_get_type((MonoReflectionType*)type);

			if (hasComponentFuncs.find(mType) != hasComponentFuncs.end()) {
				return hasComponentFuncs[mType](entityId);
			}
			else {
				LOG_WARNING("HasComponent: Type (" + std::string{ mono_type_get_name(mType) } + ") could not be found");
			}

			return false;
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Destroy
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Destroy_Entity_Engine(unsigned int id) {
			dreamECSGame->DestroyEntity(id);
		}

		void Destroy_Transform_Engine(unsigned int id) {
			dreamECSGame->RemoveComponent<TransformComponent>(id);
		}

		void Destroy_Collider_Engine(unsigned int id) {
			dreamECSGame->RemoveComponent<ColliderComponent>(id);
		}

		void Destroy_Script_Engine(unsigned int id, MonoString* str) {
			ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(id);
			if (!csScript) return;
			char* text = mono_string_to_utf8(str);
			csScript->RemoveScript(text);
			mono_free(text);
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Active
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*void SetTransform_Active_Engine(unsigned int id, bool boolean) {
			SetEngineType(id, TransformComponent, isActive, boolean);
		}

		void GetTransform_Active_Engine(unsigned int id, bool* boolean) {
			GetEngineType(id, TransformComponent, isActive, *boolean);
		}

		void SetCollider_Active_Engine(unsigned int id, bool boolean) {
			SetEngineType(id, ColliderComponent, isActive, boolean);
		}

		void GetCollider_Active_Engine(unsigned int id, bool* boolean) {
			GetEngineType(id, ColliderComponent, isActive, *boolean);
		}

		void SetScript_Active_Engine(unsigned int id, bool boolean, MonoString* str) {
			SetEngineType(id, ScriptComponent, klassInstance.find(mono_string_to_utf8(str))->second.isActive, boolean);
		}

		void GetScript_Active_Engine(unsigned int id, bool* boolean, MonoString* str) {
			GetEngineType(id, ScriptComponent, klassInstance.find(mono_string_to_utf8(str))->second.isActive, *boolean);
		}*/

		void Active_Transform_Engine(unsigned int id, bool boolean) {
			if (boolean)
				dreamECSGame->EnableTransform(id);
			else {
				SetEngineType(id, TransformComponent, isActive, boolean);
			}
		}


		void Active_Collider_Engine(unsigned int id, bool boolean) {
			SetEngineType(id, ColliderComponent, isActive, boolean);
		}
		
		void Active_Light_Engine(unsigned int id, bool boolean) {
			SetEngineType(id, LightComponent, isActive, boolean);
		}
		
		void Active_Text_Engine(unsigned int id, bool boolean) {
			SetEngineType(id, FontComponent, isActive, boolean);
		}

		void Active_Script_Engine(unsigned int id, bool boolean, MonoString* str) {
			char* text = mono_string_to_utf8(str);
			SetEngineType(id, ScriptComponent, klassInstance.find(text)->second.isActive, boolean);
			mono_free(text);
		}
	}
}
