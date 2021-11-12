/* Start Header**********************************************************************************/
/*
@file    EditorSceneCamera.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    22/07/2021	
\brief
#include "Editor/Header/Graphic/EditorSceneCamera.hpp"
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

namespace Editor 
{
	class EditorSceneCamera 
	{
	public:
		static void Create(Math::vec2 pos);
		static void Destroy();

		static Math::mat3 GetTransform();
		static Math::mat3 GetInverseTransform();
		static Math::mat3 GetTransformUI();
		static float GetAR();

		static void changeHeight(float val);
		static float GetHeight();
		static void changePosition(Math::vec2 val);

	private:
		static Math::vec2 position;
		static float ar;
	};
}

#endif