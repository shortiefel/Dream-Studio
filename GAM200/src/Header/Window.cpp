/*
Function definitions for creating and destroying a window using GLFW API
*/

#include "Window.hpp"
#include "pch.hpp"
#include <iostream>

#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"

GLFWwindow* Window::glfw_window = 0;
//Window* Window::s_instance = 0;
Window::WinData Window::w_data = {"untitled", 900, 900};

//Create instance of window class
bool Window::Create(const std::string& ttitle, unsigned int twidth, unsigned int theight) {
	//For logging purposes
	w_data.title = ttitle;
	w_data.width = twidth;
	w_data.height = theight;

	if (!glfwInit()) {
		std::cout << "GLFW initialization has failed \n";
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
		std::cout << "unable to create openGL context \n";
		glfwTerminate();
		return false;
	}
	
	glfwMakeContextCurrent(glfw_window);
	glfwSetWindowUserPointer(glfw_window, &w_data); //test call back function inside

	//Set GLFW callback
	glfwSetWindowSizeCallback(glfw_window, [](GLFWwindow* window, int width, int height) {
		WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		WindowResizeEvent event(width, height);
		data.eventCallBack(event);
		});

	glfwSetWindowCloseCallback(glfw_window, [](GLFWwindow* window) {
		WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.eventCallBack(event);
		});

	glfwSetKeyCallback(glfw_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
		switch (action) {
		case GLFW_PRESS: {
			KeyPressedEvent event(key, false);
			data.eventCallBack(event);
			break;
		}
		case GLFW_RELEASE: {
			KeyReleasedEvent event(key);
			data.eventCallBack(event);
			break;
		}
		case GLFW_REPEAT: {
			KeyPressedEvent event(key, true);
			data.eventCallBack(event);
			break;
		}
		}
		});

	glfwSetMouseButtonCallback(glfw_window, [](GLFWwindow* window, int button, int action, int mods) {
		WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
		switch (action) {
		case GLFW_PRESS: {
			MousePressedEvent event(button);
			data.eventCallBack(event);
			break;
		}
		case GLFW_RELEASE: {
			MouseReleasedEvent event(button);
			data.eventCallBack(event);
			break;
		}
		}
		});

	glfwSetScrollCallback(glfw_window, [](GLFWwindow* window, double xoffset, double yoffset) {
		WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent event((float)xoffset, (float)yoffset);
		data.eventCallBack(event);
		});

	glfwSetCursorPosCallback(glfw_window, [](GLFWwindow* window, double xpos, double ypos) {
		WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
		MouseMoveEvent event((float)xpos, (float)ypos);
		data.eventCallBack(event);
		});
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Unable to initialize GLEW - error: "
			<< glewGetErrorString(err) << " abort program" << std::endl;
		return false;
	}
	if (GLEW_VERSION_4_5) {
		std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
	}
	else {
		std::cerr << "Driver doesn't support OpenGL 4.5 - abort program" << std::endl;
		return false;
	}

	return true;
}

//Destroy glfw window
void Window::Destroy() {
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
	//delete s_instance;
}

GLFWwindow* Window::GetGLFWwindow() {
	return glfw_window;
}


unsigned int Window::GetWidth() { return w_data.width; }
unsigned int Window::GetHeight() { return w_data.height; }

void Window::OnUpdate() {
	glfwPollEvents();
	glfwSwapBuffers(glfw_window);
}

void Window::SetEventCallBack(const std::function<void(Event&)> callback) {
	w_data.eventCallBack = callback;
}
