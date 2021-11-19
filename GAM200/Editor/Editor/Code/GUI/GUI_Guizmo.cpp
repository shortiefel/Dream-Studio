/* Start Header**********************************************************************************/
/*
@file    GUI_Guizmo.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   100%
@date    20/11/2021
\brief
This file contain the GUI guizmo definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Guizmo.hpp"

#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include <ImGuizmo.h>

namespace Editor {
	namespace GUI_Guizmo {
		void Guizmo_Update(const Engine::Entity_id& id) {
			/*ImGuizmo::SetOrthographic(true);
			ImGuizmo::SetDrawlist();*/
		}

	}
}