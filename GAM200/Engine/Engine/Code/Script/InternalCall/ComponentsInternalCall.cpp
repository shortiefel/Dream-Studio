/* Start Header**********************************************************************************/
/*
@file    ComponentsInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/ComponentsInternalCall.hpp"
This file contain the definition of ComponentsInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/Script/InternalCall/ComponentsInternalCall.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

#include "Engine/Header/Graphic/SpaceTransform.hpp"
#include "Engine/Header/Management/SoundManager.hpp"
#include "Engine/Header/ECS/System/SoundSystem.hpp"

#include "Engine/Header/Management/Settings.hpp"

#include <mono/jit/jit.h>


namespace Engine {
	namespace InternalCall {
		Math::mat3(*GetViewportFuncPtr)() = []() -> Math::mat3 {
			return Math::mat3(2.f / Settings::windowWidth, 0.f, 0.f,
				0.f, 2.f / Settings::windowHeight, 0.f,
				-1.f, -1.f, 1.f);
		};

		void SetGetViewportInternalFunc(Math::mat3(*fp)()) {
			GetViewportFuncPtr = fp;
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Transform
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void GetTransform_Position_Engine(unsigned int id, Math::vec2* outVec2, bool local);
		void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2, bool local);
		void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2);
		void GetTransform_Scale_Engine(unsigned int id, Math::vec2* outVec2);
		void SetTransform_Scale_Engine(unsigned int id, Math::vec2* inVec2);
		void GetTransform_Angle_Engine(unsigned int id, float* outVec2);
		void SetTransform_Angle_Engine(unsigned int id, float* inVec2);
		void GetTransform_Layer_Engine(unsigned int id, int* outLayer);
		void SetTransform_Layer_Engine(unsigned int id, int* inLayer);

		void GetTransform_IsActive_Engine(unsigned int entityID, bool* result);

		//void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2);
		void GetTransform_up_Engine(unsigned int id, Math::vec2* outVec2);
		void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2);
		void SetParent_Engine(int parentId, unsigned int child);

		void Transform_GetChildCount_Engine(unsigned int entityId, int* result);
		void Transform_GetChild_Engine(unsigned int entityId, int index, unsigned int* targetId);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Camera
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ScreenToWorldPoint_Engine(unsigned int id, Math::vec3* outPosition, Math::vec3 inPosition);
		void GetCameraHeight_Engine(unsigned int id, float* _height);
		void SetCameraHeight_Engine(unsigned int id, float _height);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Texture
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ChangeTexture_Engine(unsigned int entityID, MonoString* name);
		void SetTexture_Color_Engine(unsigned int entityID, Math::vec4 col);
		void GetTexture_Alpha_Engine(unsigned int entityID, float* alpha);
		void SetTexture_Alpha_Engine(unsigned int entityID, float alpha);
		void RetrieveTexture_Engine(unsigned int entityID, MonoString** name);


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Rigidbody2d
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void GetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* velocity);
		void SetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* inVec2);
		void GetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* velocity);
		void SetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* inVec2);
		/*void GetRigidbody_Inertia_Engine(unsigned int entityID, float* result);
		void SetRigidbody_Inertia_Engine(unsigned int entityID, float* inertia);*/
		void AddForce_Physics_Engine(unsigned int entityID, Math::vec2 force);
		void AddTorque_Physics_Engine(unsigned int entityID, float torque);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Text/Font
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetFont_Text_Engine(unsigned int entityID, MonoString* _text);
		//void GetFont_Text_Engine(unsigned int entityID, MonoString** _text);
		void SetFont_Color_Engine(unsigned int entityID, Math::vec4 col);
		void GetText_Alpha_Engine(unsigned int entityID, float* alpha);
		void SetText_Alpha_Engine(unsigned int entityID, float alpha);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		UI color
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetUI_Color_Engine(unsigned int entityID, Math::vec4 col);
		void ChangeTexture_UI_Engine(unsigned int entityID, MonoString* name);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Sound / Audio Source
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetSound_State_Engine(unsigned int entityID, int audioState);

		void GetSound_Volume_Engine(unsigned int entityID, float* _vol);
		void SetSound_Volume_Engine(unsigned int entityID, float* _vol);

		void GetSound_Mute_Engine(unsigned int entityID, bool* _mute);
		void SetSound_Mute_Engine(unsigned int entityID, bool*);

		void SetSoundGroup_Mute_Engine(int audioGroup, bool _state);
		bool GetSoundGroup_Mute_Engine(int audioGroup);
		void SetSoundGroup_Volume_Engine(int audioGroup, float vol);
		float GetSoundGroup_Volume_Engine(int audioGroup);

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Animation
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetAnimation_Engine(unsigned int entityID, MonoString* _state);


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Waypoint
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		//void Waypoint_GetNumberOfRoute_Engine(unsigned int entityID, unsigned int* num);
		void Waypoint_GetWaypoints_Engine(unsigned int entityID, MonoArray* points, MonoArray* order, int* section);


		/*-----------------------------------------------------
		Called in ScriptingInternalCall
		-----------------------------------------------------*/
		void RegisterComponentsInternalCall() {
			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Transform
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Transform::GetTransform_Position_Engine", GetTransform_Position_Engine);
			mono_add_internal_call("Transform::SetTransform_Position_Engine", SetTransform_Position_Engine);
			mono_add_internal_call("Transform::MoveTransform_Position_Engine", MoveTransform_Position_Engine);
			mono_add_internal_call("Transform::GetTransform_Scale_Engine", GetTransform_Scale_Engine);
			mono_add_internal_call("Transform::SetTransform_Scale_Engine", SetTransform_Scale_Engine);
			mono_add_internal_call("Transform::GetTransform_Angle_Engine", GetTransform_Angle_Engine);
			mono_add_internal_call("Transform::SetTransform_Angle_Engine", SetTransform_Angle_Engine);
			mono_add_internal_call("Transform::GetTransform_Layer_Engine", GetTransform_Layer_Engine);
			mono_add_internal_call("Transform::SetTransform_Layer_Engine", SetTransform_Layer_Engine);
			mono_add_internal_call("Transform::GetTransform_IsActive_Engine", GetTransform_IsActive_Engine);
			//mono_add_internal_call("Transform::GetTransform_forward_Engine", GetTransform_forward_Engine);
			mono_add_internal_call("Transform::GetTransform_up_Engine", GetTransform_up_Engine);
			mono_add_internal_call("Transform::GetTransform_right_Engine", GetTransform_right_Engine);
			mono_add_internal_call("Transform::SetParent_Engine", SetParent_Engine);

			mono_add_internal_call("Transform::Transform_GetChildCount_Engine", Transform_GetChildCount_Engine);
			mono_add_internal_call("Transform::Transform_GetChild_Engine", Transform_GetChild_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Camera
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Camera::ScreenToWorldPoint_Engine", ScreenToWorldPoint_Engine);
			mono_add_internal_call("Camera::GetCameraHeight_Engine", GetCameraHeight_Engine);
			mono_add_internal_call("Camera::SetCameraHeight_Engine", SetCameraHeight_Engine);


			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Texture
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Texture::ChangeTexture_Engine", ChangeTexture_Engine);
			mono_add_internal_call("Texture::SetTexture_Color_Engine", SetTexture_Color_Engine);
			mono_add_internal_call("Texture::GetTexture_Alpha_Engine", GetTexture_Alpha_Engine);
			mono_add_internal_call("Texture::SetTexture_Alpha_Engine", SetTexture_Alpha_Engine);
			mono_add_internal_call("Texture::RetrieveTexture_Engine", RetrieveTexture_Engine);
			

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Rigidbody2d
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Rigidbody2D::GetRigidbody_LinearVelocity_Engine", GetRigidbody_LinearVelocity_Engine);
			mono_add_internal_call("Rigidbody2D::SetRigidbody_LinearVelocity_Engine", SetRigidbody_LinearVelocity_Engine);
			mono_add_internal_call("Rigidbody2D::GetRigidbody_AngularVelocity_Engine", GetRigidbody_AngularVelocity_Engine);
			mono_add_internal_call("Rigidbody2D::SetRigidbody_AngularVelocity_Engine", SetRigidbody_AngularVelocity_Engine);
			/*mono_add_internal_call("Rigidbody2D::GetRigidbody_Inertia_Engine", GetRigidbody_Inertia_Engine);
			mono_add_internal_call("Rigidbody2D::SetRigidbody_Inertia_Engine", SetRigidbody_Inertia_Engine);*/
			mono_add_internal_call("Rigidbody2D::AddForce_Physics_Engine", AddForce_Physics_Engine);
			mono_add_internal_call("Rigidbody2D::AddTorque_Physics_Engine", AddTorque_Physics_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Text/Font
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Text::SetFont_Text_Engine", SetFont_Text_Engine);
			mono_add_internal_call("Text::SetFont_Color_Engine", SetFont_Color_Engine);
			mono_add_internal_call("Text::GetText_Alpha_Engine", GetText_Alpha_Engine);
			mono_add_internal_call("Text::SetText_Alpha_Engine", SetText_Alpha_Engine);


			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			UI color
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("UI::SetUI_Color_Engine", SetUI_Color_Engine);
			mono_add_internal_call("UI::ChangeTexture_UI_Engine", ChangeTexture_UI_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Sound / Audio Source
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("AudioSource::SetSound_State_Engine", SetSound_State_Engine);

			mono_add_internal_call("AudioSource::GetSound_Volume_Engine", GetSound_Volume_Engine);
			mono_add_internal_call("AudioSource::SetSound_Volume_Engine", SetSound_Volume_Engine);
			mono_add_internal_call("AudioSource::GetSound_Mute_Engine", GetSound_Mute_Engine);
			mono_add_internal_call("AudioSource::SetSound_Mute_Engine", SetSound_Mute_Engine);

			mono_add_internal_call("AudioSource::SetSoundGroup_Mute_Engine", SetSoundGroup_Mute_Engine);
			mono_add_internal_call("AudioSource::GetSoundGroup_Mute_Engine", GetSoundGroup_Mute_Engine);
			mono_add_internal_call("AudioSource::SetSoundGroup_Volume_Engine", SetSoundGroup_Volume_Engine);
			mono_add_internal_call("AudioSource::GetSoundGroup_Volume_Engine", GetSoundGroup_Volume_Engine);
			

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Animation
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			mono_add_internal_call("Animation::SetAnimation_Engine", SetAnimation_Engine);

			/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			Waypoint
			----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			//mono_add_internal_call("Waypoint::Waypoint_GetNumberOfRoute_Engine", Waypoint_GetNumberOfRoute_Engine);
			mono_add_internal_call("Waypoint::Waypoint_GetWaypoints_Engine", Waypoint_GetWaypoints_Engine);
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Transform
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void GetTransform_Position_Engine(unsigned int id, Math::vec2* outVec2, bool local) {
			if (!local) {
				GetEngineType(id, TransformComponent, position, *outVec2);
			}
			else {
				GetEngineType(id, TransformComponent, position, *outVec2);
			}
		}
		void SetTransform_Position_Engine(unsigned int id, Math::vec2* inVec2, bool local) {
			if (!local) {
				//SetEngineType(id, TransformComponent, position, *inVec2);
				
				TransformComponent* ctype = dreamECSGame->GetComponentPTR<TransformComponent>(id);
				if (!ctype) return;
				Math::vec2 moveDis = *inVec2 - ctype->position;
				ctype->position = *inVec2;

				auto& entityMap = dreamECSGame->GetUsedConstEntityMap();
				const auto& itr = entityMap.find(ctype->GetEntityId());
				const auto& entity = itr->second;
				Entity_id parent = entity.parent;

				if (parent != DEFAULT_ENTITY_ID) //TODO: Need to fix parent-child
					ctype->position -= dreamECSGame->GetComponent<TransformComponent>(parent).position;
				else
					ctype->position = *inVec2;

				for (auto& newId : entity.child) {
					TransformComponent* newTransform = dreamECSGame->GetComponentPTR<TransformComponent>(newId);
					if (newTransform != nullptr)
						newTransform->position += moveDis;
				}
			}
			else {
				//SetEngineType(id, TransformComponent, localPosition, *inVec2);
				
				TransformComponent* ctype = dreamECSGame->GetComponentPTR<TransformComponent>(id);
				if (!ctype) return;
				Math::vec2 moveDis = *inVec2 - ctype->position;
				ctype->position = *inVec2;
				auto& entityMap = dreamECSGame->GetUsedConstEntityMap();
				const auto& itr = entityMap.find(ctype->GetEntityId());
				const auto& entity = itr->second;
				Entity_id parent = entity.parent;

				if (parent != DEFAULT_ENTITY_ID) //TODO: Need to fix parent-child
					ctype->position = ctype->position + dreamECSGame->GetComponent<TransformComponent>(parent).position;
				else
					ctype->position = *inVec2;

				for (auto& newId : entity.child) {
					TransformComponent* newTransform = dreamECSGame->GetComponentPTR<TransformComponent>(newId);
					if (newTransform != nullptr)
						newTransform->position += moveDis;
				}
			}

		}

		void GetTransform_IsActive_Engine(unsigned int entityID, bool* result) {
			GetEngineType(entityID, TransformComponent, isActive, *result);
		}

		void MoveTransform_Position_Engine(unsigned int id, Math::vec2* inVec2) {
			//call hascomponent with entityid
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (!transform) return;
			transform->position += *inVec2;
		}

		void GetTransform_Scale_Engine(unsigned int id, Math::vec2* outVec2) {
			GetEngineType(id, TransformComponent, scale, *outVec2);
		}
		void SetTransform_Scale_Engine(unsigned int id, Math::vec2* inVec2) {
			SetEngineType(id, TransformComponent, scale, *inVec2);
		}


		void GetTransform_Angle_Engine(unsigned int id, float* outVec2) {
			GetEngineType(id, TransformComponent, angle, *outVec2);

		}
		void SetTransform_Angle_Engine(unsigned int id, float* inVec2) {
			SetEngineType(id, TransformComponent, angle, *inVec2);
		}

		void GetTransform_Layer_Engine(unsigned int id, int* outLayer) {
			GetEngineType(id, TransformComponent, layer, *outLayer);
		}
		void SetTransform_Layer_Engine(unsigned int id, int* inLayer) {
			SetEngineType(id, TransformComponent, layer, *inLayer);
		}
		/*void GetTransform_forward_Engine(unsigned int id, Math::vec2* outVec2) {
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (!transform) return;
			float newAngle = Math::radians(transform->angle);
			*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
		}*/

		void GetTransform_up_Engine(unsigned int id, Math::vec2* outVec2) {
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (!transform) return;
			float newAngle = Math::radians(transform->angle + 90.f);
			*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
		}

		void GetTransform_right_Engine(unsigned int id, Math::vec2* outVec2) {
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (!transform) return;
			float newAngle = Math::radians(transform->angle);
			*outVec2 = Math::vec2{ Math::cos(newAngle), Math::sin(newAngle) };
		}

		void SetParent_Engine(int parentId, unsigned int child) {
			if (parentId < 0) dreamECSGame->Unparent(child);
			else dreamECSGame->Parent(parentId, child);
		}

		void Transform_GetChildCount_Engine(unsigned int entityId, int* result) {
			const auto& entity = dreamECSGame->GetUsedConstEntityMap().find(entityId)->second;
			*result = static_cast<int>(entity.child.size());
		}

		void Transform_GetChild_Engine(unsigned int entityId, int index, unsigned int* targetId) {
			const auto& entity = dreamECSGame->GetUsedConstEntityMap().find(entityId)->second;
			auto t_ = entity.child.find(index);
			if (t_ == entity.child.end()) return;
			*targetId = *(t_);
		}
		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Camera
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ScreenToWorldPoint_Engine(unsigned int id, Math::vec3* outPosition, Math::vec3 inPosition) {
			*outPosition = ScreenToWorldPoint(inPosition, CameraSystem::GetInstance().GetInverseTransform(&id), GetViewportFuncPtr());
		}

		void GetCameraHeight_Engine(unsigned int id, float* _height) {
			GetEngineType(id, CameraComponent, height, *_height);
		}
		void SetCameraHeight_Engine(unsigned int id, float _height) {
			SetEngineType(id, CameraComponent, height, _height);
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Texture
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void ChangeTexture_Engine(unsigned int entityID, MonoString* name) {
			const auto ptr = dreamECSGame->GetComponentPTR<TextureComponent>(entityID);
			if (ptr != nullptr) {
				char* text = mono_string_to_utf8(name);
				GraphicImplementation::SetTexture(ptr, "Assets\\Textures\\" + std::string{ text } + ".png");
				mono_free(text);
			}
		}

		void SetTexture_Color_Engine(unsigned int entityID, Math::vec4 col) {
			SetEngineType(entityID, TextureComponent, colour, col);
		}

		void GetTexture_Alpha_Engine(unsigned int entityID, float* alpha) {
			GetEngineType(entityID, TextureComponent, colour.a, *alpha);
		}

		void SetTexture_Alpha_Engine(unsigned int entityID, float alpha) {
			if (alpha < 0.f) alpha = 0.f;
			else if (alpha > 1.f) alpha = 1.f;
			SetEngineType(entityID, TextureComponent, colour.a, alpha);
		}

		void RetrieveTexture_Engine(unsigned int entityID, MonoString** name) {
			const auto& ptr = dreamECSGame->GetComponentPTR<TextureComponent>(entityID);

			if (ptr != nullptr) {
				*name = mono_string_new(mono_domain_get(), (ptr->textureName).c_str());
			}
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Rigidbody2d
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void GetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* velocity) {
			GetEngineType(entityID, RigidBodyComponent, linearVelocity, *velocity);
		}

		void SetRigidbody_LinearVelocity_Engine(unsigned int entityID, Math::vec2* inVec2) {
			SetEngineType(entityID, RigidBodyComponent, linearVelocity, *inVec2);
		}

		void GetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* velocity) {
			GetEngineType(entityID, RigidBodyComponent, angularVelocity, *velocity);
		}

		void SetRigidbody_AngularVelocity_Engine(unsigned int  entityID, float* inVec2) {
			SetEngineType(entityID, RigidBodyComponent, angularVelocity, *inVec2);
		}

		/*void GetRigidbody_Inertia_Engine(unsigned int entityID, float* result) {
			GetEngineType(entityID, RigidBodyComponent, inertia, *result);
		}

		void SetRigidbody_Inertia_Engine(unsigned int entityID, float* inertia) {
			SetEngineType(entityID, RigidBodyComponent, inertia, *inertia);
		}*/

		void AddForce_Physics_Engine(unsigned int entityID, Math::vec2 force) {
			RigidBodyComponent* rb = dreamECSGame->GetComponentPTR<RigidBodyComponent>(entityID);
			if (rb != nullptr) {
				float magnitude = Math::length(force);
				if (Math::EpsilonCheck(magnitude)) magnitude = 1.f;
				force = force / magnitude;
				rb->linearForces.emplace_back(LinearForces{ force, magnitude });
			}
		}

		void AddTorque_Physics_Engine(unsigned int entityID, float torque) {
			RigidBodyComponent* rb = dreamECSGame->GetComponentPTR<RigidBodyComponent>(entityID);
			if (rb != nullptr) {
				int direction = torque < 0.f ? -1 : 1;
				torque *= direction;
				rb->rotationForces.emplace_back(RotationForces{ torque, direction });
			}
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Text/Font
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetFont_Text_Engine(unsigned int entityID, MonoString* _text) {
			char* tempText = mono_string_to_utf8(_text);
			SetEngineType(entityID, FontComponent, text, std::string{ tempText });
			mono_free(tempText);
		}

		void SetFont_Color_Engine(unsigned int entityID, Math::vec4 col) {
			SetEngineType(entityID, FontComponent, colour, col);
		}

		void GetText_Alpha_Engine(unsigned int entityID, float* alpha) {
			GetEngineType(entityID, FontComponent, colour.a, *alpha);
		}

		void SetText_Alpha_Engine(unsigned int entityID, float alpha) {
			if (alpha < 0.f) alpha = 0.f;
			else if (alpha > 1.f) alpha = 1.f;
			SetEngineType(entityID, FontComponent, colour.a, alpha);
		}

		//void GetFont_Text_Engine(unsigned int entityID, MonoString** _text) {}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		UI color
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetUI_Color_Engine(unsigned int entityID, Math::vec4 col) {
			SetEngineType(entityID, UIComponent, colour, col);
		}

		void ChangeTexture_UI_Engine(unsigned int entityID, MonoString* name) {
			const auto ptr = dreamECSGame->GetComponentPTR<UIComponent>(entityID);
			if (ptr != nullptr) {
				char* text = mono_string_to_utf8(name);
				GraphicImplementation::SetTexture(ptr, "Assets\\Textures\\" + std::string{ text } + ".png");
				mono_free(text);
			}
		}



		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Sound / Audio Source
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetSound_State_Engine(unsigned int entityID, int audioState) {
			SoundComponent* ctype = dreamECSGame->GetComponentPTR<SoundComponent>(entityID);

			switch (audioState) {
			case 0:
				SoundSystem::GetInstance().SoundPlay(ctype);
				break;
			case 1:
				SoundSystem::GetInstance().SoundPause(ctype->channelID);
				break;
			case 2:
				SoundSystem::GetInstance().SoundUnpause(ctype->channelID);
				break;
			default:
				break;
			}
		}

		void GetSound_Volume_Engine(unsigned int entityID, float* _vol) {
			SoundComponent* ctype = dreamECSGame->GetComponentPTR<SoundComponent>(entityID);
			*_vol = 0;

			if (!ctype) return;
			*_vol = ctype->volume;
		}
		void SetSound_Volume_Engine(unsigned int entityID, float* _vol) {
			SoundComponent* ctype = dreamECSGame->GetComponentPTR<SoundComponent>(entityID);

			if (!ctype) return;
			ctype->volume = *_vol;
		}

		void GetSound_Mute_Engine(unsigned int entityID, bool* _mute) {
			SoundComponent* ctype = dreamECSGame->GetComponentPTR<SoundComponent>(entityID);
			*_mute = false;

			if (!ctype) return;
			*_mute = ctype->isMute;
		}
		void SetSound_Mute_Engine(unsigned int entityID, bool*){
			SoundComponent* ctype = dreamECSGame->GetComponentPTR<SoundComponent>(entityID);

			if (!ctype) return;
			//SoundManager::GetInstance().MuteSound(ctype, *_mute);
			std::cout << "SetSound_Mute_Engine is currently not in used\n";
		}

		void SetSoundGroup_Mute_Engine(int audioGroup, bool _state) {
			//In AudioSource.cs
			//Master = 0,
			//SFX,
			//Music

			switch (audioGroup) {
			case 0: {
				SoundManager::GetInstance().SetSoundGroup_Mute(SoundGrp::MASTER, _state);
				break;
			}
			case 1: {
				SoundManager::GetInstance().SetSoundGroup_Mute(SoundGrp::SFX, _state);
				break;
			}
			case 2: {
				SoundManager::GetInstance().SetSoundGroup_Mute(SoundGrp::MUSIC, _state);
				break;
			}
			default: {
				break;
			}
			}
			
		}

		bool GetSoundGroup_Mute_Engine(int audioGroup) {
			//In AudioSource.cs
			//Master = 0,
			//SFX,
			//Music

			switch (audioGroup) {
			case 0: {
				return SoundManager::GetInstance().GetSoundGroup_Mute(SoundGrp::MASTER);
			}
			case 1: {
				return SoundManager::GetInstance().GetSoundGroup_Mute(SoundGrp::SFX);
			}
			case 2: {
				return SoundManager::GetInstance().GetSoundGroup_Mute(SoundGrp::MUSIC);
			}
			default: {
				return false;
			}
			}

		}

		void SetSoundGroup_Volume_Engine(int audioGroup, float vol) {
			switch (audioGroup) {
			case 0: {
				SoundManager::GetInstance().SetSoundGroup_Volume(SoundGrp::MASTER, vol);
				break;
			}
			case 1: {
				SoundManager::GetInstance().SetSoundGroup_Volume(SoundGrp::SFX, vol);
				break;
			}
			case 2: {
				SoundManager::GetInstance().SetSoundGroup_Volume(SoundGrp::MUSIC, vol);
				break;
			}
			default: {
				break;
			}
			}
		}

		float GetSoundGroup_Volume_Engine(int audioGroup) {
			switch (audioGroup) {
			case 0: {
				return SoundManager::GetInstance().GetSoundGroup_Volume(SoundGrp::MASTER);
			}
			case 1: {
				return SoundManager::GetInstance().GetSoundGroup_Volume(SoundGrp::SFX);
			}
			case 2: {
				return SoundManager::GetInstance().GetSoundGroup_Volume(SoundGrp::MUSIC);
			}
			default: {
				return 0;
			}
			}
		}

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Animation
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		void SetAnimation_Engine(unsigned int entityID, MonoString* _state) {
			char* tempText = mono_string_to_utf8(_state);
			SetEngineType(entityID, TextureComponent, nextAnimationState, std::string{ tempText });
			mono_free(tempText);
		}


		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Waypoint
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		//void Waypoint_GetNumberOfRoute_Engine(unsigned int entityID, unsigned int* num) {
		//	WaypointComponent* ctype = dreamECSGame->GetComponentPTR<WaypointComponent>(entityID);
		//	if (ctype == nullptr) return;
		//	*num = ctype->numOfWaypoint.size();
		//}

		void Waypoint_GetWaypoints_Engine(unsigned int entityID, MonoArray* points, MonoArray* order, int* section) {
			WaypointComponent* ctype = dreamECSGame->GetComponentPTR<WaypointComponent>(entityID);
			if (ctype == nullptr) return;
			{
				const auto& target = ctype->listOfWaypoint;
				int i = 0;
				for (const auto& t : target) {
					mono_array_set(points, Math::vec2, i, t);
					++i;
				}
			}

			{
				const auto& target = ctype->numOfWaypoint;
				int i = 0;
				for (const auto& t : target) {
					mono_array_set(order, unsigned int, i, t);
					++i;
				}
			}

			{
				*section = ctype->section;
			}

			printf("setting the points now \n");
		}

	}
}