/* Start Header**********************************************************************************/
/*
@file    Scene.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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
		/*--------------------------------------------------------------------
		Start play mode
		--------------------------------------------------------------------*/
		bool Play();
		/*--------------------------------------------------------------------
		Stop scene (End play mode)
		--------------------------------------------------------------------*/
		void Stop();
		/*--------------------------------------------------------------------
		Save
		--------------------------------------------------------------------*/
		void Save();
		/*--------------------------------------------------------------------
		dt - delta time
		defaultRender - whether to use default rendering or not
		--------------------------------------------------------------------*/
		void Update(float dt, bool playing);

		unsigned int EntityCount();

	private:
		//Path + scene name
		std::string fullPathSceneName;
	};
}

#endif