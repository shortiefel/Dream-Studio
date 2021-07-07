/* Start Header**********************************************************************************/
/*
@file    PhysicSystem.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the class to manage physic: PhysicSystem
includes declaration to static function for a singleton PhysicSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PHYSIC_SYSTEM_H
#define PHYSIC_SYSTEM_H

//#include "ECSGlobal.hpp"
#include "pch.hpp"
#include "ECS/System/System.hpp"


class PhysicSystem : public System {
public:
	static bool Create(const std::shared_ptr<PhysicSystem>& physicSystem);
	virtual void Destroy() override;
	~PhysicSystem();

	//static PhysicSystem* Get();
	static void Update(float dt);
	
private:
	//float gravity = 10.f;
	static std::shared_ptr<PhysicSystem> PS;
};


#endif