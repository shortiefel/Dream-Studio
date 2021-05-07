/*
Function definitions for creating and destroying a window using GLFW API
*/

#include "Window.hpp"
#include "pch.hpp"

//static--------------------------------------------------------
GLFWwindow* Window::glfw_window = 0;
Window* Window::s_instance = 0;

//Create instance of window class
Window* Window::Create(const std::string& ttitle, unsigned int twidth, unsigned int theight) {
	return s_instance = new Window(ttitle, twidth, theight);
}

//Destroy glfw window
void Window::Destroy() {
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
	delete s_instance;
}

GLFWwindow* Window::GetGLFWwindow() {
	return glfw_window;
}
//-------------------------------------------------------------------

unsigned int Window::GetWidth() { return w_data.width; }
unsigned int Window::GetHeight() { return w_data.height; }

void Window::OnUpdate() {
	glfwPollEvents();
	glfwSwapBuffers(glfw_window);
}

//constructor to actually create the window with glfw
//constructor is hidden so window is created with Window::create so it would be more readable
Window::Window(const std::string& ttitle, unsigned int twidth, unsigned int theight) {
	//For logging purposes
	w_data.title = ttitle;
	w_data.width = twidth;
	w_data.height = theight;
	
	glfwInit();

	glfw_window = glfwCreateWindow((int)w_data.width, (int)w_data.height, w_data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(glfw_window);
	glfwSetWindowUserPointer(glfw_window, &w_data); //test call back function inside
}