/* Start Header**********************************************************************************/
/*
@file    Scene.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/06/2021
\brief
An application of the dream engine can have multiple game scene to be used
When created and deleted, it should rebuild the systems and get the correct information from textfiles


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Scene/Scene.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"
//#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

//#include "Engine/Header/Debug Tools/Profiler.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    Scene::Scene(std::string fullPath) : fullPathSceneName{ fullPath } {
        GameSceneSerializer::DeserializeScene(fullPathSceneName);
        std::cout << "Deserialize scene \n";
        ScriptSystem::GetInstance().UpdateMapData();
    }

    //When user click play to run their game
    bool Scene::Play() {
         if (!ScriptSystem::GetInstance().CompileCS()) {
            std::cout << "Fail to compile \n";
            //GameState::GetInstance().SetPlaying(false);
            //Scene::SetPlaying(false);
            return false;
        }

        ScriptSystem::GetInstance().UpdateMapData();
        //const auto& entScriptArray = DreamECS::GetComponentArrayData<CSScript>();
        //for (auto& csScript : entScriptArray) {
        //    auto& classScriptInstances = csScript.klassInstance;
        //    const auto& entityId = csScript.GetEntity();

        //    //Single class and (class and CS public variable)
        //    for (auto& [className, csScriptInstance] : classScriptInstances) {
        //        void* param[] = { (void*)&entityId }; //Change to entity.id after ECS rework
        //        std::cout << "class: " << className << " " << entityId << "\n";
        //    }
        //}
        ScriptSystem::GetInstance().PlayInit();
        //Change to sceneName (might be fullName(path + name) instead)
        GameSceneSerializer::SerializeScene(fullPathSceneName);

        return true;
    }

    void Scene::Stop() {
        CollisionSystem::GetInstance().Stop();
        DreamECS::GetInstance().ResetECS();
        //GameSceneSerializer::DeserializeScene(fullPathSceneName);
    }

    void Scene::Save() {
        if (!ScriptSystem::GetInstance().CompileCS()) {
            std::cout << "Fail to compile \n";
            //Scene::SetPlaying(false);
            return;
        }

        ScriptSystem::GetInstance().UpdateMapData();
        //Change to sceneName (might be fullName(path + name) instead)
        GameSceneSerializer::SerializeScene(fullPathSceneName);
    }

    void Scene::Update(float dt, bool playing) {
        //std::cout << DreamECS::GetComponentArraySize<CSScript>() << "   " << DreamECS::GetComponentArraySize<Transform>() << "\n";
        //PROFILER_START("Scene Update");

        if (playing) {
            ScriptSystem::GetInstance().PlayRunTime();
            CollisionSystem::GetInstance().Update(dt);
            PhysicsSystem::GetInstance().Update(DeltaTime::GetInstance().GetFixedDeltaTime());
        }

        CameraSystem::GetInstance().Update(dt);
        GraphicSystem::GetInstance().Render();
        UISystem::GetInstance().Render();

        DreamECS::GetInstance().ClearDestroyQueue();

        //LayerStack::Update();
        //LayerStack::Draw();
    }

    unsigned int Scene::EntityCount() {
        return DreamECS::GetInstance().GetUsedEntitySize();
    }

    //bool Scene::SceneSave() {
    //    //if (!ScriptSystem::CompileCS()) {
    //    //    std::cout << "Fail to compile \n";
    //    //    //Scene::SetPlaying(false);
    //    //    return false;
    //    //}

    //    //ScriptSystem::UpdateMapData();
    //    ////Change to sceneName (might be fullName(path + name) instead)
    //    //GameSceneSerializer::SerializeScene(fullPathSceneName);

    //    return true;
    //}
}