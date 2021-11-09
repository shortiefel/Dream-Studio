/* Start Header**********************************************************************************/
/*
@file    SoundComponent.cpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief

This file contains the definition function for sound component with FMOD

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {

	FMOD::System* SoundComponent::SystemCore = nullptr;
	FMOD::Channel* SoundComponent::Channel = nullptr;
	FMOD::SoundGroup* SoundComponent::SoundGroup;
	FMOD::ChannelGroup* SoundComponent::MasterGroup = nullptr;
	FMOD::ChannelGroup* SoundComponent::MusicGroup = nullptr;

	float SoundComponent::MinDecibels = 20;
	float SoundComponent::MaxDeciibels = 100;

	std::map<std::string, FMOD::Sound*> SoundComponent::SoundMap;
	std::map<int, FMOD::Channel*> SoundComponent::ChannelMap;

	int SoundComponent::ChannelID = 0;

	float VolumeToDecibels(float volume)
	{
		if (volume < SoundComponent::MinDecibels)
			volume = SoundComponent::MinDecibels;
		else if (volume > SoundComponent::MaxDeciibels)
			volume = SoundComponent::MaxDeciibels;

		return volume / 100.f;
	}

	float DecibelsToVolume(float volume)
	{
		return volume * 100.f;
	}


	void SoundComponent::Init()
	{
		//main 
		if (!FMOD::System_Create(&SystemCore))
			throw std::runtime_error("FMOD: Failed to create system Object");

		if(!SystemCore->init(50, FMOD_INIT_NORMAL, nullptr))
			throw std::runtime_error("FMOD: Failed to initialise system object");

		if (!SystemCore->getMasterChannelGroup(&MasterGroup))
			throw std::runtime_error("FMOD: Failed to get Master Channel Group");

		if (!SystemCore->createChannelGroup("Music", &MusicGroup))
			throw std::runtime_error("FMOD: Failed to create Music Channel Group");

		if (MasterGroup->addGroup(MusicGroup))
			throw std::runtime_error("FMOD: Failed to add Music Channel to Master Group");

		SetVolume(50.f);
	}

	void SoundComponent::ReleaseAll()
	{
		std::map<std::string, FMOD::Sound*>::iterator soundit;
		for (soundit = SoundMap.begin(); soundit != SoundMap.end(); ++soundit)
		{
			soundit->second->release();
		}

		SoundMap.clear();
		ChannelMap.clear();
		MusicGroup->release();
		MasterGroup->release();
		SystemCore->release();
	}

	int SoundComponent::EPlaySound(const std::string& file, float volume, bool paused)
	{
		int ID = ChannelID++;
		auto tFoundIt = SoundMap.find(file);
		FMOD::Sound* sound;

		if (tFoundIt == SoundMap.end())
			sound = GetSound(file);

		else
			sound = tFoundIt->second;

		FMOD::Channel* pChannel = nullptr;
		if (!SystemCore->playSound(sound, nullptr, true, &pChannel))
			throw std::runtime_error("FMOD: Failed to play sound" + file);

		if (pChannel)
		{
			if (!pChannel->setVolume(VolumeToDecibels(volume)))
				throw std::runtime_error("FMOD: Failed to set volume sound: " + file);
			if (!pChannel->setPaused(paused))
				throw std::runtime_error("FMOD: Failed to pause sound: " + file);
		}
		ChannelMap[ID] = pChannel;

		return ID;
		
	}

	void SoundComponent::Pause(int ChannelID)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
			return;
		if (!it->second->setPaused(true))
			throw std::runtime_error("Failed to set volume Channel : " + ChannelID);
	}

	void SoundComponent::PauseEnd(int ChannelID)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
			return;
		if (!it->second->setPaused(false))
			throw std::runtime_error("Failed to set volume Channel : " + ChannelID);
	}

	void SoundComponent::StopSound(int ChannelID)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
		{
			MusicGroup->stop();
			MasterGroup->stop();
			return;
		}
		if (!it->second->stop())
			throw std::runtime_error("Failed to set Stop Channel : " + ChannelID);
	}

	bool SoundComponent::IsPlaying(int ChannelID)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
			return false;
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		return bIsPlaying;
	}
	
	void SoundComponent::SetVolume(int ChannelID, float volume)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
		{
			return;
		}
		if (!it->second->setVolume(VolumeToDecibels(volume)))
			throw std::runtime_error("Failed to set volume Channel : " + ChannelID);
	}

	float SoundComponent::GetVolume(int ChannelID)
	{
		float volume;
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
		{
			return 0.f;
		}
		if (!it->second->getVolume(&volume))
			throw std::runtime_error("Failed to set volume Channel : " + ChannelID);

		return DecibelsToVolume(volume);
	}

	void SoundComponent::ChangeVolume(int ChannelID, float volume)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
		{
			return;
		}
		float previousVolume;
		if (!it->second->getVolume(&previousVolume))
			throw std::runtime_error("Failed to set volume Channel : " + ChannelID);

		previousVolume = VolumeToDecibels(DecibelsToVolume(previousVolume) + volume);

		if (!it->second->setVolume(previousVolume))
			throw std::runtime_error("Failed to set volume Channel : " + ChannelID);
	}

	void SoundComponent::SetVolume(float volume)
	{
		if (!MasterGroup->setVolume(VolumeToDecibels(volume)))
			throw std::runtime_error("FMOD: Failed to set Channel Volume master");
		if (!MusicGroup->setVolume(VolumeToDecibels(volume)))
			throw std::runtime_error("FMOD: Failed to set Channel Volume music");
	}

	void SoundComponent::SetLoop(int ChannelID, bool isLoop)
	{
		auto it = ChannelMap.find(ChannelID);
		if (it == ChannelMap.end())
		{
			return;
		}
		FMOD_MODE eMode = FMOD_LOOP_NORMAL;
		eMode |= isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

		if (!it->second->setMode(eMode))
		{
			throw std::runtime_error("FMOD: Failed to play sound" + ChannelID);
			return;
		}
	}

	FMOD::Sound* SoundComponent::GetSound(const std::string& file)
	{
		auto it = SoundMap.find(file);
		if (it == SoundMap.end())
		{
			FMOD_MODE eMode = FMOD_DEFAULT;
			eMode |= FMOD_LOOP_OFF;
			FMOD::Sound* pSound = nullptr;
			if (SystemCore->createSound(file.c_str(), eMode, nullptr, &pSound))
				throw std::runtime_error("FMOD: Unable to create sound: " + file);

			if (pSound)
				SoundMap[file] = pSound;

			return pSound;
		}

		return it->second;

	}

	bool SoundComponent::Update()
	{
		std::vector<std::map<int, FMOD::Channel*>::iterator> pStopChannels;
		for (auto it = ChannelMap.begin(); it != ChannelMap.end(); ++it)
		{
			bool bIsPlaying = false;
			it->second->isPlaying(&bIsPlaying);
			if (!bIsPlaying)
			{
				pStopChannels.push_back(it);
			}
		}
		for (auto& it : pStopChannels)
		{
			ChannelMap.erase(it);
		}
		if (!SystemCore->update())
			throw std::runtime_error("FMOD: Failed to Update Core System");

		return true;
	}

}