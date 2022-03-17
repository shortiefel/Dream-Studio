/*
@file    ScriptInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    25/08/2021
\brief
This file contain the definition of ScriptInternalCall
Register all internal call function used by the C# side


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Script/ScriptInternalCall.hpp"

#include "Engine/Header/Event/WindowEvent.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Window.hpp"

#include "Engine/Header/Script/InternalCall/GridInternalCall.hpp"
#include "Engine/Header/Script/InternalCall/UtilityInternalCall.hpp"
#include "Engine/Header/Script/InternalCall/CoreInternalCall.hpp"
#include "Engine/Header/Script/InternalCall/ComponentsInternalCall.hpp"
#include "Engine/Header/Script/InternalCall/GameObjectInternalCall.hpp"
#include "Engine/Header/Script/InternalCall/MathInternalCall.hpp"

#include "Engine/Header/Management/Settings.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include <mono/metadata/reflection.h>

#define REGISTER_TYPE(Type, cStype) \
{\
MonoType* type = mono_reflection_type_from_name(const_cast<char*>(#cStype), Scripting::imageCore); \
if (type) { \
addComponentFuncs[type] = [](Entity_id entityId) { dreamECSGame->AddComponent<Type>(Type{entityId}); };\
hasComponentFuncs[type] = [](Entity_id entityId) { return (dreamECSGame->GetComponentPTR<Type>(entityId) != nullptr); };\
}\
}

namespace Engine {
	namespace Scripting {
		extern MonoImage* imageCore;
	}

	namespace InternalCall {

		std::unordered_map<MonoType*, std::function<void(Entity_id)>> addComponentFuncs;
		std::unordered_map<MonoType*, std::function<bool(Entity_id)>> hasComponentFuncs;

		void SetConsoleWriteFunc(void(*fp)(std::string)) {
			SetConsoleWriteInternalFunc(fp);
		}

		void SetGetMousePositionFunc(Math::vec2(*fp)()) {
			SetGetMousePositionInternalFunc(fp);
		}

		bool gameViewportCallBack(const WindowResizeEvent& e) {
			Math::uvec2 sz = e.GetSize();
			Settings::windowWidth = sz.x;
			Settings::windowHeight = sz.y;
			return true;
		}

		void SetGetViewportFunc(Math::mat3(*fp)()) {
			SetGetViewportInternalFunc(fp);
		}

		void InitializeSavedData() {
			InitializeSavedDataInternal();
		}

		void StoreSavedData() {
			StoreSavedDataInternal();
		}

		void RegisterInternalCall() {
			//Register Event callback
			WindowResizeEvent::RegisterFunction(gameViewportCallBack);

			RegisterGridInternalCall();
			RegisterUtilityInternalCall();
			RegisterCoreInternalCall();
			RegisterComponentsInternalCall();
			RegisterGameObjectInternalCall();
			RegisterMathInternalCall();

		}

		void RegisterTypes() {
			//Only called after Mono is reloaded
			REGISTER_TYPE(TransformComponent, Transform);
			REGISTER_TYPE(ColliderComponent, Collider);
			REGISTER_TYPE(CameraComponent, Camera);
			REGISTER_TYPE(RigidBodyComponent, Rigidbody2D);
			REGISTER_TYPE(TextureComponent, Texture);
			REGISTER_TYPE(TextureComponent, Animation); //DO note that since Animation and Texture are the same component, Animation might sometimes give false positive
			REGISTER_TYPE(FontComponent, Text);
			REGISTER_TYPE(SoundComponent, AudioSource);
			REGISTER_TYPE(UIComponent, UI);
			REGISTER_TYPE(WaypointComponent, Waypoint);
		}


	}
}