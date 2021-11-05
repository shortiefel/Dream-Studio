/* Start Header**********************************************************************************/
/*!
@file		ComponentManager.hpp
@author  tan wei ling felicia	weilingfelicia.tan@digipen.edu

@date 26/04/2021
@brief

A component manager acts as an in charge of handling the different Component Array whenever a
component has tpo be added or removed. It contains Component Type, RegisterComponent. it also has
a unique key which is a map to ComponentArray to the ComponentType

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/Commands/Command.hpp"
//#include <any> //type safe container
#include <memory>
#include <unordered_map>

#define DUPLICATE_COMPONENT(type)\
type* tptr = GetComArray<type>()->GetDataPtr(entIdFrom);\
if (tptr) {\
type t {*tptr};\
t.SetEntityId(entIdTo);\
GetComArray<type>()->AddComponent(std::move(t));\
}

namespace Engine {
	class ComponentManager {
	public:
		template<typename T>
		void RegisterCom() {
			const char* TypeName = typeid(T).name();

			//error checking 
			LOG_ASSERT(mComponentTypes.find(TypeName) == mComponentTypes.end() && "Register Component more than 1 time");

			mComponentTypes.insert({ TypeName, NextComType }); //adding to com type map
			mComponentArrayInter.insert({ TypeName, std::make_shared < ComponentArray<T>>() });//ptr to comarray

			++NextComType;
		}

		template<typename T>
		ComponentType GetterComType() {
			const char* TypeName = typeid(T).name();

			//error checking
			LOG_ASSERT(mComponentTypes.find(TypeName) != mComponentTypes.end() && "Component not registered");

			//used to create signature
			return mComponentTypes[TypeName];
		}

		template<typename T>
		bool AddComponent(T component) {
			return GetComArray<T>()->AddComponent(std::move(component));
		}

		bool AddScript(ScriptComponent component) {
			return GetComArray<ScriptComponent>()->AddScriptComponent(std::move(component));
		}

		/*template<typename T>
		void DuplicateComponentAsInstance(T component) {
			GetComArray<T>()->AddComponent(std::move(component));
		}*/

		void DuplicateEntityAsInstance(Entity_id entIdFrom, Entity_id entIdTo) {
			//variable name is same so its scoped
			{ DUPLICATE_COMPONENT(CameraComponent); }
			{ DUPLICATE_COMPONENT(TextureComponent); }
			{ DUPLICATE_COMPONENT(TransformComponent); }
			{ DUPLICATE_COMPONENT(ColliderComponent); }
			{ DUPLICATE_COMPONENT(RigidBodyComponent); }
		}

		template<typename T>
		void RemoveCom(Entity_id entity_id) {
			GetComArray<T>()->RemoveComponent(entity_id);
		}

		void RemoveScript(Entity_id entity_id, const char* className) {
			auto& csScript = GetComArray<ScriptComponent>()->GetData(entity_id);
			if (csScript.RemoveScript(className)) {
				GetComArray<ScriptComponent>()->RemoveComponent(entity_id);
			}
		}

		template<typename T>
		T& GetCom(Entity_id entity_id) {
			//a reference to component from array for entity
			return GetComArray<T>()->GetData(entity_id);
		}

		template<typename T>
		T* GetComPtr(Entity_id entity_id) {
			//a reference to component from array for entity
			return GetComArray<T>()->GetDataPtr(entity_id);
		}

		template<typename T>
		std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return GetComArray<T>()->GetComponentArrayData();
		}

		template<typename T>
		size_t GetComponentArraySize() {
			return GetComArray<T>()->GetComponentArraySize();
		}

		template<typename T>
		bool HasCom(T*& com, Entity_id entity_id) {
			//a reference to component from array for entity
			return GetComArray<T>()->HasData(com, entity_id);
		}

		void DestroyEntity(Entity_id entity_id) {
			//tell com arry that entity is destroyed, if exist remove
			for (auto const& [name, compArray] : mComponentArrayInter) {
				compArray->EntityDestroyed(entity_id);
			}
		}

	private:
		std::unordered_map<const char*, ComponentType> mComponentTypes{}; //type string ptr -> com type
		std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>> mComponentArrayInter{}; //type string ptr -> com array
		ComponentType NextComType{}; //registering

		//static ptr to ComArray
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComArray() {
			const char* TypeName = typeid(T).name();

			LOG_ASSERT(mComponentTypes.find(TypeName) != mComponentTypes.end() && "Component not registered yet.");

			return std::static_pointer_cast<ComponentArray<T>>(mComponentArrayInter[TypeName]);
		}
	};
}