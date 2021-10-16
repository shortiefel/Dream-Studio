/* Start Header**********************************************************************************/
/*
@file    CollisionSystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    19/06/2021
@brief
This file has the class to manage physic: CollisionSystem
includes declaration to static function for a singleton CollisionSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "Engine/Header/pch.hpp"

#include "Engine/Header/Singleton/Singleton.hpp"


namespace Engine {
	struct Ray;

	class CollisionSystem : public Singleton<CollisionSystem> {
	public:
		bool Create();
		void Destroy();

		bool RayCast(const Ray& ray, float* hitDistance);

		void Stop();
		void Update(float dt);

	private:
		SINGLETON_SETUP(CollisionSystem);
	};
}

#endif