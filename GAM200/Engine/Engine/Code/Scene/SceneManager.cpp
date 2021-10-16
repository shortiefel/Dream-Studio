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

#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"


#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

namespace Engine {
    //SceneManager* SceneManager::sceneManager;

    //std::string SceneManager::currentSceneName;
    /*std::string SceneManager::defaultSceneName;
    Scene* SceneManager::currentScene;*/

	void SceneManager::StartScene() {
        defaultSceneName = "test2";
       // currentSceneName = defaultSceneName;
        currentScene = new Scene{ defaultSceneName };
	}

    void SceneManager::ChangeScene(std::string sceneName) {
        nextScene = sceneName;
    }

	void SceneManager::ChangeSceneInternal() {
        if (nextScene.length()) {
            currentScene->Stop();
            delete currentScene;

            //currentSceneName = sceneName;
            currentScene = new Scene{ nextScene };
            nextScene = std::string{};
            if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
        }
	}

	void SceneManager::Update(float dt, bool defaultRender) {
        currentScene->Update(dt, GameState::GetInstance().GetPlaying(), defaultRender);

        //Scene change at end of update to not disturb entity that is currently being updated
        ChangeSceneInternal();
	}

	void SceneManager::Destroy() {
        delete currentScene;
	}

    void SceneManager::SetDefaultScene(std::string sn) {
        defaultSceneName = sn;
    }

    bool SceneManager::Play() {
        return currentScene->Play();
    }

    void SceneManager::Stop() {
        currentScene->Stop();
    }

    void SceneManager::Save() {
        currentScene->Save();
    }
}