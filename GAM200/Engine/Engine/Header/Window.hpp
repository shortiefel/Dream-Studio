/* Start Header**********************************************************************************/
/*!
@file Window.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
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
	public:
		float aspectRatio = 1.f;

		bool Create(const std::string& ttitle = "untitled", unsigned int twidth = 1280, unsigned int theight = 720);
		void Destroy();

		inline const char* GetGLSLVersion() { return "#version 450"; }
		inline GLFWwindow* GetGLFWwindow() { return glfw_window; }
		inline unsigned int GetWidth() { return w_data.width; }
		inline unsigned int GetHeight() { return w_data.height; }
		inline void* GetNativewindow() { return (void*)glfw_window; }

		Math::vec2 GetWindowPosition();

		void DisplayFPS(float fps);

		void Update();

		//static void SetEventCallBack(const std::function<void(Event&)> callback);


		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void CursorCallBack(GLFWwindow* window, double xpos, double ypos);


	private:
		struct WinData {
			std::string title;
			unsigned int width, height;

			//std::function<void(Event&)> eventCallBack;
		};

		WinData w_data { "", 0, 0 };
		GLFWwindow* glfw_window = 0;
		//static Window* s_instance;

		Window() {}
		~Window() {}

		friend class Singleton<Window>;
	};
}

#endif