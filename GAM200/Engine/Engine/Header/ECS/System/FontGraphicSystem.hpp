/* Start Header**********************************************************************************/
/*!
@file FontGraphicSystem.hpp
@authors	Goh See Yong Denise				g.seeyongdenise@digipen.edu
@date 29/06/2021
@brief
FontSystem.hpp: This file contains all the structure and class related to the font systems

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FONTGRAPHICSYSTEM_HPP
#define FONTGRAPHICSYSTEM_HPP

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/GraphicSystem.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/ECS/Component/UI/TextComponent.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Management/TextureManager.hpp"
#include "Engine/Header/Management/AssetManager.hpp"

#include "Engine/Header/Graphic/FontSystem.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/Math/MathLib.hpp"


#include <vector>
#include <cmath>

namespace Engine
{
	class FontGraphicSystem : public Singleton<FontGraphicSystem>
	{
	public:
		FontSystem font_renderer;

		Math::mat4& GetProjection();


		bool Create();
		void Destroy();

		void Render(Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransform(), Graphic::FrameBuffer* _fbo = nullptr);

	private:
		glm::mat4 proj;
		SINGLETON_SETUP(FontGraphicSystem);
	};
}

#endif
