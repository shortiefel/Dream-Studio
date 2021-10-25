/* Start Header**********************************************************************************/
/*
@file    IComponent.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
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
		inline Entity_id GetEntityId() const { return entity_id; }
		//inline void SetEntity(Entity ent) { entity = ent; }
		inline void SetEntityId(Entity_id _entity_id) { entity_id = _entity_id; }
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

		IComponent() : entity_id{ DEFAULT_ENTITY_ID } {}
		IComponent(Entity_id _entity_id) : entity_id{ _entity_id } {}
	private:
		Entity_id entity_id = DEFAULT_ENTITY_ID;
	};
}

#endif