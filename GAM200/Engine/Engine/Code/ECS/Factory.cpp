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

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    //Entity ent;
    //Entity ent2;
    //Entity camera;
    //std::shared_ptr<GraphicSystem> graphicSystem;
    //std::shared_ptr<PhysicSystem> physicSystem;
    Coordinator gCoordinator;

    void Factory::Create() {
        gCoordinator.Init();
        gCoordinator.RegisterComponent<Camera2D>();
        gCoordinator.RegisterComponent<Transform>();
        gCoordinator.RegisterComponent<Collider>();
        gCoordinator.RegisterComponent<Custom_Script>();
        gCoordinator.RegisterComponent<Texture>();
        //gCoordinator.RegisterComponent<CSharpScript>();

        CameraSystem::Create(gCoordinator.RegSystem<CameraSystem>());
        GraphicSystem::Create(gCoordinator.RegSystem<GraphicSystem>());
        PhysicSystem::Create(gCoordinator.RegSystem<PhysicSystem>());
        ScriptSystem::Create(gCoordinator.RegSystem<ScriptSystem>());

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
        gCoordinator.setSystemSignature<PhysicSystem>(signature);

        signature.reset();
        signature.set(gCoordinator.GetComType<Custom_Script>());
        gCoordinator.setSystemSignature<ScriptSystem>(signature);
    }

    //Prefix options------------------------------------------------------------------------------

    //Create blank transform

    //Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(MathD::Vec2 pos, MathD::Vec2 scale, bool isMoveable) {
        Entity ent = gCoordinator.createEntity();
        gCoordinator.AddComponent(
            ent,
            Transform{ pos, scale, "Square" });
        gCoordinator.AddComponent(ent,
            Collider{ ColliderType::SQUARE, isMoveable });
    }

    //Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(MathD::Vec2 pos, MathD::Vec2 scale, bool isMoveable) {
        Entity ent = gCoordinator.createEntity();
        gCoordinator.AddComponent(
            ent,
            Transform{ pos, scale, "Circle" });
        gCoordinator.AddComponent(ent,
            Collider{ ColliderType::CIRCLE, isMoveable });
    }
    //------------------------------------------------------------------------------

}