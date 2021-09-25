/* Start Header**********************************************************************************/
/*
@file    Profiler.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    18/08/2021
\brief
This file contain the Profiler definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/Tools/Profiler.hpp"

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Window.hpp"

//#include <Tracy.hpp>
//#include <server/TracyView.hpp>


#ifdef TRACY_ENABLE
//std::unique_ptr<tracy::View> view;
//uint16_t port = 8086;
//ImFont* bigFont;
//ImFont* smallFont;
//ImFont* fixedWidth;
//
//std::thread::id mainThread;
#endif

namespace Editor {
	namespace Profiler {
#ifdef TRACY_ENABLE

		void RunOnMainThread(std::function<void()> cb)
		{
			/*if (std::this_thread::get_id() == mainThread)
			{
				cb();
			}*/
			/*else
			{
				std::lock_guard<std::mutex> lock(mainThreadLock);
				mainThreadTasks.emplace_back(cb);
			}*/
		}

		void Profiler_Setup() {
			//mainThread = std::this_thread::get_id();

			///*ImGuiIO& io = ImGui::GetIO();
			//ImFontConfig configBasic;
			//configBasic.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_LightHinting;

			//io.Fonts->AddFontFromMemoryCompressedTTF(tracy::Arimo_compressed_data, tracy::Arimo_compressed_size, 15.0f * dpiScale, &configBasic, rangesBasic);
			//io.Fonts->AddFontFromMemoryCompressedTTF(tracy::FontAwesomeSolid_compressed_data, tracy::FontAwesomeSolid_compressed_size, 14.0f * dpiScale, &configMerge, rangesIcons);
			//fixedWidth = io.Fonts->AddFontFromMemoryCompressedTTF(tracy::Cousine_compressed_data, tracy::Cousine_compressed_size, 14.0f * dpiScale, &configBasic);
			//bigFont = io.Fonts->AddFontFromMemoryCompressedTTF(tracy::Arimo_compressed_data, tracy::Arimo_compressed_size, 20.0f * dpiScale, &configBasic);
			//smallFont = io.Fonts->AddFontFromMemoryCompressedTTF(tracy::Arimo_compressed_data, tracy::Arimo_compressed_size, 10.0f * dpiScale, &configBasic);*/

			//fixedWidth->Scale = 20;
			//bigFont->Scale = 20;
			//smallFont->Scale = 20;

			//view = std::make_unique<tracy::View>(RunOnMainThread, nullptr, port, fixedWidth, smallFont, bigFont, nullptr, Engine::Window::GetNativewindow);
		}

		void Profiler_Draw() {
			/*if (!view)
				view->Draw();*/
		}
#else
		void Profiler_Setup() {}
		void Profiler_Draw() {}
#endif
	}
}