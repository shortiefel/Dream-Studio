/* Start Header**********************************************************************************/
/*
@file    ScriptSystem.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/08/2021
\brief
This file contain the definition of ScriptSystem

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
#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#include "Engine/Header/Script/ScriptInternalCall.hpp"

#include "Engine/Header/Event/OverlapColliderEvent.hpp"

#include "Engine/Header/ECS/ECSWrapper.hpp"

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

#define NEWSCRIPTING 1

namespace Engine {
	//CSEntityClassInstance ScriptSystem::csEntityClassInstance;

	MonoDomain* domain;
	MonoAssembly* assem;
	MonoImage* image;
	MonoImage* imageCore;

	void destroy_child_domain();
	bool CallOverlapFunc(const OverlapColliderEvent& e); //To be registered to Event

	void ScriptSystem::PlayInit() {
#if NEWSCRIPTING
		const auto& entScriptArray = DreamECS::GetComponentArrayData<CSScript>();
		for (auto& csScript : entScriptArray) {
			auto& classScriptInstances = csScript.klassInstance;
			const auto& entityId = csScript.GetEntityId();
#else
		//Entity and map of classScript
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
#endif
			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				void* param[] = { (void*)&entityId }; //Change to entity.id after ECS rework
				if (csScriptInstance.isActive && csScriptInstance.csClass.ConstructorFunc != nullptr)
					mono_runtime_invoke(csScriptInstance.csClass.ConstructorFunc, csScriptInstance.csClass.object, param, nullptr);
				if (csScriptInstance.isActive && csScriptInstance.csClass.InitFunc != nullptr)
					mono_runtime_invoke(csScriptInstance.csClass.InitFunc, csScriptInstance.csClass.object, nullptr, nullptr);
			}
		}
	}

	void ScriptSystem::PlayRunTime() {
#if NEWSCRIPTING
		const auto& entScriptArray = DreamECS::GetComponentArrayData<CSScript>();
		for (auto& csScript : entScriptArray) {
			auto& classScriptInstances = csScript.klassInstance;
			const auto& entityId = csScript.GetEntityId();
#else
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
#endif
			//if (csEntityClassInstance.find(entityId) == csEntityClassInstance.end()) continue;
			//Single class and (class and CS public variable)
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				//Run time check in case it is deleted 
				//if (csEntityClassInstance.find(entityId) == csEntityClassInstance.end()) break;
				if (csScriptInstance.isActive && csScriptInstance.csClass.UpdateFunc != nullptr)
					mono_runtime_invoke(csScriptInstance.csClass.UpdateFunc, csScriptInstance.csClass.object, nullptr, nullptr);
			}
		}
	}

	void ScriptSystem::Stop() {
		//csEntityClassInstance.clear();
	}

	bool ScriptSystem::CompileCS() {
		destroy_child_domain();
		int status = std::system("CompileCS.bat");
		if (status > 0) return false;
		return true;
	}

	CSType ScriptSystem::GetCSType(MonoType* mt) {
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


	void ScriptSystem::Create() {
		//Rlative path from exe
		mono_set_dirs("Vendor/Mono/lib",
			"Vendor/Mono/etc");

		domain = mono_jit_init("Root Domain");

		mono_thread_set_main(mono_thread_current());

		RegisterInternalCall();

		OverlapColliderEvent::RegisterFunction(CallOverlapFunc);
	}

	void ScriptSystem::Destroy() {
		destroy_child_domain();
		//clean up root domain
		mono_jit_cleanup(mono_domain_get());
	}

	void ScriptSystem::ReloadMono() {
		destroy_child_domain();

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

	bool CallOverlapFunc(const OverlapColliderEvent& e) {
		CSScript* csScript = DreamECS::GetComponentTest<CSScript>(e.self);
		if (!csScript) return false;
		for (auto& [className, csScriptInstance] : csScript->klassInstance) {
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
		return true;
	}


	void ScriptSystem::CallFunction(MonoObject*& object, MonoMethod*& method, void** param) {
		if (method) {
			mono_runtime_invoke(method, object, param, nullptr);
		}
	}

	void ScriptSystem::UpdateMapData() {
		ReloadMono();
		InitEntityClassInstance();
		InitPublicVariable();
	}

	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Private static function called within class
	------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	void ScriptSystem::InitEntityClassInstance() {
#if NEWSCRIPTING
		auto& entScriptArray = DreamECS::GetComponentArrayData<CSScript>();
		for (auto& csScript : entScriptArray) {
			auto& classScriptInstances = csScript.klassInstance;
			const auto& entityId = csScript.GetEntityId();
#else
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
#endif
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

				methodDesc = className + ":OnInit()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.InitFunc = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":OnUpdate()";
				description = mono_method_desc_new(methodDesc.c_str(), NULL);
				csClass.UpdateFunc = mono_method_desc_search_in_image(description, image);

				methodDesc = className + ":OnDestroy()";
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

	void ScriptSystem::InitPublicVariable() {
#if NEWSCRIPTING
		auto& entScriptArray = DreamECS::GetComponentArrayData<CSScript>();
		for (auto& csScript : entScriptArray) {
			auto& classScriptInstances = csScript.klassInstance;
			const auto& entityId = csScript.GetEntityId();
#else
		for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
#endif
			for (auto& [className, csScriptInstance] : classScriptInstances) {
				if (csScriptInstance.csClass.klass == nullptr) continue;

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

	void Serialize(const SSerializer& _serializer) {
		/*const CSClassInstance& entityclassInstance = ScriptSystem::csEntityClassInstance.find(ent)->second;
		rapidjson::Value classArray(rapidjson::kArrayType);

		for (const auto& [className, scriptInstance] : entityclassInstance) {
			rapidjson::Value classNameFP;
			char buffer[200];
			int len = sprintf_s(buffer, "%s", className.c_str());
			classNameFP.SetString(buffer, len, doc.GetAllocator());

			rapidjson::Value classObj(rapidjson::kObjectType);
			classObj.AddMember("Class", classNameFP, doc.GetAllocator());

			classObj.AddMember("IsActive", scriptInstance.isActive, doc.GetAllocator());

			if (scriptInstance.csVariableMap.size()) {
				rapidjson::Value variableArray(rapidjson::kArrayType);

				for (const auto& [variableName, variableInstance] : scriptInstance.csVariableMap) {
					rapidjson::Value variableObject(rapidjson::kObjectType);
					SSerializer serializer(doc, variableObject);
					ScriptSystem::SerializeVariable(serializer, variableName, variableInstance);

					variableArray.PushBack(variableObject, doc.GetAllocator());
				}
				classObj.AddMember("Variable", variableArray, doc.GetAllocator());
			}

			classArray.PushBack(classObj, doc.GetAllocator());
		}*/
	}

	void ScriptSystem::SerializeVariable(const SSerializer& _serializer, const CSScriptInstance& _scriptInstance) {
		for (const auto& [variableName, variableInstance] : _scriptInstance.csVariableMap) {
			rapidjson::Value variableObject(rapidjson::kObjectType);
			SSerializer vserializer(_serializer, variableObject);

			vserializer.SetValue("Name", variableName);
			vserializer.SetValue("Type", (int)variableInstance.variableType);

			switch (variableInstance.variableType) {
			case CSType::CHAR:
				vserializer.SetValue("Data", variableInstance.GetVariableData<char>());
				break;
			case CSType::BOOL:
				vserializer.SetValue("Data", variableInstance.GetVariableData<bool>());
				break;
			case CSType::FLOAT:
				vserializer.SetValue("Data", variableInstance.GetVariableData<float>());
				break;
			case CSType::INT:
				vserializer.SetValue("Data", variableInstance.GetVariableData<int>());
				break;
			case CSType::UINT:
				vserializer.SetValue("Data", variableInstance.GetVariableData<unsigned int>());
				break;
			case CSType::VEC2:
				vserializer.SetValue("Data", variableInstance.GetVariableData<Math::vec2>());
				break;
			}

			_serializer.SetValueJSonArray(variableObject);
		}


	}

	void ScriptSystem::SerializeClass(const SSerializer& _serializer, const CSClassInstance& _classInstance) {
		for (const auto& [className, scriptInstance] : _classInstance) {

			rapidjson::Value classObj(rapidjson::kObjectType);
			SSerializer cserializer(_serializer, classObj);

			cserializer.SetValue("Class", className);
			cserializer.SetValue("IsActive", scriptInstance.isActive);

			if (scriptInstance.csVariableMap.size()) {
				rapidjson::Value variableArray(rapidjson::kArrayType);

				SSerializer serializer(cserializer, variableArray);
				SerializeVariable(serializer, scriptInstance);

				cserializer.SetValueJSon("Variable", variableArray);
			}

			_serializer.SetValueJSonArray(classObj);
		}
	}


	void ScriptSystem::Deserialize(const DSerializer& _serializer, CSClassInstance& classInstance) {
		for (auto& classJSon : _serializer.GetArray()) {
			const auto& className = classJSon["Class"].GetString();

			CSScriptInstance csScriptInstance{
				className,
				classJSon["IsActive"].GetBool() };

			rapidjson::Value::ConstMemberIterator variableItr = classJSon.FindMember("Variable");
			if (variableItr != classJSon.MemberEnd()) {
				for (auto& variableData : variableItr->value.GetArray()) {
					const auto& variableName = variableData["Name"].GetString();
					const auto& variableType = CSType{ variableData["Type"].GetInt() };


					CSPublicVariable csPublicvariable{ variableName, variableType };


					if (variableType == CSType::CHAR) {
						char charData = variableData["Data"].GetInt();
						csPublicvariable.SetVariableData(&charData);
					}

					else if (variableType == CSType::BOOL) {
						bool boolData = variableData["Data"].GetBool();
						csPublicvariable.SetVariableData(&boolData);
					}

					else if (variableType == CSType::FLOAT) {
						float floatData = variableData["Data"].GetFloat();
						csPublicvariable.SetVariableData(&floatData);
					}
					else if (variableType == CSType::INT) {
						int intData = variableData["Data"].GetInt();
						csPublicvariable.SetVariableData(&intData);
					}
					else if (variableType == CSType::UINT) {
						unsigned int uinData = variableData["Data"].GetUint();
						csPublicvariable.SetVariableData(&uinData);
					}

					else if (variableType == CSType::VEC2) {
						Math::vec2 vec2Data{ variableData["Data"].GetArray()[0].GetFloat(),
											variableData["Data"].GetArray()[1].GetFloat() };
						csPublicvariable.SetVariableData(&vec2Data);
					}

					csScriptInstance.csVariableMap.emplace(variableName, std::move(csPublicvariable));
				}
			}
			classInstance.emplace(className, std::move(csScriptInstance));
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