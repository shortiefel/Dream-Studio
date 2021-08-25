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

namespace Engine {

	extern Coordinator gCoordinator;

	namespace Scripting {

		/*void GetComponentInScriptEmbeded(unsigned int id, Transform* outTransform);
		void SetComponentInScriptEmbeded(unsigned int id, Transform* inTransform);*/

		void GetTransform_Position_Engine(unsigned int id, glm::vec2* outVec2);
		void SetTransform_Position_Engine(unsigned int id, glm::vec2* inVec2);
		void GetTransform_Scale_Engine(unsigned int id, glm::vec2* outVec2);
		void SetTransform_Scale_Engine(unsigned int id, glm::vec2* inVec2);

		bool HasComponent_Transform_Engine(unsigned int id);


		void RegisterInternalCall() {
			mono_add_internal_call("Transform::GetTransform_Position_Engine", GetTransform_Position_Engine);
			mono_add_internal_call("Transform::SetTransform_Position_Engine", SetTransform_Position_Engine);
			mono_add_internal_call("Transform::GetTransform_Scale_Engine", GetTransform_Scale_Engine);
			mono_add_internal_call("Transform::SetTransform_Scale_Engine", SetTransform_Scale_Engine);

			mono_add_internal_call("MonoBehaviour::HasComponent_Transform_Engine", HasComponent_Transform_Engine);
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


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Check if component exist
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		bool HasComponent_Transform_Engine(unsigned int id) {
			Transform* tem = nullptr;
			return gCoordinator.HasCom<Transform>(tem, id);
		}
	}
}