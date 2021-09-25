/* Start Header**********************************************************************************/
/*!
\file Application.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen.o@digipen.edu				TECHINCAL DIRECTOR
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

#include "Engine/Header/Singleton/Singleton.hpp"

typedef void (*FuncNoData)();
typedef void (*Func1Param)(float);

namespace Engine {
	//Forward declaration
	struct GLFWwindow;
	class Event;
	class WindowCloseEvent;
	class DeltaTime;

	class Application : public Singleton<Application> {
	public:
		

		void Create();
		/*Main application loop is done here
		defaultRender - whether to use default rendering or not (For scene update)*/
		void Update(bool defaultRender);
		void Destroy();


		inline void SetAppRun(bool _bool) { app_run_bool = _bool; }
		//void OnEvent(Event& event);
		//Set event call back for events
		//void SetEventCallBack();

		//Set up function callback for editor function
		void SetupCallbackFunction(FuncNoData func1, Func1Param func2, FuncNoData func3);
	private:
		Application* s_app_instance = 0;
		//static GLFWwindow* s_glfw_window;

		bool app_run_bool = true;
		float m_lastframeTime = 0.f;

		SINGLETON_SETUP(Application);

		FuncNoData CreateFunc = nullptr;
		Func1Param UpdateFunc = nullptr;
		FuncNoData DestroyFunc = nullptr;
	};
}

#endif