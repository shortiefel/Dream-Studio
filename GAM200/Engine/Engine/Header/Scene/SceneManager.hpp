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

#include <string>

namespace Engine {
	class SceneManager {
	public:
		static void ChangeScene(std::string sceneName);
	private:

	};
}

#endif