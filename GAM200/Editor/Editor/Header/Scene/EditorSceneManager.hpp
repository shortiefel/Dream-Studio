/* Start Header**********************************************************************************/
/*
@file    EditorSceneManager.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Scene/Scene.hpp"
#include <string>
#include "Engine/Header/Event/KeyEvent.hpp"

namespace Editor {
	class EditorSceneManager {
	public:


		static Engine::KeyPressedFP GetSceneHotKey();
		/*
		Check whether pause or save is pressed and react accordingly
		*/
		static bool SceneHotKeyCheck(Engine::Input_KeyCode keyCode);

	private:
		static std::string editorSceneName;
	};
}

#endif