/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    16/06/2021
@brief
This file contains function declaration for class GraphicsSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRAPHIC_SYSTEM_H
#define GRAPHIC_SYSTEM_H

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"
#include "Engine/Header/Graphic/FrameBuffer.hpp"
#include "Engine/Header/ECS/Component/Graphics/LightComponent.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class GraphicSystem : public Singleton<GraphicSystem>
	{
	public:
		bool Create();
		void Destroy();

		//If _fbo is nullptr = default draw (game scene draw) otherwise it is for editor scene
		void Render(float _dt,  Graphic::FrameBuffer* _fbo = nullptr,
					Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransform(), 
					bool gameDraw = true);

		//void Render(float _dt, LightComponent* _fbo);

	private:
		SINGLETON_SETUP(GraphicSystem);
	};
}

#endif