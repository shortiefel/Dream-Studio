/* Start Header**********************************************************************************/
/*!
\file Application.hpp
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
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.hpp"
#include "Event/EventDispatcher.hpp"

class Application {
public:
	static void Create();
	static void Run();
	static void Destroy();

	~Application();

	void OnEvent(Event& event);
	void SetEventCallBack();

	bool OnWindowClose(WindowCloseEvent& e);
private:
	static Application* s_app_instance;
	//static Window* window;
	static bool app_run_bool;

	Application() = default;
};

#endif