/*
Create a window and other various required manager (e.g Physic / Graphic Manager)
Contains the main application loop and the game loop
*/

#include "Debug Tools/Logging.hpp"
#include "Application.hpp"

#include "Window.hpp"
#include "Event/EventDispatcher.hpp"
#include "Layer/LayerStack.hpp"
#include "Layer/GUILayer.hpp"

//-----testing only----------------------------------
#include "Coordinator/Coordinator.hpp" // testing only
#include "Component/Graphics/TransformComponent.hpp" // testing only
#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"
#include "System/GraphicSystem.hpp"
#include "System/PhysicSystem.hpp"

Entity ent;
std::shared_ptr<GraphicSystem> graphicSystem;
Coordinator gCoordinator; //-----------------------

#include "Math/MathLib.hpp"
#include <iostream>
//---------------------------------------------

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

    if (!LayerStack::Create()) LOG_ERROR("LayerStack creation has failed");

    const char* glsl_version = "#version 450";
    if (!GUILayer::Create(Window::GetGLFWwindow(), glsl_version)) LOG_ERROR("GUILayer creation has failed");

    LayerStack::AddOverlayLayer(GUILayer::Get());

    //-------testing only---------------------------
    gCoordinator.Init();
    gCoordinator.RegisterComponent<Collider>();
    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Renderer2D>();

    graphicSystem = gCoordinator.RegSystem<GraphicSystem>();
    
    Signature signature;
    signature.set(gCoordinator.GetComType<Transform>());
    signature.set(gCoordinator.GetComType<Renderer2D>());
    gCoordinator.setSystemSignature<GraphicSystem>(signature);

    ent = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent,
        Transform{ MathD::Vec3 {0.f, 0.f, 0.f}, MathD::Vec2 {2.f, 1.f}, 1.f });
    
    gCoordinator.AddComponent(
        ent,
        Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });
    //----------------------------------------
}

//Main application loop is done here
void Application::Update() {
   //Temporary loop
    while (app_run_bool) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 1, 1);
        
        //-------Testing only-----------------------------------------
        graphicSystem->Update(0.f); //Testing only
        graphicSystem->Render();
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