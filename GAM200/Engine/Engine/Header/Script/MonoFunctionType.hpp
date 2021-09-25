/* Start Header**********************************************************************************/
/*
@file    MonoFunctionType.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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
		CONSTRUCTOR,
		INIT,
		UPDATE,
		DESTROY,
		COLLISION_ENTER,
		COLLISION_STAY,
		COLLISION_EXIT,
		TRIGGER_ENTER,
		TRIGGER_STAY,
		TRIGGER_EXIT
	};
}

#endif
