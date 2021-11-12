/* Start Header**********************************************************************************/
/*
@file    GUI_AssetBrowser.hpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu		100%
@date    26/07/2021
\brief
This file contain the GUI Asset browser declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include <Imgui/imgui.h>
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"

namespace Editor {
	namespace GUI_Windows {
		void GUI_AssetBrowser(bool* asset_bool, ImGuiWindowFlags window_flags);
	}
}