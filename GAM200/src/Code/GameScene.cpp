/* Start Header**********************************************************************************/
/*
@file    GameScene.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
An application of the dream engine can have multiple game scene to be used
When created and deleted, it should rebuild the systems and get the correct information from textfiles

*/
/* End Header **********************************************************************************/

#include "GameScene.hpp"
#include "Debug Tools/Logging.hpp"

#include "Window.hpp"
#include "Event/EventDispatcher.hpp"
#include "Layer/LayerStack.hpp"
#include "Layer/GUILayer.hpp"

#include "Factory/Factory.hpp"

#include "Coordinator/Coordinator.hpp"
#include "Component/Graphics/TransformComponent.hpp"
#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"

#include "Graphic/Camera.hpp"

#include "System/GraphicSystem.hpp"
#include "System/PhysicSystem.hpp"

extern Coordinator gCoordinator;
Entity camera;

//Entity player;

bool up = false, down = false, left = false, right = false;

void GameScene::Create() {
    //Serialization
    //Read from text file all information

    //Reset all system

    if (!LayerStack::Create()) LOG_ERROR("LayerStack creation has failed");

    const char* glsl_version = "#version 450";
    if (!GUILayer::Create(Window::GetGLFWwindow(), glsl_version)) LOG_ERROR("GUILayer creation has failed");

    LayerStack::AddOverlayLayer(GUILayer::Get());

    Factory::Create();

    camera = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        camera,
        Transform{ MathD::Vec2 {0.f, 0.f}, MathD::Vec2 {0.f, 0.f}, 0.f });

    GraphicImplementation::camera2d.init(Window::GetGLFWwindow(), &gCoordinator.GetCom<Transform>(camera));

    /*player = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        player,
        Transform{ MathD::Vec2 {-150.f, 0.f}, MathD::Vec2 {60.f, 60.f}, 0.f });

    gCoordinator.AddComponent(
        player,
        Renderer2D{ GraphicImplementation::models.find("Circle"),  GraphicImplementation::shdrpgms.find("Default") });

    gCoordinator.AddComponent(
        player,
        Collider{ ColliderType::CIRCLE, true });

    Factory::InstantiateCircle();
    Factory::InstantiateSquare();*/
}

void GameScene::Update(float dt) {

    ////-------Testing only-----------------------------------------
    /*if (up) {
        auto& transform1 = gCoordinator.GetCom<Transform>(player);
        transform1.pos.y += 2.f;
    }
    if (down) {
        auto& transform1 = gCoordinator.GetCom<Transform>(player);
        transform1.pos.y -= 2.f;
    }
    if (left) {
        auto& transform1 = gCoordinator.GetCom<Transform>(player);
        transform1.pos.x -= 2.f;
    }
    if (right) {
        auto& transform1 = gCoordinator.GetCom<Transform>(player);
        transform1.pos.x += 2.f;
    }*/
    //-------Testing only-----------------------------------------

    PhysicSystem::Update(dt); //Testing only

    GraphicImplementation::camera2d.update(Window::GetGLFWwindow());
    GraphicSystem::Update(dt); //Testing only
    GraphicSystem::Render();

    LayerStack::Update();
    LayerStack::Draw();
}

void GameScene::Destroy() {
    //Destroy in reverse order
    GUILayer::Destroy();
    LayerStack::Destroy();
    Window::Destroy();
}