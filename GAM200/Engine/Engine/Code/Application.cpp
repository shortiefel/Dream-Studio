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

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Application.hpp"
#include "Engine/Header/Window.hpp"

#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Event/WindowEvent.hpp"

#include "Engine/Header/Management/GameSceneSerializer.hpp"
#include "Engine/Header/Management/Settings.hpp"

#include "Engine/Header/DeltaTime/DeltaTime.hpp"

#include "Engine/Header/EngineCore.hpp"

namespace Engine {
    //Static----------------------------------------------------------------------------------

    Application* Application::s_app_instance = 0;
    bool Application::app_run_bool = true;
    float Application::m_lastframeTime = 0.f;

    FuncNoData Application::CreateFunc = nullptr;
    Func1Param Application::UpdateFunc = nullptr;
    FuncNoData Application::DestroyFunc = nullptr;

    bool OnWindowClose(const WindowCloseEvent& e);
    
    void Application::Create() {
        if (s_app_instance) LOG_WARNING("An instance of application already exist!");
        s_app_instance = new Application();
        LOG_INSTANCE("Application created");

        GameSceneSerializer::DeserializeSetting();
        ////Create window and instantiate managers
        if (!Window::Create("Dream Engine", Settings::windowWidth, Settings::windowHeight)) LOG_ERROR("Window creation has failed");
        //s_app_instance->SetEventCallBack();
        
        WindowCloseEvent::RegisterFunction(&OnWindowClose);

        Engine::EngineCore::Create();
    }
    
    void Application::Update(bool defaultRender) {
        //Called here since Application have 
        //to be created before callback is added
        if (CreateFunc != nullptr) CreateFunc();

        while (app_run_bool) {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            

            float current_time = static_cast<float>(glfwGetTime());
            Engine::DeltaTime::UpdateDeltaTime(current_time, m_lastframeTime);
            m_lastframeTime = current_time;
            Engine::Window::DisplayFPS(DeltaTime::GetFPS());

            Engine::EngineCore::Update(DeltaTime::GetSec(), defaultRender);
            
            if (UpdateFunc != nullptr) UpdateFunc(Engine::DeltaTime::GetSec());
            
            Engine::Window::Update();

            //FrameMark;
        }
    }

    void Application::Destroy() {
        delete s_app_instance;
        LOG_INSTANCE("Application destroyed");

    }
    //------------------------------------------------------------------------------------------

    Application::~Application() {
        if (DestroyFunc != nullptr) DestroyFunc();
        Engine::EngineCore::Destroy();
        Engine::Window::Destroy();
    }


    //void Application::OnEvent(Event& event) {

    //    //LOG_EVENT(event);

    //    //Send event down the layers
    //    //EventDispatcher dispatcher(event);
    //    //event.CallRegisteredFunctions();

    //    //switch (event.GetEventType()) {
    //    //case EventType::WINDOW_CLOSE:
    //    //    //dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
    //    //    //event.CallRegisteredFunctions();
    //    //    break;
    //    //    /*case EventType::KEY_PRESSED:

    //    //        break;
    //    //    case EventType::KEY_RELEASED:

    //    //        break;*/
    //    //        //case EventType::MOUSE_BUTTON_PRESSED:
    //    //        //    LOG_WARNING(event);
    //    //        //    break;
    //    //        //case EventType::MOUSE_BUTTON_RELEASED:
    //    //        //    LOG_DEBUG(event);
    //    //        //    break;
    //    //        //case EventType::MOUSE_MOVE:
    //    //        //    //LOG_ERROR(event);
    //    //        //    break;
    //    //}

    //}
   
    /*void Application::SetEventCallBack() {
        Window::SetEventCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }*/

    void Application::SetupCallbackFunction(FuncNoData func1, Func1Param func2, FuncNoData func3) {
        CreateFunc = func1;
        UpdateFunc = func2;
        DestroyFunc = func3;
    }


    //Local functions-----------------------------------------------------------------
    bool OnWindowClose(const WindowCloseEvent& e) {
        Application::app_run_bool = false;
        return true;
    }
}