/* Start Header**********************************************************************************/
/*
@file    SoundImplementation.cpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Sound/SoundImplementation.hpp"


namespace Engine {

	SoundImplementation* soundImplementation;

	SoundImplementation::SoundImplementation() {

		fmodSystem = NULL;
	}

	SoundImplementation::~SoundImplementation() {

	}

	void SoundImplementation::Update() {

	}

}

