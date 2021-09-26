/* Start Header**********************************************************************************/
/*
@file    SceneManager.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    14/09/2021
\brief
This file has the function definition of the SceneManager
Controls the switching between scenes


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/Scene/EditorSceneManager.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"



#include "Engine/Header/Management/GameState.hpp"

namespace Editor {

    std::string EditorSceneManager::editorSceneName = "test2";

    /*
    Return function pointer
    */
    bool SceneHotKey(const Engine::KeyPressedEvent& e);

    bool EditorSceneManager::SceneHotKeyCheck(Engine::Input_KeyCode keyCode) {
        if (keyCode == Engine::Input_KeyCode::P) {
            if (Engine::GameState::GetPlaying()) {
                //Destroy current scene and create new scene (default)
                Engine::GameState::SetPlaying(false);
                Engine::SceneManager::ChangeScene(editorSceneName);
            }

            else {
                Engine::GameState::SetPlaying(true);
                Engine::SceneManager::Play();
            }
            return true;
        }

        //Save
        else if (keyCode == Engine::Input_KeyCode::S) {
            if (!Engine::GameState::GetPlaying()) {
                Engine::SceneManager::Save();
                std::cout << "Saving... \n";
                return true;
            }

            std::cout << "Scene is Playing. unable to Save... \n";
            return false;
        }

        return true;
    }

    bool SceneHotKey(const Engine::KeyPressedEvent& e) {
        if (e.GetKeyCode() == Engine::Input_KeyCode::G) {
            Engine::SceneManager::ChangeScene("test2");
        }
        else if (e.GetKeyCode() == Engine::Input_KeyCode::H) {
            Engine::SceneManager::ChangeScene("test3");
        }

        if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Control)) {
            return EditorSceneManager::SceneHotKeyCheck(e.GetKeyCode());
        }
        return true;
    }

    Engine::KeyPressedFP EditorSceneManager::GetSceneHotKey() {
        return SceneHotKey;
    }

}