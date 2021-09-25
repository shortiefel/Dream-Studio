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

#define TO_FULL_PATH(name) ("Data/Scenes/" + name + ".json")

namespace Engine {
    //SceneManager* SceneManager::sceneManager;

    std::string SceneManager::currentScenePath;
    std::string SceneManager::defaultSceneName;
    Scene* SceneManager::currentScene;

	void SceneManager::StartScene() {
        defaultSceneName = "test2";
        currentScenePath = TO_FULL_PATH(defaultSceneName);
        currentScene = new Scene{ currentScenePath };
	}

	void SceneManager::ChangeScene(std::string sceneName) {
        currentScene->Stop();
        delete currentScene;

        currentScenePath = TO_FULL_PATH(sceneName);
        currentScene = new Scene{ currentScenePath };
        if (GameState::GetPlaying()) ScriptSystem::GetInstance().PlayInit();
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
        /*if (currentSceneName != TO_FULL_PATH(defaultSceneName)) {
            currentScene->Stop();
            delete currentScene;

            currentScene = new Scene{ TO_FULL_PATH(defaultSceneName) };
        }*/

        //if (!ScriptSystem::CompileCS()) {
        //    std::cout << "Fail to compile \n";
        //    //Scene::SetPlaying(false);
        //    return;
        //}

        //ScriptSystem::UpdateMapData();
        //ScriptSystem::PlayInit();
        ////Change to sceneName (might be fullName(path + name) instead)
        //GameSceneSerializer::SerializeScene(currentScenePath);

        currentScene->Play();
    }

    /*void SceneManager::Stop() {
        currentScene->Stop();
    }*/

    void SceneManager::Save() {
        currentScene->Save();
        //if (!ScriptSystem::CompileCS()) {
        //    std::cout << "Fail to compile \n";
        //    //Scene::SetPlaying(false);
        //    return;
        //}

        //ScriptSystem::UpdateMapData();
        ////Change to sceneName (might be fullName(path + name) instead)
        //GameSceneSerializer::SerializeScene(currentScenePath);
    }
}