/* Start Header**********************************************************************************/
/*
@file    Scene.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
This contain the declaration of GameScene class with its function


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "Engine/Header/Event/KeyEvent.hpp"

namespace Engine {
	class Scene {
	public:
		static void Create(std::string scenename);
		static void Destroy();
		static void Play();
		static void Stop();
		static void Update(float dt, bool defaultRender);

		static KeyPressedFP GetSceneHotKey();

		static void InvertPlaying();
		static void SetPlaying(bool state);
		static bool GetPlaying();

		static std::string& GetFullPath();
	private:
		//Path + scene name
		static std::string fullPathName;
		static bool playing;
	};
}

#endif