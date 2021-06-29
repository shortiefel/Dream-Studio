/* Start Header**********************************************************************************/
/*
@file    ScriptEmbed.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    28/06/2021
\brief
This file has the function definition for ScriptEmbed


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
