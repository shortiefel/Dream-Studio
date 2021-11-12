/* Start Header**********************************************************************************/
/*
@file    ComponentArray.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu	100%
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
		virtual void EntityDestroyed(Entity_id entity_id) = 0;
	};


	//This template is to inherit the interface to prevent repeatation of codes
	//To include inserting and deleting of data
	template<typename T>
	class ComponentArray : public ComponentArrayInterface {
	public:
		bool AddComponent(T component) {
			Entity_id entity_id = component.GetEntityId();
			//error checking
			if (EntityToIndexMap.find(entity_id) != EntityToIndexMap.end()) return false;
			//LOG_ASSERT(EntityToIndexMap.find(entity_id) == EntityToIndexMap.end() && "Component is added again");
			
			size_t newIndex = Size;
			EntityToIndexMap[entity_id] = newIndex; //Entity -> Index
			componentArray[newIndex] = std::move(component); //Creating of the array and calls it component
			Size++;
			return true;
		}

		bool AddScriptComponent(T component) {
			Entity_id entity_id = component.GetEntityId();
			size_t index{};
			
			//No ScriptComponent
			if (EntityToIndexMap.find(entity_id) == EntityToIndexMap.end()) {
				index = Size;
				EntityToIndexMap[entity_id] = index; //Entity -> Index
				//componentArray[index] = std::move(component);
				componentArray[index] = std::move(T{ entity_id });
				//componentArray[index].AddScript(component);
				Size++;
			}
			//Has at least one ScriptComponent
			else {
				
				index = EntityToIndexMap[entity_id];
				//componentArray[index].AddScript(component);
			}

			return componentArray[index].AddScript(component);
		}


		void RemoveComponent(Entity_id entity_id) {
			//error checking
			assert(EntityToIndexMap.find(entity_id) != EntityToIndexMap.end() && "Removing non-existance component");

			//Copies element at the end into deleted element's place 
			size_t IndexRemoveEntity = EntityToIndexMap[entity_id];
			size_t IndexLastElement = Size - 1;

			//Updating the map when it's shifted
			Entity_id EntityLastElement = componentArray[IndexLastElement].GetEntityId();
			EntityToIndexMap[EntityLastElement] = IndexRemoveEntity;

			componentArray[IndexRemoveEntity] = std::move(componentArray[IndexLastElement]);
			//componentArray[IndexLastElement].SetEntityId(DEFAULT_ENTITY);
			
			componentArray[IndexLastElement] = T{};
			EntityToIndexMap.erase(entity_id);

			--Size;
		}

		//referencing to the template to get the data
		T& GetData(Entity_id entity_id) {
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity_id) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			return componentArray[EntityToIndexMap[entity_id]];
		}

		//referencing to the template to get the data
		T* GetDataPtr(Entity_id entity_id) {
			if (EntityToIndexMap.find(entity_id) == EntityToIndexMap.end()) return nullptr;

			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity_id) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			return &componentArray[EntityToIndexMap[entity_id]];
		}

		bool HasData(T*& com, Entity_id entity_id) {
			if (EntityToIndexMap.find(entity_id) == EntityToIndexMap.end()) return false;
			//error checking
			LOG_ASSERT(EntityToIndexMap.find(entity_id) != EntityToIndexMap.end() && "Does not exist");

			//if exist, return data
			com = &componentArray[EntityToIndexMap[entity_id]];
			return true;
		}

		void EntityDestroyed(Entity_id entity_id) override {
			if (EntityToIndexMap.find(entity_id) != EntityToIndexMap.end()) {
				RemoveComponent(entity_id);
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