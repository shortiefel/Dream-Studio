/* Start Header**********************************************************************************/
/*
@file			SoundManager.hpp
@author	Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
@date		29/11/2021
\brief

This file contain the definiation for sound

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Management/SoundManager.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine
{

	std::map<std::string, FMOD::Sound*> SoundManager::_soundMap;
	std::map<int, FMOD::Channel*>  SoundManager::channelMap;
	FMOD::System* SoundManager::System = nullptr;
	FMOD::ChannelGroup* SoundManager::MasterGroup = nullptr;
	FMOD::ChannelGroup* SoundManager::MusicGroup = nullptr;
	FMOD::ChannelGroup* SoundManager::SFXGroup = nullptr;

	void SoundManager::Create()
	{
		LOG_INSTANCE("SoundManager created");
	}

	void SoundManager::Destroy()
	{

		std::map<std::string, FMOD::Sound*>::iterator soundit;
		for (soundit = SoundManager::_soundMap.begin(); soundit != SoundManager::_soundMap.end(); ++soundit)
		{
			soundit->second->release();
		}

		SoundManager::_soundMap.clear();
		SoundManager::channelMap.clear();
		SoundManager::SFXGroup->release();
		SoundManager::MusicGroup->release();
		SoundManager::MasterGroup->release();
		SoundManager::System->release();
	}

	FMOD::Sound* SoundManager::GetSound(SoundComponent* soundCom, std::string&, std::string& soundName)
	{

		auto it = SoundManager::_soundMap.find(soundName);
		if (it == SoundManager::_soundMap.end())
		{
			FMOD_MODE eMode = FMOD_DEFAULT;
			eMode |= FMOD_LOOP_OFF;
			FMOD::Sound* pSound;
			std::cout << soundCom->filepath << "\n";
			SoundManager::System->createSound(soundCom->filepath.c_str(), eMode, nullptr, &pSound);
			//throw std::runtime_error("FMOD: Unable to create sound" + _path);

			if (pSound)
			{
				SoundManager::_soundMap[soundCom->soundName] = pSound;
				return pSound;
			}

			return it->second;

		}

		return it->second;
	}

	int SoundManager::SetPlay(SoundComponent* soundCom)
	{
		int ID;
		if (soundCom->channelID != -1) {
			ID = soundCom->channelID;
			channelMap[ID]->stop();
		}
		else {
			ID = ChannelID++;
			soundCom->channelID = ID;
		}

		auto tFoundIt = _soundMap.find(soundCom->soundName);
		FMOD::Sound* sound = nullptr;

		if (tFoundIt == _soundMap.end())
			sound = GetSound(soundCom, soundCom->filepath, soundCom->soundName);

		else
			sound = tFoundIt->second;

		FMOD::Channel* pChannel = nullptr;

		System->playSound(sound, nullptr, false, &pChannel);
		pChannel->isPlaying(&(soundCom->isPlaying));
		if (pChannel)
		{
			float vol = soundCom->volume;;
			switch (soundCom->soundType)
			{
			case SoundGrp::MUSIC:
				MusicGroup->setVolume(0.5f * vol);
				pChannel->setChannelGroup(MusicGroup);
				break;
			case SoundGrp::SFX:
				SFXGroup->setVolume(0.8f * vol);
				pChannel->setChannelGroup(SFXGroup);
				break;

			default:
				MusicGroup->setVolume(vol);
				pChannel->setChannelGroup(MasterGroup);
				break;
			};

			channelMap[ID] = pChannel;
		}
		std::cout << "channel ID Play" << ID << "\n";
		return ID;
	}

	int SoundManager::SetLoop(SoundComponent* soundCom)
	{
		auto it = channelMap.find(soundCom->channelID);

		if (soundCom->loop == true)
		{
			if (it != channelMap.end())
			{
				FMOD_MODE eMode = FMOD_LOOP_NORMAL;
				eMode |= soundCom->loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

				return it->second->setMode(eMode);
			}
		}

		return 0;
	}

	bool SoundManager::IsPlaying(int channelID)
	{
		auto it = channelMap.find(channelID);
		if (it == channelMap.end())
		{
			return false;
		}
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		return bIsPlaying;
	}

	void SoundManager::SetPauseAllSound(bool paused) {
		MasterGroup->setPaused(paused);
		MusicGroup->setPaused(paused);
		SFXGroup->setPaused(paused);
	}

	void SoundManager::MuteBGM(SoundComponent* soundCom)
	{

		if (soundCom->soundType == SoundGrp::MUSIC)
		{
			auto it = channelMap.find(soundCom->channelID);
			it->second->setMute(soundCom->isBGMMuted);
		}


	}


}