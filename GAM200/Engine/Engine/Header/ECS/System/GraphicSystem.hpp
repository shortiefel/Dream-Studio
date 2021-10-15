/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
@brief
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

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/ECS/System/CameraSystem.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class GraphicSystem : public Singleton<GraphicSystem>
	{
	public:
		bool Create();
		void Destroy();

		void Render(Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransform());

	private:
		GLboolean isDebugDraw = GL_TRUE;

		SINGLETON_SETUP(GraphicSystem);
	};
}

#endif