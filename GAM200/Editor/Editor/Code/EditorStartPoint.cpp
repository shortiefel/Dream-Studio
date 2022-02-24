/* Start Header**********************************************************************************/
/*
@file    EditorStartPoint.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	100%
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
#include "Engine/Header/ECS/DreamECS.hpp"

#include "Editor/Header/GUI/GUI.hpp"
#include "Editor/Header/Graphic/EditorSceneCamera.hpp"

#include "Engine/Header/Event/KeyEvent.hpp" //Register function

#include "Engine/Header/ECS/System/GraphicSystem.hpp"
#include "Engine/Header/ECS/System/UISystem.hpp"
#include "Engine/Header/AI/AISystem.hpp"

#include "Engine/Header/ECS/System/FontSystem.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Management/Settings.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Editor {
	void EditorStartPoint::Create() {
		GUI::Create(Engine::Window::GetInstance().GetGLFWwindow(), Engine::Window::GetInstance().GetGLSLVersion());

		//Deserialize then put as position
		EditorSceneCamera::Create({ 0.f,0.f });
	}

	void EditorStartPoint::Update(float _dt) {
		// Loops through lightArray to get object that has a lightComponent, render to lightComponent's FBO
		auto& lightArray = Engine::dreamECSGame->GetComponentArrayData<Engine::LightComponent>();
		for (auto& light : lightArray)
		{
			// Option to not render individual game object
			if (!light.isActive) continue;

			// If element in array is not used, skip it
			const Engine::Entity_id& entity_id = light.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			glViewport(0, 0, light.shadowWidth, light.shadowHeight);

			Engine::GraphicSystem::GetInstance().Render(_dt, &light);
		}

		glViewport(0, 0, Engine::Settings::windowWidth, Engine::Settings::windowHeight);

		// Render Editor scene with shadow mapping
		Engine::GraphicSystem::GetInstance().Render(_dt, GUI::GetGameFboPtr());
		Engine::UISystem::GetInstance().Render(GUI::GetGameFboPtr());
		Engine::FontSystem::GetInstance().Render(_dt, GUI::GetGameFboPtr());

		// Render Game scene with shadow mapping
		Engine::GraphicSystem::GetInstance().Render(0.f, GUI::GetEditorFboPtr(), EditorSceneCamera::GetTransform(), false);
		Engine::UISystem::GetInstance().Render(GUI::GetEditorFboPtr(), EditorSceneCamera::GetTransform());
		Engine::FontSystem::GetInstance().Render(_dt, GUI::GetEditorFboPtr(), EditorSceneCamera::GetTransform());
		

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