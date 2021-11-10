/* Start Header**********************************************************************************/
/*
@file    EngineCore.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Layer/LayerStack.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Management/AssetManager.hpp"
#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"

#include "Engine/Header/Input/Input.hpp"

#include <iostream>

namespace Engine {

	void EngineCore::Create() {
		if (!LayerStack::Create()) LOG_ERROR("LayerStack creation has failed");

		//const char* glsl_version = "#version 450";
		//if (!GUILayer::Create(Window::GetGLFWwindow(), glsl_version)) LOG_ERROR("GUILayer creation has failed");

		//LayerStack::AddOverlayLayer(GUILayer::Get());

		Factory::Create();
		ResourceManager::GetInstance().Create();
		AssetManager::GetInstance().Create();
		SceneManager::GetInstance().StartScene();
	}

	void EngineCore::Update(float dt) {
		SceneManager::GetInstance().Update(dt);
	}

	void EngineCore::Destroy() {
		SceneManager::GetInstance().Destroy();
		AssetManager::GetInstance().Destroy();
		ResourceManager::GetInstance().Destroy();

		Factory::Destroy();
		//GUILayer::Destroy();
		LayerStack::Destroy();
	}

}