/* Start Header**********************************************************************************/
/*
@file    EngineCore.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    24/07/2021
\brief
This file has the function definition for class EngineCore


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/EngineCore.hpp"

#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Management/AssetManager.hpp"
#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"

#include "Engine/Header/Input/Input.hpp"

#include <iostream>

namespace Engine {

	void EngineCore::Create() {
		Factory::Create();
		ResourceManager::GetInstance().Create();
		AssetManager::GetInstance().Create();
		SceneManager::GetInstance().Create();
	}

	void EngineCore::Update(float dt) {
		SceneManager::GetInstance().Update(dt);
	}

	void EngineCore::Destroy() {
		SceneManager::GetInstance().Destroy();
		AssetManager::GetInstance().Destroy();
		ResourceManager::GetInstance().Destroy();

		Factory::Destroy();
	}

}