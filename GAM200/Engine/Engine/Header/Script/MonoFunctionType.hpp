/* Start Header**********************************************************************************/
/*
@file    MonoFunctionType.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    21/09/2021
\brief
This file contain the enum of Mono function type


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_TYPE_HPP
#define SCRIPT_TYPE_HPP

namespace Engine {
	enum class MonoFunctionType {
		Awake,
		Constructor,
		Init,
		Update,
		Fixed_Update,
		Destroy,
		On_Enable,
		On_Disable,
		Collision_Enter,
		Collision_Stay,
		Collision_Exit,
		Trigger_Enter,
		Trigger_Stay,
		Trigger_Exit,
		Mouse_Enter,
		Mouse_Click,
		Mouse_Over,
		Mouse_Exit
	};
}

#endif
