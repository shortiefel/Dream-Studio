/*
This file has the class to manage physic: PhysicSystem
includes declaration to static function for a singleton PhysicSystem
*/

#ifndef PHYSIC_SYSTEM_H
#define PHYSIC_SYSTEM_H

#include "ECSGlobal.hpp"
#include "pch.hpp"
#include "System/System.hpp"


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