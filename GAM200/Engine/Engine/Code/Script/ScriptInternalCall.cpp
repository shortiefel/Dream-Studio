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


namespace Engine {
	namespace InternalCall {

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


	}
}