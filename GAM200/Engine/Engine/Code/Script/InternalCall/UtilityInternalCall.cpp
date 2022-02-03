/* Start Header**********************************************************************************/
/*
@file    UtilityInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/UtilityInternalCall.hpp"
This file contain the definition of UtilityInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/Script/InternalCall/UtilityInternalCall.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Random/Random.hpp"
#include "Engine/Header/Input/Input.hpp" //Input key/mouse code

#include "Engine/Header/Script/Scripting.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

#include "Engine/Header/ECS/System/FontSystem.hpp"

#include "Engine/Header/Window.hpp"

#include "Engine/Header/Physics/Collision.hpp"
#include "Engine/Header/ECS/System/CollisionSystem.hpp" //For raycast
#include "Engine/Header/Physics/Ray.hpp" //For raycast

#include "Engine/Header/Serialize/SSerializer.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp" //Serialize Prefab
#include "Engine/Header/Scene/SceneManager.hpp"

#include "Engine/Header/Event/WindowEvent.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"


#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include <mono/jit/jit.h>



namespace Engine {
	namespace InternalCall {
		void(*ConsoleFuncPtr)(std::string) = [](std::string) {};

		void SetConsoleWriteInternalFunc(void(*fp)(std::string)) {
			ConsoleFuncPtr = fp;
		}

		Math::vec2(*GetMousePositionFuncPtr)() = []() {
			//window y size - y position (flip y value)
			Math::vec2 pos = Input::GetMousePosition();
			pos.y = Window::GetInstance().GetWindowSize().y - pos.y;
			return pos;
		};

		void SetGetMousePositionInternalFunc(Math::vec2(*fp)()) {
			GetMousePositionFuncPtr = fp;
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Input
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		bool GetKey_Engine(Input_KeyCode key);
		bool GetKeyDown_Engine(Input_KeyCode key);

		bool GetMouse_Engine(Input_MouseCode button);
		bool GetMouseDown_Engine(Input_MouseCode button);
		bool GetMouseUp_Engine(Input_MouseCode button);

		void GetMousePosition_Engine(Math::vec2* outPosition);



		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Save highscore
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ScoreSetUp();
		void SetHighscore_Engine(int value, MonoString* str);
		void GetHighscore_Engine(int* value, MonoString* str);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Prefab
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Instantiate_Prefab_Transform_Engine(MonoString* prefabName, int entityId, unsigned int* newId);
		void Instantiate_Prefab_Position_Engine(MonoString* prefabName, Math::vec3 pos, int layer, unsigned int* newId);
		//void Instantiate_Prefab_Engine(MonoString* prefabName, Math::vec2 position, float angle);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Deltatime
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void GetDeltaTime_Engine(float* dt, bool _timeScale);
		void GetFixedDeltaTime_Engine(float* dt);
		void SetTimeScale_Engine(float timeScale);
		void GetTimeScale_Engine(float* timeScale);
		void WaitForSeconds_Engine(float timer);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Scene
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void LoadScene_Engine(MonoString* sceneName);
		void SetDrawMode_Engine(bool state);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Console Write
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ConsoleWrite_Engine(MonoString* message);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Random
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Random_Range_Engine(int num1, int num2, int* answer);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Physics
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		bool RayCast_Engine(Math::vec3 pos, Math::vec2 dir, int ignoreTarget, float distance, unsigned int* entity_id, float* hitDistance, Math::vec2* hitPoint);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Application
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Quit_Engine();

		/*-----------------------------------------------------
		Called in ScriptingInternalCall
		-----------------------------------------------------*/
		void RegisterUtilityInternalCall() {
			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Input
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Input::GetKey_Engine", GetKey_Engine);
			mono_add_internal_call("Input::GetKeyDown_Engine", GetKeyDown_Engine);

			mono_add_internal_call("Input::GetMouse_Engine", GetMouse_Engine);
			mono_add_internal_call("Input::GetMouseDown_Engine", GetMouseDown_Engine);
			mono_add_internal_call("Input::GetMouseUp_Engine", GetMouseUp_Engine);
			mono_add_internal_call("Input::GetMousePosition_Engine", GetMousePosition_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Save highscore
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("MonoBehaviour::SetHighscore_Engine", SetHighscore_Engine);
			mono_add_internal_call("MonoBehaviour::GetHighscore_Engine", GetHighscore_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Prefab
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("MonoBehaviour::Instantiate_Prefab_Transform_Engine", Instantiate_Prefab_Transform_Engine);
			mono_add_internal_call("MonoBehaviour::Instantiate_Prefab_Position_Engine", Instantiate_Prefab_Position_Engine);
			//mono_add_internal_call("MonoBehaviour::Instantiate_Prefab_Engine", Instantiate_Prefab_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Deltatime
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Time::GetDeltaTime_Engine", GetDeltaTime_Engine);
			mono_add_internal_call("Time::GetFixedDeltaTime_Engine", GetFixedDeltaTime_Engine);
			mono_add_internal_call("Time::SetTimeScale_Engine", SetTimeScale_Engine);
			mono_add_internal_call("Time::GetTimeScale_Engine", GetTimeScale_Engine);
			mono_add_internal_call("Time::WaitForSeconds_Engine", WaitForSeconds_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Scene
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("SceneManager::LoadScene_Engine", LoadScene_Engine);
			mono_add_internal_call("SceneManager::SetDrawMode_Engine", SetDrawMode_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Console Write
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Debug::ConsoleWrite_Engine", ConsoleWrite_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Random
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Random::Random_Range_Engine", Random_Range_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Physics
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Physics2D::RayCast_Engine", RayCast_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Application
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Application::Quit_Engine", Quit_Engine);

			ScoreSetUp();
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Input
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

		bool GetKey_Engine(Input_KeyCode key) { return Input::IsKeyHold(key); }
		bool GetKeyDown_Engine(Input_KeyCode key) { return Input::IsKeyPressed(key); }

		bool GetMouse_Engine(Input_MouseCode button) { return Input::IsMouseHold(button); }
		bool GetMouseDown_Engine(Input_MouseCode button) { return Input::IsMousePressed(button); }
		bool GetMouseUp_Engine(Input_MouseCode button) { return Input::IsMouseReleased(button); }

		void GetMousePosition_Engine(Math::vec2* outPosition) {
			*outPosition = GetMousePositionFuncPtr();
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Save highscore
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		int highScore = 0;
		int currentScore = 0;
		void ScoreSetUp() {
			std::ifstream fileStream;
			rapidjson::Document doc;

			fileStream.open("Data/highscore.json");
			rapidjson::IStreamWrapper isw(fileStream);

			doc.ParseStream(isw);

			rapidjson::Value::ConstMemberIterator itr = doc.GetArray()[0].FindMember("Score");
			if (itr != doc.GetArray()[0].MemberEnd()) {
				highScore = itr->value["HighScore"].GetInt();
				currentScore = itr->value["CurrentScore"].GetInt();
			}
		}
		void SetHighscore_Engine(int value, MonoString* str) {
			char* text = mono_string_to_utf8(str);

			rapidjson::Document doc(rapidjson::kArrayType);
			rapidjson::Value entityObject(rapidjson::kObjectType);

			rapidjson::Value objTypeEntity(rapidjson::kObjectType);
			SSerializer serializerEntity(doc, objTypeEntity);
			if (strcmp(text, "HighScore") == 0) {
				highScore = value;
				serializerEntity.SetValue("HighScore", value);
			}
			else
				serializerEntity.SetValue("HighScore", highScore);

			if (strcmp(text, "CurrentScore") == 0) {
				currentScore = value;
				serializerEntity.SetValue("CurrentScore", value);
			}
			else
				serializerEntity.SetValue("CurrentScore", currentScore);

			entityObject.AddMember("Score", objTypeEntity, doc.GetAllocator());

			doc.PushBack(entityObject, doc.GetAllocator());


			std::ofstream fileStream("Data/highscore.json");
			rapidjson::OStreamWrapper osw(fileStream);

			rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
			doc.Accept(writer);

			fileStream.close();
			mono_free(text);
		}

		void GetHighscore_Engine(int* value, MonoString* str) {
			char* text = mono_string_to_utf8(str);

			//std::ifstream fileStream;
			//rapidjson::Document doc;
			//
			//fileStream.open("Data/highscore.json");
			//rapidjson::IStreamWrapper isw(fileStream);
			//
			//doc.ParseStream(isw);
			//
			//rapidjson::Value::ConstMemberIterator itr = doc.GetArray()[0].FindMember("Score");
			//if (itr != doc.GetArray()[0].MemberEnd()) {
			//	*value = itr->value[text].GetInt();
			//}
			if (strcmp(text, "HighScore") == 0) {
				*value = highScore;
			}

			if (strcmp(text, "CurrentScore") == 0) {
				std::cout << "Current " << currentScore << "\n";
				*value = currentScore;
			}

			mono_free(text);
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Prefab
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Instantiate_Prefab_Transform_Engine(MonoString* prefabName, int entityId, unsigned int* newId) {
			char* text = mono_string_to_utf8(prefabName);
			if (entityId < 0) {
				GameSceneSerializer::DeserializePrefab(text, newId, Math::vec2{ 0.f,0.f }, 0.f);
			}
			else {
				const auto& transform = dreamECSGame->GetComponent<TransformComponent>(static_cast<unsigned int>(entityId));
				GameSceneSerializer::DeserializePrefab(text, newId, transform.position, transform.angle);
			}
			mono_free(text);
			//if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
		}

		void Instantiate_Prefab_Position_Engine(MonoString* prefabName, Math::vec3 pos, int layer, unsigned int* newId) {
			char* text = mono_string_to_utf8(prefabName);
			GameSceneSerializer::DeserializePrefab(text, newId, Math::vec2{ pos.x, pos.y }, 0, layer);
			mono_free(text);
		}

		//void Instantiate_Prefab_Engine(MonoString* prefabName, Math::vec2 position, float angle) {
		//	unsigned int id;
		//	GameSceneSerializer::DeserializePrefab(mono_string_to_utf8(prefabName), position, angle, id);
		//	//if (GameState::GetInstance().GetPlaying()) ScriptSystem::GetInstance().PlayInit();
		//}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Deltatime
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		//_timeScale = true means affected by time scale
		void GetDeltaTime_Engine(float* dt, bool _timeScale) {
			if (_timeScale)
				*dt = DeltaTime::GetInstance().GetDeltaTime();
			else
				*dt = DeltaTime::GetInstance().GetUnscaledDeltaTime();
		}

		void GetFixedDeltaTime_Engine(float* dt) {
			*dt = DeltaTime::GetInstance().GetFixedDeltaTime();
		}

		void SetTimeScale_Engine(float timeScale) {
			DeltaTime::GetInstance().SetTimeScale(timeScale);
		}

		void GetTimeScale_Engine(float* timeScale) {
			*timeScale = DeltaTime::GetInstance().GetTimeScale();
		}

		void WaitForSeconds_Engine(float) {

		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Scene
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void LoadScene_Engine(MonoString* sceneName) {
			char* text = mono_string_to_utf8(sceneName);
			FontSystem::GetInstance().SetFadeToBlack(text);
			//SceneManager::GetInstance().ChangeScene(text);
			mono_free(text);
		}

		void SetDrawMode_Engine(bool state) {
			GameState::GetInstance().SetShouldDraw(state);
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Console Write
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ConsoleWrite_Engine(MonoString* message) {
			char* text = mono_string_to_utf8(message);
			ConsoleFuncPtr(text);
			mono_free(text);
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Random
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Random_Range_Engine(int num1, int num2, int* answer) {
			Random::Range(num1, num2, answer);
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Physics
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		bool RayCast_Engine(Math::vec3 pos, Math::vec2 dir, int ignoreTarget, float distance, unsigned int* entity_id, float* hitDistance, Math::vec2* hitPoint) {
			RaycastHit hitCast;
			//if (distance < 0) distance = RAY_LENGTH;
			std::uint32_t ignored = ignoreTarget < 0 ? DEFAULT_ENTITY_ID : ignoreTarget;
			CollisionSystem::GetInstance().RayCast(Engine::Ray{ Math::vec2 {pos.x, pos.y}, dir, distance }, &hitCast, ignored);
			*hitDistance = hitCast.distance;
			*hitPoint = hitCast.point;
			*entity_id = hitCast.entity_id;

			if (hitCast.entity_id < 0) return false;
			return true;
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Application
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void Quit_Engine() {
	#ifdef _GAME_BUILD
			Engine::WindowCloseEvent event;
			Engine::EventDispatcher::SendEvent(event);
	#else
			Scripting::CallDisplayFuncPtr("Game Stopped\n");
			SceneManager::GetInstance().Stop();
	#endif
		}
	
	}
}

