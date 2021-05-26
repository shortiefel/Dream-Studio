/*
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains the main application loop and the game loop
*/

#include "Debug Tools/Logging.hpp"
#include "GUIManager.hpp"
#include "Application.hpp"

//Static----------------------------------------------

Application* Application::s_app_instance = 0;
//Window* Application::window = 0;
bool Application::app_run_bool = true;

void Application::Create() {
    s_app_instance = new Application();

	//Create window and instantiate managers
    Window::Create();
    s_app_instance->SetEventCallBack();

    const char* glsl_version = "#version 450";
    GUIManager::Create(Window::GetGLFWwindow(), glsl_version);
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
    delete s_app_instance;
}

//------------------------------------------------------

Application::~Application() {
    //Destroy in reverse order

    //Imgui destroy
    Window::Destroy();
}


void Application::OnEvent(Event& event) {

    LOG_DEBUG(event);

    EventDispatcher dispatcher(event);

    switch (event.GetEventType()) {
    case EventType::WINDOW_CLOSE:
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        break;
    //case EventType::KEY_PRESSED:
    //    LOG_INFO(event);
    //    break;
    //case EventType::KEY_RELEASED:
    //    LOG_ERROR(event);
    //    break;
    //case EventType::MOUSE_BUTTON_PRESSED:
    //    LOG_WARNING(event);
    //    break;
    //case EventType::MOUSE_BUTTON_RELEASED:
    //    LOG_DEBUG(event);
    //    break;
    //case EventType::MOUSE_MOVE:
    //    //LOG_ERROR(event);
    //    break;
    }
    
}

void Application::SetEventCallBack() {
    Window::SetEventCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    app_run_bool = false;
    return true;
}