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

	SoundComponent::SoundComponent(Entity_id _ID ,  std::string _filepath,  std::string _soundName ,bool _isSound , bool _isActive , bool _loop, float _vol, SoundGrp _soundType)
		: IComponent{ _ID }, filepath{ _filepath }, soundName{ _soundName } , isSound{ _isSound }, isActive{ _isActive }, loop{ _loop }, volume{ _vol }, soundType { _soundType }
	{
		
	}


	SoundComponent::~SoundComponent()
	{
		//Called by SoundManager
	}

	/**
	*		VOLUMES
	*		--- LOUD = 100.f ->1.f
	*		--- NORMAL = 50.f -> 0.5f
	*		--- SOFT = 20.f ->0.2f
	*/
	float SoundComponent::VolumeDecimal(float _vol)
	{
		if (_vol < 20.f)
			_vol = 20.f;
		else if (_vol >= 20.f && _vol <= 100.f)
			_vol = 50.f;
		else if (_vol > 100.f)
			_vol = 100.f;
		
		return _vol / 100.f;
			
	}

	float SoundComponent::DecimalVolume(float _vol)
	{
		return _vol * 100.f;
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
		_serializer.SetValue("SoundGroup", static_cast<int>(soundType));

	}

}