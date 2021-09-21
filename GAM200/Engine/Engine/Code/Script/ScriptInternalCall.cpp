/*
@file    ScriptInternalCall.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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
#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#include <mono/metadata/assembly.h>

#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/ECS/ECSWrapper.hpp"

#include "Engine/Header/Input/Input.hpp" //Input key/mouse code

#include "Engine/Header/DeltaTime/DeltaTime.hpp" //To get deltaTime

#define GetEngineType(ID, type, paramName, param)\
type* ctype = DreamECS::GetComponentTest<type>(ID);\
if (!ctype) return;\
param = ctype->paramName;

#define SetEngineType(ID, type, paramName, param)\
type* ctype = DreamECS::GetComponentTest<type>(ID);\
if (!ctype) return;\
ctype->paramName = param;



namespace Engine {

	//extern Coordinator gCoordinator;
	//Coordinator& gCoordinator = DreamECS::GetCoordinator();

	/*void GetComponentInScriptEmbeded(unsigned int id, Transform* outTransform);
	void SetComponentInScriptEmbeded(unsigned int id, Transform* inTransform);*/

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

	void Destroy_Entity_Engine(unsigned int id);
	void Destroy_Transform_Engine(unsigned int id);
	void Destroy_Collider_Engine(unsigned int id);
	void Destroy_Script_Engine(unsigned int id, MonoString* str);

	void Active_Transform_Engine(unsigned int id, bool boolean);
	void Active_Collider_Engine(unsigned int id, bool boolean);
	void Active_Script_Engine(unsigned int id, bool boolean, MonoString* str);

	void GetDeltaTime_Engine(float* dt);


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

		mono_add_internal_call("MonoBehaviour::Destroy_Entity_Engine", Destroy_Entity_Engine);
		mono_add_internal_call("MonoBehaviour::Destroy_Transform_Engine", Destroy_Transform_Engine);
		mono_add_internal_call("MonoBehaviour::Destroy_Collider_Engine", Destroy_Collider_Engine);
		mono_add_internal_call("MonoBehaviour::Destroy_Script_Engine", Destroy_Script_Engine);

		mono_add_internal_call("MonoBehaviour::Active_Transform_Engine", Active_Transform_Engine);
		mono_add_internal_call("MonoBehaviour::Active_Collider_Engine", Active_Collider_Engine);
		mono_add_internal_call("MonoBehaviour::Active_Script_Engine", Active_Script_Engine);

		mono_add_internal_call("Time::GetDeltaTime_Engine", GetDeltaTime_Engine);
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
		GetEngineType(id, Transform, position, *outVec2);

	}
	void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2) {
		SetEngineType(id, Transform, position, *inVec2);
	}
	void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2) {
		//call hascomponent with entityid
		Transform* transform = DreamECS::GetComponentTest<Transform>(id);
		if (!transform) return;
		transform->position += *inVec2;
	}


	void GetTransform_Scale_Engine(unsigned int id, Math::vec2* outVec2) {
		GetEngineType(id, Transform, scale, *outVec2);
	}
	void SetTransform_Scale_Engine(unsigned int id, Math::vec2* inVec2) {
		SetEngineType(id, Transform, scale, *inVec2);
	}


	void GetTransform_Angle_Engine(unsigned int id, float* outVec2) {
		GetEngineType(id, Transform, angle, *outVec2);

	}
	void SetTransform_Angle_Engine(unsigned int id, float* inVec2) {
		SetEngineType(id, Transform, angle, *inVec2);
	}

	void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2) {
		Transform* transform = DreamECS::GetComponentTest<Transform>(id);
		if (!transform) return;
		float newAngle = Math::radians(transform->angle + 90.f);
		*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
	}

	void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2) {
		Transform* transform = DreamECS::GetComponentTest<Transform>(id);
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
		Transform* tem = nullptr;
		return DreamECS::HasComponent<Transform>(tem, id);
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Destroy
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Destroy_Entity_Engine(unsigned int id) {
		DreamECS::DestroyEntity(id);
	}

	void Destroy_Transform_Engine(unsigned int id) {
		DreamECS::RemoveComponent<Transform>(id);
	}

	void Destroy_Collider_Engine(unsigned int id) {
		DreamECS::RemoveComponent<Collider>(id);
	}

	void Destroy_Script_Engine(unsigned int id, MonoString* str) {
		CSScript* csScript = DreamECS::GetComponentTest<CSScript>(id);
		if (!csScript) return;
		csScript->klassInstance.erase(std::string{ mono_string_to_utf8(str) });
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Active
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void Active_Transform_Engine(unsigned int id, bool boolean) {
		SetEngineType(id, Transform, isActive, boolean);
	}

	void Active_Collider_Engine(unsigned int id, bool boolean) {
		SetEngineType(id, Collider, isActive, boolean);
	}

	void Active_Script_Engine(unsigned int id, bool boolean, MonoString* str) {
		CSScript* csScript = DreamECS::GetComponentTest<CSScript>(id);
		if (!csScript) return;
		csScript->klassInstance.find(std::string{ mono_string_to_utf8(str) })->second.isActive = boolean;
	}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Deltatime
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetDeltaTime_Engine(float* dt) {
		*dt = DeltaTime::GetSec();
	}
}