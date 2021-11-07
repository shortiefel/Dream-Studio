/* Start Header**********************************************************************************/
/*
@file    SceneManager.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    14/09/2021
\brief
This file has the function declaration of the SceneManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP


#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/Scene/Scene.hpp"
#include <string>

namespace Engine {
	class SceneManager : public Singleton<SceneManager> {
	public:
		void StartScene();
		
		/*
		* Add next scene to be changed at the end of the game loop
		* if empty, scene is the scene which was last played
		*/
		void ChangeScene(std::string sceneName);

		void Update(float dt);
		void Destroy();

		bool Play();
		void Stop();
		void Save();

		std::string GetCurrentScene() const;

		void SetDefaultScene(std::string sceneName);

	private:
		//static SceneManager* sceneManager;

		//static std::string currentSceneName;
		std::string defaultSceneName = std::string{};
		//The scene when the play was clicked
		std::string playScene = std::string{};
		std::string nextScene = std::string{};
		Scene* currentScene = nullptr;

		/*
		* Actually changing to nextScene scene
		* Requires all scripting stuff to be completed before deleting it
		*/
		void ChangeSceneInternal();

		SINGLETON_SETUP(SceneManager);
	};
}

#endif