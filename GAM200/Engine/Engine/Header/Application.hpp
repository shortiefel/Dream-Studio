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

typedef void (*FuncNoData)();
typedef void (*Func1Param)(float);

namespace Engine {
	//Forward declaration
	struct GLFWwindow;
	class Event;
	class WindowCloseEvent;
	class DeltaTime;

	class Application {
	public:
		static bool app_run_bool;

		static void Create();
		/*Main application loop is done here
		defaultRender - whether to use default rendering or not (For scene update)*/
		static void Update(bool defaultRender);
		static void Destroy();

		//Destroy other stuff when application is destroyed
		~Application();

		void OnEvent(Event& event);
		//Set event call back for events
		void SetEventCallBack();

		//Set up function callback for editor function
		static void SetupCallbackFunction(FuncNoData func1, Func1Param func2, FuncNoData func3);
	private:
		static Application* s_app_instance;
		//static GLFWwindow* s_glfw_window;

		static float m_lastframeTime;

		Application() = default;

		static FuncNoData CreateFunc;
		static Func1Param UpdateFunc;
		static FuncNoData DestroyFunc;
	};
}

#endif