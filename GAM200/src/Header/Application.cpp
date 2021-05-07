/*
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains the main application loop and the game loop
*/

#include "Application.hpp"

//Static----------------------------------------------

Application* Application::s_instance = 0;
Window* Application::window = 0;

void Application::Create() {
	s_instance = new Application();

	//Create window and instantiate managers
    window = Window::Create();
}

//Main application loop is done here
void Application::Run() {
   //Temporary loop
    while (!glfwWindowShouldClose(window->GetGLFWwindow())) {
        window->OnUpdate();

        //temporary break
        if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
            break;
        }
    } 
}

void Application::Destroy() {
    delete s_instance;
}

//------------------------------------------------------

Application::~Application() {
    //Destroy in reverse order
    Window::Destroy();
}