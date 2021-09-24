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

#include <string>

namespace Engine {
	class Scene {
	public:
		Scene(std::string fullPath);

		bool Play();
		void Stop();
		void Update(float dt, bool playing, bool defaultRender);
		void PlayInit();

		//bool SceneSave();
	private:
		//Path + scene name
		std::string fullPathSceneName;
	};
}

#endif