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
#include <vector>


namespace Engine {

	SoundImplementation* soundImplementation = nullptr;

	SoundImplementation::SoundImplementation() {

		fmodStudioSystem = NULL;
		SoundComponent::ErrorCheck(FMOD::Studio::System::create(&fmodStudioSystem));
		SoundComponent::ErrorCheck(fmodStudioSystem->initialize(64, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

		fmodSystem = NULL;
		SoundComponent::ErrorCheck(fmodStudioSystem->getCoreSystem(&fmodSystem));
		
	}

	SoundImplementation::~SoundImplementation() {

		SoundComponent::ErrorCheck(fmodStudioSystem->unloadAll());
		SoundComponent::ErrorCheck(fmodSystem->release());

	}

	void SoundImplementation::Update() {

		std::vector<channelMap::iterator> stopChannel;
		for (auto mBegin = cMap.begin(); mBegin != cMap.end(); ++mBegin)
		{
			bool isPlaying = false;
			mBegin->second->isPlaying(&isPlaying);
			if (!isPlaying)
				stopChannel.push_back(mBegin);
		}

		for (auto& i : stopChannel)
		{
			cMap.erase(i);
		}

		SoundComponent::ErrorCheck(fmodStudioSystem->update());
	}

}

