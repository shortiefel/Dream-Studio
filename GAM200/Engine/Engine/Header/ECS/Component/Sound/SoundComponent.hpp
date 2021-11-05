/* Start Header**********************************************************************************/
/*
@file    SoundComponent.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include "Engine/Header/ECS/Component/Sound/SoundImplementation.hpp"

namespace Engine {


	class SoundComponent {
		public:
			static void Init();
			static void Soundget();
			static void Shutdown();
			static int ErrorCheck(FMOD_RESULT result);

			void LoadSound(const std::string& soundName, bool b3d = true, bool bLooping = false, bool bStream = false);
			void UnLoadSound(const std::string& soundName);
			int PlaySounds(const std::string& soundName, const Engine::DreamMath::vec3& vPos = Engine::DreamMath::vec3{ 0, 0, 0 }, float fVolumedB = 0.0f);
			void StopChannel(int nChannelId);
			float dbToVolume(float dB);
			float VolumeTodB(float volume);
			FMOD_VECTOR VectorToFmod(const Engine::DreamMath::vec3& vPosition);


		
	};
}


#endif // !SOUND_COMPONENT_H

