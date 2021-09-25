/* Start Header**********************************************************************************/
/*
@file    CameraSystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	class CameraSystem : public Singleton<CameraSystem> {
	public:
		//static bool Create(const std::shared_ptr<CameraSystem>& cameraSystem);
		bool Create();
		void Destroy();

		void Update(float dt);
		Math::mat3 GetTransform();

	private:
		Math::mat3 world_to_ndc_xform{};
		//static std::shared_ptr<CameraSystem> CS;
		GLFWwindow* pwindow{};

		CameraSystem() {}
		~CameraSystem() {}

		friend class Singleton<CameraSystem>;
	};
}

#endif