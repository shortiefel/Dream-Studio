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

	FontComponent::FontComponent(Entity_id entId, const FontComponent& rhs) :
		IComponent{ entId }, filepath{ rhs.filepath }, text{ rhs.text }, isFont{ rhs.isFont },
		colour{ rhs.colour }, isActive{ rhs.isActive }, position{ rhs.position }, scale{ rhs.scale }, fontName{ rhs.fontName } {

	}

	// Destructor for Text Component
	FontComponent::~FontComponent()
	{
		// Done by ResourceManager::Destroy
	}

	//// Deserialize function for Text Component
	//FontComponent& FontComponent::Deserialize(const DSerializer& _serializer)
	//{
	//	GraphicImplementation::SetFont(this, std::move(_serializer.GetValue<std::string>("Filepath")));
	//	text = _serializer.GetValue<std::string>("Text");
	//
	//	colour = _serializer.GetValue<Math::vec4>("Colour");
	//
	//	isActive = _serializer.GetValue<bool>("IsActive");
	//
	//	return *this;
	//}
	//
	//// Serialize function for Text Component
	//void FontComponent::Serialize(const SSerializer& _serializer)
	//{
	//	_serializer.SetValue("Filepath", filepath);
	//	_serializer.SetValue("Text", text);
	//
	//	_serializer.SetValue("Colour", colour);
	//
	//	_serializer.SetValue("IsActive", isActive);
	//}
}