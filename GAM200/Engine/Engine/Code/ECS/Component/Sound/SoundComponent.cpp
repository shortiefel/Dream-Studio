/* Start Header**********************************************************************************/
/*
@file			SoundComponent.cpp
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
#include <stdexcept>

#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"
#include "Engine/Header/Management/SoundManager.hpp"

namespace Engine {

	SoundComponent::SoundComponent(Entity_id _ID, std::string _filepath, std::string _soundName, bool _isSound, bool _isActive, bool _loop, float _vol, SoundGrp _soundType, bool _isMute)
		: IComponent{ _ID }, filepath{ _filepath }, soundName{ _soundName }, isSound{ _isSound }, isActive{ _isActive }, loop{ _loop }, volume{ _vol }, soundType{ _soundType }, isMute{_isMute}
	{

	}


	SoundComponent::~SoundComponent()
	{
		//Called by SoundManager
	}


	float SoundComponent::GetVolume(float _vol) 
	{
		return volume;
	}

	float SoundComponent::SetVolume(float _vol)
	{
		volume = _vol < 0.0f ? 0.0f : _vol;
		return volume;
	}


	SoundComponent& SoundComponent::Deserialize(const DSerializer& _serializer)
	{
		//SoundGrp(_serializer.GetValue<int>("SoundGrpType"));
		isActive = _serializer.GetValue<bool>("IsActive");
		loop = _serializer.GetValue<bool>("IsLoop");
		//Pause = _serializer.GetValue<bool>("IsPause");
		filepath = _serializer.GetValue<std::string>("filepath");
		soundName = filepath.substr(filepath.find_last_of("\\") + 1);
		soundName = soundName.substr(0, soundName.find_last_of("."));

		//SoundManager::GetInstance().GetSound(filepath, soundName);
		volume = _serializer.GetValue<float>("volume");
		isSound = _serializer.GetValue<bool>("isSound");
		isMute = _serializer.GetValue<bool>("isMute");
		soundType = static_cast<SoundGrp>(_serializer.GetValue<int>("SoundGroup"));


		return *this;
	}

	void SoundComponent::Serialize(const SSerializer& _serializer)
	{
		//_serializer.SetValue("SoundGrpType", (int)_SG);
		_serializer.SetValue("IsActive", isActive);
		_serializer.SetValue("IsLoop", loop);
		//_serializer.SetValue("IsPause", Pause);
		_serializer.SetValue("filepath", filepath);
		//std::cout << "filepath: " << filepath << "\n";
		_serializer.SetValue("volume", volume);
		_serializer.SetValue("isSound", isSound);
		_serializer.SetValue("isMute", isMute);
		_serializer.SetValue("SoundGroup", static_cast<int>(soundType));


	}

}