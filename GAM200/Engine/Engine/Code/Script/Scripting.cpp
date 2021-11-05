/* Start Header**********************************************************************************/
/*
@file    Scripting.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Management/GameState.hpp"


#define INVOKE_FUNCTION(name)\
if (_csScriptInstance.csClass.name != nullptr) {\
	mono_runtime_invoke(_csScriptInstance.csClass.name, _csScriptInstance.csClass.object, _param, &exception);\
	if (exception != nullptr) {\
	displayFuncPtr(mono_string_to_utf8(mono_object_to_string(exception, nullptr)));\
	GameState::GetInstance().SetPlaying(false);\
	Scripting::DestroyChildDomain();\
	}\
}


namespace Engine {
	namespace Scripting {
		MonoDomain* domain;
		MonoAssembly* assem;
		MonoImage* image;
		MonoImage* imageCore;
		//Does nothing in base game
		void(*displayFuncPtr)(std::string) = [](std::string) {};
		void(*compileFuncPtr)() = []() {};

		CSType GetCSType(MonoType* mt);

		void Mono_Runtime_Invoke(const CSScriptInstance& _csScriptInstance, MonoFunctionType _type, void** _param) {
			MonoObject* exception = nullptr;
			switch (_type) {
			case MonoFunctionType::CONSTRUCTOR:
				INVOKE_FUNCTION(ConstructorFunc);
				break;
			case MonoFunctionType::INIT:
				INVOKE_FUNCTION(InitFunc);
				break;
			case MonoFunctionType::UPDATE:
				//INVOKE_FUNCTION(UpdateFunc);
				if (_csScriptInstance.csClass.UpdateFunc != nullptr) {
						mono_runtime_invoke(_csScriptInstance.csClass.UpdateFunc, _csScriptInstance.csClass.object, _param, &exception);
						if (exception != nullptr) {
							
								displayFuncPtr(mono_string_to_utf8(mono_object_to_string(exception, nullptr))); 
								GameState::GetInstance().SetPlaying(false); 
								Scripting::DestroyChildDomain(); 
						}
				}
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
			case MonoFunctionType::MOUSE_ENTER:
				INVOKE_FUNCTION(OnMouseEnter);
				break;
			/*case MonoFunctionType::MOUSE_CLICK:
				INVOKE_FUNCTION(OnMouseClick);
				break;*/
			case MonoFunctionType::MOUSE_OVER:
				INVOKE_FUNCTION(OnMouseOver);
				break;
			case MonoFunctionType::MOUSE_EXIT:
				INVOKE_FUNCTION(OnMouseExit);
				break;
			}
		}

		void Setup() {
			//Rlative path from exe
			mono_set_dirs("Vendor/Mono/lib",
				"Vendor/Mono/etc");

			domain = mono_jit_init("Root Domain");

			mono_thread_set_main(mono_thread_current());
		}

		void Cleanup() {
			Scripting::DestroyChildDomain();
			//clean up root domain
			mono_jit_cleanup(mono_domain_get());
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

		bool CompileCSInternal(bool play) {
			Scripting::DestroyChildDomain();
			int status = std::system("CompileCS.bat");
			if (play)
				compileFuncPtr();
			if (status > 0) return false;
			return true;
		}


		void ReloadMono() {
			Scripting::DestroyChildDomain();

			domain = mono_domain_create_appdomain((char*)("Child_Domain"), NULL);
			if (!domain) {
				mono_environment_exitcode_set(-1);
			}

			else {
				mono_domain_set(domain, false);
			}

			assem = mono_domain_assembly_open(domain, "Data/CSScript/CSScript.dll");
			if (!assem) {
				LOG_ERROR("Failed loading assembly");
				return;
			}

			image = mono_assembly_get_image(assem);
			if (!image) {
				LOG_ERROR("Failed loading image");
				return;
			}

			MonoAssembly* assemCore = mono_domain_assembly_open(domain, "Data/CSScript/EngineCS.dll");
			if (!assemCore) {
				LOG_ERROR("Failed loading assembly");
				return;
			}
			imageCore = mono_assembly_get_image(assemCore);
			if (!imageCore) {
				LOG_ERROR("Failed loading image");
				return;
			}
		}

		void InitScript(const Entity_id& entity_id, const CSScriptInstance& csScriptInstance) {
			if (!GameState::GetInstance().GetPlaying()) return;
			void* param[] = { (void*)&entity_id };
			//std::cout << "class: " << className << "\n";
			if (csScriptInstance.isActive && csScriptInstance.csClass.ConstructorFunc != nullptr) {
				Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::CONSTRUCTOR, param);
			}
			if (csScriptInstance.isActive && csScriptInstance.csClass.InitFunc != nullptr) {
				Scripting::Mono_Runtime_Invoke(csScriptInstance, MonoFunctionType::INIT);
			}
		}

		bool InitCSClass(CSScriptInstance& _csScriptInstance, const Entity_id& entity_id) {
			//If no child domain the klass doesnt exist
			MonoDomain* currentDomain = mono_domain_get();
			if (!currentDomain || currentDomain == mono_get_root_domain()) return true;
			//if (!GameState::GetInstance().GetPlaying()) return true;

			auto& csClass = _csScriptInstance.csClass;
			auto& fullName = csClass.fullName;
			
			csClass.klass = mono_class_from_name(image, csClass.namespaceName.c_str(), csClass.className.c_str());
			if (!csClass.klass) {
				LOG_ERROR("Failed loading class");
				return false;
			}

			csClass.object = (mono_object_new(mono_domain_get(), csClass.klass));
			if (!(csClass.object)) {
				LOG_ERROR("Failed loading obj");
				return false;
			}

			std::string methodDesc = "MonoBehaviour:.ctor(uint)";
			MonoMethodDesc* description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.ConstructorFunc = mono_method_desc_search_in_image(description, imageCore);

			methodDesc = fullName + ":Start()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.InitFunc = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":Update()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.UpdateFunc = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnDestroy()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.DestroyFunc = mono_method_desc_search_in_image(description, image);


			methodDesc = fullName + ":OnCollisionEnter()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnCollisionEnter = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnCollisionStay()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnCollisionStay = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnCollisionExit()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnCollisionExit = mono_method_desc_search_in_image(description, image);


			methodDesc = fullName + ":OnTriggerEnter()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnTriggerEnter = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnTriggerStay()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnTriggerStay = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnTriggerExit()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnTriggerExit = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnMouseEnter()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnMouseEnter = mono_method_desc_search_in_image(description, image);
			
			/*methodDesc = fullName + ":OnMouseClick()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnMouseClick = mono_method_desc_search_in_image(description, image);*/

			methodDesc = fullName + ":OnMouseOver()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnMouseOver = mono_method_desc_search_in_image(description, image);

			methodDesc = fullName + ":OnMouseExit()";
			description = mono_method_desc_new(methodDesc.c_str(), NULL);
			csClass.OnMouseExit = mono_method_desc_search_in_image(description, image);

			Scripting::InitScript(entity_id, _csScriptInstance);

			return true;
		}

		void InitAllCSClass() {
			auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
			for (auto& csScript : entScriptArray) {
				auto& classScriptInstances = csScript.klassInstance;
				
				std::set<std::string> classToDelete;
				for (auto& [className, csScriptInstance] : classScriptInstances) {
					if (!InitCSClass(csScriptInstance, csScript.GetEntityId())) {
						classToDelete.emplace(className);
					}
				}

				for (auto& className : classToDelete) {
					classScriptInstances.erase(className);
				}
			}
		}

		void InitVariable(CSScriptInstance&) {
			//if (_csScriptInstance.csClass.klass == nullptr) return;

			//auto& variableMap = _csScriptInstance.csVariableMap;

			//std::unordered_map<std::string, CSPublicVariable> oldVariable;
			//oldVariable.reserve(variableMap.size());

			//for (auto& [variableName, variableData] : variableMap) {
			//	oldVariable.emplace(variableName, std::move(variableData));
			//}
			//
			//variableMap.clear();

			//MonoClassField* classField;
			//void* ptr = nullptr;
			//while ((classField = mono_class_get_fields(_csScriptInstance.csClass.klass, &ptr)) != nullptr) {
			//	const char* name = mono_field_get_name(classField);
			//	unsigned int flags = mono_field_get_flags(classField);

			//	//Ignore private variables
			//	if ((flags & MONO_FIELD_ATTR_PUBLIC) == 0)
			//		continue;
			//	MonoType* variableType = mono_field_get_type(classField);
			//	CSType csType = GetCSType(variableType);

			//	//char* typeName = mono_type_get_name(variableType);

			//	if (oldVariable.find(name) != oldVariable.end() && oldVariable.find(name)->second.variableType == csType) {
			//		variableMap.emplace(name, std::move(oldVariable.at(name)));
			//	}
			//	else {
			//		if (csType == CSType::NONE) {
			//			LOG_WARNING("Type not found");
			//			continue;
			//		}
			//		CSPublicVariable publicVariable = { name, csType };
			//		variableMap.emplace(name, std::move(publicVariable));
			//	}

			//}
		}

		void InitAllPublicVariable() {
			/*auto& entScriptArray = dreamECSGame->GetComponentArrayData<ScriptComponent>();
			for (auto& csScript : entScriptArray) {
				auto& classScriptInstances = csScript.klassInstance;
				
				for (auto& [className, csScriptInstance] : classScriptInstances) {
					InitVariable(csScriptInstance);
				}
			}*/
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
				if (strcmp(name, "Vector2") == 0) return CSType::VEC2;
				break;
			}
			/*case MONO_TYPE_CLASS: {
				char* name = mono_type_get_name(mt);
				if (strcmp(name, "GameObject") == 0) {
					printf("GameObject \n");
					return CSType::GAMEOBJECT;
				}
			}*/
			}
			return CSType::NONE;
		}

		void OpenVS(std::string fileName) {

			//std::system("Data\\OpenVS.bat");
			printf("Does nothing for now\n");
		}

		void SetDisplayFuncPtr(void(*fp)(std::string)) {
			displayFuncPtr = fp;
		}

		void SetCompileFuncPtr(void(*fp)()) {
			compileFuncPtr = fp;
		}

	}
}