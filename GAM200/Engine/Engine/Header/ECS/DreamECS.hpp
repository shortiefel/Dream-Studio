/* Start Header**********************************************************************************/
/*
@file    DreamECS.hpp
@author  Ow Jian Wen			jianwen.o@digipen.edu
		 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
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

#ifndef DreamECS_HPP
#define DreamECS_HPP

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/ECS/Component/ComponentManager.hpp"
#include "Engine/Header/ECS/Entity/EntityManager.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

#include <memory>
#include <unordered_set>

namespace Engine {
	class DreamECS : public Singleton<DreamECS> {
	public:
		void Create();
		/*--------------------------------------------------------------------------------------------------------------
		Entity related functions
		--------------------------------------------------------------------------------------------------------------*/
		Entity CreateEntity(const char* _entityName = DEFAULT_ENTITY_NAME, Entity_id _parent = DEFAULT_ENTITY_ID);
		void DuplicateEntityAsInstance(Entity ent);
		void DestroyEntity(Entity_id entity_id);
		//const std::vector<Entity>& GetUsedEntitySet();
		const std::unordered_map<Entity_id, Entity>& GetUsedEntityMap();
		void ClearDestroyQueue();
		void ResetECS();

		void Parent(Entity _parent, Entity _child);
		void Unparent(Entity _child);

		/*--------------------------------------------------------------------------------------------------------------
		Component related functions
		--------------------------------------------------------------------------------------------------------------*/
		template<typename T>
		void RegisterComponent() {
			compManager->RegisterCom<T>();
		}

		template<typename T>
		void AddComponent(T com) {
			auto ptr = compManager->GetComTest<T>(com.GetEntityId());
			LOG_ASSERT(!ptr && "Unable add the same component for one entity");
			if (ptr) return;
			compManager->AddComponent<T>(std::move(com));
			//auto Signature = entityManager->GetSignature(entity); //unique signature key
			//Signature.set(compManager->GetterComType<T>(), true); //setting the unique signature key
			//entityManager->SetSignature(entity, Signature);

			//sysManager->EntitySignatureChanged(entity, Signature); //letting system manager know abt the change in signature on entity
		}

		template<>
		void AddComponent(ScriptComponent com) {
			compManager->AddScript(std::move(com));
		}

		template<typename T>
		void RemoveComponent(Entity_id entity_id) {
			auto ptr = compManager->GetComTest<T>(entity_id);
			LOG_ASSERT(ptr && "Unable remove an entity that does not exist");
			if (!ptr) return;
			compManager->RemoveCom<T>(entity_id);
			/*auto Signature = entityManager->GetSignature(entity);
			Signature.set(compManager->GetterComType<T>(), false);
			entityManager->SetSignature(entity, Signature);

			sysManager->EntitySignatureChanged(entity, Signature);*/
		}

		/*static void RemoveScript(Entity entity, const char* className)
		{
			gCoordinator.RemoveScript(entity, className);
		}*/

		/*
		* Get component by reference
		*/
		template <typename T>
		T& GetComponent(Entity_id entity_id) {
			return compManager->GetCom<T>(entity_id);
		}
		/*
		* Get component by pointer
		* For nullptr checks
		*/
		template <typename T>
		T* GetComponentPTR(Entity_id entity_id) {
			return compManager->GetComTest<T>(entity_id);
		}
		/*
		* Check only (data is not given)
		*/
		template<typename T>
		bool HasComponentCheck(Entity_id entity_id) {
			T* com;
			return compManager->HasCom<T>(com, entity_id);
		}

		template<typename T>
		ComponentType GetComponentType() {
			return compManager->GetterComType<T>();
		}

		template<typename T>
		std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return compManager->GetComponentArrayData<T>();
		}

		template<typename T>
		size_t GetComponentArraySize() {
			return compManager->GetComponentArraySize<T>();
		}

		/*--------------------------------------------------------------------------------------------------------------
		System related functions
		--------------------------------------------------------------------------------------------------------------*/
		/*template<typename T>
		std::shared_ptr<T> RegisterSystem() {
			return sysManager->SystemReg<T>();
		}
		template<typename T>
		static void setSystemSignature(Signature sign) {
			gCoordinator.setSystemSignature<T>(sign);
		}
		*/

	private:

		std::unique_ptr<ComponentManager>compManager;
		std::unique_ptr<EntityManager>entityManager;
		//std::unique_ptr<SystemManager>sysManager;

		//static Coordinator gCoordinator;
		std::unordered_set<Entity_id> destroySet{};


		SINGLETON_SETUP(DreamECS);
	};
}

#endif