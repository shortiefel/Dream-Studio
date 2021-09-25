/* Start Header**********************************************************************************/
/*
@file    ScriptInternalCall.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    25/08/2021
\brief
This file contain the declaration of ScriptInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_INTERNAL_CALL
#define SCRIPT_INTERNAL_CALL

namespace Engine {
	//Register Internal call for C# side to use
	//Found in ScriptInternalCall.hpp
	void RegisterInternalCall();
}

#endif