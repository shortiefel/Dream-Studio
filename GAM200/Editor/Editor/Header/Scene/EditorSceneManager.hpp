/* Start Header**********************************************************************************/
/*
@file    EditorSceneManager.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    16/09/2021
\brief
This file has the function declaration of the EditorSceneManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef EDITOR_SCENE_MANAGER_HPP
#define EDITOR_SCENE_MANAGER_HPP

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/Scene/Scene.hpp"
#include <string>
#include "Engine/Header/Event/KeyEvent.hpp"

namespace Editor {
	class EditorSceneManager : public Engine::Singleton<EditorSceneManager> {
	public:


		Engine::KeyPressedFP GetSceneHotKey();
		/*
		Check whether pause or save is pressed and react accordingly
		*/
		bool SceneHotKeyCheck(Engine::Input_KeyCode keyCode);

		bool Play();
		void Stop();

	private:
		std::string editorSceneName = "test2";;

		SINGLETON_SETUP(EditorSceneManager);
	};
}

#endif