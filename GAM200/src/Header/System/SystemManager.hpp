/* Start Header**********************************************************************************/
/*!
\file SystemManager.hpp
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

Maintining a record of registered systems and the signatures. Each system is to have a set of 
signature to allow the manager to add the correct entities to the system's list

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "System.hpp"
#include "../Global.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>

class SystemManager
{
	public:
		template<typename T>
		std::shared_ptr<T> SystemReg()
		{
			const char* TypeName = typeid(T).name();

			//error checking
			assert(Systems.find(TypeName) == Systems.end() && "Register system more than once.");

			//ptr to system for return value
			auto system = std::make_shared<T>();
			Systems.insert({ TypeName, system });

			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* TypeName = typeid(T).name();

			//error checking
			assert(Systems.find(TypeName) != Systems.end() && "Used before register.");

			// Set the signature for this system
			mSignatures.insert({ TypeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			// Erase destroyed entity from all system lists
			for (auto const& sys : Systems)
			{
				auto const& system = sys.second;

				system->mEntities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			// Notify each system that an entity's signature changed
			for (auto const& sys : Systems)
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

	private:
		std::unordered_map<const char*, Signature> Signatures{}; //system typ->signature
		std::unordered_map<const char*, std::shared_ptr<System>> Systems{}; //system ptr->system ptr

};