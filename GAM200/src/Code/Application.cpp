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
#include "Layer/LayerStack.hpp"
#include "Layer/GUILayer.hpp"

#include "Factory/Factory.hpp"
////-----testing only----------------------------------
#include "Coordinator/Coordinator.hpp" // testing only
#include "Component/Graphics/TransformComponent.hpp" // testing only
#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"

//
//Entity ent;
//Entity ent2;
//Entity ent3;
//Entity ent4, ent5;
Entity camera;
//std::shared_ptr<GraphicSystem> graphicSystem;
//std::shared_ptr<PhysicSystem> physicSystem;
extern Coordinator gCoordinator; //-----------------------
//
//#include "Math/MathLib.hpp"
//#include <iostream>
////---------------------------------------------
bool up = false, down = false, left = false, right = false;

//Static----------------------------------------------

#include "Graphic/Camera.hpp"

#include "System/GraphicSystem.hpp"
#include "System/PhysicSystem.hpp"

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

    if (!LayerStack::Create()) LOG_ERROR("LayerStack creation has failed");

    const char* glsl_version = "#version 450";
    if (!GUILayer::Create(Window::GetGLFWwindow(), glsl_version)) LOG_ERROR("GUILayer creation has failed");

    LayerStack::AddOverlayLayer(GUILayer::Get());

    Factory::SetUp();

    camera = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        camera,
        Transform{ MathD::Vec2 {0.f, 0.f}, MathD::Vec2 {0.f, 0.f}, 0.f });

    GraphicImplementation::camera2d.init(Window::GetGLFWwindow(), &gCoordinator.GetCom<Transform>(camera));

    //ent = gCoordinator.createEntity();
    //gCoordinator.AddComponent(
    //    ent,
    //    Transform{ MathD::Vec2 {-150.f, 0.f}, MathD::Vec2 {60.f, 60.f}, 0.f });
    //
    //gCoordinator.AddComponent(
    //    ent,
    //    Renderer2D{ GraphicImplementation::models.find("Circle"),  GraphicImplementation::shdrpgms.find("Default") });

    //gCoordinator.AddComponent(
    //    ent,
    //    Collider{ ColliderType::CIRCLE, true });

    //////----------------------------------------

    //ent2 = gCoordinator.createEntity();
    //gCoordinator.AddComponent(
    //    ent2,
    //    Transform{ MathD::Vec2 {100.f, 0.f}, MathD::Vec2 {50.f, 50.f}, 0.f });

    //gCoordinator.AddComponent(
    //    ent2,
    //    Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });

    //gCoordinator.AddComponent(
    //    ent2,
    //    Collider{ ColliderType::SQUARE, true });
    //-------------------------------------------------------------------------------------------------------------------

    /*ent3 = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent3,
        Transform{ MathD::Vec2 {100.f, 0.f}, MathD::Vec2 {50.f, 50.f}, 0.f });

    gCoordinator.AddComponent(
        ent3,
        Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });

    gCoordinator.AddComponent(
        ent3,
        Collider{ ColliderType::SQUARE, true });*/

    //ent4 = gCoordinator.createEntity();

    //gCoordinator.AddComponent(
    //    ent4,
    //    Transform{ MathD::Vec2 {-100.f, 200.f}, MathD::Vec2 {20.f, 20.f}, 0.f });
    //gCoordinator.AddComponent(
    //    ent4,
    //    Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });
    //gCoordinator.AddComponent(
    //    ent4,
    //    Collider{ ColliderType::SQUARE, false });

    //ent5 = gCoordinator.createEntity();

    //gCoordinator.AddComponent(
    //    ent5,
    //    Transform{ MathD::Vec2 {300.f, 100.f}, MathD::Vec2 {50.f, 50.f}, 0.f });
    //gCoordinator.AddComponent(
    //    ent5,
    //    Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });
    //gCoordinator.AddComponent(
    //    ent5,
    //    Collider{ ColliderType::SQUARE, false });

    
}

//Main application loop is done here
void Application::Update() {
   //Temporary loop
    while (app_run_bool) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 1, 1);
        
        ////-------Testing only-----------------------------------------
        /*if (up) {
            auto& transform1 = gCoordinator.GetCom<Transform>(ent);
            transform1.pos.y += 2.f;
        }
        if (down) {
            auto& transform1 = gCoordinator.GetCom<Transform>(ent);
            transform1.pos.y -= 2.f;
        }
        if (left) {
            auto& transform1 = gCoordinator.GetCom<Transform>(ent);
            transform1.pos.x -= 2.f;
        }
        if (right) {
            auto& transform1 = gCoordinator.GetCom<Transform>(ent);
            transform1.pos.x += 2.f;
        }*/
        PhysicSystem::Update(0.f); //Testing only

        GraphicImplementation::camera2d.update(Window::GetGLFWwindow());
        GraphicSystem::Update(0.f); //Testing only
        GraphicSystem::Render();

        //---------------------------------------------------
        LayerStack::Update();
        LayerStack::Draw();

        Window::Update();
    } 
}

void Application::Destroy() {
    delete s_app_instance;
    LOG_INSTANCE("Application destroyed");

}

//------------------------------------------------------

Application::~Application() {
    //Destroy in reverse order
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
    case EventType::KEY_PRESSED:
        
        break;
    case EventType::KEY_RELEASED:
        
        break;
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