/* Start Header**********************************************************************************/
/*!
@file Window.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
\date 26/04/2021
\brief
#include "Engine/Header/Window.hpp"
This file contains the starting point of the application. 


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "pch.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/Singleton/Singleton.hpp"

//
#define ASPECT_RATIO_FIX(size) \
float temY = size.x * Engine::Window::GetInstance().aspectRatio; \
if (temY < size.y) { \
	size.y = temY; \
} \
else { \
	size.x = size.y * (1 / Engine::Window::GetInstance().aspectRatio); \
}

namespace Engine {
	class Event; //Forward declaration
	

	class Window : public Singleton<Window> {
		struct WinData;
	public:
		float aspectRatio = 1.f;

		bool Create(const std::string& ttitle, unsigned int twidth, unsigned int theight);
		void Destroy();

		inline const char* GetGLSLVersion() { return "#version 450"; }
		inline GLFWwindow* GetGLFWwindow() { return glfw_window; }
		inline unsigned int GetWidth() { return w_data.width; }
		inline unsigned int GetHeight() { return w_data.height; }
		inline void* GetNativewindow() { return (void*)glfw_window; }
		inline WinData& GetWindowData() { return w_data; }

		bool GetFocusStatus();
		Math::vec2 GetWindowPosition();
		Math::vec2 GetWindowSize();

		void ToggleFullscreen();

		//void DisplayFPS(float fps);

		void Update();

		//static void SetEventCallBack(const std::function<void(Event&)> callback);



	private:
		struct WinData {
			std::string title;
			unsigned int width, height;

			//std::function<void(Event&)> eventCallBack;
		};

#ifdef _GAME_BUILD
		bool fullScreen = true;
#else
		bool fullScreen = false;
#endif
		

		WinData w_data { "", 0, 0 };
		GLFWwindow* glfw_window = 0;
		GLFWcursor* glfw_custom_cursor = 0;
		//static Window* s_instance;

		SINGLETON_SETUP(Window);
	};
}

#endif