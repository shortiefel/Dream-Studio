/* Start Header**********************************************************************************/
/*
@file    ScriptEngine.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/08/2021
\brief
This file contain the definition of ScriptEngine


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Script/ScriptEngine.hpp"

#include "Engine/Header/Script/ScriptEmbed.hpp"
#include "Engine/Header/Script/ScriptInternalCall.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>

/*-------------------------------------
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
-------------------------------------*/
#include <iostream>

namespace Engine {
	namespace Scripting {
		CSEntityClassInstance ScriptEngine::csEntityClassInstance;

		MonoDomain* domain;
		MonoAssembly* assem;
		MonoImage* image;

		void ReloadMono();
		void destroy_child_domain();

		void ScriptEngine::Play() {
			ReloadMono();
			
			//Entity and map of classScript
			for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
				//Single class and (class and CS public variable)
				for (auto& [className, csScriptInstance] : classScriptInstances) {
					void* param[] = { (void*)&entityId }; //Change to entity.id for the future
					//mono_runtime_invoke(csScriptInstance.csClass.ConstructorFunc, csScriptInstance.csClass.object, param, nullptr);
					//mono_runtime_invoke(csScriptInstance.csClass.InitFunc, csScriptInstance.csClass.object, nullptr, nullptr);

					ReloadObject(csScriptInstance.csClass.object, csScriptInstance.csClass, param);
					//ReloadObject(csScriptInstance.csClass.object, csScriptInstance.csClass, param);
				}
			}
		}

		void ScriptEngine::InitEntityClassInstance() {
			ReloadMono();

			for (auto& [entityId, classScriptInstances] : csEntityClassInstance) {
				for (auto& [className, csScriptInstance] : classScriptInstances) {
					MonoClass* klass = mono_class_from_name(image, "", className.c_str());
					if (!klass) {
						LOG_ERROR("Failed loading class");
						return;
					}

					auto& csClass = csScriptInstance.csClass;
					csClass.object = (mono_object_new(mono_domain_get(), klass));
					if (!(csClass.object)) {
						LOG_ERROR("Failed loading obj");
						return;
					}

					//Call Constructor and Init
					klass = mono_class_from_name(image, "", "MonoBehaviour");

					//Set up virtual functions in MonoBehaviour
					MonoMethod* method = mono_class_get_method_from_name(klass, "Constructor", -1);
					csClass.UpdateFunc = mono_object_get_virtual_method(csClass.object, method);
					
					method = mono_class_get_method_from_name(klass, "Init", -1);
					csClass.UpdateFunc = mono_object_get_virtual_method(csClass.object, method);

					method = mono_class_get_method_from_name(klass, "Update", -1);
					csClass.UpdateFunc = mono_object_get_virtual_method(csClass.object, method);


					method = mono_class_get_method_from_name(klass, "Destroy", -1);
					csClass.DestroyFunc = mono_object_get_virtual_method(csClass.object, method);
				}
			}
		}


		void ScriptEngine::Create() {
			//Will to be changed to be automatic (can detect folders
			mono_set_dirs("C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/External Resources/include/Mono/lib",
				"C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/External Resources/include/Mono/etc");

			domain = mono_jit_init("Root Domain");

			mono_thread_set_main(mono_thread_current());

			RegisterInternalCall();
		}

		void ScriptEngine::Destroy() {
			destroy_child_domain();
			//clean up root domain
			mono_jit_cleanup(mono_domain_get());
		}

		



		void ScriptEngine::ReloadObject(MonoObject*& object, CSClass& csScript, void** param) {
			MonoClass* klass = mono_class_from_name(image, "", csScript.className.c_str());
			if (!klass) {
				LOG_ERROR("Failed loading class");
				return;
			}

			object = (mono_object_new(mono_domain_get(), klass));
			if (!(object)) {
				LOG_ERROR("Failed loading obj");
				return;
			}

			//Call Constructor and Init
			klass = mono_class_from_name(image, "", "MonoBehaviour");
			MonoMethod* method = mono_class_get_method_from_name(klass, "Constructor", -1);
			method = mono_object_get_virtual_method(object, method);
			if (method) {
				mono_runtime_invoke(method, object, param, nullptr);
			}

			method = mono_class_get_method_from_name(klass, "Init", -1);
			method = mono_object_get_virtual_method(object, method);
			if (method) {
				mono_runtime_invoke(method, object, nullptr, nullptr);
			}

			//Set up virtual functions in MonoBehaviour
			method = mono_class_get_method_from_name(klass, "Update", -1);
			csScript.UpdateFunc = mono_object_get_virtual_method(object, method);


			method = mono_class_get_method_from_name(klass, "Destroy", -1);
			csScript.DestroyFunc = mono_object_get_virtual_method(object, method);


			/*Testing only*/

			//mono_field_set_value();

			/*klass = mono_class_from_name(image, "", "Test");
			void* ptr = nullptr;
			MonoClassField* iter = mono_class_get_fields(klass, &ptr);
			const char* name = mono_field_get_name(iter);
			iter = mono_class_get_fields(klass, &ptr);
			const char* name2 = mono_field_get_name(iter);
			iter = mono_class_get_fields(klass, &ptr);
			const char* name3 = mono_field_get_name(iter);

			MONO_TYPE_BOOLEAN;
			MONO_TYPE_CHAR;
			MONO_TYPE_R4;*/

			//--------------------------

		}

		void ScriptEngine::CallFunction(MonoObject*& object, MonoMethod*& method, void** param) {
			if (method) {
				mono_runtime_invoke(method, object, param, nullptr);
			}
		}


		/*-----------------------------------------------------
			Called when play button is pressed
			-Serialize
			-Stop child domain
			-Create child domain
			-Load assemblies
		-----------------------------------------------------*/
		void ReloadMono() {
			destroy_child_domain();

			domain = mono_domain_create_appdomain((char*)("Child_Domain"), NULL);
			if (!domain) {
				mono_environment_exitcode_set(-1);
			}

			assem = mono_domain_assembly_open(domain, "Data/tem.dll");
			if (!assem) {
				LOG_ERROR("Failed loading assembly");
				return;
			}

			image = mono_assembly_get_image(assem);
			//images_v.emplace_back(image);
			if (!image) {
				LOG_ERROR("Failed loading image");
				return;
			}
		}

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
}