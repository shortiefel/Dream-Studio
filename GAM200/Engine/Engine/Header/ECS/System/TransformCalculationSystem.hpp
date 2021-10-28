/* Start Header**********************************************************************************/
/*
@file    TransformCalculationSystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    28/10/2021
@brief
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"
This file has the class to manage: TransformCalculationSystem
This class calculates the true position of entity (taking into account the child relative position to parent)
in global space


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TRANSFORM_CALCULATION_SYSTEM_H
#define TRANSFORM_CALCULATION_SYSTEM_H

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	//using TrueTransformMap = std::unordered_map<Entity_id, TransformComponent>;

	class TransformCalculationSystem : public Singleton<TransformCalculationSystem>
	{
	public:
		bool Create();
		void Destroy();
		/*true position = local position
		Set true postion to be local position + Calculation(adding parents calculation)
		Editor changes is set to true position*/
		void Update();

		/*true position = local position
		Set true postion to be local position + Calculation(adding parents calculation)
		Update all Child true position (Child movement is linked to parent)*/
		void ChildUpdate();
		
		/*local position = true position
		Set local position = true postion - Calculation(adding parents calculation)
		Called after physics (since physics affect true position)*/
		void Release();

		void Parent(Entity_id _parent, Entity_id _child);
		void Unparent(Entity_id _target);

	private:

		SINGLETON_SETUP(TransformCalculationSystem);
	};
}

#endif