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


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Script/ScriptEmbed.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

MonoDomain* domain;

namespace ScriptEmbed {
	void Init() {
		//domain = mono_jit_init("Test name");

	}
}
