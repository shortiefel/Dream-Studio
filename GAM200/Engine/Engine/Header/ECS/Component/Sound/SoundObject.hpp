/* Start Header**********************************************************************************/
/*
@file    SoundObject.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    09/11/2021
@brief

This file contains the declaration function for sound component with FMOD


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SOUND_OBJECT_H
#define SOUND_OBJECT_H

#include <fmod/fmod.hpp>
#include <string>
#include <map>

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine {

	class SoundObject : public IComponent {

		public:
			void PlayAudio(std::string filename);
			void StopAudio(std::string filename);
			void MuteAudio(std::string filename);
			void UnmuteAudio(std::string filename);
			void SetAudioVolume(std::string filename, float vol);
			void SetAudioLoop(std::string filename, bool isActive);


		private:
			bool isActive;
			bool loop = true;

	};

}

#endif