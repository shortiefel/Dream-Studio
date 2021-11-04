/* Start Header**********************************************************************************/
/*
@file    SoundComponent.cpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine {

	SoundImplementation::SoundImplementation() {

		fmodSystem = NULL;
	}

	SoundImplementation::~SoundImplementation() {

	}

	void SoundImplementation::update() {

	}

	void SoundComponent::Init(SoundImplementation* soundImplementation) {

		soundImplementation = new SoundImplementation;
	}

	void SoundComponent::Update(SoundImplementation* soundImplementation) {

		soundImplementation->update();
	}

	void SoundComponent::LoadSound(const std::string& soundName, bool b3d = true, bool slooping = false, bool sStream = false) {

		SoundImplementation* soundImplementation;
		soundImplementation = new SoundImplementation;

	}
}