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

#include "Engine/Header/Math/MathLib.hpp"

namespace Editor {
	class EditorSceneCamera {
	public:
		static void Create(Engine::MathD::Vec2 pos);
		static void Destroy();

		static void Update(float dt);

		static Engine::MathD::Mat3 GetTransform();
	private:
		static Engine::MathD::Vec2 position;
		static float ar;

		static Engine::MathD::Mat3 world_to_ndc_xform;
	};
}

#endif