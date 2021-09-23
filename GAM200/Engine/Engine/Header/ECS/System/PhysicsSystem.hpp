/* Start Header**********************************************************************************/
/*
@file    PhysicsSystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/09/2021
\brief
This file has the class declaration for PhysicsSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "Engine/Header/pch.hpp"
#include "Engine/Header/ECS/System/System.hpp"

namespace Engine {
	class PhysicsSystem : public System {
	public:
		static bool Create();
		static void Destroy();
		//~PhysicsSystem();

		//static void Stop();
		static void Update(float dt);

	private:
		//float gravity = 10.f;
		//static std::shared_ptr<CollisionSystem> CS;
	};
}

#endif