/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain the Script class


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "Engine/Header/ECS/ECSGlobal.hpp"

namespace Engine {
	class Script {
	public:
		virtual void Init(const Entity& ent) {}
		virtual void Update(const Entity& ent, float dt) {}
		//Should be called when entity is destroyed
		//also when game scene stop is pressed
		virtual void OnDestroy(const Entity& ent) {}

		//Will be in late update after physic checks
		//Otherwise it might go into the next loop
		virtual void OnTriggerEnter(const Entity& ent) {}
		virtual void OnTriggerExit(const Entity& ent) {}
		virtual void OnCollisionEnter(const Entity& ent) {}
		virtual void OnCollisionExit(const Entity& ent) {}
	};
}

#endif