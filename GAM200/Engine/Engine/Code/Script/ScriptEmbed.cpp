/* Start Header**********************************************************************************/
/*
@file    ScriptEmbed.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    28/06/2021
\brief
This file has the function definition for ScriptEmbed

find assembly with mono_domain_assembly_open and 
get class inside file (class should be same name as filename)
c++ code will find method and call it (method like: update, init)

Steps to test
1. call code from c# class from dll
2. call code that is overwritten
3. runtime creation of dll
4. combine 2 files into 1 dll
5. comb through folders to get all dll (Resource System) (might do it at a later time)


When entering play mode
Compiles        
Serialize
Stop child domain
Create child domain
Load assemblies
Load objects
Deserialize
Initialize object

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Script/ScriptEmbed.hpp"
#include "Engine/Header/Script/ScriptInternalCall.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>

#include <glm/glm.hpp>

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/ECS/Coordinator.hpp"

#include <iostream> //remove



namespace Engine {
	namespace Scripting {
		MonoDomain* domain;
		MonoAssembly* assem;
		MonoImage* image;
		
		void destroy_child_domain();

		

		/*-----------------------------------------------------
			Get Component by type
			return null if doesnt exist
		-----------------------------------------------------*/
		

		void Create() {
			//Will to be changed to be automatic (can detect folders
			mono_set_dirs("C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/External Resources/include/Mono/lib",
				"C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/External Resources/include/Mono/etc");

			domain = mono_jit_init("Root Domain");

			mono_thread_set_main(mono_thread_current());
			
			//mono_add_internal_call("GameObject::GetTransform_Native", GetComponentInScriptEmbeded);
			//mono_add_internal_call("GameObject::SetTransform_Native", SetComponentInScriptEmbeded);

			RegisterInternalCall();
		}

		void Destroy() {
			destroy_child_domain();
			//clean up root domain
			mono_jit_cleanup(mono_domain_get());
		}

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



		void ReloadObject(MonoObject*& object, CSharpScript& cSharpScript, void** param) {
			MonoClass* klass = mono_class_from_name(image, "", cSharpScript.className.c_str());
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
			cSharpScript.UpdateFunc = mono_object_get_virtual_method(object, method);
			

			method = mono_class_get_method_from_name(klass, "Destroy", -1);
			cSharpScript.DestroyFunc = mono_object_get_virtual_method(object, method);
			
		}

		void CallFunction(MonoObject*& object, std::string& className, std::string& func) {
			MonoClass* klass = mono_class_from_name(image, "", "MonoBehaviour");
			MonoMethod* method = mono_class_get_method_from_name( klass, func.c_str(), -1);
			
			//void* param[] = { tem };

			if (method) {
				mono_runtime_invoke(method, object, nullptr, nullptr);
			}
		}

		void CallFunction(MonoObject*& object, MonoMethod*& method, void** param) {
			if (method) {
				mono_runtime_invoke(method, object, param, nullptr);
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
