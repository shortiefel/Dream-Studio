/* Start Header**********************************************************************************/
/*
@file    ScriptEngine.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/08/2021
\brief
This file contain the definition of ScriptEngine

find assembly with mono_domain_assembly_open and
get class inside file (class should be same name as filename)
c++ code will find method and call it (method like: update, init)

Steps to test
4. combine 2 files into 1 dll

When entering play mode
Compiles
Serialize
Stop child domain
Create child domain
Load assemblies
Load objects
Deserialize
Initialize object


Terminology

CSPublicVariable
-Class containing the data and description of a variable in CS

CSClass
-Store the name and some functions of a CS class (update/destroy)

CSScriptInstance
-CSClass and Map of string(Variable name) and CSPublicVariable

CSClassInstance
-Map of string(Class name) and CSScriptInstance

CSEntityClassInstance
-Map of entity id and CSClassInstance


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Script/ScriptEngine.hpp"

#include "Engine/Header/Script/ScriptInternalCall.hpp"

#include "Engine/Header/Event/OverlapColliderEvent.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/debug-helpers.h> //MonoMethodDesc
#include <mono/metadata/attrdefs.h> //Attribute

#include <cstdlib> //For file to be run by cmd (std::system)


#define OverlapFunctionCalls(name)\
if (csScriptInstance.csClass.name != nullptr) \
mono_runtime_invoke(csScriptInstance.csClass.name, csScriptInstance.csClass.object, nullptr, nullptr);
/*-------------------------------------

-------------------------------------*/
#include <iostream>


namespace Engine {
	CSEntityClassInstance ScriptEngine::csEntityClassInstance;

	MonoDomain* domain;
	MonoAssembly* assem;
	MonoImage* image;
	MonoImage* imageCore;

	void destroy_child_domain();
	bool CallOverlapFunc(const OverlapColliderEvent& e); //To be registered to Event

	void ScriptEngine::PlayInit() {
		//Entity and map of classScript
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				void* param[] = { (void*)&entityId }; //Change to entity.id after ECS rework
				if (csScriptInstance.csClass.ConstructorFunc != nullptr)
					mono_runtime_invoke(csScriptInstance.csClass.ConstructorFunc, csScriptInstance.csClass.object, param, nullptr);
				if (csScriptInstance.csClass.InitFunc != nullptr)
					mono_runtime_invoke(csScriptInstance.csClass.InitFunc, csScriptInstance.csClass.object, nullptr, nullptr);
			}
		}
	}

	void ScriptEngine::PlayRunTime() {
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				void* param[] = { (void*)&entityId }; //Change to entity.id after ECS rework
				if (csScriptInstance.csClass.UpdateFunc != nullptr)
					mono_runtime_invoke(csScriptInstance.csClass.UpdateFunc, csScriptInstance.csClass.object, nullptr, nullptr);
			}
		}
	}

	void ScriptEngine::Stop() {
		csEntityClassInstance.clear();
	}

	bool ScriptEngine::CompileCS() {
		destroy_child_domain();
		int status = std::system("CompileCS.bat");
		if (status > 0) return false;
		return true;
	}

	CSType ScriptEngine::GetCSType(MonoType* mt) {
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


	void ScriptEngine::Create() {
		//Rlative path from exe
		mono_set_dirs("Vendor/Mono/lib",
				      "Vendor/Mono/etc");

		domain = mono_jit_init("Root Domain");

		mono_thread_set_main(mono_thread_current());

		RegisterInternalCall();

		OverlapColliderEvent::RegisterFunction(CallOverlapFunc);
	}

	void ScriptEngine::Destroy() {
		destroy_child_domain();
		//clean up root domain
		mono_jit_cleanup(mono_domain_get());
	}

	void ScriptEngine::ReloadMono() {
		destroy_child_domain();

		domain = mono_domain_create_appdomain((char*)("Child_Domain"), NULL);
		if (!domain) {
			mono_environment_exitcode_set(-1);
		}

		else {
			mono_domain_set(domain, false);
		}

		assem = mono_domain_assembly_open(domain, "Data/CSScript.dll");
		if (!assem) {
			LOG_ERROR("Failed loading assembly");
			return;
		}

		image = mono_assembly_get_image(assem);
		if (!image) {
			LOG_ERROR("Failed loading image");
			return;
		}

		MonoAssembly* assemCore = mono_domain_assembly_open(domain, "Data/EngineCS.dll");
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

	bool CallOverlapFunc(const OverlapColliderEvent& e) {
		//std::cout << "calling overlap function \n";
		if (ScriptEngine::csEntityClassInstance.find(e.self) != ScriptEngine::csEntityClassInstance.end()) {
			for (auto& [className, csScriptInstance] : ScriptEngine::csEntityClassInstance[e.self]) {
				switch (e.type) {
				case OverlapType::OnCollisionEnter:
					OverlapFunctionCalls(OnCollisionEnter);
					break;
				case OverlapType::OnCollisionStay:
					OverlapFunctionCalls(OnCollisionStay);
					break;
				case OverlapType::OnCollisionExit:
					OverlapFunctionCalls(OnCollisionExit);
					break;
				case OverlapType::OnTriggerEnter:
					OverlapFunctionCalls(OnTriggerEnter);
					break;
				case OverlapType::OnTriggerStay:
					OverlapFunctionCalls(OnTriggerStay);
					break;
				case OverlapType::OnTriggerExit:
					OverlapFunctionCalls(OnTriggerExit);
					break;

				}
			}
		}
		return true;
	}


	void ScriptEngine::CallFunction(MonoObject*& object, MonoMethod*& method, void** param) {
		if (method) {
			mono_runtime_invoke(method, object, param, nullptr);
		}
	}

	void ScriptEngine::UpdateMapData() {
		ReloadMono();
		InitEntityClassInstance();
		InitPublicVariable();
	}

	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Private static function called within class
	------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ScriptEngine::InitEntityClassInstance() {
			
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				auto& csClass = csScriptInstance.csClass;

				csClass.klass = mono_class_from_name(image, "", className.c_str());
				if (!csClass.klass) {
					LOG_ERROR("Failed loading class");
					return;
				}

				csClass.object = (mono_object_new(mono_domain_get(), csClass.klass));
				if (!(csClass.object)) {
					LOG_ERROR("Failed loading obj");
					return;
				}
					

				std::string methodDesc = "MonoBehaviour:.ctor(uint)";
				MonoMethodDesc* description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.ConstructorFunc = mono_method_desc_search_in_image(description, imageCore);

				methodDesc = className + ":Init()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.InitFunc = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":Update()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.UpdateFunc = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":Destroy()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.DestroyFunc = mono_method_desc_search_in_image(description, image);


				methodDesc = className + ":OnCollisionEnter()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.OnCollisionEnter = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":OnCollisionStay()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.OnCollisionStay = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":OnCollisionExit()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.OnCollisionExit = mono_method_desc_search_in_image(description, image);


				methodDesc = className + ":OnTriggerEnter()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.OnTriggerEnter = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":OnTriggerStay()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.OnTriggerStay = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":OnTriggerExit()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.OnTriggerExit = mono_method_desc_search_in_image(description, image);
			}
		}
	}

	void ScriptEngine::InitPublicVariable() {
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				auto& variableMap = csScriptInstance.csVariableMap;

				std::unordered_map<std::string, CSPublicVariable> oldVariable;
				oldVariable.reserve(variableMap.size());

				for (auto& [variableName, variableData] : variableMap) {
					oldVariable.emplace(variableName, std::move(variableData));
				}

				variableMap.clear();

				MonoClassField* classField;
				void* ptr = nullptr;
				while ((classField = mono_class_get_fields(csScriptInstance.csClass.klass, &ptr)) != nullptr) {
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
		}
	}


	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Local Functions
	------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

	/*-----------------------------------------------------
		Destroy child domain
		-Check if child domain exist
		-delete if it exist
	-----------------------------------------------------*/
	void destroy_child_domain() {
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