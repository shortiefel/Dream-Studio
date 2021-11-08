/* Start Header**********************************************************************************/
/*
@file    SoundManager.cpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    08/11/2021
@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Sound/SoundManager.hpp"

namespace Engine {

	SoundManager::SoundManager() : currentSong(0), fade(FADE_NONE)
	{
		//init system
		FMOD::System_Create(&system);
		system->init(100, FMOD_INIT_NORMAL, 0);

		//Create channel group for each category
		system->getMasterChannelGroup(&master);
		for (int i{ 0 }; i < CATEGORY_COUNT; ++i)
		{
			system->createChannelGroup(0, &groups[i]);
			master->addGroup(groups[i]);
		}

		//set up modes for each catergory
		modes[CATEGORY_SFX] = FMOD_DEFAULT;
		modes[CATEGORY_SONG] = FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL;
	}

	SoundManager::~SoundManager()
	{
		//release sound for each cat
		SoundMap::iterator iter;
		for (int i{ 0 }; i < CATEGORY_COUNT; ++i)
		{
			for (iter = sounds[i].begin(); iter != sounds[i].end(); ++iter)
				iter->second->release();
			sounds[i].clear();
		}

		//release system
		system->release();
	}


}