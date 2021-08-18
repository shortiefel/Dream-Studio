/* Start Header**********************************************************************************/
/*
@file    EditorStartPoint.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/07/2021
\brief
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

#include "Engine/Header/ECS/System/GraphicSystem.hpp"
#include "Engine/Header/Window.hpp"

namespace Editor {
	void EditorStartPoint::Create() {
		GUI::Create(Engine::Window::GetGLFWwindow(), Engine::Window::GetGLSLVersion());

		//Deserialize then put as position
		EditorSceneCamera::Create({ 150.f,100.f });
	}

	void EditorStartPoint::Update(float dt) {
		//Engine::GraphicImplementation::SetFramebuffer(gameWinFBO);
		GUI::SetGameFBO();
		Engine::GraphicSystem::Update(dt);
		Engine::GraphicSystem::Render();

		EditorSceneCamera::Update(dt);

		GUI::SetSceneFBO();
		Engine::GraphicSystem::Update(dt, EditorSceneCamera::GetTransform());
		Engine::GraphicSystem::Render();

		GUI::Update();
		GUI::Draw();

	}
	void EditorStartPoint::Destroy() {
		//Serialize everything for scene (scene camera position)

		EditorSceneCamera::Destroy();
		GUI::Destroy();
	}
}