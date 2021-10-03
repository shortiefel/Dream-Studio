/* Start Header**********************************************************************************/
/*
@file    SubTexture.hpp
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

#ifndef SUB_TEXTURE_HPP
#define SUB_TEXTURE_HPP

#include "Engine/Header/pch.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"


namespace Engine {
	class SubTexture 
	{
	public:
		SubTexture(const std::shared_ptr<Texture>& texture, const MathD::Vec2& min, const MathD::Vec2& max, const std::string name);

		SubTexture(std::string name);


		// cellSize: pixels per sprite, spriteSize: size of sprite
		static std::shared_ptr<SubTexture> CreateFromCoords(const std::shared_ptr<Texture>& texture, const std::string SpriteName, const MathD::Vec2& coords, const MathD::Vec2& cellSize, const MathD::Vec2& spriteSize = { 1, 1 });

		const std::shared_ptr<Texture> getTexture() const { return m_Texture; }
		const MathD::Vec2* getTexCoords() const { return TexCoords; }
	private:
		std::shared_ptr<Texture> m_Texture;
		MathD::Vec2 TexCoords[4];
		std::string SpriteName;
	};
}

#endif