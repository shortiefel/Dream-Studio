/* Start Header**********************************************************************************/
/*
@file    SoundImplementation.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SOUND_IMPLEMENTATION_H
#define SOUND_IMPLEMENTATION_H

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#include <fmod/fmod_common.h>
#include <fmod/fmod_output.h>
#include <fmod/fmod_studio.hpp>

#include <map>

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine {

	class SoundImplementation : public IComponent {

		public:
			SoundImplementation();
			~SoundImplementation();

			FMOD::Studio::System* fmodStudioSystem;
			FMOD::System* fmodSystem;

			void Update();

			typedef std::map<std::string, FMOD::Sound*> soundMap;
			typedef std::map<int, FMOD::Channel*> channelMap;
			soundMap sMap;
			channelMap cMap;
			int channelID;
	};

	extern SoundImplementation* soundImplementation;
}



#endif