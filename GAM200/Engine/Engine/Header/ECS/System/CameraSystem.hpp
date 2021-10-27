/* Start Header**********************************************************************************/
/*
@file    CameraSystem.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    26/06/2021
@brief
#include "Engine/Header/ECS/System/CameraSystem.hpp"
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

namespace Engine 
{
	class CameraSystem : public Singleton<CameraSystem> 
	{
	public:
		bool Create();
		void Destroy();

		void Update(float dt);
		Math::mat3 GetTransform();
		Math::mat3 GetTransformUI();
		Math::vec2 GetPosition();

		float GetAR() const;

	private:
		Math::vec2 camPosition;
		float camFov;
		int camHeight;
		//Math::mat3 world_to_ndc_xform{};
		GLFWwindow* pwindow{};

		SINGLETON_SETUP(CameraSystem);
	};
}

#endif