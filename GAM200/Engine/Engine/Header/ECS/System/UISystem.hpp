/* Start Header**********************************************************************************/
/*
@file    UISystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    24/10/2021
@brief
#include "Engine/Header/ECS/System/UISystem.hpp"
This file has the class to manage UI: UISystem
includes declaration to singleton UISystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/ECS/System/CameraSystem.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/FrameBuffer.hpp"

namespace Engine
{
	class UISystem : public Singleton<UISystem>
	{
	public:
		bool Create();
		void Destroy();

		void Render(Graphic::FrameBuffer* _fbo = nullptr, Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransformUI(), bool gameDraw = true);
		void Reset();
	private:

		SINGLETON_SETUP(UISystem);
	};
}

#endif