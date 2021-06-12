/*
This file has the class to manage graphics: GraphicsSystem
includes declaration to static function for a singleton GraphicsSystem
*/

#ifndef GRAPHIC_SYSTEM_H
#define GRAPHIC_SYSTEM_H

#include "ECSGlobal.hpp"
#include "pch.hpp"
#include "System/system.hpp"

class GraphicSystem : public System {
public:
	
	virtual bool Create() override;
	virtual void Destroy() override;
	~GraphicSystem();
	//void Destroy();

	void Update(float dt);
	void Render();
private:
	//static GraphicSystem* gs;
};

#endif