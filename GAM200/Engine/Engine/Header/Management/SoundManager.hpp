/* Start Header**********************************************************************************/
/*
@file			SoundManager.hpp
@author	Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
@date		29/11/2021
\brief

It contains all the FMOD functions and to manage the sound

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/
#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"
#include <fmod/fmod.hpp>

//// MACROS
//#define SET_SOUND(filepath, soundName)  if (_filepath.empty()) return;\
//														filepath = _filepath.substr(_filepath.rfind("Assets"));\
//														soundName = filepath.substr(filepath.find_last_of("\\") + 1);\
//														soundName = soundName.substr(0, soundName.find_last_of("."));
//														//soundhandler = SoundManager::GetInstance().LoadSound(filepath);

namespace Engine {

	struct SoundComponent;

	using SoundMap = std::map<std::string, FMOD::Sound*>;
	using ChannelMap = std::map<int, FMOD::Channel*>;

	struct SoundManager : public Singleton<SoundManager>
	{

		void Create();
		void Destroy();

		FMOD::Sound* GetSound(SoundComponent* soundCom, std::string& filePath, std::string& soundName);
		//void SetSound(SoundComponent* _textptr, std::string _filepath);
		int SetPlay(SoundComponent* soundCom);
		int SetLoop(SoundComponent* soundCom);

		bool IsPlaying(int channelID);

		//for toggling
		void SetPauseAllSound(bool paused);


		//NEW STUFF
		void MuteBGM(SoundComponent* soundCom);
		void MuteSFX(SoundComponent* soundCom);


		/**
		*		FMOD RELATED
		*/
		static SoundMap _soundMap;
		static FMOD::System* System;
		static ChannelMap channelMap;
		static FMOD::ChannelGroup* MasterGroup;
		static FMOD::ChannelGroup* MusicGroup;
		static FMOD::ChannelGroup* SFXGroup;

		//SoundGrp SG;
		int ChannelID;

		SINGLETON_SETUP(SoundManager);

	};
}


#endif