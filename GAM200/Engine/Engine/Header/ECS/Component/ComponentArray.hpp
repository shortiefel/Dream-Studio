/* Start Header**********************************************************************************/
/*
@file    ComponentArray.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
		 Ow Jian Wen			 jianwen.o@digipen.edu
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
	class ComponentArrayInterface {
	public:
		virtual ~ComponentArrayInterface() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};


	//This template is to inherit the interface to prevent repeatation of codes
	//To include inserting and deleting of data
	template<typename T>
	class ComponentArray : public ComponentArrayInterface {
	public:
		void InsertCom(Entity entity, T component) {
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity) == EntityToIndexMap.end() && "Component is added again");

			size_t newIndex = Size;
			EntityToIndexMap[entity] = newIndex; //Entity -> Index
			IndexToEntityMap[newIndex] = entity; //Index -> Entity
			componentArray[newIndex] = component; //Creating of the array and calls it component
			Size++;
		}

		void Removing(Entity entity) {
			//error checking
			assert(EntityToIndexMap.find(entity) != EntityToIndexMap.end() && "Removing non-existance component");

			//Copies element at the end into deleted element's place 
			size_t IndexRemoveEntity = IndexToEntityMap[entity];
			size_t IndexLastElement = Size - 1;
			componentArray[IndexRemoveEntity] = componentArray[IndexLastElement];

			//Updating the map when it's shifted
			Entity EntityLastElement = IndexToEntityMap[IndexLastElement];
			EntityToIndexMap[EntityLastElement] = IndexRemoveEntity;
			IndexToEntityMap[IndexRemoveEntity] = EntityLastElement;

			EntityToIndexMap.erase(entity);
			IndexToEntityMap.erase(IndexLastElement);

			--Size;
		}

		//referencing to the template to get the data
		T& GetData(Entity entity) {
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			return componentArray[EntityToIndexMap[entity]];
		}

		bool HasData(T*& com, Entity entity) {
			if (EntityToIndexMap.find(entity) == EntityToIndexMap.end()) return false;
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			com = &componentArray[EntityToIndexMap[entity]];
			return true;
		}

		void EntityDestroyed(Entity entity) override {
			if (EntityToIndexMap.find(entity) != EntityToIndexMap.end())
				Removing(entity);
		}

		std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return componentArray;
		}

	private:
		std::array<T, MAX_ENTITIES> componentArray{};
		std::unordered_map<Entity, size_t> EntityToIndexMap{}; //mapping for entity ID to array index
		std::unordered_map<size_t, Entity> IndexToEntityMap{}; //mappign array index to entity ID
		size_t Size = size_t{}; //total size of valid enteries in array
	};
}

#endif