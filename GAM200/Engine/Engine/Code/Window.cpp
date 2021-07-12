/* Start Header**********************************************************************************/
/*
@file    Window.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
Function definitions for creating and destroying a window using GLFW API


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Window.hpp"

#include "Engine/Header/pch.hpp"

#include "Engine/Header/Event/KeyEvent.hpp"
#include "Engine/Header/Event/MouseEvent.hpp"
#include "Engine/Header/Event/WindowEvent.hpp"


namespace Engine {
	GLFWwindow* Window::glfw_window = 0;
	//Window* Window::s_instance = 0;

	//Changed on Create
	Window::WinData Window::w_data = { "", 0, 0 };

	void Window::Update() {

		glfwPollEvents();
		glfwSwapBuffers(glfw_window);
	}

	//Destroy glfw window
	void Window::Destroy() {
		glfwDestroyWindow(glfw_window);
		glfwTerminate();

		LOG_INSTANCE("Window destroyed");
	}

	void Window::DisplayFPS(int fps) {
		std::string stitle = { w_data.title };
		stitle += " | FPS: ";
		char buffer[5];
		sprintf_s(buffer, "%d", fps);
		stitle += buffer;

		glfwSetWindowTitle(glfw_window, stitle.c_str());
	}

	//Create instance of window class
	bool Window::Create(const std::string& ttitle, unsigned int twidth, unsigned int theight) {

		LOG_INSTANCE("Window Created");

		//For logging purposes
		w_data.title = ttitle;
		w_data.width = twidth;
		w_data.height = theight;

		if (!glfwInit()) {
			LOG_ERROR("GLFW initialization has failed");
			return false;
		}

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		//glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
		//glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static

		glfw_window = glfwCreateWindow((int)w_data.width, (int)w_data.height, w_data.title.c_str(), nullptr, nullptr);
		if (!glfw_window) {
			LOG_ERROR("unable to create openGL context");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(glfw_window);

		//Set GLFW callback
		glfwSetWindowSizeCallback(glfw_window, WindowSizeCallback);
		glfwSetWindowCloseCallback(glfw_window, WindowCloseCallback);
		glfwSetKeyCallback(glfw_window, KeyCallback);
		glfwSetMouseButtonCallback(glfw_window, MouseButtonCallback);
		glfwSetScrollCallback(glfw_window, ScrollCallback);
		glfwSetCursorPosCallback(glfw_window, CursorCallBack);

		GLenum err = glewInit();
		if (GLEW_OK != err) {
			LOG_ERROR("Unable to initialize GLEW - error: ", glewGetErrorString(err), " abort program");
			return false;
		}
		if (GLEW_VERSION_4_5) {
			LOG_INFO("Using glew version: ", glewGetString(GLEW_VERSION));
			LOG_INFO("Driver supports OpenGL 4.5");
		}
		else {
			LOG_ERROR("Driver doesn't support OpenGL 4.5 - abort program");
			return false;
		}

		return true;
	}






	//Event call back order
	//glfw detects event -> call user-defined specific type of event call back function (listed below SetEventCallBack function) 
	//-> within those function the w_data.eventCallBack is called to pass the event details to application

	//Set event call back to application
	void Window::SetEventCallBack(const std::function<void(Event&)> callback) {
		w_data.eventCallBack = callback;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//Listed below are function callbacks which are called on glfw side when its instruction/command is executed
	//E.g function WindowSizeCallback is called when glfw detects a window resize event

	//Within the function another function callback to application is done to pass the event details to application
	//E.g WindowSizeCallback: w_data.eventCallBack(event)

	//Note: functions here follows the parameter order and type specified by the glfw API
	/*
	List of glfw set call back used:
	glfwSetWindowSizeCallback
	glfwSetWindowCloseCallback
	glfwSetKeyCallback
	glfwSetMouseButtonCallback
	glfwSetScrollCallback
	glfwSetCursorPosCallback
	*/

	void Window::WindowSizeCallback(GLFWwindow* window, int width, int height) {
		w_data.width = width;
		w_data.height = height;

		WindowResizeEvent event(width, height);
		w_data.eventCallBack(event);
	}

	void Window::WindowCloseCallback(GLFWwindow* window) {
		WindowCloseEvent event;
		w_data.eventCallBack(event);
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS: {
			KeyPressedEvent event(key, false);
			w_data.eventCallBack(event);
			break;
		}
		case GLFW_RELEASE: {
			KeyReleasedEvent event(key);
			w_data.eventCallBack(event);
			break;
		}
		case GLFW_REPEAT: {
			KeyPressedEvent event(key, true);
			w_data.eventCallBack(event);
			break;
		}
		}
	}

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		switch (action) {
		case GLFW_PRESS: {
			MousePressedEvent event(button);
			w_data.eventCallBack(event);
			break;
		}
		case GLFW_RELEASE: {
			MouseReleasedEvent event(button);
			w_data.eventCallBack(event);
			break;
		}
		}
	}

	void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		MouseScrolledEvent event((float)xoffset, (float)yoffset);
		w_data.eventCallBack(event);
	}

	void Window::CursorCallBack(GLFWwindow* window, double xpos, double ypos) {
		MouseMoveEvent event((float)xpos, (float)ypos);
		w_data.eventCallBack(event);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}