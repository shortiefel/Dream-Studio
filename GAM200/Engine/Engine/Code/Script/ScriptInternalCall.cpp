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

#include "Engine/Header/Script/ScriptInternalCall.hpp"

#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/ECS/Coordinator.hpp"

#include "Engine/Header/Input/Input.hpp" //Input key/mouse code

#include "Engine/Header/DeltaTime/DeltaTime.hpp" //To get deltaTime

namespace Engine {

	extern Coordinator gCoordinator;

	/*void GetComponentInScriptEmbeded(unsigned int id, Transform* outTransform);
	void SetComponentInScriptEmbeded(unsigned int id, Transform* inTransform);*/

	void GetTransform_Position_Engine(unsigned int id, glm::vec2* outVec2);
	void SetTransform_Position_Engine(unsigned int id, glm::vec2* inVec2);
	void MoveTransform_Position_Engine(unsigned int id, glm::vec2* inVec2);
	void GetTransform_Scale_Engine(unsigned int id, glm::vec2* outVec2);
	void SetTransform_Scale_Engine(unsigned int id, glm::vec2* inVec2);
	void GetTransform_Angle_Engine(unsigned int id, float* outVec2);
	void SetTransform_Angle_Engine(unsigned int id, float* inVec2);

	bool Input_IsKeyPressed(Input_KeyCode key);
	bool Input_IsMouseButtonPressed(Input_MouseCode button);
	void Input_GetMousePosition(glm::vec2* outPosition);

	bool HasComponent_Transform_Engine(unsigned int id);

	void GetDeltaTime_Engine(float* dt);


	void RegisterInternalCall() {
		mono_add_internal_call("Transform::GetTransform_Position_Engine", GetTransform_Position_Engine);
		mono_add_internal_call("Transform::SetTransform_Position_Engine", SetTransform_Position_Engine);
		mono_add_internal_call("Transform::MoveTransform_Position_Engine", MoveTransform_Position_Engine);
		mono_add_internal_call("Transform::GetTransform_Scale_Engine", GetTransform_Scale_Engine);
		mono_add_internal_call("Transform::SetTransform_Scale_Engine", SetTransform_Scale_Engine);
		mono_add_internal_call("Transform::GetTransform_Angle_Engine", GetTransform_Angle_Engine);
		mono_add_internal_call("Transform::SetTransform_Angle_Engine", SetTransform_Angle_Engine);

		mono_add_internal_call("Input::IsKeyPressed_Engine", Input_IsKeyPressed);
		mono_add_internal_call("Input::IsMousePressed_Engine", Input_IsMouseButtonPressed);
		mono_add_internal_call("Input::GetMousePosition_Engine", Input_GetMousePosition);

		mono_add_internal_call("MonoBehaviour::HasComponent_Transform_Engine", HasComponent_Transform_Engine);

		mono_add_internal_call("Time::GetDeltaTime_Engine", GetDeltaTime_Engine);
	}


		
	void GetComponentInScriptEmbeded(unsigned int id, Transform* outTransform) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		*outTransform = *transform;

		/*Transform& transform = gCoordinator.GetCom<Transform>(id);
		*outTransform = transform;*/
	}

	void SetComponentInScriptEmbeded(unsigned int id, Transform* inTransform) {
		//call hascomponent with entityid
		/*Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		*transform = *inTransform;*/
		Transform& transform = gCoordinator.GetCom<Transform>(id);
		transform = *inTransform;
	}


	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Transform
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void GetTransform_Position_Engine(unsigned int id, glm::vec2* outVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		*outVec2 = transform->position;

	}
	void SetTransform_Position_Engine(unsigned int id, glm::vec2* inVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		transform->position = *inVec2;
	}
	void MoveTransform_Position_Engine(unsigned int id, glm::vec2* inVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		transform->position += *inVec2;
	}


	void GetTransform_Scale_Engine(unsigned int id, glm::vec2* outVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		*outVec2 = transform->scale;
	}
	void SetTransform_Scale_Engine(unsigned int id, glm::vec2* inVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		transform->scale = *inVec2;
	}


	void GetTransform_Angle_Engine(unsigned int id, float* outVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		*outVec2 = transform->angle;
	}
	void SetTransform_Angle_Engine(unsigned int id, float* inVec2) {
		//call hascomponent with entityid
		Transform* transform = nullptr;
		gCoordinator.HasCom<Transform>(transform, id);
		transform->angle = *inVec2;
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

	void Input_GetMousePosition(glm::vec2* outPosition)
	{
		glm::vec2 result = Input::GetMousePosition();
		*outPosition = result;
	}

	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
	Check if component exist
	----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	bool HasComponent_Transform_Engine(unsigned int id) {
		Transform* tem = nullptr;
		return gCoordinator.HasCom<Transform>(tem, id);
	}


	void GetDeltaTime_Engine(float* dt) {
		*dt = DeltaTime::GetSec();
	}
}