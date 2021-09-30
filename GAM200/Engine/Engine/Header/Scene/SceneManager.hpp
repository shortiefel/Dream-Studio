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
		* Change to sceneName scene
		*/
		void ChangeScene(std::string sceneName);

		void Update(float dt, bool defaultRender);
		void Destroy();

		void Play();
		//void Stop();
		void Save();

		void SetDefaultScene(std::string sceneName);

	private:
		//static SceneManager* sceneManager;

		//static std::string currentSceneName;
		std::string defaultSceneName;
		Scene* currentScene;

		SINGLETON_SETUP(SceneManager);
	};
}

#endif