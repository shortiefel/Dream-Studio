/* Start Header**********************************************************************************/
/*
@file    Factory.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
This file allow user to create shapes easily with function: CreateSquare and CreateCircle
It also setup all the components and system when a factory is created

*/
/* End Header **********************************************************************************/

#include "Factory/Factory.hpp"

#include "Coordinator/Coordinator.hpp"

//Components
#include "Component/Graphics/TransformComponent.hpp"
#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"

//Systems
#include "System/GraphicSystem.hpp"
#include "System/PhysicSystem.hpp"
//#include "Graphic/Camera.hpp"

#define CREATE_SHAPE(str, type, mv) \
gCoordinator.AddComponent(ent, \
Renderer2D{ GraphicImplementation::models.find(str),  GraphicImplementation::shdrpgms.find("Default") }); \
gCoordinator.AddComponent(ent, \
Collider{ type, mv });

//Entity ent;
//Entity ent2;
//Entity camera;
//std::shared_ptr<GraphicSystem> graphicSystem;
//std::shared_ptr<PhysicSystem> physicSystem;
Coordinator gCoordinator;

void Factory::Create() {
    gCoordinator.Init();
    gCoordinator.RegisterComponent<Collider>();
    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Renderer2D>();

    GraphicSystem::Create(gCoordinator.RegSystem<GraphicSystem>());
    PhysicSystem::Create(gCoordinator.RegSystem<PhysicSystem>());
    
    Signature signature;
    signature.set(gCoordinator.GetComType<Transform>());
    signature.set(gCoordinator.GetComType<Renderer2D>());
    gCoordinator.setSystemSignature<GraphicSystem>(signature);

    signature.reset();
    signature.set(gCoordinator.GetComType<Transform>());
    signature.set(gCoordinator.GetComType<Collider>());
    gCoordinator.setSystemSignature<PhysicSystem>(signature);
}


void Factory::InstantiateSquare(MathD::Vec2 pos, MathD::Vec2 scale, bool isMoveable) {
    Entity ent = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent,
        Transform{ pos, scale, 0.f });

    CREATE_SHAPE("Square", ColliderType::SQUARE, isMoveable)
}


void Factory::InstantiateCircle(MathD::Vec2 pos, MathD::Vec2 scale, bool isMoveable) {
    Entity ent = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent,
        Transform{ pos, scale, 0.f });

    CREATE_SHAPE("Circle", ColliderType::CIRCLE, isMoveable)
}
