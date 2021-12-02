/* Start Header**********************************************************************************/
/*
@file			SoundSystem.hpp
@author	Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
@date		15/11/2021
\brief
This file contain the declaration needed for sound system 

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H


#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"
#include "Engine/Header/Management/SoundManager.hpp"

#include <fmod/fmod.hpp>
#include <map>
#include <string>

namespace Engine {

	struct SoundSystem : public Singleton<SoundSystem>
	{

		/**
		*		BASICS
		*/
		void SoundInit();
		bool SoundUpdate();
		void SoundPlay(SoundComponent* soundCom, int channelID);
		void SoundPause(int channelID);
		void SoundUnpause(int channelD);
		void SoundStop(int channelID);
		
		void SoundSetVolume(int channelID, float _vol);
		float SoundGetVolume(int channelID, float _vol);


		SINGLETON_SETUP(SoundSystem);

	};
}

#endif
