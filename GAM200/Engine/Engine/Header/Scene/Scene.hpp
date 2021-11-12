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
		/*--------------------------------------------------------------------
		bool tem true = load temporary file
		temporary file is saved before going into play mode
		--------------------------------------------------------------------*/
		Scene(std::string _sceneName, bool _play = false);
		//Destructor
		~Scene();
		/*--------------------------------------------------------------------
		Start play mode
		--------------------------------------------------------------------*/
		bool Play();
		/*--------------------------------------------------------------------
		Stop scene (End play mode)
		deserialize - check whether to deserialize
		--------------------------------------------------------------------*/
		void Stop(bool deserialize);
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
		std::string GetName();

	private:
		//Path + scene name
		std::string sceneName;
	};
}

#endif