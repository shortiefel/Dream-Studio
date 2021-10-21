/* Start Header**********************************************************************************/
/*
@file    Main.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    26/04/2021
\brief
This file contains the starting point of the application.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

//Memory check-----------------------------
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//-----------------------------

#include "Engine/Header/Application.hpp"
#include "Editor/Header/EditorStartPoint.hpp"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //For memory check
    //use try and except (require logging)
    Engine::Application::GetInstance().Create(); //Needed for game

    Engine::Application::GetInstance().Update(false); //Needed for game

    Engine::Application::GetInstance().Destroy(); //Needed for game

    return 1;
}
