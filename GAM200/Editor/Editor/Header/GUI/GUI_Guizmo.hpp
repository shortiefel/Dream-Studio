/* Start Header**********************************************************************************/
/*
@file    GUI_Guizmo.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   100%
@date    20/11/2021
\brief
#include "Editor/Header/GUI/GUI_Guizmo.hpp"
This file contain the GUI guizmo declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GUI_GUIZMO_H
#define GUI_GUIZMO_H

#include "Engine/Header/ECS/ECSGlobal.hpp"

namespace Editor {
	namespace GUI_Guizmo {
		void Guizmo_Update(const Engine::Entity_id& id);
		
	}
}

#endif