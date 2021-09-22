/* Start Header**********************************************************************************/
/*
@file    SceneManager.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

#include "Engine/Header/Scene/Scene.hpp"
#include <string>

namespace Engine {
	class SceneManager {
	public:
		static void StartScene();
		/*
		* Change to sceneName scene
		*/
		static void ChangeScene(std::string sceneName);

		static void Update(float dt, bool defaultRender);
		static void Destroy();

		static void Play();
		//static void Stop();
		static void Save();

		static void SetDefaultScene(std::string sceneName);
		static bool GetPlaying();
		static void SetPlaying(bool state);
	private:
		//static SceneManager* sceneManager;

		static std::string currentScenePath;
		static std::string defaultSceneName;
		static Scene* currentScene;
	};
}

#endif