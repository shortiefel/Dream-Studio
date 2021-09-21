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


#define INVOKE_FUNCTION(name)\
if (_csScriptInstance.csClass.name != nullptr) \
mono_runtime_invoke(_csScriptInstance.csClass.name, _csScriptInstance.csClass.object, _param, nullptr);

namespace Engine {
	namespace Scripting {
		MonoDomain* domain;
		MonoAssembly* assem;
		MonoImage* image;
		MonoImage* imageCore;

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
	}
}