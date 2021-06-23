/* Start Header**********************************************************************************/
/*
@file    Application.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains the main application loop and the game loop

*/
/* End Header **********************************************************************************/


#include "Debug Tools/Logging.hpp"
#include "Application.hpp"
#include "Window.hpp"

#include "Event/EventDispatcher.hpp"

#include "Factory/Factory.hpp"
#include "GameScene.hpp"

//Static----------------------------------------------

Application* Application::s_app_instance = 0;
//GLFWwindow* Application::s_glfw_window = 0;
bool Application::app_run_bool = true;


void Application::Create() {
    if (s_app_instance) LOG_WARNING("An instance of application already exist!");
    s_app_instance = new Application();
    LOG_INSTANCE("Application created");

	//Create window and instantiate managers
    if (!Window::Create("Dream Engine")) LOG_ERROR("Window creation has failed");
    s_app_instance->SetEventCallBack();

    GameScene::Create();
}

//Main application loop is done here
void Application::Update() {
   //Temporary loop
    while (app_run_bool) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 1, 1);

        GameScene::Update(0.f);

        Window::Update();
    } 
}

void Application::Destroy() {
    delete s_app_instance;
    LOG_INSTANCE("Application destroyed");

}

//------------------------------------------------------

Application::~Application() {
    GameScene::Destroy();
    
}


void Application::OnEvent(Event& event) {

    LOG_EVENT(event);

    //Send event down the layers
    EventDispatcher dispatcher(event);

    switch (event.GetEventType()) {
    case EventType::WINDOW_CLOSE:
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        break;
    /*case EventType::KEY_PRESSED:
        
        break;
    case EventType::KEY_RELEASED:
        
        break;*/
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