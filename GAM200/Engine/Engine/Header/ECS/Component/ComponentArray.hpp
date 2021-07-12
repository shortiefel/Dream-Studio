/* Start Header**********************************************************************************/
/*
@file    ComponentArray.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    26/04/2021
\brief
To create a data structure that is a simple array with no holes. It contains the mapping from
entity IDs to array indices. When accessing array, it uses entity ID to look up the actual array index 
but when destroyed, it takes the last elemet of array and move into deleted entity's spott and update
the map


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include <array>
#include <cassert>
#include <unordered_map>

namespace Engine {
	class ComponentArrayInterface
	{
	public:
		virtual ~ComponentArrayInterface() = default; //for it to be used everywhere i think ?
		virtual void EntityDestroyed(Entity entity) = 0; //tells my array its destroyed and it needs to update array mapping
	};


	//This template is to inherit the interface to prevent repeatation of codes
	//To include inserting and deleting of data
	template<typename T>
	class ComponentArray : public ComponentArrayInterface
	{
	public:
		void InsertCom(Entity entity, T component)
		{
			//error checking
			assert(EntityToIndexMap.find(entity) == EntityToIndexMap.end() && "Component is added again");

			size_t newIndex = Size;
			EntityToIndexMap[entity] = newIndex; //Entity -> Index
			IndexToEntityMap[newIndex] = entity; //Index -> Entity
			ComponentArrayMAX[newIndex] = component; //Creating of the array and calls it component
			Size++;
		}

		void Removing(Entity entity)
		{
			//error checking
			assert(EntityToIndexMap.find(entity) != EntityToIndexMap.end() && "Removing non-existance component");

			//Copies element at the end into deleted element's place 
			size_t IndexRemoveEntity = IndexToEntityMap[entity];
			size_t IndexLastElement = Size - 1;
			ComponentArrayMAX[IndexRemoveEntity] = ComponentArrayMAX[IndexLastElement];

			//Updating the map when it's shifted
			Entity EntityLastElement = IndexToEntityMap[IndexLastElement];
			EntityToIndexMap[EntityLastElement] = IndexRemoveEntity;
			IndexToEntityMap[IndexRemoveEntity] = EntityLastElement;

			EntityToIndexMap.erase(entity);
			IndexToEntityMap.erase(IndexLastElement);

			--Size;
		}

		//referencing to the template to get the data
		T& GetData(Entity entity)
		{
			//error checking
			assert(EntityToIndexMap.find(entity) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			return ComponentArrayMAX[EntityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity) override
		{
			if (EntityToIndexMap.find(entity) != EntityToIndexMap.end())
			{
				// Remove the entity's component if it existed
				Removing(entity);
			}
		}

	private:
		std::array<T, MAX_ENTITIES> ComponentArrayMAX{};
		std::unordered_map<Entity, size_t> EntityToIndexMap{}; //mapping for entity ID to array index
		std::unordered_map<size_t, Entity> IndexToEntityMap{}; //mappign array index to entity ID
		size_t Size = size_t{}; //total size of valid enteries in array
	};
}

#endif