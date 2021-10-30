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

#include "Engine/Header/Event/KeyEvent.hpp" //Register function

#include "Engine/Header/ECS/System/GraphicSystem.hpp"
#include "Engine/Header/ECS/System/UISystem.hpp"
#include "Engine/Header/AI/AISystem.hpp"

#include "Engine/Header/Window.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Editor {
	void EditorStartPoint::Create() {
		GUI::Create(Engine::Window::GetInstance().GetGLFWwindow(), Engine::Window::GetInstance().GetGLSLVersion());

		//Deserialize then put as position
		EditorSceneCamera::Create({ 0.f,0.f });
	}

	void EditorStartPoint::Update(float) {
		//Engine::GraphicImplementation::SetFramebuffer(gameWinFBO);
		

		//GUI::SetGameFBO();
		////Engine::GraphicSystem::Update(dt);
		//Engine::GraphicSystem::GetInstance().Render();
		
		//GUI::SetSceneFBO();
		////Engine::GraphicSystem::Update(dt);
		////Change this line to editor graphic system

		Engine::GraphicSystem::GetInstance().Render(EditorSceneCamera::GetTransform(), GUI::GetFboPtr());
		Engine::UISystem::GetInstance().Render(EditorSceneCamera::GetTransform(), GUI::GetFboPtr());
		Engine::AI::AISystem::GetInstance().Render(EditorSceneCamera::GetTransform(), GUI::GetFboPtr());

		//The system already added the time taken
		PROFILER_START("Rendering");
		GUI::Update();
		
		
		GUI::Draw();

	}
	void EditorStartPoint::Destroy() {
		//Serialize everything for scene (scene camera position)

		EditorSceneCamera::Destroy();
		GUI::Destroy();
	}
}