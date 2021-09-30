/* Start Header**********************************************************************************/
/*
@file    IComponent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    08/09/2021
@brief
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
	public:
		inline Entity GetEntity() const { return entity; }
		inline void SetEntity(Entity ent) { entity = ent; }
		/*
		* List below must be added as functionality
		T& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		//Explict copy 
		void CopyComponentAsInstance(const T& target);
		//Not needed if Prefab still uses unique T
		//Example: Transform / CSScript
		void CopyComponentAsPrefab(const T& target);
		*/

		IComponent() : entity{ DEFAULT_ENTITY } {}
		IComponent(Entity ent) : entity{ ent } {}
	private:
		Entity entity = DEFAULT_ENTITY;
	};
}

#endif