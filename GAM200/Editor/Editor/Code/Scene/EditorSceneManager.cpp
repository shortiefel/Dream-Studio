/* Start Header**********************************************************************************/
/*
@file    SceneManager.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
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

   // std::string EditorSceneManager::editorSceneName = "test2";

    /*
    Return function pointer
    */
    bool SceneHotKey(const Engine::KeyPressedEvent& e);

    void EditorSceneManager::Play() {
        Engine::GameState::SetPlaying(true);
        Engine::SceneManager::GetInstance().Play();
    }

    void EditorSceneManager::Stop() {
        std::cout << "Stopping\n";
        Engine::GameState::SetPlaying(false);
        Engine::SceneManager::GetInstance().ChangeScene(editorSceneName);
    }

    bool EditorSceneManager::SceneHotKeyCheck(Engine::Input_KeyCode keyCode) {
        if (keyCode == Engine::Input_KeyCode::P) {
            if (Engine::GameState::GetPlaying()) {
                //Destroy current scene and create new scene (default)
                Stop();
            }

            else {
                Play();
            }
            return true;
        }

        //Save
        else if (keyCode == Engine::Input_KeyCode::S) {
            if (!Engine::GameState::GetPlaying()) {
                Engine::SceneManager::GetInstance().Save();
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
            Engine::SceneManager::GetInstance().ChangeScene("test2");
        }
        else if (e.GetKeyCode() == Engine::Input_KeyCode::H) {
            Engine::SceneManager::GetInstance().ChangeScene("test3");
        }

        if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Control)) {
            return EditorSceneManager::GetInstance().SceneHotKeyCheck(e.GetKeyCode());
        }
        return true;
    }

    Engine::KeyPressedFP EditorSceneManager::GetSceneHotKey() {
        return SceneHotKey;
    }

}