/* Start Header**********************************************************************************/
/*
@file    Factory.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
This file allow user to create shapes easily with function: CreateSquare and CreateCircle
It also setup all the components and system when a factory is created


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/ECSWrapper.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    //Coordinator gCoordinator;

    void Factory::Create() {
#if NEW_ECS
        DreamECS::Init();
        DreamECS::RegisterComponent<Camera2D>();
        DreamECS::RegisterComponent<Transform>();
        DreamECS::RegisterComponent<Collider>();
        DreamECS::RegisterComponent<Texture>();
        DreamECS::RegisterComponent<RigidBody>();
        //gCoordinator.RegisterComponent<CSScript>();
        //gCoordinator.RegisterComponent<CSharpScript>();

        CameraSystem::Create(DreamECS::RegisterSystem<CameraSystem>());
        GraphicSystem::Create(DreamECS::RegisterSystem<GraphicSystem>());
        CollisionSystem::Create(DreamECS::RegisterSystem<CollisionSystem>());
        ScriptEngine::Create();

#else
        DreamECS::Init();
        DreamECS::RegisterComponent<Camera2D>();
        DreamECS::RegisterComponent<Transform>();
        DreamECS::RegisterComponent<Collider>();
        DreamECS::RegisterComponent<Texture>();
        DreamECS::RegisterComponent<RigidBody>();
        //gCoordinator.RegisterComponent<CSScript>();
        //gCoordinator.RegisterComponent<CSharpScript>();

        CameraSystem::Create(DreamECS::RegisterSystem<CameraSystem>());
        GraphicSystem::Create(DreamECS::RegisterSystem<GraphicSystem>());
        CollisionSystem::Create(DreamECS::RegisterSystem<CollisionSystem>());
        //ScriptSystem::Create(gCoordinator.RegSystem<ScriptSystem>());

        Signature signature;
        signature.set(DreamECS::GetComponentType<Transform>());
        signature.set(DreamECS::GetComponentType<Texture>());
        DreamECS::setSystemSignature<GraphicSystem>(signature);

        signature.reset();
        signature.set(DreamECS::GetComponentType<Transform>());
        signature.set(DreamECS::GetComponentType<Camera2D>());
        DreamECS::setSystemSignature<CameraSystem>(signature);


        signature.reset();
        signature.set(DreamECS::GetComponentType<Transform>());
        signature.set(DreamECS::GetComponentType<Collider>());
        DreamECS::setSystemSignature<CollisionSystem>(signature);

        //signature.reset();
        //signature.set(gCoordinator.GetComType<CSScript>());
        //gCoordinator.setSystemSignature<ScriptSystem>(signature);
#endif
    }

    void Factory::Destroy() {
        ScriptEngine::Destroy();
    }

    //Prefix options------------------------------------------------------------------------------

    //Create blank transform

    //Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(Math::vec2 pos, Math::vec2 scale, bool isMoveable) {
        printf("%s\n", "Doesnt work");
        /*Entity ent = DreamECS::CreateEntity();
        DreamECS::AddComponent(
            ent,
            Transform{ ent, pos, scale, 0 });
        DreamECS::AddComponent(ent,
            Collider{ ent, ColliderType::SQUARE, isMoveable });*/
    }

    //Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(Math::vec2 pos, Math::vec2 scale, bool isMoveable) {
        printf("%s\n", "Doesnt work");
        /*Entity ent = DreamECS::CreateEntity();
        DreamECS::AddComponent(
            ent,
            Transform{ ent, pos, scale, 0 });
        DreamECS::AddComponent(ent,
            Collider{ ent, ColliderType::CIRCLE, isMoveable });*/
    }
    //------------------------------------------------------------------------------

}