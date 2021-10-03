/* Start Header**********************************************************************************/
/*
@file    SubTexture.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    02/07/2021
\brief
This file contain the SubTexture declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Graphics/SubTexture.hpp"
#include "Engine/Header/Graphic/Graphic.hpp" 

namespace Engine 
{
	//template<typename T, typename ... Args>
	//constexpr Ref<T> CreateRef(Args&& ... args)
	//{
	//	return std::make_shared<T>(std::forward<Args>(args)...);
	//}

	SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, const MathD::Vec2& min, const MathD::Vec2& max, const std::string name) : m_Texture{texture}, SpriteName {name}
	{
		TexCoords[0] = { min.x, min.y };
		TexCoords[1] = { max.x, min.y };
		TexCoords[2] = { max.x, max.y };
		TexCoords[3] = { min.x, max.y };

		GraphicImplementation::setup_vao_square_sprite(name, TexCoords);

		std::cout << "SUBTEXTURE CONSTRUCTOR CALLED" << std::endl;
	}

	SubTexture::SubTexture(std::string name) : SpriteName{ name }
	{
		if (!GraphicImplementation::modelsCheck(SpriteName))
			std::cout << "ERROR: MODEL NAME NOT FOUND" << std::endl;

		std::cout << "MODEL NAME FOUND" << std::endl;
	}

	std::shared_ptr<SubTexture> SubTexture::CreateFromCoords(const std::shared_ptr<Texture>& texture, const std::string name, const MathD::Vec2& coords, const MathD::Vec2& cellSize, const MathD::Vec2& spriteSize)
	{
		MathD::Vec2 min = { (coords.x * cellSize.x) / texture->getWidth(),
							(coords.y * cellSize.y) / texture->getHeight() };

		MathD::Vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->getWidth(),
							((coords.y + spriteSize.y) * cellSize.y) / texture->getHeight() };

		std::cout << "CreateFromCoords CALLED" << std::endl;

		return std::make_shared<SubTexture>(texture, min, max, name);
	}
}