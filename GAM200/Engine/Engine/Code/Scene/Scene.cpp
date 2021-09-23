/* Start Header**********************************************************************************/
/*
@file    Scene.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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
//#include "Layer/GUILayer.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/ECSWrapper.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    Scene::Scene(std::string fullPath) : fullPathSceneName{ fullPath } {
        GameSceneSerializer::DeserializeScene(fullPathSceneName);

        ScriptSystem::UpdateMapData();
    }

    //When user click play to run their game
    void Scene::Play() {
         if (!ScriptSystem::CompileCS()) {
            std::cout << "Fail to compile \n";
            //Scene::SetPlaying(false);
            return;
        }

        ScriptSystem::UpdateMapData();
        //const auto& entScriptArray = DreamECS::GetComponentArrayData<CSScript>();
        //for (auto& csScript : entScriptArray) {
        //    auto& classScriptInstances = csScript.klassInstance;
        //    const auto& entityId = csScript.GetEntityId();

        //    //Single class and (class and CS public variable)
        //    for (auto& [className, csScriptInstance] : classScriptInstances) {
        //        void* param[] = { (void*)&entityId }; //Change to entity.id after ECS rework
        //        std::cout << "class: " << className << " " << entityId << "\n";
        //    }
        //}
        ScriptSystem::PlayInit();
        //Change to sceneName (might be fullName(path + name) instead)
        GameSceneSerializer::SerializeScene(fullPathSceneName);
    }

    

    void Scene::Stop() {
        CollisionSystem::Stop(); 
        DreamECS::ResetECS();
        //GameSceneSerializer::DeserializeScene(fullPathSceneName);
        //std::cout << "Stopping \n";
    }

    void Scene::Save() {
        if (!ScriptSystem::CompileCS()) {
            std::cout << "Fail to compile \n";
            //Scene::SetPlaying(false);
            return;
        }

        ScriptSystem::UpdateMapData();
        //Change to sceneName (might be fullName(path + name) instead)
        GameSceneSerializer::SerializeScene(fullPathSceneName);
    }

    void Scene::Update(float dt, bool playing, bool defaultRender) {
        //std::cout << DreamECS::GetComponentArraySize<CSScript>() << "   " << DreamECS::GetComponentArraySize<Transform>() << "\n";

        if (playing) {
            ScriptSystem::PlayRunTime();
            CollisionSystem::Update(dt);
            PhysicsSystem::Update(dt);
        }
        if (Input::IsKeyPressed(Input_KeyCode::N))
            DreamECS::DuplicateEntity(0);

        CameraSystem::Update(dt);

        if (defaultRender) {
            //GraphicSystem::Update(dt);
            GraphicSystem::Render();
        }


        DreamECS::ClearDestroyQueue();

        LayerStack::Update();
        LayerStack::Draw();


        if (Input::IsKeyPressed(Input_KeyCode::B))
            std::cout << DreamECS::GetUsedEntitySet().size() << "\n";

        
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