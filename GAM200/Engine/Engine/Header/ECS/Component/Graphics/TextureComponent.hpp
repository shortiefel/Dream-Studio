/* Start Header**********************************************************************************/
/*
@file    TextureComponent.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    02/07/2021
\brief
This file contain the TextureComponent declaration

//Serialize list
-string: pathname

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

//#include "Engine/Header/Graphic/glslshader.hpp" // for GLSLShader
//#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/pch.hpp"

#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"


namespace Engine {
	class DSerializer;
	class SSerializer;

	struct TextureComponent : public IComponent {
	public:
		GLuint texobj_hdl = GLuint{};

		std::string filepath = "";

		GraphicShape mdl_ref = GraphicShape{};
		//GraphicShader shd_ref = GraphicShader{};

		bool isActive = true;

		GLint width = GLint{}, height = GLint{}, BPP = GLint{}; //BPP - bits per pixel

		TextureComponent(Entity _ID = DEFAULT_ENTITY, const std::string _path = "", GraphicShape _shape = GraphicShape::SQUARE, //GraphicShader shader = "Default",
			bool _active = true);
		TextureComponent(const TextureComponent&) = default;
		TextureComponent& operator= (const TextureComponent&) = default;
		~TextureComponent();

		void Bind(GLuint slot = 0) const;
		void Unbind() const;

		TextureComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);
		//static std::shared_ptr<TextureComponent> CreateFromString(const std::string path);

		/*
		inline GLint getWidth() const { return width; }
		inline GLint getHeight() const { return height; }
		inline GLuint getTexObj() const { return texobj_hdl; }
		inline std::string getFilepath() const { return filepath; }
		inline bool GetActive() const { return isActive; }
		inline GraphicShape get_mdl_ref() const { return mdl_ref; }
		*/
		//inline GraphicShader get_shd_ref() const { return shd_ref; }
	};
}

#endif