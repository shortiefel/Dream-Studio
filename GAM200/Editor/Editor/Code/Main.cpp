/* Start Header**********************************************************************************/
/*!
\file Main.cpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021
\brief
This file contains the starting point of the application. This is provided by Elie in CSD1130.
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
	Engine::Application::Create(); //Needed for game

	Engine::Application::SetupCallbackFunction(
		&Editor::EditorStartPoint::Create,
		&Editor::EditorStartPoint::Update,
		&Editor::EditorStartPoint::Destroy);

	Engine::Application::Update(false); //Needed for game

	Engine::Application::Destroy(); //Needed for game

	return 1;
}

