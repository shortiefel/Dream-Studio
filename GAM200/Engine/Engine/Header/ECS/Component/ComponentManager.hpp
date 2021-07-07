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

#include "ECS/Component/ComponentArray.hpp"
#include "ECS/ECSGlobal.hpp"
//#include <any> //type safe container
#include <memory>
#include <unordered_map>


class ComponentManager
{
public:
	template<typename T>
	void RegisterCom()
	{
		const char* TypeName = typeid(T).name();

		//error checking 
		assert(mComponentTypes.find(TypeName) == mComponentTypes.end() && "Register Component more than 1 time");

		mComponentTypes.insert({ TypeName, NextComType }); //adding to com type map
		mComponentArrayInter.insert({ TypeName, std::make_shared < ComponentArray<T>>() });//ptr to comarray

		++NextComType;

	}

	template<typename T>
	ComponentType GetterComType()
	{
		const char* TypeName = typeid(T).name();

		//error checking
		assert(mComponentTypes.find(TypeName) != mComponentTypes.end() && "Component not registered");

		//used to create signature
		return mComponentTypes[TypeName];
	}

	template<typename T>
	void AddCom(Entity entity, T component)
	{
		GetComArry<T>()->InsertCom(entity, component);
	}

	template<typename T>
	void RemoveCom(Entity entity)
	{
		GetComArry<T>()->RemoveCom(entity);
	}

	template<typename T>
	T& GetCom(Entity entity)
	{
		//a reference to component from array for entity
		return GetComArry<T>()->GetData(entity);
	}

	void DestoryEntity(Entity entity)
	{
		//tell com arry that entity is destroyed, if exist remove
		for (auto const& notify : mComponentArrayInter)
		{
			auto const& com = notify.second;
			com->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> mComponentTypes{}; //type string ptr -> com type
	std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>> mComponentArrayInter{}; //type string ptr -> com array
	ComponentType NextComType{}; //registering

	//static ptr to ComArray
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComArry()
	{
		const char* TypeName = typeid(T).name();

		assert(mComponentTypes.find(TypeName) != mComponentTypes.end() && "Component not registered yet.");

		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrayInter[TypeName]);
	}



};