/* Start Header**********************************************************************************/
/*
@file    Application.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/06/2021
\brief
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains declaration of application


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

namespace Engine
{
	//Forward declaration
	struct GLFWwindow;
	class Event;
	class WindowCloseEvent;
	class DeltaTime;

	class Application : public Singleton<Application>
	{
	public:
		void Create();

		/*
		Main application loop is done here
		defaultRender - whether to use default rendering or not (For scene update)
		*/
		void Update();
		void Destroy();

		inline void SetAppRun(bool _bool) { app_run_bool = _bool; }
		//Set event call back for events
		//void OnEvent(Event& event);
		//void SetEventCallBack();

		//Set up function callback for editor function
		void SetupCallbackFunction(FuncNoData func1, Func1Param func2, FuncNoData func3);

	private:
		Application* s_app_instance = 0;
		//static GLFWwindow* s_glfw_window;

		bool app_run_bool = true;
		float m_lastframeTime = 0.f;

		FuncNoData CreateFunc = nullptr;
		Func1Param UpdateFunc = nullptr;
		FuncNoData DestroyFunc = nullptr;

		SINGLETON_SETUP(Application);
	};
}

#endif