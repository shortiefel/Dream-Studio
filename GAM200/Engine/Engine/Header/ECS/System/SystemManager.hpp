/* Start Header**********************************************************************************/
/*
@file			SystemManager.hpp
@author			Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date    19/06/2021
@brief

Maintining a record of registered systems and the signatures. Each system is to have a set of
signature to allow the manager to add the correct entities to the system's list


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/ECS/System/System.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>

namespace Engine {
	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> SystemReg()
		{
			const char* TypeName = typeid(T).name();

			//error checking
			assert(mSystems.find(TypeName) == mSystems.end() && "Register system more than once.");

			//ptr to system for return value
			auto system = std::make_shared<T>();
			mSystems.insert({ TypeName, system });
			return system;
		}
#ifndef NEW_ECS
		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* TypeName = typeid(T).name();

			//error checking
			assert(mSystems.find(TypeName) != mSystems.end() && "Used before register.");

			// Set the signature for this system
			Signatures.insert({ TypeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			// Erase destroyed entity from all system lists
			for (auto const& sys : mSystems)
			{
				auto const& system = sys.second;

				system->mEntities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			// Notify each system that an entity's signature changed
			for (auto const& sys : mSystems)
			{
				auto const& Type = sys.first;
				auto const& systemptr = sys.second;
				auto const& systemSignature = Signatures[Type];

				// Entity signature matches system signature 
				if ((entitySignature & systemSignature) == systemSignature)
				{
					systemptr->mEntities.insert(entity);
				}
				// Entity signature does not match system signature 
				else
				{
					systemptr->mEntities.erase(entity);
				}
			}
		}
#endif

	private:
#ifndef NEW_ECS
		std::unordered_map<const char*, Signature> Signatures{}; //system typ->signature
#endif
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{}; //system ptr->system ptr
	};
}
