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

#include <stdexcept>
#include < iterator >


namespace Engine
{

	std::map<std::string, FMOD::Sound*> SoundComponent::_soundMap;
	std::map<int, FMOD::Channel*>  SoundComponent::channelMap;
	FMOD::System* SoundComponent::System = nullptr;
	FMOD::ChannelGroup* SoundComponent::MasterGroup = nullptr;
	FMOD::ChannelGroup* SoundComponent::MusicGroup = nullptr;
	FMOD::ChannelGroup* SoundComponent::SFXGroup = nullptr;

	
	bool operator!(FMOD_RESULT res)
	{
		return res != FMOD_OK;
	}


	void SoundSystem::SoundInit()
	{
		if (!FMOD::System_Create(&SoundComponent::System))
			throw std::runtime_error("FMOD: Failed to create system object");

		if (!SoundComponent::System->init(512, FMOD_INIT_NORMAL, nullptr))
			throw std::runtime_error("FMOD: Failed to initialise system object");

		if (!SoundComponent::System->getMasterChannelGroup(&SoundComponent::MasterGroup))
			throw std::runtime_error("FMOD: Failed to get Master Channel Group");

		if (!SoundComponent::System->createChannelGroup("Music", &SoundComponent::MusicGroup))
			throw std::runtime_error("FMOD: Failed to create Music Channel Group");

		SoundComponent::MasterGroup->addGroup(SoundComponent::MusicGroup);

		if (!SoundComponent::System->createChannelGroup("SFX", &SoundComponent::SFXGroup))
			throw std::runtime_error("FMOD: Failed to create SFX Channel Group");

		SoundComponent::MasterGroup->addGroup(SoundComponent::SFXGroup);

		

	}

	bool SoundSystem::SoundUpdate()
	{
		std::vector<std::map<int, FMOD::Channel*>::iterator> StoppedChannels;
		for (auto it = SoundComponent::channelMap.begin(); it != SoundComponent::channelMap.end(); ++it)
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
			SoundComponent::channelMap.erase(it);
		}

		SoundComponent::System->update();
			//throw std::runtime_error("FMOD: Failed to Update System");

		return true;
	}

	int SoundSystem::SoundPlay(const std::string& _path, bool _pause)
	{
		SoundGrp sg = SoundGrp::MASTER;
		int ID = SoundComponent::ChannelID++;
		auto tFoundIt = SoundComponent::_soundMap.find(_path);
		FMOD::Sound* sound;
		
		if (tFoundIt == SoundComponent::_soundMap.end())
			sound = SoundComponent::GetSound(_path);

		else
			sound = tFoundIt->second;

		FMOD::Channel* pChannel = nullptr;

		SoundComponent::System->playSound(sound, nullptr, _pause, &pChannel);
		if (pChannel)
		{
			
			switch (sg)
			{
			case SoundGrp::MASTER:
				pChannel->setChannelGroup(SoundComponent::MasterGroup);
				SoundComponent::MusicGroup->setVolume(SoundComponent::VolumeDecimal(100.f));
				break;
			case SoundGrp::MUSIC:
				pChannel->setChannelGroup(SoundComponent::MusicGroup);
				SoundComponent::MusicGroup->setVolume(SoundComponent::VolumeDecimal(100.f));
				break;
			case SoundGrp::SFX:
				pChannel->setChannelGroup(SoundComponent::SFXGroup);
				SoundComponent::SFXGroup->setVolume(SoundComponent::VolumeDecimal(50.f));
				break;
			
			};

			SoundComponent::channelMap[ID] = pChannel;
		}

		std::cout << "channel ID Play" << ID << "\n";
		return ID;

	}

	void SoundSystem::SoundPause(int channelID)
	{
		auto it = SoundComponent::channelMap.find(channelID);

		if (it == SoundComponent::channelMap.end())
			return;
		else
			it->second->setPaused(true);
	}

	void SoundSystem::SoundUnpause(int channelID)
	{
		auto it = SoundComponent::channelMap.find(channelID);

		if (it == SoundComponent::channelMap.end())
			return;
		else
			it->second->setPaused(false);
	}

	void SoundSystem::SoundStop(int channelID)
	{
		std::cout << "channel ID Stop" << channelID << "\n";
		auto it = SoundComponent::channelMap.find(channelID);
		std::cout << "Sound Stop"  << channelID << "\n";
		if (it == SoundComponent::channelMap.end())
		{
			SoundComponent::SFXGroup->stop();
			SoundComponent::MusicGroup->stop();
			SoundComponent::MasterGroup->stop();
			return;
		}
	}

	void SoundSystem::SoundSetVolume(int channelID,float _vol)
	{
		auto it = SoundComponent::channelMap.find(channelID);
		if (it == SoundComponent::channelMap.end())
		{
			return;
		}

		it->second->setVolume(SoundComponent::VolumeDecimal(_vol));
	}

	float SoundSystem::SoundGetVolume(int channelID)
	{
		float vol;
		auto it = SoundComponent::channelMap.find(channelID);
		if (it == SoundComponent::channelMap.end())
		{
			return 0.f;
		}

		it->second->getVolume(&vol);

		return SoundComponent::DecimalVolume(vol);
	}

	void SoundSystem::SoundRelease()
	{
	
		std::map<std::string, FMOD::Sound*>::iterator soundit;
		for (soundit = SoundComponent::_soundMap.begin(); soundit != SoundComponent::_soundMap.end(); ++soundit)
		{
			soundit->second->release();
		}

		SoundComponent::_soundMap.clear();
		SoundComponent::channelMap.clear();
		SoundComponent::SFXGroup->release();
		SoundComponent::MusicGroup->release();
		SoundComponent::MasterGroup->release();
		SoundComponent::System->release();
	}

}