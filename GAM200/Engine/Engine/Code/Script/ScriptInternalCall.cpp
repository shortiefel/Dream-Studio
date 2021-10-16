/*
@file    ScriptInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Serialize/GameSceneSerializer.hpp" //Serialize Prefab

#include <mono/metadata/assembly.h>

#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/Scene/SceneManager.hpp"

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Input/Input.hpp" //Input key/mouse code

#include "Engine/Header/ECS/System/CollisionSystem.hpp" //For raycast
#include "Engine/Header/Physics/Ray.hpp" //For raycast

#define GetEngineType(ID, type, paramName, param)\
type* ctype = DreamECS::GetInstance().GetComponentPTR<type>(ID);\
if (!ctype) return;\
param = ctype->paramName;

#define SetEngineType(ID, type, paramName, param)\
type* ctype = DreamECS::GetInstance().GetComponentPTR<type>(ID);\
if (!ctype) return;\
ctype->paramName = param;



namespace Engine {
	//Function to call when writing to console (With editor function ptr is overwritten)
	void(*ConsoleFuncPtr)(std::string) = [](std::string) { printf("Not set"); };

	void GetTransform_Position_Engine(unsigned int id, Math::vec2* outVec2);
	void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2);
	void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2);
	void GetTransform_Scale_Engine(unsigned int id, Math::vec2* outVec2);
	void SetTransform_Scale_Engine(unsigned int id, Math::vec2* inVec2);
	void GetTransform_Angle_Engine(unsigned int id, float* outVec2);
	void SetTransform_Angle_Engine(unsigned int id, float* inVec2);
	void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2);
	void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2);

	bool Input_IsKeyPressed(Input_KeyCode key);
	bool Input_IsMouseButtonPressed(Input_MouseCode button);
	void Input_GetMousePosition(Math::vec2* outPosition);

	bool HasComponent_Transform_Engine(unsigned int id);
	bool HasComponent_Collider_Engine(unsigned int id);

	void Destroy_Entity_Engine(unsigned int id);
	void Destroy_Transform_Engine(unsigned int id);
	void Destroy_Collider_Engine(unsigned int id);
	void Destroy_Script_Engine(unsigned int id, MonoString* str);

	void SetTransform_Active_Engine(unsigned int id, bool boolean);
	void GetTransform_Active_Engine(unsigned int id, bool* boolean);
	void SetCollider_Active_Engine(unsigned int id, bool boolean);
	void GetCollider_Active_Engine(unsigned int id, bool* boolean);
	void SetScript_Active_Engine(unsigned int id, bool boolean, MonoString* str);
	void GetScript_Active_Engine(unsigned int id, bool* boolean, MonoString* str);

	void Instantiate_Prefab(MonoString* prefabName, Math::vec2 position, float angle);

	void GetDeltaTime_Engine(float* dt);

	void LoadScene_Engine(MonoString* sceneName);

	bool RayCast_Engine(Math::vec2 pos, Math::vec2 dir, float* hit, float distance);

	void ConsoleWrite_Engine(MonoString* message);


	void RegisterInternalCall() {
		mono_add_internal_call("Transform::GetTransform_Position_Engine", GetTransform_Position_Engine);
		mono_add_internal_call("Transform::SetTransform_Position_Engine", SetTransform_Position_Engine);
		mono_add_internal_call("Transform::MoveTransform_Position_Engine", MoveTransform_Position_Engine);
		mono_add_internal_call("Transform::GetTransform_Scale_Engine", GetTransform_Scale_Engine);
		mono_add_internal_call("Transform::SetTransform_Scale_Engine", SetTransform_Scale_Engine);
		mono_add_internal_call("Transform::GetTransform_Angle_Engine", GetTransform_Angle_Engine);
		mono_add_internal_call("Transform::SetTransform_Angle_Engine", SetTransform_Angle_Engine);
		mono_add_internal_call("Transform::GetTransform_forward_Engine", GetTransform_forward_Engine);
		mono_add_internal_call("Transform::GetTransform_right_Engine", GetTransform_right_Engine);

		mono_add_internal_call("Input::IsKeyPressed_Engine", Input_IsKeyPressed);
		mono_add_internal_call("Input::IsMousePressed_Engine", Input_IsMouseButtonPressed);
		mono_add_internal_call("Input::GetMousePosition_Engine", Input_GetMousePosition);

		mono_add_internal_call("MonoBehaviour::HasComponent_Transform_Engine", HasComponent_Transform_Engine);
		mono_add_internal_call("MonoBehaviour::HasComponent_Collider_Engine", HasComponent_Collider_Engine);

		mono_add_internal_call("MonoBehaviour::Destroy_Entity_Engine", Destroy_Entity_Engine);
		mono_add_internal_call("MonoBehaviour::Destroy_Transform_Engine", Destroy_Transform_Engine);
		mono_add_internal_call("MonoBehaviour::Destroy_Collider_Engine", Destroy_Collider_Engine);
		mono_add_internal_call("MonoBehaviour::Destroy_Script_Engine", Destroy_Script_Engine);

		mono_add_internal_call("Transform::SetTransform_Active_Engine", SetTransform_Active_Engine);
		mono_add_internal_call("Transform::GetTransform_Active_Engine", GetTransform_Active_Engine);
		mono_add_internal_call("Collider::SetCollider_Active_Engine", SetCollider_Active_Engine);
		mono_add_internal_call("Collider::GetCollider_Active_Engine", GetCollider_Active_Engine);
		mono_add_internal_call("MonoBehaviour::SetScript_Active_Engine", SetScript_Active_Engine);
		mono_add_internal_call("MonoBehaviour::GetScript_Active_Engine", GetScript_Active_Engine);

		mono_add_internal_call("MonoBehaviour::Instantiate_Prefab", Instantiate_Prefab);

		mono_add_internal_call("Time::GetDeltaTime_Engine", GetDeltaTime_Engine);

		mono_add_internal_call("SceneManager::LoadScene_Engine", LoadScene_Engine);

		mono_add_internal_call("Physics::RayCast_Engine", RayCast_Engine);

		mono_add_internal_call("Debug::ConsoleWrite_Engine", ConsoleWrite_Engine);
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
	Transform
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetTransform_Position_Engine(unsigned int id, Math::vec2* outVec2) {
		GetEngineType(id, TransformComponent, position, *outVec2);
	}
	void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2) {
		SetEngineType(id, TransformComponent, position, *inVec2);
	}
	void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2) {
		//call hascomponent with entityid
		TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(id);
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

	void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2) {
		TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(id);
		if (!transform) return;
		float newAngle = Math::radians(transform->angle + 90.f);
		*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
	}

	void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2) {
		TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(id);
		if (!transform) return;
		float newAngle = Math::radians(transform->angle);
		*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Input
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool Input_IsKeyPressed(Input_KeyCode key)
	{
		return Input::IsKeyPressed(key);
	}

	bool Input_IsMouseButtonPressed(Input_MouseCode button)
	{
		return Input::IsMousePressed(button);
	}

	void Input_GetMousePosition(Math::vec2* outPosition)
	{
		Math::vec2 result = Input::GetMousePosition();
		*outPosition = result;
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Check if component exist
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool HasComponent_Transform_Engine(unsigned int id) {
		TransformComponent* tem = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(id);
		return !(tem == nullptr);
	}

	bool HasComponent_Collider_Engine(unsigned int id) {
		ColliderComponent* tem = DreamECS::GetInstance().GetComponentPTR<ColliderComponent>(id);
		return !(tem == nullptr);
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Destroy
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Destroy_Entity_Engine(unsigned int id) {
		DreamECS::GetInstance().DestroyEntity(id);
	}

	void Destroy_Transform_Engine(unsigned int id) {
		DreamECS::GetInstance().RemoveComponent<TransformComponent>(id);
	}

	void Destroy_Collider_Engine(unsigned int id) {
		DreamECS::GetInstance().RemoveComponent<ColliderComponent>(id);
	}

	void Destroy_Script_Engine(unsigned int id, MonoString* str) {
		ScriptComponent* csScript = DreamECS::GetInstance().GetComponentPTR<ScriptComponent>(id);
		if (!csScript) return;
		csScript->RemoveScript(mono_string_to_utf8(str));
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Active
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void SetTransform_Active_Engine(unsigned int id, bool boolean) {
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
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Prefab
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Instantiate_Prefab(MonoString* prefabName, Math::vec2 position, float angle) {
		//GameSceneSerializer::DeserializeScene(mono_string_to_utf8(prefabName));
		GameSceneSerializer::DeserializePrefab(mono_string_to_utf8(prefabName), position, angle);
		if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
	}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Deltatime
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetDeltaTime_Engine(float* dt) {
		*dt = GameState::GetInstance().GetDeltaTime();
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Scene
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void LoadScene_Engine(MonoString* sceneName) {
		SceneManager::GetInstance().ChangeScene(mono_string_to_utf8(sceneName));
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Physics
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool RayCast_Engine(Math::vec2 pos, Math::vec2 dir, float* hit, float distance) {
		if (distance < 0) distance = RAY_LENGTH;
		return CollisionSystem::GetInstance().RayCast(Engine::Ray{ pos, dir, distance }, hit);
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Console Write
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void SetConsoleWriteFunc(void(*fp)(std::string)) {
		ConsoleFuncPtr = fp;
	}
	
	void ConsoleWrite_Engine(MonoString* message) {
		ConsoleFuncPtr(mono_string_to_utf8(message));
	}
}