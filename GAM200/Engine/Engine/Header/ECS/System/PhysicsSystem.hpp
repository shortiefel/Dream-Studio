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

#include "Engine/Header/Singleton/Singleton.hpp"

namespace Engine {
	class PhysicsSystem : public Singleton<PhysicsSystem> {
	public:
		bool Create();
		void Destroy();
		//~PhysicsSystem();

		//static void Stop();
		void Update(float dt);

	private:
		//float gravity = 10.f;
		//static std::shared_ptr<CollisionSystem> CS;

		PhysicsSystem() {}
		~PhysicsSystem() {}

		friend class Singleton<PhysicsSystem>;
	};
}

#endif