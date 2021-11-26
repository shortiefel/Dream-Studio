/* Start Header**********************************************************************************/
/*!
\file 			Main.cpp
\team name		Dream Studio
\software name	Dream Express
\authors		Ow Jian Wen				jianwen.o@digipen.edu				100%	
\date 26/04/2021
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

#include <Windows.h>

//#define GAME_BUILD

//int main() {
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //For memory check
	//use try and except (require logging)
	Engine::Application::GetInstance().Create(); //Needed for game

#ifndef _GAME_BUILD
	Engine::Application::GetInstance().SetupCallbackFunction(
		&Editor::EditorStartPoint::Create,
		&Editor::EditorStartPoint::Update,
		&Editor::EditorStartPoint::Destroy);
#endif

	Engine::Application::GetInstance().Update(); //Needed for game

	Engine::Application::GetInstance().Destroy(); //Needed for game

	return 1;
}

