/*
@file    ScriptInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    25/08/2021
\brief
This file contain the definition of ScriptInternalCall
Register all internal call function used by the C# side


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Script/ScriptInternalCall.hpp"
#include "Engine/Header/Script/Scripting.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp" //Serialize Prefab
#include "Engine/Header/Scene/SceneManager.hpp"

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/System/CameraSystem.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Random/Random.hpp"
#include "Engine/Header/Input/Input.hpp" //Input key/mouse code

#include "Engine/Header/ECS/System/UISystem.hpp"

#include "Engine/Header/ECS/System/CollisionSystem.hpp" //For raycast
#include "Engine/Header/Physics/Collision.hpp"
#include "Engine/Header/Physics/Ray.hpp" //For raycast
#include "Engine/Header/Graphic/SpaceTransform.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"

#include "Engine/Header/Event/WindowEvent.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Window.hpp"

#include "Engine/Header/Script/InternalCall/GridInternalCall.hpp"

#include "Engine/Header/Graphic/Picking2D.hpp"
#include "Engine/Header/Window.hpp"

#include "Engine/Header/Management/Settings.hpp"

#include <mono/metadata/assembly.h>

#define GetEngineType(ID, type, paramName, param)\
type* ctype = dreamECSGame->GetComponentPTR<type>(ID);\
if (ctype != nullptr) param = ctype->paramName;

#define SetEngineType(ID, type, paramName, param)\
type* ctype = dreamECSGame->GetComponentPTR<type>(ID);\
if (ctype != nullptr) ctype->paramName = param;

#define GET_COMPONENT_PTR(type) type* tem = dreamECSGame->GetComponentPTR<type>(id);\
								return !(tem == nullptr);


namespace Engine {
	//Function to call when writing to console (With editor function ptr is overwritten)
	//Function does nothing in actual game
	void(*ConsoleFuncPtr)(std::string) = [](std::string) {};

	Math::vec2 game_viewportSize{}; //Window size

	bool gameViewportCallBack(const WindowResizeEvent& e) {
		Math::uvec2 sz = e.GetSize();
		game_viewportSize = Math::vec2{ static_cast<float>(sz.x), static_cast<float>(sz.y) };
		return true;
	}

	Math::mat3(*GetViewportFuncPtr)() = []() -> Math::mat3 { 
		return Math::mat3(2.f / game_viewportSize.x, 0.f, 0.f,
			0.f, 2.f / game_viewportSize.y, 0.f,
			-1.f, -1.f, 1.f);
	};
	Math::vec2(*GetMousePositionFuncPtr)() = []() {  
		//window y size - y position (flip y value)
		Math::vec2 pos = Input::GetMousePosition();
		pos.y = Window::GetInstance().GetWindowSize().y - pos.y;
		return pos;
	};

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Entity
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void CreateEntity_Engine(unsigned int* entityId, MonoString* str);
	void FindEntity_Engine(int* entityId, MonoString* str);

	bool AddComponent_Scripts_Engine(unsigned int entityId, MonoString* name);
	bool AddComponent_Transform_Engine(unsigned int entityId);
	bool AddComponent_Collider_Engine(unsigned int entityId);
	bool AddComponent_Camera_Engine(unsigned int entityId);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Transform
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetTransform_Position_Engine(unsigned int id, Math::vec2* outVec2, bool local);
	void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2, bool local);
	void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2);
	void GetTransform_Scale_Engine(unsigned int id, Math::vec2* outVec2);
	void SetTransform_Scale_Engine(unsigned int id, Math::vec2* inVec2);
	void GetTransform_Angle_Engine(unsigned int id, float* outVec2);
	void SetTransform_Angle_Engine(unsigned int id, float* inVec2);
	void GetTransform_Layer_Engine(unsigned int id, int* outLayer);
	void SetTransform_Layer_Engine(unsigned int id, int* inLayer);
	//void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2);
	void GetTransform_up_Engine(unsigned int id, Math::vec2* outVec2);
	void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2);
	void SetParent_Engine(int parentId, unsigned int child);

	void Transform_GetChildCount_Engine(unsigned int entityId, int* result);
	void Transform_GetChild_Engine(unsigned int entityId, int index, unsigned int* targetId);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Camera
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ScreenToWorldPoint_Engine(unsigned int id, Math::vec3* outPosition, Math::vec3 inPosition);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Texture
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ChangeTexture_Engine(unsigned int entityID, MonoString* name);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Rigidbody2d
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* velocity);
	void SetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* inVec2);
	void GetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* velocity);
	void SetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* inVec2);
	/*void GetRigidbody_Inertia_Engine(unsigned int entityID, float* result);
	void SetRigidbody_Inertia_Engine(unsigned int entityID, float* inertia);*/
	void AddForce_Physics_Engine(unsigned int entityID, Math::vec2 force);
	void AddTorque_Physics_Engine(unsigned int entityID, float torque);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Text/Font
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void SetFont_Text_Engine(unsigned int entityID, MonoString* _text);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Input
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool GetKey_Engine(Input_KeyCode key);
	bool GetKeyDown_Engine(Input_KeyCode key);

	bool GetMouse_Engine(Input_MouseCode button);
	bool GetMouseDown_Engine(Input_MouseCode button);
	bool GetMouseUp_Engine(Input_MouseCode button);

	void GetMousePosition_Engine(Math::vec2* outPosition);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Check if component exist
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool HasComponent_Scripts_Engine(unsigned int id, MonoString* str);
	bool HasComponent_Transform_Engine(unsigned int id);
	bool HasComponent_Collider_Engine(unsigned int id);
	bool HasComponent_Camera_Engine(unsigned int id);
	bool HasComponent_Rigidbody_Engine(unsigned int id);
	bool HasComponent_Texture_Engine(unsigned int id);
	bool HasComponent_Font_Engine(unsigned int id);

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
	void Active_Script_Engine(unsigned int id, bool boolean, MonoString* str);

	void SetActive_GameObject_Engine(unsigned int entityId, bool state);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Prefab
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Instantiate_Prefab_Transform_Engine(MonoString* prefabName, int entityId, unsigned int* newId);
	void Instantiate_Prefab_Position_Engine(MonoString* prefabName, Math::vec3 pos, int layer, unsigned int* newId);
	//void Instantiate_Prefab_Engine(MonoString* prefabName, Math::vec2 position, float angle);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Deltatime
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetDeltaTime_Engine(float* dt);
	void SetTimeScale_Engine(float timeScale);
	void GetTimeScale_Engine(float* timeScale);
	void WaitForSeconds_Engine(float timer);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Scene
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void LoadScene_Engine(MonoString* sceneName);
	void SetDrawMode_Engine(bool state);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Physics
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool RayCast_Engine(Math::vec3 pos, Math::vec2 dir, int ignoreTarget, float distance, unsigned int* entity_id, float* hitDistance, Math::vec2* hitPoint);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Console Write
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ConsoleWrite_Engine(MonoString* message);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Random
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Random_Range_Engine(int num1, int num2, int* answer);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Math
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Atan2_Engine(float* outFloat, float xVal, float yVal);
	void Approximately_Engine(float num1, float num2, bool* result);

	void GetDistance_Engine(float* outFloat, Math::vec2 a, Math::vec2 b);
	void GetLength_Engine(float* length, Math::vec2 vec);
	void GetNormalised_Engine(Math::vec2* vec);
	void DotProduct_Engine(float* outFloat, Math::vec2 lhs, Math::vec2 rhs);

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Application
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Quit_Engine();


	void RegisterInternalCall() {
		//Register Event callback
		WindowResizeEvent::RegisterFunction(gameViewportCallBack);
		game_viewportSize = Math::vec2{ static_cast<float>(Settings::windowWidth), static_cast<float>(Settings::windowHeight) };

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Entity
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("GameObject::CreateEntity_Engine", CreateEntity_Engine);
		mono_add_internal_call("GameObject::FindEntity_Engine", FindEntity_Engine);

		mono_add_internal_call("GameObject::AddComponent_Scripts_Engine", AddComponent_Scripts_Engine);
		mono_add_internal_call("GameObject::AddComponent_Transform_Engine", AddComponent_Transform_Engine);
		mono_add_internal_call("GameObject::AddComponent_Collider_Engine", AddComponent_Collider_Engine);
		mono_add_internal_call("GameObject::AddComponent_Camera_Engine", AddComponent_Camera_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Transform
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Transform::GetTransform_Position_Engine", GetTransform_Position_Engine);
		mono_add_internal_call("Transform::SetTransform_Position_Engine", SetTransform_Position_Engine);
		mono_add_internal_call("Transform::MoveTransform_Position_Engine", MoveTransform_Position_Engine);
		mono_add_internal_call("Transform::GetTransform_Scale_Engine", GetTransform_Scale_Engine);
		mono_add_internal_call("Transform::SetTransform_Scale_Engine", SetTransform_Scale_Engine);
		mono_add_internal_call("Transform::GetTransform_Angle_Engine", GetTransform_Angle_Engine);
		mono_add_internal_call("Transform::SetTransform_Angle_Engine", SetTransform_Angle_Engine);
		mono_add_internal_call("Transform::GetTransform_Layer_Engine", GetTransform_Layer_Engine);
		mono_add_internal_call("Transform::SetTransform_Layer_Engine", SetTransform_Layer_Engine);
		//mono_add_internal_call("Transform::GetTransform_forward_Engine", GetTransform_forward_Engine);
		mono_add_internal_call("Transform::GetTransform_up_Engine", GetTransform_up_Engine);
		mono_add_internal_call("Transform::GetTransform_right_Engine", GetTransform_right_Engine);
		mono_add_internal_call("Transform::SetParent_Engine", SetParent_Engine);

		mono_add_internal_call("Transform::Transform_GetChildCount_Engine", Transform_GetChildCount_Engine);
		mono_add_internal_call("Transform::Transform_GetChild_Engine", Transform_GetChild_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Camera
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Camera::ScreenToWorldPoint_Engine", ScreenToWorldPoint_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Texture
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Texture::ChangeTexture_Engine", ChangeTexture_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Rigidbody2d
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Rigidbody2D::GetRigidbody_LinearVelocity_Engine", GetRigidbody_LinearVelocity_Engine);
		mono_add_internal_call("Rigidbody2D::SetRigidbody_LinearVelocity_Engine", SetRigidbody_LinearVelocity_Engine);
		mono_add_internal_call("Rigidbody2D::GetRigidbody_AngularVelocity_Engine", GetRigidbody_AngularVelocity_Engine);
		mono_add_internal_call("Rigidbody2D::SetRigidbody_AngularVelocity_Engine", SetRigidbody_AngularVelocity_Engine);
		/*mono_add_internal_call("Rigidbody2D::GetRigidbody_Inertia_Engine", GetRigidbody_Inertia_Engine);
		mono_add_internal_call("Rigidbody2D::SetRigidbody_Inertia_Engine", SetRigidbody_Inertia_Engine);*/
		mono_add_internal_call("Rigidbody2D::AddForce_Physics_Engine", AddForce_Physics_Engine);
		mono_add_internal_call("Rigidbody2D::AddTorque_Physics_Engine", AddTorque_Physics_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Text/Font
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Text::SetFont_Text_Engine", SetFont_Text_Engine);


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Input
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Input::GetKey_Engine", GetKey_Engine);
		mono_add_internal_call("Input::GetKeyDown_Engine", GetKeyDown_Engine);

		mono_add_internal_call("Input::GetMouse_Engine", GetMouse_Engine);
		mono_add_internal_call("Input::GetMouseDown_Engine", GetMouseDown_Engine);
		mono_add_internal_call("Input::GetMouseUp_Engine", GetMouseUp_Engine);
		mono_add_internal_call("Input::GetMousePosition_Engine", GetMousePosition_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Check if component exist
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("IBehaviour::HasComponent_Scripts_Engine", HasComponent_Scripts_Engine);
		mono_add_internal_call("IBehaviour::HasComponent_Transform_Engine", HasComponent_Transform_Engine);
		mono_add_internal_call("IBehaviour::HasComponent_Collider_Engine", HasComponent_Collider_Engine);
		mono_add_internal_call("IBehaviour::HasComponent_Camera_Engine", HasComponent_Camera_Engine);
		mono_add_internal_call("IBehaviour::HasComponent_Rigidbody_Engine", HasComponent_Rigidbody_Engine);
		mono_add_internal_call("IBehaviour::HasComponent_Texture_Engine", HasComponent_Texture_Engine);
		mono_add_internal_call("IBehaviour::HasComponent_Font_Engine", HasComponent_Font_Engine);
		
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
		mono_add_internal_call("MonoBehaviour::Active_Script_Engine", Active_Script_Engine);

		mono_add_internal_call("GameObject::SetActive_GameObject_Engine", SetActive_GameObject_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Prefab
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("MonoBehaviour::Instantiate_Prefab_Transform_Engine", Instantiate_Prefab_Transform_Engine);
		mono_add_internal_call("MonoBehaviour::Instantiate_Prefab_Position_Engine", Instantiate_Prefab_Position_Engine);
		//mono_add_internal_call("MonoBehaviour::Instantiate_Prefab_Engine", Instantiate_Prefab_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Deltatime
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Time::GetDeltaTime_Engine", GetDeltaTime_Engine);
		mono_add_internal_call("Time::SetTimeScale_Engine", SetTimeScale_Engine);
		mono_add_internal_call("Time::GetTimeScale_Engine", GetTimeScale_Engine);
		mono_add_internal_call("Time::WaitForSeconds_Engine", WaitForSeconds_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Scene
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("SceneManager::LoadScene_Engine", LoadScene_Engine);
		mono_add_internal_call("SceneManager::SetDrawMode_Engine", SetDrawMode_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Physics
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Physics2D::RayCast_Engine", RayCast_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Console Write
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Debug::ConsoleWrite_Engine", ConsoleWrite_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Random
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Random::Random_Range_Engine", Random_Range_Engine);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Math
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Mathf::Atan2_Engine", Atan2_Engine);
		mono_add_internal_call("Mathf::Approximately_Engine", Approximately_Engine);

		mono_add_internal_call("Vector2::GetDistance_Engine", GetDistance_Engine);
		mono_add_internal_call("Vector2::GetLength_Engine", GetLength_Engine);
		mono_add_internal_call("Vector2::GetNormalised_Engine", GetNormalised_Engine);
		mono_add_internal_call("Vector2::DotProduct_Engine", DotProduct_Engine);
		
		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Application
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Application::Quit_Engine", Quit_Engine);
		

		RegisterGridInternalCall();
	}

	//void GetComponentInScriptEmbeded(unsigned int id, Transform* outTransform) {
	//	//call hascomponent with entityid
	//	Transform* transform = nullptr;
	//	DreamECS::HasComponent<Transform>(transform, id);
	//	*outTransform = *transform;

	//	/*Transform& transform = gCoordinator.GetCom<Transform>(id);
	//	*outTransform = transform;*/
	//}

	//void SetComponentInScriptEmbeded(unsigned int id, Transform* inTransform) {
	//	//call hascomponent with entityid
	//	/*Transform* transform = nullptr;
	//	gCoordinator.HasCom<Transform>(transform, id);
	//	*transform = *inTransform;*/
	//	Transform& transform = DreamECS::GetComponent<Transform>(id);
	//	transform = *inTransform;
	//}
	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Entity
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
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

	bool AddComponent_Scripts_Engine(unsigned int entityId, MonoString* name) {
		//return false;
		char* text = mono_string_to_utf8(name);
		bool result = dreamECSGame->AddComponent<ScriptComponent>(ScriptComponent{ entityId, text });
		mono_free(text);
		return result;
	}

	bool AddComponent_Transform_Engine(unsigned int entityId) {
		return dreamECSGame->AddComponent<TransformComponent>(TransformComponent{ entityId });
	}

	bool AddComponent_Collider_Engine(unsigned int entityId) {
		return dreamECSGame->AddComponent<ColliderComponent>(ColliderComponent{ entityId });
	}

	bool AddComponent_Camera_Engine(unsigned int entityId) {
		return dreamECSGame->AddComponent<CameraComponent>(CameraComponent{ entityId });
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Transform
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetTransform_Position_Engine(unsigned int id, Math::vec2* outVec2, bool local) {
		if (!local) {
			GetEngineType(id, TransformComponent, position, *outVec2);
		}
		else {
			GetEngineType(id, TransformComponent, localPosition, *outVec2);
		}
	}
	void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2, bool local) {
		if (!local) {
			//SetEngineType(id, TransformComponent, position, *inVec2);

			TransformComponent* ctype = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (!ctype) return;
			Math::vec2 moveDis = *inVec2 - ctype->position;
			ctype->position = *inVec2;
			
			auto& entityMap = dreamECSGame->GetUsedConstEntityMap();
			const auto& itr = entityMap.find(ctype->GetEntityId());
			const auto& entity = itr->second;
			Entity_id parent = entity.parent;

			if (parent != DEFAULT_ENTITY_ID) //TODO: Need to fix parent-child
				ctype->localPosition -= dreamECSGame->GetComponent<TransformComponent>(parent).position;
			else
				ctype->localPosition = *inVec2;

			for (auto& newId : entity.child) {
				TransformComponent* newTransform = dreamECSGame->GetComponentPTR<TransformComponent>(newId);
				if (newTransform != nullptr)
					newTransform->position += moveDis;
			}
		}
		else {
			//SetEngineType(id, TransformComponent, localPosition, *inVec2);

			TransformComponent* ctype = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (!ctype) return;
			Math::vec2 moveDis = *inVec2 - ctype->position;
			ctype->localPosition = *inVec2;
			auto& entityMap = dreamECSGame->GetUsedConstEntityMap();
			const auto& itr = entityMap.find(ctype->GetEntityId());
			const auto& entity = itr->second;
			Entity_id parent = entity.parent;

			if (parent != DEFAULT_ENTITY_ID) //TODO: Need to fix parent-child
				ctype->position = ctype->localPosition + dreamECSGame->GetComponent<TransformComponent>(parent).position;
			else
				ctype->position = *inVec2;

			for (auto& newId : entity.child) {
				TransformComponent* newTransform = dreamECSGame->GetComponentPTR<TransformComponent>(newId);
				if (newTransform != nullptr)
					newTransform->position += moveDis;
			}
		}

	}
	void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2) {
		//call hascomponent with entityid
		TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
		if (!transform) return;
		transform->position += *inVec2;
	}

	void GetTransform_Scale_Engine(unsigned int id, Math::vec2* outVec2) {
		GetEngineType(id, TransformComponent, scale, *outVec2);
	}
	void SetTransform_Scale_Engine(unsigned int id, Math::vec2* inVec2) {
		SetEngineType(id, TransformComponent, scale, *inVec2);
	}


	void GetTransform_Angle_Engine(unsigned int id, float* outVec2) {
		GetEngineType(id, TransformComponent, angle, *outVec2);

	}
	void SetTransform_Angle_Engine(unsigned int id, float* inVec2) {
		SetEngineType(id, TransformComponent, angle, *inVec2);
	}

	void GetTransform_Layer_Engine(unsigned int id, int* outLayer) {
		GetEngineType(id, TransformComponent, layer, *outLayer);
	}
	void SetTransform_Layer_Engine(unsigned int id, int* inLayer) {
		SetEngineType(id, TransformComponent, layer, *inLayer);
	}
	/*void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2) {
		TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
		if (!transform) return;
		float newAngle = Math::radians(transform->angle);
		*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
	}*/

	void GetTransform_up_Engine(unsigned int id, Math::vec2* outVec2) {
		TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
		if (!transform) return;
		float newAngle = Math::radians(transform->angle + 90.f);
		*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
	}

	void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2) {
		TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
		if (!transform) return;
		float newAngle = Math::radians(transform->angle);
		*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
	}

	void SetParent_Engine(int parentId, unsigned int child) {
		if (parentId < 0) dreamECSGame->Unparent(child);
		else dreamECSGame->Parent(parentId, child);
	}

	void Transform_GetChildCount_Engine(unsigned int entityId, int* result) {
		const auto& entity = dreamECSGame->GetUsedConstEntityMap().find(entityId)->second;
		*result = static_cast<int>(entity.child.size());
	}

	void Transform_GetChild_Engine(unsigned int entityId, int index, unsigned int* targetId) {
		const auto& entity = dreamECSGame->GetUsedConstEntityMap().find(entityId)->second;
		*targetId = *(entity.child.find(index));
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Camera
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ScreenToWorldPoint_Engine(unsigned int id, Math::vec3* outPosition, Math::vec3 inPosition) {
		*outPosition = ScreenToWorldPoint(inPosition, CameraSystem::GetInstance().GetInverseTransform(&id), GetViewportFuncPtr());
	}

	void SetGetViewportFunc(Math::mat3(*fp)()) {
		GetViewportFuncPtr = fp;
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Texture
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ChangeTexture_Engine(unsigned int entityID, MonoString* name) {
		const auto ptr = dreamECSGame->GetComponentPTR<TextureComponent>(entityID);
		if (ptr != nullptr) {
			char* text = mono_string_to_utf8(name);
			GraphicImplementation::SetTexture(ptr, "Assets\\Textures\\" + std::string{ text } + ".png");
			mono_free(text);
		}
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Rigidbody2d
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* velocity) {
		GetEngineType(entityID, RigidBodyComponent, linearVelocity, *velocity);
	}

	void SetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* inVec2) {
		SetEngineType(entityID, RigidBodyComponent, linearVelocity, *inVec2);
	}

	void GetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* velocity) {
		GetEngineType(entityID, RigidBodyComponent, angularVelocity, *velocity);
	}

	void SetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* inVec2) {
		SetEngineType(entityID, RigidBodyComponent, angularVelocity, *inVec2);
	}

	/*void GetRigidbody_Inertia_Engine(unsigned int entityID, float* result) {
		GetEngineType(entityID, RigidBodyComponent, inertia, *result);
	}

	void SetRigidbody_Inertia_Engine(unsigned int entityID, float* inertia) {
		SetEngineType(entityID, RigidBodyComponent, inertia, *inertia);
	}*/

	void AddForce_Physics_Engine(unsigned int entityID, Math::vec2 force) {
		RigidBodyComponent* rb = dreamECSGame->GetComponentPTR<RigidBodyComponent>(entityID);
		if (rb != nullptr) {
			float magnitude = Math::length(force);
			if (Math::EpsilonCheck(magnitude)) magnitude = 1.f;
			force = force / magnitude;
			rb->linearForces.emplace_back(LinearForces{ force, magnitude });
		}
	}

	void AddTorque_Physics_Engine(unsigned int entityID, float torque) {
		RigidBodyComponent* rb = dreamECSGame->GetComponentPTR<RigidBodyComponent>(entityID);
		if (rb != nullptr) {
			int direction = torque < 0.f ? -1 : 1;
			torque *= direction;
			rb->rotationForces.emplace_back(RotationForces{ torque, direction });
		}
	}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Text/Font
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void SetFont_Text_Engine(unsigned int entityID, MonoString* _text) {
		char* tempText = mono_string_to_utf8(_text);
		SetEngineType(entityID, FontComponent, text, std::string{ tempText });
		mono_free(tempText);
	}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Input
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

	bool GetKey_Engine(Input_KeyCode key) { return Input::IsKeyHold(key); }
	bool GetKeyDown_Engine(Input_KeyCode key) { return Input::IsKeyPressed(key); }

	bool GetMouse_Engine(Input_MouseCode button) { return Input::IsMouseHold(button); }
	bool GetMouseDown_Engine(Input_MouseCode button) { return Input::IsMousePressed(button); }
	bool GetMouseUp_Engine(Input_MouseCode button) { return Input::IsMouseReleased(button); }

	void GetMousePosition_Engine(Math::vec2* outPosition) {
		*outPosition = GetMousePositionFuncPtr();
	}

	void SetGetMousePositionFunc(Math::vec2(*fp)()) {
		GetMousePositionFuncPtr = fp;
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

	bool HasComponent_Transform_Engine(unsigned int id) {
		GET_COMPONENT_PTR(TransformComponent);
	}

	bool HasComponent_Collider_Engine(unsigned int id) {
		GET_COMPONENT_PTR(ColliderComponent);
	}

	bool HasComponent_Camera_Engine(unsigned int id) {
		GET_COMPONENT_PTR(CameraComponent);
	}

	bool HasComponent_Rigidbody_Engine(unsigned int id) {
		GET_COMPONENT_PTR(RigidBodyComponent);
	}

	bool HasComponent_Texture_Engine(unsigned int id) {
		GET_COMPONENT_PTR(TextureComponent);
	}

	bool HasComponent_Font_Engine(unsigned int id) {
		GET_COMPONENT_PTR(FontComponent);
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
		SetEngineType(id, TransformComponent, isActive, boolean);
	}

	void Active_Collider_Engine(unsigned int id, bool boolean) {
		SetEngineType(id, ColliderComponent, isActive, boolean);
	}

	void Active_Script_Engine(unsigned int id, bool boolean, MonoString* str) {
		char* text = mono_string_to_utf8(str);
		SetEngineType(id, ScriptComponent, klassInstance.find(text)->second.isActive, boolean);
		mono_free(text);
	}

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

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Prefab
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Instantiate_Prefab_Transform_Engine(MonoString* prefabName, int entityId, unsigned int* newId) {
		char* text = mono_string_to_utf8(prefabName);
		if (entityId < 0) {
			GameSceneSerializer::DeserializePrefab(text, newId, Math::vec2{ 0.f,0.f }, 0.f);
		}
		else {
			const auto& transform = dreamECSGame->GetComponent<TransformComponent>(static_cast<unsigned int>(entityId));
			GameSceneSerializer::DeserializePrefab(text, newId, transform.position, transform.angle);
		}
		mono_free(text);
		//if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
	}

	void Instantiate_Prefab_Position_Engine(MonoString* prefabName, Math::vec3 pos, int layer, unsigned int* newId) {
		char* text = mono_string_to_utf8(prefabName);
		std::cout << "pref " << std::string{ text } << "\n";
		GameSceneSerializer::DeserializePrefab(text, newId, Math::vec2{ pos.x, pos.y }, 0, layer);
		mono_free(text);
	}

	//void Instantiate_Prefab_Engine(MonoString* prefabName, Math::vec2 position, float angle) {
	//	unsigned int id;
	//	GameSceneSerializer::DeserializePrefab(mono_string_to_utf8(prefabName), position, angle, id);
	//	//if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
	//}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Deltatime
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetDeltaTime_Engine(float* dt) {
		*dt = DeltaTime::GetInstance().GetDeltaTime();
	}

	void SetTimeScale_Engine(float timeScale) {
		DeltaTime::GetInstance().SetTimeScale(timeScale);
	}

	void GetTimeScale_Engine(float* timeScale) {
		*timeScale = DeltaTime::GetInstance().GetTimeScale();
	}

	void WaitForSeconds_Engine(float) {

	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Scene
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void LoadScene_Engine(MonoString* sceneName) {
		char* text = mono_string_to_utf8(sceneName);
		UISystem::GetInstance().SetFadeToBlack(text);
		//SceneManager::GetInstance().ChangeScene(text);
		mono_free(text);
	}

	void SetDrawMode_Engine(bool state) {
		GameState::GetInstance().SetShouldDraw(state);
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Physics
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool RayCast_Engine(Math::vec3 pos, Math::vec2 dir, int ignoreTarget, float distance, unsigned int* entity_id, float* hitDistance, Math::vec2* hitPoint) {
		RaycastHit hitCast;
		//if (distance < 0) distance = RAY_LENGTH;
		std::uint32_t ignored = ignoreTarget < 0 ? DEFAULT_ENTITY_ID : ignoreTarget;
		CollisionSystem::GetInstance().RayCast(Engine::Ray{ Math::vec2 {pos.x, pos.y}, dir, distance }, &hitCast, ignored);
		*hitDistance = hitCast.distance;
		*hitPoint = hitCast.point;
		*entity_id = hitCast.entity_id;

		if (hitCast.entity_id < 0) return false;
		return true;
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Console Write
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void SetConsoleWriteFunc(void(*fp)(std::string)) {
		ConsoleFuncPtr = fp;
	}

	void ConsoleWrite_Engine(MonoString* message) {
		char* text = mono_string_to_utf8(message);
		ConsoleFuncPtr(text);
		mono_free(text);
	}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Random
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Random_Range_Engine(int num1, int num2, int* answer) {
		Random::Range(num1, num2, answer);
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Math
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Atan2_Engine(float* outFloat, float xVal, float yVal) {
		if (Math::EpsilonCheck(xVal)) {
			*outFloat = 0.f;
			return;
		}
		*outFloat = atan2(yVal, xVal);
	}

	void Approximately_Engine(float num1, float num2, bool* result) {
		*result = Math::EpsilonCheck(num1, num2);
	}

	void GetDistance_Engine(float* outFloat, Math::vec2 a, Math::vec2 b) {
		*outFloat = Math::distance(a, b);
	}

	void GetLength_Engine(float* length, Math::vec2 vec) {
		*length = Math::length(vec);
	}

	void GetNormalised_Engine(Math::vec2* vec) {
		Math::vec2 temp = *vec;
		*vec = Math::normalize(temp);
	}

	void DotProduct_Engine(float* outFloat, Math::vec2 lhs, Math::vec2 rhs) {
		*outFloat = Math::dot(lhs, rhs);
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Application
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Quit_Engine() {
#ifdef _GAME_BUILD
		Engine::WindowCloseEvent event;
		Engine::EventDispatcher::SendEvent(event);
#else
		Scripting::CallDisplayFuncPtr("Game Stopped\n");
		SceneManager::GetInstance().Stop();
#endif
	}
}