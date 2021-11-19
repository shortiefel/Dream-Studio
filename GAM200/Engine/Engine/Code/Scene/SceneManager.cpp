/* Start Header**********************************************************************************/
/*
@file    SceneManager.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   	100%
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

#include "Engine/Header/Event/WindowEvent.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
    Math::vec2 sceneManagerViewportSize{ 0.f,0.f }; //Window size

    bool gamevpCallBack(const WindowResizeEvent& e) {
        Math::uvec2 sz = e.GetSize();
        sceneManagerViewportSize = Math::vec2{ static_cast<float>(sz.x), static_cast<float>(sz.y) };
        return true;
    }

    //SceneManager* SceneManager::sceneManager;

    //std::string SceneManager::currentSceneName;
    /*std::string SceneManager::defaultSceneName;
    Scene* SceneManager::currentScene;*/

	void SceneManager::Create() {
        //defaultSceneName = "Default";
       // currentSceneName = defaultSceneName;
        currentScene = new Scene{ defaultSceneName };
        WindowResizeEvent::RegisterFunction(&gamevpCallBack);
	}

    void SceneManager::ChangeScene(std::string sceneName) {
        if (sceneName.empty()) {
            nextScene = playScene;
            return;
        }
        nextScene = sceneName;
    }

	void SceneManager::ChangeSceneInternal() {
        if (nextScene.length()) {
            //bool tem = false;

            //if (!nextScene.compare(currentScene->GetName())) {
            //    /*currentScene->Stop(true);
            //    nextScene = std::string{};
            //    if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();*/
            //    tem = true;
            //}

            currentScene->Stop(false);
            delete currentScene;

            //currentSceneName = sceneName;
            currentScene = new Scene{ nextScene };
            //currentScene = new Scene{ nextScene, GameState::GetInstance().GetPlaying() };
            nextScene = std::string{};
            if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
        }
	}

	void SceneManager::Update(float dt) {
        currentScene->Update(dt, GameState::GetInstance().GetPlaying(), sceneManagerViewportSize);
        //currentScene->Update(dt, GameState::GetInstance().GetPlaying(), Math::vec2{});
        //std::cout << sceneManagerViewportSize << "\n";
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
        playScene = currentScene->GetName();
        return currentScene->Play();
    }

    void SceneManager::Stop() {
        currentScene->Stop(true);
    }

    void SceneManager::Save() {
        currentScene->Save();
    }

    std::string SceneManager::GetCurrentScene() const {
        return currentScene->GetName();
    }
}