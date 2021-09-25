/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    26/06/2021
\brief
This file contain the Script component


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Script/ScriptClass.hpp"
#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	struct CSScript : public IComponent {
		CSClassInstance klassInstance;
		//std::unordered_map<std::string, CSScriptInstance> tem;

		CSScript& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		void AddScript(CSScript& comp);
		//Return true if no more scripts left
		bool RemoveScript(const char* _className);
		void SetActive(const char* _className, bool _boolean);

		//Explict copy 
		void CopyComponentAsInstance(const CSScript& target);
		void CopyComponentAsPrefab(const CSScript& target);

		CSScript(Entity _ID = DEFAULT_ENTITY, const char* _className = nullptr);
		CSScript(CSScript&& rhs) noexcept;
		CSScript& operator=(CSScript&& rhs) noexcept;
		CSScript(const CSScript&) = delete;
		CSScript& operator=(const CSScript& rhs) = delete;

	private:
		void AddSpecial();
		//void InitVariable(const char* className);
	};
}

#endif