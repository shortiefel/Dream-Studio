/* Start Header**********************************************************************************/
/*
@file    EditorStartPoint.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    23/07/2021
@brief
This file contain the EditorStartPoint definition
EditorMain contains the editor side of function calls


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/EditorStartPoint.hpp"

#include "Editor/Header/GUI/GUI.hpp"
#include "Editor/Header/Graphic/EditorSceneCamera.hpp"
#include "Editor/Header/Tools/Profiler.hpp"

#include "Engine/Header/Event/KeyEvent.hpp" //Register function
#include "Editor/Header/Scene/EditorSceneManager.hpp"

#include "Engine/Header/ECS/System/GraphicSystem.hpp"
#include "Engine/Header/Window.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Editor {
	void EditorStartPoint::Create() {
		GUI::Create(Engine::Window::GetInstance().GetGLFWwindow(), Engine::Window::GetInstance().GetGLSLVersion());

		//Deserialize then put as position
		EditorSceneCamera::Create({ 150.f,100.f });

		Engine::KeyPressedEvent::RegisterFunction(EditorSceneManager::GetInstance().GetSceneHotKey());

		//Profiler::Profiler_Setup();
	}

	void EditorStartPoint::Update(float dt) {
		//Engine::GraphicImplementation::SetFramebuffer(gameWinFBO);
		GUI::SetGameFBO();
		//Engine::GraphicSystem::Update(dt);
		{
			PROFILER_START("Game Graphic System");
			Engine::GraphicSystem::GetInstance().Render();
		}

		//EditorSceneCamera::Update(dt);

		GUI::SetSceneFBO();
		//Engine::GraphicSystem::Update(dt);
		//Change this line to editor graphic system
		{
			PROFILER_START("Editor Graphic System");
			Engine::GraphicSystem::GetInstance().Render(EditorSceneCamera::GetTransform());
		}
		{
			PROFILER_START("GUI Update");
			GUI::Update();
		}
		{
			PROFILER_START("GUI Draw");
			GUI::Draw();
		}
		//Profiler::Profiler_Draw();

	}
	void EditorStartPoint::Destroy() {
		//Serialize everything for scene (scene camera position)

		EditorSceneCamera::Destroy();
		GUI::Destroy();
	}
}