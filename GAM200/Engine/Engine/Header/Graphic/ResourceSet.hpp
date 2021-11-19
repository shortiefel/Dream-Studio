/* Start Header**********************************************************************************/
/*
@file    ResourceSet.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    29/10/2021
@brief
#include "Engine/Header/Graphic/ResourceSet.hpp"
This file contain a texture setter


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RESOURCE_SET_HPP
#define RESOURCE_SET_HPP

#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/ParticleComponent.hpp"
#include "Engine/Header/ECS/Component/UI/UIComponent.hpp"
#include "Engine/Header/ECS/Component/UI/FontComponent.hpp"

#include <string>

namespace Engine
{
	namespace GraphicImplementation
	{
		void SetTexture(TextureComponent* _texptr, std::string _filepath);
		void SetTexture(ParticleComponent* _texptr, std::string _filepath);
		void SetTexture(UIComponent* _texptr, std::string _filepath);
		void SetFont(FontComponent* _texptr, std::string _filepath);
	}
}
#endif