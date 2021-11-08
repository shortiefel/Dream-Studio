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

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {

	SoundComponent::SoundComponent(const std::string _path, bool _isActive) : path {_path}, isActive{_isActive}
	{
		FMOD::System_Create(&system);
		system->init(100, FMOD_INIT_NORMAL, 0);
	}

	SoundComponent::~SoundComponent()
	{
		//release sound to clear map
		SoundMap::iterator iter;

		for (iter = sounds.begin(); iter != sounds.end(); ++iter)
			iter->second->release();
		sounds.clear();

		//release the system object
		system->release();
		system = 0;
	}

	void SoundComponent::Update(float elapsed)
	{
		system->update();
	}

	void SoundComponent::Play(const std::string& _path)
	{
		

		//search for match sound
		SoundMap::iterator sound = sounds.find(_path);

		//ignore if no sound found
		if (sound == sounds.end())
			return;

		//if got sound, play
		system->playSound(soundN, channelGp, false, &channel);
	}

	void SoundComponent::LoadStream(const std::string& _path, bool _isActive)
	{
		//error check
		if (sounds.find(_path) != sounds.end())
			return;

		//load file into sound object
		FMOD::Sound* sound;
		if (_isActive)
			system->createStream(path.c_str(), FMOD_DEFAULT, 0, &sound);
		else
			system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);
		
		//storing of sound object in map
		sounds.insert(std::make_pair(_path, sound));
	}

	void SoundComponent::Load(const std::string& _path)
	{
		LoadStream(path, false);
	}

	void SoundComponent::Stream(const std::string& _path)
	{
		LoadStream(path, true);
	}

	SoundComponent& SoundComponent::Deserialize(const DSerializer& _serializer)
	{
		SoundComponent::LoadStream (_serializer.GetValue<std::string>("Filepath"), _serializer.GetValue<bool>("IsActive"));

		return *this;
	}

	void SoundComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", path);
		_serializer.SetValue("IsActive", isActive);
	}
	
}