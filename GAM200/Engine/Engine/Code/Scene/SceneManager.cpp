/* Start Header**********************************************************************************/
/*
@file    SceneManager.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Management/GameState.hpp"

#define TO_FULL_PATH(name) ("Data/Scenes/" + name + ".json")

namespace Engine {
    //SceneManager* SceneManager::sceneManager;

    std::string SceneManager::currentSceneName;
    std::string SceneManager::defaultSceneName;
    Scene* SceneManager::currentScene;

	void SceneManager::StartScene() {
        currentSceneName = defaultSceneName;
        currentScene = new Scene{ TO_FULL_PATH(currentSceneName) };
	}

	void SceneManager::ChangeScene(std::string sceneName) {
        currentScene->Stop();
        delete currentScene;

        currentSceneName = sceneName;
        currentScene = new Scene{ TO_FULL_PATH(sceneName) };
        if (GameState::GetPlaying()) currentScene->Play();
	}

	void SceneManager::Update(float dt, bool defaultRender) {
        currentScene->Update(dt, GameState::GetPlaying(), defaultRender);
	}

	void SceneManager::Destroy() {
        delete currentScene;
	}

    void SceneManager::SetDefaultScene(std::string sn) {
        defaultSceneName = sn;
    }

    void SceneManager::Play() {
        if (currentSceneName != TO_FULL_PATH(defaultSceneName)) {
            currentScene->Stop();
            delete currentScene;

            currentScene = new Scene{ TO_FULL_PATH(defaultSceneName) };
        }

        currentScene->Play();
    }

    /*void SceneManager::Stop() {
        currentScene->Stop();
    }*/

    void SceneManager::Save() {
        currentScene->SceneSave();
    }
}