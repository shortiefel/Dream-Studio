/* Start Header**********************************************************************************/
/*
@file    ComponentArray.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
		 Ow Jian Wen			 jianwen.o@digipen.edu
@date    26/04/2021
@brief
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

#include <iostream>

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
		void AddComponent(T component) {
			Entity entity = component.GetEntity();
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity.id) == EntityToIndexMap.end() && "Component is added again");
			
			size_t newIndex = Size;
			EntityToIndexMap[entity.id] = newIndex; //Entity -> Index
			componentArray[newIndex] = std::move(component); //Creating of the array and calls it component
			Size++;
		}

		void AddScriptComponent(T component) {
			Entity entity = component.GetEntity();
			size_t index{};
			
			//No Script
			if (EntityToIndexMap.find(entity.id) == EntityToIndexMap.end()) {
				index = Size;
				EntityToIndexMap[entity.id] = index; //Entity -> Index
				//componentArray[index] = std::move(component);
				componentArray[index] = std::move(T{ entity });
				//componentArray[index].AddScript(component);
				Size++;
			}
			//Has at least one script
			else {
				
				index = EntityToIndexMap[entity.id];
				//componentArray[index].AddScript(component);
			}

			componentArray[index].AddScript(component);
		}


		void RemoveComponent(Entity entity) {
			//error checking
			assert(EntityToIndexMap.find(entity.id) != EntityToIndexMap.end() && "Removing non-existance component");

			//Copies element at the end into deleted element's place 
			size_t IndexRemoveEntity = EntityToIndexMap[entity.id];
			size_t IndexLastElement = Size - 1;

			//Updating the map when it's shifted
			Entity EntityLastElement = componentArray[IndexLastElement].GetEntity();
			EntityToIndexMap[EntityLastElement.id] = IndexRemoveEntity;

			componentArray[IndexRemoveEntity] = std::move(componentArray[IndexLastElement]);
			//componentArray[IndexLastElement].SetEntityId(DEFAULT_ENTITY);
			
			componentArray[IndexLastElement] = T{};
			EntityToIndexMap.erase(entity.id);

			--Size;
		}

		//referencing to the template to get the data
		T& GetData(Entity entity) {
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity.id) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			return componentArray[EntityToIndexMap[entity.id]];
		}

		//referencing to the template to get the data
		T* GetDataTest(Entity entity) {
			if (EntityToIndexMap.find(entity.id) == EntityToIndexMap.end()) return nullptr;

			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity.id) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			return &componentArray[EntityToIndexMap[entity.id]];
		}

		bool HasData(T*& com, Entity entity) {
			if (EntityToIndexMap.find(entity.id) == EntityToIndexMap.end()) return false;
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity.id) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			com = &componentArray[EntityToIndexMap[entity.id]];
			return true;
		}

		void EntityDestroyed(Entity entity) override {			
			if (EntityToIndexMap.find(entity.id) != EntityToIndexMap.end()) {
				RemoveComponent(entity);
			}
		}

		std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return componentArray;
		}

		size_t GetComponentArraySize() {
			return Size;
		}

	private:
		std::array<T, MAX_ENTITIES> componentArray{};
		std::unordered_map<Entity_id, size_t> EntityToIndexMap{}; //mapping for entity ID to array index

		size_t Size = size_t{}; //total size of valid enteries in array
	};
}

#endif