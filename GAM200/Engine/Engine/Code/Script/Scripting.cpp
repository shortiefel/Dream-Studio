/* Start Header**********************************************************************************/
/*
@file    Scripting.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    21/09/2021
\brief
This file contain the definition of Scripting


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Script/Scripting.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/debug-helpers.h> //MonoMethodDesc
#include <mono/metadata/attrdefs.h> //Attribute


#define INVOKE_FUNCTION(name)\
if (_csScriptInstance.csClass.name != nullptr) \
mono_runtime_invoke(_csScriptInstance.csClass.name, _csScriptInstance.csClass.object, _param, nullptr);

namespace Engine {
	namespace Scripting {
		MonoDomain* domain;
		MonoAssembly* assem;
		MonoImage* image;
		MonoImage* imageCore;

		CSType GetCSType(MonoType* mt);

		void Mono_Runtime_Invoke(const CSScriptInstance& _csScriptInstance, MonoFunctionType _type, void** _param) {
			switch (_type) {
			case MonoFunctionType::CONSTRUCTOR:
				INVOKE_FUNCTION(ConstructorFunc);
				break;
			case MonoFunctionType::INIT:
				INVOKE_FUNCTION(InitFunc);
				break;
			case MonoFunctionType::UPDATE:
				INVOKE_FUNCTION(UpdateFunc);
				break;
			case MonoFunctionType::DESTROY:
				INVOKE_FUNCTION(DestroyFunc);
				break;
			case MonoFunctionType::COLLISION_ENTER:
				INVOKE_FUNCTION(OnCollisionEnter);
				break;
			case MonoFunctionType::COLLISION_STAY:
				INVOKE_FUNCTION(OnCollisionStay);
				break;
			case MonoFunctionType::COLLISION_EXIT:
				INVOKE_FUNCTION(OnCollisionExit);
				break;
			case MonoFunctionType::TRIGGER_ENTER:
				INVOKE_FUNCTION(OnTriggerEnter);
				break;
			case MonoFunctionType::TRIGGER_STAY:
				INVOKE_FUNCTION(OnTriggerStay);
				break;
			case MonoFunctionType::TRIGGER_EXIT:
				INVOKE_FUNCTION(OnTriggerExit);
				break;
			}
		}


		void DestroyChildDomain() {
			MonoDomain* currentDomain = mono_domain_get();
			//Check if there is a child domain first
			if (currentDomain && currentDomain != mono_get_root_domain()) {
				if (!mono_domain_set(mono_get_root_domain(), false)) {
					LOG_ERROR("Scripting: Unable to set domain");
				}
				mono_domain_unload(currentDomain);
			}
		}

		void InitVariable(CSScriptInstance& _csScriptInstance) {
			if (_csScriptInstance.csClass.klass == nullptr) return;

			auto& variableMap = _csScriptInstance.csVariableMap;

			std::unordered_map<std::string, CSPublicVariable> oldVariable;
			oldVariable.reserve(variableMap.size());

			for (auto& [variableName, variableData] : variableMap) {
				oldVariable.emplace(variableName, std::move(variableData));
			}

			variableMap.clear();

			MonoClassField* classField;
			void* ptr = nullptr;
			while ((classField = mono_class_get_fields(_csScriptInstance.csClass.klass, &ptr)) != nullptr) {
				const char* name = mono_field_get_name(classField);
				unsigned int flags = mono_field_get_flags(classField);

				//Ignore private variables
				if ((flags & MONO_FIELD_ATTR_PUBLIC) == 0)
					continue;

				MonoType* variableType = mono_field_get_type(classField);
				CSType csType = GetCSType(variableType);

				char* typeName = mono_type_get_name(variableType);

				if (oldVariable.find(name) != oldVariable.end() && oldVariable.find(name)->second.variableType == csType) {
					variableMap.emplace(name, std::move(oldVariable.at(name)));
				}
				else {
					if (csType == CSType::NONE) {
						LOG_WARNING("Type not found");
						continue;
					}
					CSPublicVariable publicVariable = { name, csType };
					variableMap.emplace(name, std::move(publicVariable));
				}

			}
		}

		CSType GetCSType(MonoType* mt) {
			int type = mono_type_get_type(mt);
			switch (type) {
			case MONO_TYPE_CHAR: return CSType::CHAR;
			case MONO_TYPE_BOOLEAN: return CSType::BOOL;
			case MONO_TYPE_R4: return CSType::FLOAT;
			case MONO_TYPE_I4: return CSType::INT;
			case MONO_TYPE_U4: return CSType::UINT;
				//case MONO_TYPE_STRING: return CSType::STRING;
			case MONO_TYPE_VALUETYPE:
			{
				char* name = mono_type_get_name(mt);
				if (strcmp(name, "Vec2") == 0) return CSType::VEC2;
			}
			}
			return CSType::NONE;
		}
	}
}