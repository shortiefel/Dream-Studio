/* Start Header**********************************************************************************/
/*!
\file Window.hpp
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

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "pch.hpp"
#include <glm/glm.hpp>

//
#define ASPECT_RATIO_FIX(size) \
float temY = size.x * Engine::Window::aspectRatio; \
if (temY < size.y) { \
	size.y = temY; \
} \
else { \
	size.x = size.y * (1 / Engine::Window::aspectRatio); \
}

namespace Engine {
	class Event; //Forward declaration

	class Window {
	public:
		static float aspectRatio;

		static bool Create(const std::string& ttitle = "untitled", unsigned int twidth = 1280, unsigned int theight = 720);
		static void Destroy();

		static inline const char* GetGLSLVersion() { return "#version 450"; }
		static inline GLFWwindow* GetGLFWwindow() { return glfw_window; }
		static inline unsigned int GetWidth() { return w_data.width; }
		static inline unsigned int GetHeight() { return w_data.height; }
		static inline void* GetNativewindow() { return (void*)glfw_window; }

		static glm::vec2 GetWindowPosition();

		static void DisplayFPS(float fps);

		static void Update();

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

		static WinData w_data;
		static GLFWwindow* glfw_window;
		//static Window* s_instance;
	};
}

#endif