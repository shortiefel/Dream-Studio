/* Start Header**********************************************************************************/
/*
@file    EngineCore.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/Scene/Scene.hpp"
#include "Engine/Header/Management/GameSceneSerializer.hpp" // remove

namespace Engine {
	void EngineCore::Create() {
		if (!LayerStack::Create()) LOG_ERROR("LayerStack creation has failed");

		//const char* glsl_version = "#version 450";
		//if (!GUILayer::Create(Window::GetGLFWwindow(), glsl_version)) LOG_ERROR("GUILayer creation has failed");

		//LayerStack::AddOverlayLayer(GUILayer::Get());

		Factory::Create();

		ResourceManager::Create();

		Scene::Create();
		Scene::Play(); //Temporary placement (will be linked to GUI play button)

		GameSceneSerializer::Deserialize("Assets/test1.json"); // remove
		//SceneSerializer::Serialize("Assets/test1.json"); // remove
	}

	void EngineCore::Update(float dt, bool defaultRender) {
		Scene::Update(dt, defaultRender);
	}

	void EngineCore::Destroy() {
		Scene::Destroy(); //Destroy currently active game scene
		ResourceManager::Destroy();
		//GUILayer::Destroy();
		LayerStack::Destroy();
	}
}