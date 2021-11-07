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

#include <fmod/fmod.hpp>

#include <string>
#include <map>

typedef std::map<std::string, FMOD::Sound*> SoundMap;



namespace Engine {


	class SoundComponent {

	public:
	

	};
}


#endif // !SOUND_COMPONENT_H

