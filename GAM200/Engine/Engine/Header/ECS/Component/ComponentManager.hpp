/* Start Header**********************************************************************************/
/*!
\file ComponentManager.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021
\brief

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
//#include <any> //type safe container
#include <memory>
#include <unordered_map>

#define DUPLICATE_COMPONENT(type)\
type* tptr = GetComArray<type>()->GetDataTest(entFrom);\
if (tptr) {\
type t {*tptr};\
t.SetEntityId(entTo);\
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
		void AddComponent(T component) {
			GetComArray<T>()->AddComponent(std::move(component));
		}

		void AddScript(CSScript component) {
			GetComArray<CSScript>()->AddScriptComponent(std::move(component));
		}

		template<typename T>
		void DuplicateComponentAsInstance(T component) {
			GetComArray<T>()->AddComponent(std::move(component));
		}

		void DuplicateEntityAsInstance(Entity entFrom, Entity entTo) {
			//variable name is same so its scoped
			{ DUPLICATE_COMPONENT(Camera2D); }
			{ DUPLICATE_COMPONENT(Texture); }
			{ DUPLICATE_COMPONENT(Transform); }
			{ DUPLICATE_COMPONENT(Collider); }
			{ DUPLICATE_COMPONENT(RigidBody); }
		}

		template<typename T>
		void RemoveCom(Entity entity) {
			GetComArray<T>()->RemoveComponent(entity);
		}

		void RemoveScript(Entity entity, const char* className) {
			auto& csScript = GetComArray<CSScript>()->GetData(entity);
			if (csScript.RemoveScript(className)) {
				GetComArray<CSScript>()->RemoveComponent(entity);
			}
		}

		template<typename T>
		T& GetCom(Entity entity) {
			//a reference to component from array for entity
			return GetComArray<T>()->GetData(entity);
		}

		template<typename T>
		T* GetComTest(Entity entity) {
			//a reference to component from array for entity
			return GetComArray<T>()->GetDataTest(entity);
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
		bool HasCom(T*& com, Entity entity) {
			//a reference to component from array for entity
			return GetComArray<T>()->HasData(com, entity);
		}

		void DestroyEntity(Entity entity) {
			//tell com arry that entity is destroyed, if exist remove
			for (auto const& [name, compArray] : mComponentArrayInter) {
				compArray->EntityDestroyed(entity);
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