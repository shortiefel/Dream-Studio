/* Start Header**********************************************************************************/
/*
@file    CameraSystem.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain the CameraSystem declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include "Engine/Header/pch.hpp"
#include "Engine/Header/ECS/System/System.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	class CameraSystem : public System {
	public:
		//static bool Create(const std::shared_ptr<CameraSystem>& cameraSystem);
		static bool Create();
		static void Destroy();
		~CameraSystem();

		static void Update(float dt);

		static Math::mat3 GetTransform();
	private:
		static Math::mat3 world_to_ndc_xform;
		//static std::shared_ptr<CameraSystem> CS;
		static GLFWwindow* pwindow;
	};
}

#endif