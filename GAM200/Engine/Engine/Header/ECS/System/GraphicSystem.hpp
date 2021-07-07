/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file has the class to manage graphics: GraphicsSystem
includes declaration to static function for a singleton GraphicsSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRAPHIC_SYSTEM_H
#define GRAPHIC_SYSTEM_H

#include "pch.hpp"
#include "ECS/System/system.hpp"

class GraphicSystem : public System {
public:
	
	static bool Create(const std::shared_ptr<GraphicSystem>& graphicSystem);
	virtual void Destroy() override;
	~GraphicSystem();
	//void Destroy();

	static void Update(float dt);
	static void Render();
private:
	//static GraphicSystem* gs;
	static std::shared_ptr<GraphicSystem> GS;
};

#endif