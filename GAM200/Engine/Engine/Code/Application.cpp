/* Start Header**********************************************************************************/
/*
@file    Application.cpp
@author  Chia Yi Da		chiayida98@gmail.com
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

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/Management/Settings.hpp"

#include "Engine/Header/DeltaTime/DeltaTime.hpp"

#include "Engine/Header/EngineCore.hpp"

#include "Engine/Header/Time/Timer.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"
#include "Engine/Header/Management/GameState.hpp"
#include <iostream>

namespace Engine 
{
    bool OnWindowClose(const WindowCloseEvent& e);

    void Application::Create() 
    {
        if (s_app_instance) LOG_WARNING("An instance of application already exist!");
        s_app_instance = new Application();
        LOG_INSTANCE("Application created");

        GameSceneSerializer::DeserializeSetting();

        //Create window and instantiate managers
        if (!Window::GetInstance().Create("Dream Engine", Settings::windowWidth, Settings::windowHeight)) 
            LOG_ERROR("Window creation has failed");

        WindowCloseEvent::RegisterFunction(&OnWindowClose);
        Engine::EngineCore::GetInstance().Create();
    }

    void Application::Update(bool defaultRender) {
        //Called here since Application have 
        //to be created before callback is added
        if (CreateFunc != nullptr) 
        { 
            CreateFunc(); 
        }

        while (app_run_bool) {
            Timer timer("Application", std::move([&](ProfilerResult&& result) {
                float sec = static_cast<float>(result.time) * 0.001f;
                GameState::GetInstance().SetDeltaTime(sec);

                static float wait_time = 0;
                wait_time += sec;
                if (wait_time > FPS_Interval) {
                    GameState::GetInstance().SetFPS(1/sec);
                    wait_time = 0;
                }

                //Engine::Profiler::GetInstance().profilerResult.emplace_back(std::move(result));
                }));

            {
                //PROFILER_START("Main 1");
                Engine::EngineCore::GetInstance().Update(GameState::GetInstance().GetDeltaTime(), defaultRender);
            }

            if (UpdateFunc != nullptr) {
                //PROFILER_START("Main 2");
                UpdateFunc(GameState::GetInstance().GetDeltaTime());
            }

            {
                //PROFILER_START("Main 3");
                Engine::Window::GetInstance().Update();
            }

            Profiler::GetInstance().DisplayProfilerResult();
        }
    }

    void Application::Destroy() 
    {
        if (DestroyFunc != nullptr) DestroyFunc();
        Engine::EngineCore::GetInstance().Destroy();
        Engine::Window::GetInstance().Destroy();

        delete s_app_instance;
        LOG_INSTANCE("Application destroyed");

    }

    void Application::SetupCallbackFunction(FuncNoData func1, Func1Param func2, FuncNoData func3) 
    {
        CreateFunc = func1;
        UpdateFunc = func2;
        DestroyFunc = func3;
    }

    //Local functions-----------------------------------------------------------------
    bool OnWindowClose(const WindowCloseEvent& e) 
    {
        Application::GetInstance().SetAppRun(false);
        return true;
    }
}


//------------------------------------------------------------------------------------------


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