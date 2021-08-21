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
serialize    
shut down child domain       
create child domain    
load assemblies    
deserialize


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Script/ScriptEmbed.hpp"

#include <string>

#include <mono/jit/jit.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/environment.h>


#include <fstream> //remove
#include <vector> //remove

namespace Engine {
	namespace ScriptEmbed {
		MonoDomain* domain;
		MonoAssembly* assem;
		std::vector<MonoImage*> images;
		std::vector<MonoObject*> instances;

		void ReloadMono();
		MonoDomain* create_child_domain();
		void destroy_child_domain();

		//--------------------------------------------------------------------------------
		char* Read(std::string filename, size_t* len) {
			std::ifstream file(filename.c_str(), std::ifstream::binary);
			if (file) {
				// get length of file:
				file.seekg(0, file.end);
				auto length = file.tellg();
				*len = length;
				file.seekg(0, file.beg);

				char* arr = new char[length];
				file.read(arr, length);
				file.close();

				return arr;
			}
			return nullptr;

		}
		//--------------------------------------------------------------------------------

		void Create() {
			//Will to be changed to be automatic (can detect folders
			mono_set_dirs("C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/External Resources/include/Mono/lib",
				"C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/External Resources/include/Mono/etc");

			domain = mono_jit_init("Root Domain");

			mono_thread_set_main(mono_thread_current());

			ReloadMono();
		}

		void Destroy() {
			create_child_domain();
			//clean up root domain
			mono_jit_cleanup(mono_domain_get());
		}

		void ReloadMono() {
			destroy_child_domain();

			domain = create_child_domain();
			if (!domain) {
				mono_environment_exitcode_set(-1);
			}

			assem = mono_domain_assembly_open(domain, "Data/tem.dll");
			if (!assem) {
				LOG_ERROR("Failed loading assembly");
				return;
			}

			MonoImage* image = mono_assembly_get_image(assem);
			images.emplace_back(image);
			if (!image) {
				LOG_ERROR("Failed loading image");
				return;
			}

			MonoClass* klass = mono_class_from_name(image, "", "Test");

			if (!klass) {
				LOG_ERROR("Failed loading class");
				return;
			}


			MonoObject* obj = mono_object_new(mono_domain_get(), klass);
			if (!obj) {
				LOG_ERROR("Failed loading obj");
				return;
			}

			MonoObject* obj2 = mono_object_new(mono_domain_get(), klass);
			if (!obj2) {
				LOG_ERROR("Failed loading obj");
				return;
			}

			//instances.push_back(obj);

			MonoMethod* method = mono_class_get_method_from_name(klass, "Damage", -1);
			if (method) {
				mono_runtime_invoke(method, obj, nullptr, nullptr);
			}

			method = mono_class_get_method_from_name(klass, "ShowHealth", -1);
			if (method) {
				mono_runtime_invoke(method, obj, nullptr, nullptr);
			}


			//method = mono_class_get_method_from_name(klass, "ShowHealth", -1);
			if (method) {
				mono_runtime_invoke(method, obj2, nullptr, nullptr);
			}
			

			
			



			//size_t length;
			//std::string filename = "C:/Users/jianw/Desktop/Digipen/GAM200/GAM200/Editor/Assets/testing.cs";
			//char* data = Read(filename.c_str(), &length);
			//

			//MonoImageOpenStatus status;
			//// open the assembly from the data we read, so we never lock files
			//auto image = mono_image_open_from_data_with_name(data, length, true /* copy data */, &status, false /* ref only */, filename.c_str());
			//if (status != MONO_IMAGE_OK || image == nullptr)
			//{
			//	LOG_ERROR("F1ailed loading assembly");
			//	return;
			//}

			//// load the assembly
			//auto  assembly = mono_assembly_load_from_full(image, filename.c_str(), &status, false);
			//if (status != MONO_IMAGE_OK || assembly == nullptr)
			//{
			//	mono_image_close(image);
			//	LOG_ERROR("Failed loading assembly");
			//}

			//// save the image for lookups later and for cleaning up
			//images.push_back(image);

			//if (!assembly) {
			//	LOG_ERROR("Couldn't find assembly");
			//}

			//// locate the class we want to load
			//MonoClass* klass = mono_class_from_name(image, "TestSpace", "Test");
			//if (klass == nullptr) {
			//	LOG_ERROR("Failed loading class");
			//}

			//// create the class (doesn't run constructors)
			//MonoObject* obj = mono_object_new(mono_domain_get(), klass);
			//if (obj == nullptr) {
			//	LOG_ERROR("Failed loading class instance %s");
			//}

			//// initialize the class instance (runs default constructors)
			//mono_runtime_object_init(obj);
			//if (obj == nullptr) {
			//	LOG_ERROR("Failed initializing class instance %s");
			//}

			//// save the class instance for lookups later
			//instances.push_back(obj);

			//MonoMethod* method = mono_class_get_method_from_name(klass, "Run", -1);
			//

			//// call the Run method. This will block until the managed code decides to exit
			//mono_runtime_invoke(method, obj, NULL, NULL);
		}

		MonoDomain* create_child_domain() {
			//std::string childDomainName = ;
			MonoDomain* childDomain = mono_domain_create_appdomain((char*)("Child_Domain"), NULL);

			//mono_thread_push_appdomain_ref(childDomain);

			return childDomain;
		}

		void destroy_child_domain() {
			MonoDomain* currentDomain = mono_domain_get();
			//Check if there is a child domain first
			if (currentDomain && currentDomain != mono_get_root_domain()) {
				if (!mono_domain_set(mono_get_root_domain(), false)) {
					LOG_ERROR("Scripting: Unable to set domain");
				}

				//mono_thread_pop_appdomain_ref();
				mono_domain_unload(currentDomain);
			}
		}
	}
}
