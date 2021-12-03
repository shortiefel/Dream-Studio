/* Start Header**********************************************************************************/
/*
@file			SoundSystem.cpp
@author	Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
@date		15/11/2021
\brief
This file contain the definiation Components needed for sound

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/System/SoundSystem.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include <stdexcept>
#include < iterator >


namespace Engine
{

	//std::map<std::string, FMOD::Sound*> SoundManager::_soundMap;
	//std::map<int, FMOD::Channel*>  SoundManager::channelMap;
	//FMOD::System* SoundManager::System = nullptr;
	//FMOD::ChannelGroup* SoundManager::MasterGroup = nullptr;
	//FMOD::ChannelGroup* SoundManager::MusicGroup = nullptr;
	//FMOD::ChannelGroup* SoundManager::SFXGroup = nullptr;
	
	bool operator!(FMOD_RESULT res)
	{
		return res != FMOD_OK;
	}


	void SoundSystem::SoundCreate()
	{
		if (!FMOD::System_Create(&SoundManager::System))
			throw std::runtime_error("FMOD: Failed to create system object");

		if (SoundManager::System->init(512, FMOD_INIT_NORMAL, nullptr))
			throw std::runtime_error("FMOD: Failed to initialise system object");

		if (!SoundManager::System->getMasterChannelGroup(&SoundManager::MasterGroup))
			throw std::runtime_error("FMOD: Failed to get Master Channel Group");

		if (!SoundManager::System->createChannelGroup("Music", &SoundManager::MusicGroup))
			throw std::runtime_error("FMOD: Failed to create Music Channel Group");

		SoundManager::MasterGroup->addGroup(SoundManager::MusicGroup);

		if (!SoundManager::System->createChannelGroup("SFX", &SoundManager::SFXGroup))
			throw std::runtime_error("FMOD: Failed to create SFX Channel Group");

		SoundManager::MasterGroup->addGroup(SoundManager::SFXGroup);

	}

	bool SoundSystem::SoundUpdate()
	{
		std::vector<std::map<int, FMOD::Channel*>::iterator> StoppedChannels;
		for (auto it = SoundManager::channelMap.begin(); it != SoundManager::channelMap.end(); ++it)
		{
			bool bIsPlaying = false;
			it->second->isPlaying(&bIsPlaying);
			
			if (!bIsPlaying)
			{
				StoppedChannels.push_back(it);
			}
		}

		for (auto& it : StoppedChannels)
		{
			SoundManager::channelMap.erase(it);
		}

		SoundManager::System->update();
			//throw std::runtime_error("FMOD: Failed to Update System");

		return true;
	}



	void SoundSystem::SoundPlay(SoundComponent* soundCom)
	{
		//SoundManager::GetInstance().IsPlaying(soundCom->channelID);
		//auto it = SoundManager::channelMap.find(soundCom->channelID);
		//it->second->isPlaying(&(soundCom->));
		SoundManager::GetInstance().SetPlay(soundCom);
	}

	void SoundSystem::SoundPause(int channelID)
	{
		auto it = SoundManager::channelMap.find(channelID);

		if (it != SoundManager::channelMap.end())
			it->second->setPaused(true);
	}

	void SoundSystem::SoundUnpause(int channelID)
	{
		auto it = SoundManager::channelMap.find(channelID);

		if (it != SoundManager::channelMap.end())
			it->second->setPaused(false);	
	}

	void SoundSystem::SoundStopAllSound()
	{
		SoundManager::SFXGroup->stop();
		SoundManager::MusicGroup->stop();
		SoundManager::MasterGroup->stop();
	}

	void SoundSystem::SoundStop(SoundComponent* soundCom)
	{
		std::cout << "channel ID Stop" << soundCom->channelID << "\n";
		auto it = SoundManager::channelMap.find(soundCom->channelID);
		std::cout << "Sound Stop" << soundCom->channelID << "\n";
		if (it != SoundManager::channelMap.end())
		{
			it->second->stop();
		}
	}

	void SoundSystem::SoundDestroy()
	{
		SoundManager::GetInstance().Destroy();

		LOG_INSTANCE("Sound System destroyed");
	}

	void SoundSystem::SoundSetVolume(int channelID,float _vol)
	{
		SoundComponent SoundCom;

		auto it = SoundManager::channelMap.find(channelID);
		if (it == SoundManager::channelMap.end())
		{
			return;
		}

		it->second->setVolume(SoundCom.VolumeDecimal(_vol));
	}

	float SoundSystem::SoundGetVolume(int channelID, float _vol)
	{
		SoundComponent SoundCom;
		auto it = SoundManager::channelMap.find(channelID);
		if (it == SoundManager::channelMap.end())
		{
			return 0.f;
		}

		it->second->getVolume(&_vol);

		return SoundCom.DecimalVolume(_vol);
	}


}