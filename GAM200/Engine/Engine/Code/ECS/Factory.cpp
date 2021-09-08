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

#include "Engine/Header/ECS/Coordinator.hpp"

#include "Engine/Header/ECS/ECSWrapper.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    //Entity ent;
    //Entity ent2;
    //Entity camera;
    //Coordinator gCoordinator;

    void Factory::Create() {
        Coordinator& gCoordinator = DreamECS::GetCoordinator();
        gCoordinator.Init();
        gCoordinator.RegisterComponent<Camera2D>();
        gCoordinator.RegisterComponent<Transform>();
        gCoordinator.RegisterComponent<Collider>();
        gCoordinator.RegisterComponent<Texture>();
        gCoordinator.RegisterComponent<RigidBody>();
        //gCoordinator.RegisterComponent<CSScript>();
        //gCoordinator.RegisterComponent<CSharpScript>();

        CameraSystem::Create(gCoordinator.RegSystem<CameraSystem>());
        GraphicSystem::Create(gCoordinator.RegSystem<GraphicSystem>());
        CollisionSystem::Create(gCoordinator.RegSystem<CollisionSystem>());
        //ScriptSystem::Create(gCoordinator.RegSystem<ScriptSystem>());

        Signature signature;
        signature.set(gCoordinator.GetComType<Camera2D>());
        gCoordinator.setSystemSignature<CameraSystem>(signature);

        signature.reset();
        signature.set(gCoordinator.GetComType<Transform>());
        signature.set(gCoordinator.GetComType<Texture>());
        gCoordinator.setSystemSignature<GraphicSystem>(signature);

        signature.reset();
        signature.set(gCoordinator.GetComType<Transform>());
        signature.set(gCoordinator.GetComType<Collider>());
        gCoordinator.setSystemSignature<CollisionSystem>(signature);

        //signature.reset();
        //signature.set(gCoordinator.GetComType<CSScript>());
        //gCoordinator.setSystemSignature<ScriptSystem>(signature);
    }

    //Prefix options------------------------------------------------------------------------------

    //Create blank transform

    //Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(glm::vec2 pos, glm::vec2 scale, bool isMoveable) {
        Coordinator& gCoordinator = DreamECS::GetCoordinator();
        Entity ent = gCoordinator.createEntity();
        gCoordinator.AddComponent(
            ent,
            Transform{ pos, scale, 0 });
        gCoordinator.AddComponent(ent,
            Collider{ ColliderType::SQUARE, isMoveable });
    }

    //Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(glm::vec2 pos, glm::vec2 scale, bool isMoveable) {
        Coordinator& gCoordinator = DreamECS::GetCoordinator();
        Entity ent = gCoordinator.createEntity();
        gCoordinator.AddComponent(
            ent,
            Transform{ pos, scale, 0 });
        gCoordinator.AddComponent(ent,
            Collider{ ColliderType::CIRCLE, isMoveable });
    }
    //------------------------------------------------------------------------------

}