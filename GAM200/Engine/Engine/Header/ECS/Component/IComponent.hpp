/* Start Header**********************************************************************************/
/*
@file    IComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    08/09/2021
\brief
This file is for component to inherit


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef ICOMPONENT
#define ICOMPONENT

#include "Engine/Header/ECS/ECSGlobal.hpp"

namespace Engine {
	struct IComponent {
		Entity entityId = DEFAULT_ENTITY;
	};
}

#endif