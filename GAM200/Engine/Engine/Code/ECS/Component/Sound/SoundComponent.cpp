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


	void SoundComponent::Init() {

		soundImplementation = new SoundImplementation;
		 
	}

	void SoundComponent::Soundget() {

		soundImplementation->Update();
	}

	void SoundComponent::LoadSound(const std::string& soundName, bool b3d = true, bool slooping = false, bool sStream = false) {

		auto soundFind = soundImplementation->sMap.find(soundName);
		if (soundFind != soundImplementation->sMap.end())
			return;
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D : FMOD_2D;
		eMode |= slooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		eMode |= sStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
		FMOD::Sound* playSound = nullptr;

		SoundComponent::ErrorCheck(soundImplementation->fmodSystem->createSound(soundName.c_str(), eMode, nullptr, &playSound));

		if (playSound)
			soundImplementation->sMap[soundName] = playSound;


	}

	void SoundComponent::UnLoadSound(const std::string& soundName) {
		

		auto soundFind = soundImplementation->sMap.find(soundName);
		if (soundFind == soundImplementation->sMap.end())
			return;

		SoundComponent::ErrorCheck(soundFind->second->release());
		soundImplementation->sMap.erase(soundName);
	}

	int SoundComponent::PlaySounds(const std::string& soundName, const Engine::DreamMath::vec3& vPos = Engine::DreamMath::vec3{ 0, 0, 0 }, float fVolumedB = 0.0f) {

		int channelID = soundImplementation->channelID++;
		auto soundFind = soundImplementation->sMap.find(soundName);
		if (soundFind == soundImplementation->sMap.find(soundName))
		{
			LoadSound(soundName);
			soundFind = soundImplementation->sMap.find(soundName);
			if (soundFind == soundImplementation->sMap.end())
				return channelID;
		}

		FMOD::Channel* pChannel = nullptr;
		SoundComponent::ErrorCheck(soundImplementation->fmodSystem->playSound(soundFind->second, nullptr, true, &pChannel));

		if (pChannel)
		{
			FMOD_MODE currentMode;
			soundFind->second->getMode(&currentMode);
			if (currentMode)
			{
				FMOD_VECTOR position = VectorToFmod(vPos);
			}

			SoundComponent::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
			SoundComponent::ErrorCheck(pChannel->setPaused(false));
			soundImplementation->cMap[channelID] = pChannel;
		}

		return channelID;
	}
	
	FMOD_VECTOR SoundComponent::VectorToFmod(const Engine::DreamMath::vec3& vPosition)
	{
		FMOD_VECTOR fmodVec;
		fmodVec.x = vPosition.x;
		fmodVec.y = vPosition.y;
		fmodVec.z = vPosition.z;
		return fmodVec;
	}
}