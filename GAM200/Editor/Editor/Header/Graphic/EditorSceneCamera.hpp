/* Start Header**********************************************************************************/
/*
@file    EditorSceneCamera.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    22/07/2021
\brief
This file contain the EditorSceneCamera declaration

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef EDITOR_SCENE_CAMERA_HPP
#define EDITOR_SCENE_CAMERA_HPP

#include <glm/glm.hpp>

namespace Editor {
	class EditorSceneCamera {
	public:
		static void Create(glm::vec2 pos);
		static void Destroy();

		//static void Update(float dt);

		static glm::mat3 GetTransform();
	private:
		static glm::vec2 position;
		static float ar;
	};
}

#endif