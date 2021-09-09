/* Start Header**********************************************************************************/
/*
@file    ECSWrapper.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    08/09/2021
\brief
This file is the wrapper file for ECS 
-It is made such that in the future the ECS can be changed easily


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef ECS_WRAPPER_HPP
#define ECS_WRAPPER_HPP

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Coordinator.hpp"

namespace Engine {
	class Coordinator;

	class DreamECS {
	public:
		static void Init();
		/*--------------------------------------------------------------------------------------------------------------
		Entity related functions
		--------------------------------------------------------------------------------------------------------------*/
		static Entity CreateEntity();
		static void DestroyEntity(Entity entity);
		static void DestroyAllEntity();
		static const std::vector<Entity>& GetUsedEntityVector();


		/*--------------------------------------------------------------------------------------------------------------
		Component related functions
		--------------------------------------------------------------------------------------------------------------*/
		template<typename T>
		static void RegisterComponent()
		{
			gCoordinator.RegisterComponent<T>();
		}

		template<typename T>
		static void AddComponent(Entity entity, T com) {
			gCoordinator.AddComponent<T>(entity, com);
		}

		template<typename T>
		static void RemoveComponent(Entity entity)
		{
			gCoordinator.RemoveComponent<T>(entity);
		}
		template <typename T>
		static T& GetComponent(Entity entity) {
			return gCoordinator.GetCom<T>(entity);
		}

		//Check only (data is not given)
		template<typename T>
		static bool HasComponentCheck(Entity entity) {
			return gCoordinator.HasComCheck<T>(entity);
		}

		template<typename T>
		static bool HasComponent(T*& com, Entity entity) {
			return gCoordinator.HasCom<T>(com, entity);
		}

		template<typename T>
		static ComponentType GetComponentType() {
			return gCoordinator.GetComType<T>();
		}

		template<typename T>
		static std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return gCoordinator.GetComponentArrayData<T>();
		}

		/*--------------------------------------------------------------------------------------------------------------
		System related functions
		--------------------------------------------------------------------------------------------------------------*/
		template<typename T>
		static std::shared_ptr<T> RegisterSystem() {
			return gCoordinator.RegSystem<T>();
		}

		template<typename T>
		static void setSystemSignature(Signature sign) {
			gCoordinator.setSystemSignature<T>(sign);
		}

	private:
		static Coordinator gCoordinator;
	};
}

#endif