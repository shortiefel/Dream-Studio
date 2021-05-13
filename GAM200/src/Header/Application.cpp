/*
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains the main application loop and the game loop
*/

#include "Application.hpp"

//Static----------------------------------------------

Application* Application::s_instance = 0;
//Window* Application::window = 0;
bool Application::app_run_bool = true;

void Application::Create() {
	s_instance = new Application();

	//Create window and instantiate managers
    Window::Create();
    s_instance->SetEventCallBack();
}

//Main application loop is done here
void Application::Run() {

   //Temporary loop
    while (app_run_bool) {
        /*glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);*/
        Window::OnUpdate();

        //temporary break
        if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
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


void Application::OnEvent(Event& event) {
    EventDispatcher dispatcher(event);

    switch (event.GetEventType()) {
    case EventType::WINDOW_CLOSE:
#ifdef _DEBUG
        printf("Window close \n");
#endif
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        break;
    /*case EventType::KEY_PRESSED:
        printf("Key Press \n");
        break;
    case EventType::KEY_RELEASED:
        printf("Key Release \n");
        break;
    case EventType::MOUSE_BUTTON_PRESSED:
        printf("mouse press \n");
        break;
    case EventType::MOUSE_BUTTON_RELEASED:
        printf("mouse Release \n");
        break;*/
    }
    
}

void Application::SetEventCallBack() {
    Window::SetEventCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    app_run_bool = false;
    return true;
}