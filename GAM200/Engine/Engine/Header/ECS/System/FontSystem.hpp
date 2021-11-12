/* Start Header**********************************************************************************/
/*
@file    FontSystem.hpp
@author  Chia Yi Da c.yida@digipen.edu		100%
@date    24/10/2021
@brief
#include "Engine/Header/ECS/System/FontSystem.hpp"
This file has the class to manage Fonts: FontSystem includes declaration to singleton FontSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FONT_SYSTEM_H
#define FONT_SYSTEM_H

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"
#include "Engine/Header/Graphic/FrameBuffer.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class FontSystem : public Singleton<FontSystem>
	{
	public:
		bool Create();
		void Destroy();

		void Render(Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransformUI(), Graphic::FrameBuffer* _fbo = nullptr);

	private:

		SINGLETON_SETUP(FontSystem);
	};
}

#endif