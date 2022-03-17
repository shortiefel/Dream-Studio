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

	bool muteBGM = false;
	bool muteSFX = false;
	bool muteMaster = false;

	int volBGM = 30;
	int volSFX = 30;
	int volMaster = 30;

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
		std::cout << "playing-------------------------- \n";
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
			//float vol = soundCom->volume;
			switch (soundCom->soundType)
			{
			case SoundGrp::MUSIC:
				MusicGroup->setVolume(float(volBGM) /100);
				pChannel->setChannelGroup(MusicGroup);
				break;
			case SoundGrp::SFX:
				SFXGroup->setVolume(float(volSFX) /100);
				pChannel->setChannelGroup(SFXGroup);
				break;

			default:
				MasterGroup->setVolume(float(volMaster) / 100);
				pChannel->setChannelGroup(MasterGroup);
				break;
			};

			channelMap[ID] = pChannel;
		}
		std::cout << "channel ID Play" << ID << "\n";
		return ID;
	}

	//float SoundManager::GetCurrentMasterVolume(SoundComponent* soundCom)
	//{
	//	//float currentVol;
	//	//if (soundCom == nullptr)
	//	//{
	//	//	currentVol = MasterGroup->getVolume(&soundCom->volume);
	//	//	return currentVol;
	//	//}
	//	//else
	//	//{
	//	//	switch (soundCom->soundType)
	//	//	{
	//	//
	//	//	case SoundGrp::MUSIC:
	//	//		currentVol = MusicGroup->getVolume(&soundCom->volume);
	//	//		break;
	//	//	case SoundGrp::SFX:
	//	//		currentVol = SFXGroup->getVolume(&soundCom->volume);
	//	//		break;
	//	//	default:
	//	//		currentVol = MasterGroup->getVolume(&soundCom->volume);
	//	//		break;
	//	//
	//	//	}
	//	//	return currentVol;
	//	//}
	//	return 0;
	//	
	//}

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

	//void SoundManager::MuteSound(SoundComponent* soundCom, bool _state) {
	//	//soundCom->isMute = _state;
	//	//auto it = channelMap.find(soundCom->channelID);
	//	//if (it == channelMap.end()) return;
	//	//it->second->setMute(soundCom->isMute);
	//}

	void SoundManager::SetSoundGroup_Mute(SoundGrp _sg, bool _state)
	{
		switch (_sg)
		{
		case SoundGrp::MUSIC:
			MusicGroup->setMute(_state);
			muteBGM = _state;
			break;
		case SoundGrp::SFX:
			SFXGroup->setMute(_state);
			muteSFX = _state;
			break;
		default:
			MasterGroup->setMute(_state);
			muteMaster = _state;
			break;
		}
	}

	bool SoundManager::GetSoundGroup_Mute(SoundGrp _sg) {
		switch (_sg)
		{
		case SoundGrp::MUSIC:
			return muteBGM;
		case SoundGrp::SFX:
			return muteSFX;
		default:
			return muteMaster;
		}
	}

	void SoundManager::SetSoundGroup_Volume(SoundGrp _sg, float _vol)
	{
		int temVol = int(_vol);
		_vol /= 100.f;

		switch (_sg)
		{
		case SoundGrp::MUSIC:
			volBGM = temVol;
			MusicGroup->setVolume(_vol);
			break;
		case SoundGrp::SFX:
			volSFX = temVol;
			SFXGroup->setVolume(_vol);
			break;
		default:
			volMaster = temVol;
			MasterGroup->setVolume(_vol);
			break;
		}

	}

	float SoundManager::GetSoundGroup_Volume(SoundGrp _sg)
	{
		switch (_sg)
		{
		case SoundGrp::MUSIC:
			return (float)volBGM;
		case SoundGrp::SFX:
			return (float)volSFX;
		default:
			std::cout << "Sound master " <<  volMaster << "\n";
			return (float)volMaster;
		}

	}

	/*void SoundManager::MuteBGM(SoundComponent* soundCom)
	{

		if (soundCom->soundType == SoundGrp::MUSIC)
		{
			auto it = channelMap.find(soundCom->channelID);
			it->second->setMute(soundCom->isMute);
		}
	}

	void SoundManager::MuteSFX(SoundComponent* soundCom)
	{

		if (soundCom->soundType == SoundGrp::SFX)
		{
			auto it = channelMap.find(soundCom->channelID);
			it->second->setMute(soundCom->isMute);
		}
	}*/

	//void SoundManager::MasterVolumeDown(SoundComponent* soundCom)
	//{
	//	//float newVolume = 0.f;
	//	//float currentMasterVol = GetCurrentMasterVolume(0);
	//	//newVolume -=currentMasterVol;
	//	//
	//	//switch (soundCom->soundType)
	//	//{
	//	//
	//	//case SoundGrp::MUSIC:
	//	//	MusicGroup->setVolume(newVolume);
	//	//	break;
	//	//case SoundGrp::SFX:
	//	//	SFXGroup->setVolume(newVolume);
	//	//	break;
	//	//default:
	//	//	MasterGroup->setVolume(newVolume);
	//	//	break;
	//	//
	//	//}
	//	
	//}

	//void SoundManager::MasterVolumeUp(SoundComponent* soundCom)
	//{
	//	//float newVolume = 0.f;
	//	//float currentMasterVol = GetCurrentMasterVolume(0);
	//	//newVolume += currentMasterVol;
	//	//
	//	//switch (soundCom->soundType)
	//	//{
	//	//
	//	//case SoundGrp::MUSIC:
	//	//	MusicGroup->setVolume(newVolume);
	//	//	break;
	//	//case SoundGrp::SFX:
	//	//	SFXGroup->setVolume(newVolume);
	//	//	break;
	//	//default:
	//	//	MasterGroup->setVolume(newVolume);
	//	//	break;
	//	//
	//	//}
	//}

	//void SoundManager::VolumeChange(SoundComponent* soundCom)
	//{
	//	//if (soundCom->isIncrease)
	//	//	MasterVolumeUp(soundCom);
	//	//if (soundCom->isDecrease)
	//	//	MasterVolumeDown(soundCom);
	//}

}