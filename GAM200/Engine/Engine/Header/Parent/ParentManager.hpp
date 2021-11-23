/* Start Header**********************************************************************************/
/*
@file    ParentManager.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    23/11/2021
@brief
#include "Engine/Header/Parent/ParentManager.hpp"
This file has the class to manage: ParentManager
This class calculates the true position of entity (taking into account the child relative position to parent)
in global space


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PARENT_MANAGER_H
#define PARENT_MANAGER_H

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	class ParentManager : public Singleton<ParentManager> {
	public:
		
		/*true position = local position
		Set true postion to be local position + Calculation(adding parents calculation)
		Editor changes is set to true position*/
		void UpdateTruePos(Entity_id entity_id);
		void UpdateAllTruePos();

		/*true position = local position
		Set true postion to be local position + Calculation(adding parents calculation)
		Update all Child true position (Child movement is linked to parent)*/
		void UpdateChildTruePos(Entity_id entity_id);
		void UpdateAllChildTruePos();

		/*local position = true position
		Set local position = true postion - Calculation(adding parents calculation)
		Called after physics (since physics affect true position)*/
		void UpdateLocalPos(Entity_id entity_id);
		void UpdateAllLocalPos();

		void Parent(Entity_id _parent, Entity_id _child);
		void Unparent(Entity_id _target);

	private:

		SINGLETON_SETUP(ParentManager);
	};
}

#endif