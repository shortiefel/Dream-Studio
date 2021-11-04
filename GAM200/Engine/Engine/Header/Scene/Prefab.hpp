/* Start Header**********************************************************************************/
/*
@file    Prefab.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    03/11/2021
\brief
#include "Engine/Header/Scene/Prefab.hpp"
This contain the declaration of Prefab struct


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PREFAB_HPP
#define PREFAB_HPP

#include "Engine/Header/ECS/ECSGlobal.hpp"

#include <string>

namespace Engine {
	struct Prefab {
		//prefabName is the name of the prefab without the extension or file path
		std::string prefabName;
		const Entity& entity;

		Prefab(std::string _prefabName, const Entity& _entity) : prefabName{ _prefabName }, entity{ _entity } {}
	};
}

#endif