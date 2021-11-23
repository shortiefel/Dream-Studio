/* Start Header**********************************************************************************/
/*
@file    FontComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    01/11/2021
\brief
This file contain the FontComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/UI/FontComponent.hpp"

#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	// Contructor for Text Component
	FontComponent::FontComponent(Entity_id _ID, const std::string _path, std::string _text, bool _isFont,
		float _red, float _green, float _blue, bool _active) :
		IComponent{ _ID }, filepath{ _path }, text{ _text }, isFont{ _isFont },
		colour{ _red, _green, _blue, 1.0f }, isActive{ _active } { GraphicImplementation::SetFont(this, filepath); }

	// Destructor for Text Component
	FontComponent::~FontComponent()
	{
		// Done by ResourceManager::Destroy
	}

	// Deserialize function for Text Component
	FontComponent& FontComponent::Deserialize(const DSerializer& _serializer)
	{
		GraphicImplementation::SetFont(this, std::move(_serializer.GetValue<std::string>("Filepath")));
		text = _serializer.GetValue<std::string>("Text");

		float red = _serializer.GetValue<float>("Red");
		float green = _serializer.GetValue<float>("Green");
		float blue = _serializer.GetValue<float>("Blue");
		colour = { red, green, blue, 1.0f };

		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	// Serialize function for Text Component
	void FontComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Text", text);

		_serializer.SetValue("Red", colour.r);
		_serializer.SetValue("Green", colour.g);
		_serializer.SetValue("Blue", colour.b);

		_serializer.SetValue("IsActive", isActive);
	}
}