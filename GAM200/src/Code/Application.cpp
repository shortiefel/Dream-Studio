/* Start Header**********************************************************************************/
/*
@file    Application.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains the main application loop and the game loop


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#include "Debug Tools/Logging.hpp"
#include "Application.hpp"
#include "Window.hpp"

#include "Event/EventDispatcher.hpp"
#include "Layer/LayerStack.hpp"
#include "Layer/GUILayer.hpp"

#include "Management/ResourceManager.hpp"

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

////Create window and instantiate managers
    if (!Window::Create("Dream Engine")) LOG_ERROR("Window creation has failed");
    s_app_instance->SetEventCallBack();
    
    if (!LayerStack::Create()) LOG_ERROR("LayerStack creation has failed");

    const char* glsl_version = "#version 450";
    if (!GUILayer::Create(Window::GetGLFWwindow(), glsl_version)) LOG_ERROR("GUILayer creation has failed");

    LayerStack::AddOverlayLayer(GUILayer::Get());

    Factory::Create();

    ResourceManager::Create();

    GameScene::Create();
    GameScene::Play(); //Temporary placement (will be linked to GUI play button)
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
    GameScene::Destroy(); //Destroy currently active game scene
    ResourceManager::Destroy();
    GUILayer::Destroy();
    LayerStack::Destroy();
    Window::Destroy();
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