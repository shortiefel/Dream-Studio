/* Start Header**********************************************************************************/
/*
@file    Scene.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   	100%
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
#include "Engine/Header/Scene/Prefab.hpp"

#include "Engine/Header/Window.hpp"

#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Event/FixedUpdateEvent.hpp"

//#include "Engine/Header/Layer/LayerStack.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"

#include "Engine/Header/Grid/Grid.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

//#include "Engine/Header/Debug Tools/Profiler.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Graphic/Picking2D.hpp"

#include "Engine/Header/ECS/System/SoundSystem.hpp"
#include "Engine/Header/Management/SoundManager.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine {

    bool previousFocusState = true;

    Scene::Scene(std::string _sceneName, bool _deserializeState) : sceneName{ _sceneName } {
        if (_deserializeState) {
            std::cout << "Recreate scene\n";
            GameSceneSerializer::DeserializeScene(sceneName);
        }
        else {
            GameSceneSerializer::DeserializeScene("temporary");
        }

        DeltaTime::GetInstance().SetTimeScale(1.f);
        CameraSystem::GetInstance().Update(0.f);

        ScriptSystem::GetInstance().UpdateMapData();
        if (GameState::GetInstance().GetPlaying()) {
            ScriptSystem::GetInstance().PlayInit();
        }
        //AI::AISystem::GetInstance().CreateGrid(Math::ivec2{ 20, 10 }, Math::ivec2{ 15, 15 });
        //AI::AISystem::GetInstance().SetRender();

        //if (gameBuild) Play();

        FontSystem::GetInstance().SetFadeToClear();
    }

    Scene::~Scene() {
        ScriptSystem::GetInstance().DestroyChildDomain();

        Game::Grid::GetInstance().DestroyGrid();
    }

    //When user click play to run their game
    bool Scene::Play() {
        if (!ScriptSystem::GetInstance().CompileCS()) {
            return false;
        }
        GameState::GetInstance().SetPlaying(true);

        GameSceneSerializer::SerializeScene("temporary");
        ScriptSystem::GetInstance().UpdateMapData();
        ScriptSystem::GetInstance().PlayInit();


        DeltaTime::GetInstance().SetTimeScale(1.f);

        return true;
    }

    void Scene::Stop(bool deserialize) {
        ScriptSystem::GetInstance().DestroyChildDomain();
        DeltaTime::GetInstance().SetTimeScale(1.f);

        SoundSystem::GetInstance().SoundStopAllSound();
        std::cout << "Stop sound \n";


        CollisionSystem::GetInstance().Stop();
        
        dreamECSGame->ResetECS();
        Game::Grid::GetInstance().DestroyGrid();

        if (deserialize) {
            GameState::GetInstance().SetPlaying(false);
            GameState::GetInstance().SetShouldDraw(false);
            //GameSceneSerializer::DeserializeScene("temporary");
        }

    }

    void Scene::Save() {
        ScriptSystem::GetInstance().CompileCS();
        ScriptSystem::GetInstance().UpdateMapData();

        GameSceneSerializer::SerializeScene(sceneName);
    }

#ifdef _GAME_BUILD
    void Scene::Update(float dt, bool playing, Math::vec2 game_viewportSize) {
#else
    void Scene::Update(float dt, bool playing, Math::vec2) {
#endif
        bool focusState = Window::GetInstance().GetFocusStatus();
        if (!focusState) {
#ifdef _GAME_BUILD
            //Render game when not in focus
            GraphicSystem::GetInstance().Render(dt);
            UISystem::GetInstance().Render();
            FontSystem::GetInstance().Render(dt);
#endif
            if (focusState != previousFocusState) {
                SoundSystem::GetInstance().SoundSetPauseAllSound(true);
                previousFocusState = focusState;
            }
            return;
        }
        if (focusState != previousFocusState) {
            SoundSystem::GetInstance().SoundSetPauseAllSound(false);
            previousFocusState = focusState;
        }

        if (playing) {
            //float timeScale = DeltaTime::GetInstance().GetTimeScale();
            //if (timeScale > 0.f && !Math::EpsilonCheck(timeScale)) {
                ScriptSystem::GetInstance().PlayRunTime();
                //TransformCalculationSystem::GetInstance().ChildUpdate();
                int totalStep = DeltaTime::GetInstance().GetNumberOfSteps();
                for (int step = 0; step < totalStep; step++) {
                    CollisionSystem::GetInstance().Update(dt);
                    PhysicsSystem::GetInstance().Update(DeltaTime::GetInstance().GetFixedDeltaTime());

                    FixedUpdateEvent event;
                    EventDispatcher::SendEvent(event);
                }
            //}
                //auto tem = dreamECSGame->GetUsedConstEntityMap();
                //for (auto [id, ent] : tem) {
                //    std::cout << id << " with parent " << ent.parent << " with child count " << ent.child.size() << "\n";
                //}
                //std::cout << "end\n";
        }


        CameraSystem::GetInstance().Update(dt);


        //GraphicImplementation::FadeScene(3.f, dt, camMatrix);
        
#ifdef _GAME_BUILD
        //Default 2d picking
        Math::vec2 pos = Input::GetMousePosition();
        pos.y = Window::GetInstance().GetWindowSize().y - pos.y;

        Math::mat3 inverseCamMatrix = Math::Inverse(Engine::CameraSystem::GetInstance().GetTransform());

        Engine::Graphic::PickingCheckCollider(Math::vec3{ pos.x, pos.y, 1.f }, game_viewportSize, inverseCamMatrix,
            [&](const Engine::Entity& entity) { Engine::Graphic::RecordMouseOverlap(entity.id, true);  },
            [&](const Engine::Entity& entity) { Engine::Graphic::RecordMouseOverlap(entity.id, false); },
            Math::Inverse(Engine::CameraSystem::GetInstance().GetTransformUI()));

        GraphicSystem::GetInstance().Render(dt);
        UISystem::GetInstance().Render();
        FontSystem::GetInstance().Render(dt);
#else
        //if (Input::IsKeyPressed(Input_KeyCode::F)) {
        //    Window::GetInstance().ToggleFullscreen(); 
        //}
#endif

       
        //SoundSystem::GetInstance().SoundUpdate();


        dreamECSGame->ClearDestroyQueue();

    }

    unsigned int Scene::EntityCount() {
        return dreamECSGame->GetUsedEntitySize();
    }

    std::string Scene::GetName() {
        return sceneName;
    }
}