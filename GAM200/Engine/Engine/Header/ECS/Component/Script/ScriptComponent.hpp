/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
@brief
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

		CSScript(Entity _ID = DEFAULT_ENTITY);
		CSScript(CSScript&& rhs) noexcept;
		CSScript& operator=(CSScript&& rhs) noexcept;
		CSScript(const CSScript&) = delete;

	//private:
		//void InitVariable(const char* className);
	};
}

#endif