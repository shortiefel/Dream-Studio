/* Start Header**********************************************************************************/
/*
@file    DreamECS.hpp
@author  Ow Jian Wen			jianwen.o@digipen.edu		50%
					Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	50%
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

#define GetEngineType(ID, type, paramName, param)\
type* ctype = dreamECSGame->GetComponentPTR<type>(ID);\
if (ctype != nullptr) param = ctype->paramName;

#define SetEngineType(ID, type, paramName, param)\
type* ctype = dreamECSGame->GetComponentPTR<type>(ID);\
if (ctype != nullptr) ctype->paramName = param;

#define GET_COMPONENT_PTR(type) type* tem = dreamECSGame->GetComponentPTR<type>(id);\
								return !(tem == nullptr);

namespace Engine {
	class DreamECS;
	struct Prefab;

	//extern std::unique_ptr<DreamECS> dreamECSGame;
	//extern std::unique_ptr<DreamECS> dreamECSLoader;

	extern DreamECS* dreamECSGame;
	extern DreamECS* dreamECSLoader;

	//class DreamECS : public Singleton<DreamECS> {
	class DreamECS {
	public:
		DreamECS& operator=(DreamECS&& rhs) noexcept;
		~DreamECS();

		void Create();
		/*--------------------------------------------------------------------------------------------------------------
		Entity related functions
		--------------------------------------------------------------------------------------------------------------*/
		Entity CreateEntity(const char* _entityName = DEFAULT_ENTITY_NAME, std::unordered_set<Entity_id> _child = std::unordered_set<Entity_id>{}, Entity_id _parent = DEFAULT_ENTITY_ID);
		void DuplicateEntityAsInstance(Entity ent);
		void EnableTransform(Entity_id entity_id);
		void DestroyEntity(Entity_id entity_id);
		void RemoveScript(Entity_id entity_id, const char* className);
		//const std::vector<Entity>& GetUsedEntitySet();
		const EntityMapType& GetUsedConstEntityMap() const;
		EntityMapType& GetUsedEntityMap();
		uint32_t GetUsedEntitySize() const;
		const std::unordered_map<Entity_id, Prefab>& GetConstPrefabMap() const;
		void EndOfLoopUpdate();
		void ResetECS();
		void DuplicateNameCheck(std::string& name);
		void ChangeName(std::string _oldname, std::string _newname);

		void CreateSquare(Math::vec2 pos = Math::vec2{ 0.f, 0.f }, Math::vec2 scale = Math::vec2{ 1.f, 1.f });
		void CreateCircle(Math::vec2 pos = Math::vec2{ 0.f, 0.f }, Math::vec2 scale = Math::vec2{ 1.f, 1.f });

		void Parent(Entity_id _parent, Entity_id _child);
		void Unparent(Entity_id _target);

		/*
		* Add an object as a prefab
		*/
		void AddPrefab(const Prefab& _prefab);
		/*
		* Remove prefab - when entity is deleted / to not be affected by update
		*/
		void RemovePrefab(const Entity_id& entity_id);
		/*
		* Updates all prefab components to the latest stored version
		*/
		void UpdateAllPrefab();

		/*--------------------------------------------------------------------------------------------------------------
		Component related functions
		--------------------------------------------------------------------------------------------------------------*/
#if 0 //For pointer type
		template<typename T>
		void RegisterComponent() {
			compManager->RegisterCom<T>();
		}

		template<typename T>
		bool AddComponent(T com) {
			auto ptr = compManager->GetComPtr<T>(com.GetEntityId());
			//LOG_ASSERT(!ptr && "Unable add the same component for one entity");
			if (ptr) return false;
			return compManager->AddComponent<T>(std::move(com));
		}

		template<>
		bool AddComponent(ScriptComponent com) {
			return compManager->AddScript(std::move(com));
		}

		template<typename T>
		void RemoveComponent(Entity_id entity_id) {
			auto ptr = compManager->GetComPtr<T>(entity_id);
			//LOG_ASSERT(ptr && "Unable remove an entity that does not exist");
			if (!ptr) return;
			compManager->RemoveCom<T>(entity_id);
		}

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
			return compManager->GetComPtr<T>(entity_id);
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
#else
		template<typename T>
		void RegisterComponent() {
			compManager.RegisterCom<T>();
		}

		template<typename T>
		bool AddComponent(T com) {
			auto ptr = compManager.GetComPtr<T>(com.GetEntityId());
			//LOG_ASSERT(!ptr && "Unable add the same component for one entity");
			if (ptr) return false;
			return compManager.AddComponent<T>(std::move(com));
		}

		template<>
		bool AddComponent(ScriptComponent com) {
			if (this == dreamECSLoader) return compManager.AddScript(std::move(com), true);
			return compManager.AddScript(std::move(com));
		}

		template<typename T>
		void RemoveComponent(Entity_id entity_id) {
			auto ptr = compManager.GetComPtr<T>(entity_id);
			//LOG_ASSERT(ptr && "Unable remove an entity that does not exist");
			if (!ptr) return;
			compManager.RemoveCom<T>(entity_id);
		}

		/*
		* Get component by reference
		*/
		template <typename T>
		T& GetComponent(Entity_id entity_id) {
			return compManager.GetCom<T>(entity_id);
		}
		/*
		* Get component by pointer
		* For nullptr checks
		*/
		template <typename T>
		T* GetComponentPTR(Entity_id entity_id) {
			return compManager.GetComPtr<T>(entity_id);
		}
		/*
		* Check only (data is not given)
		*/
		template<typename T>
		bool HasComponentCheck(Entity_id entity_id) {
			T* com;
			return compManager.HasCom<T>(com, entity_id);
		}

		template<typename T>
		ComponentType GetComponentType() {
			return compManager.GetterComType<T>();
		}

		template<typename T>
		std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return compManager.GetComponentArrayData<T>();
		}

		template<typename T>
		size_t GetComponentArraySize() {
			return compManager.GetComponentArraySize<T>();
		}
#endif

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

		//std::unique_ptr<ComponentManager>compManager;
		//std::unique_ptr<EntityManager>entityManager;

		ComponentManager compManager{};
		EntityManager entityManager{};

		//Track the number of the same name and give index to them
		std::unordered_map <std::string, int> nameCount{};
		std::unordered_map<Entity_id, Prefab> mapOfPrefab{};

		std::unordered_set<Entity_id> destroySet{};
		std::unordered_map < Entity_id, std::string> destroyScript{};

		std::unordered_set<Entity_id> enableSet{};
	};
}

#endif