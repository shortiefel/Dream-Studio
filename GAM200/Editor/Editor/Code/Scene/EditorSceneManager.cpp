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

#include "Editor/Header/GUI/GUI_Windows/GUI_ConsoleWindow.hpp"

#include <fstream>
#include <sstream>

namespace Editor {

   // std::string EditorSceneManager::editorSceneName = "test2";

    /*
    Return function pointer
    */
    bool SceneHotKey(const Engine::KeyPressedEvent& e);

    bool EditorSceneManager::Play() {
        GUI_Windows::GUI_Console_Clear();

        Engine::GameState::GetInstance().SetPlaying(true);
        bool playState = true;
        if (!Engine::SceneManager::GetInstance().Play()) playState = false;

        //Read compile result
        std::ifstream fs{ "Data/msbuild.log" };
        if (fs.is_open()) {
            std::ostringstream buffer;
            buffer << fs.rdbuf();

            GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ buffer.str().c_str() });
        }

        fs.close();

        if (!playState) return false;
        return true;
    }

    void EditorSceneManager::Stop() {
        GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ "Game Stopped\n" });

        Engine::GameState::GetInstance().SetPlaying(false);
        Engine::SceneManager::GetInstance().ChangeScene("");
        //Engine::SceneManager::GetInstance().Stop();
    }

    void EditorSceneManager::EditorScenePlay() {
        if (Engine::GameState::GetInstance().GetPlaying()) {
            //Destroy current scene and create new scene (default)
            Stop();
        }

        else {
            Play();
        }
    }

    void EditorSceneManager::EditorSceneSave() {
        if (!Engine::GameState::GetInstance().GetPlaying()) {
            Engine::SceneManager::GetInstance().Save();
            GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ "Scene saved" });
            return;
        }

        GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ "Scene is Playing. unable to Save..." });
    }

}