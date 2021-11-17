/* Start Header**********************************************************************************/
/*
@file    Settings.cpp
@author  Chia Yi Da		c.yida@digipen.edu		100%
@date    11/09/2021
\brief
This file stores the data for window and game screen size


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Management/Settings.hpp"

namespace Engine
{
	unsigned int Settings::windowWidth;
	unsigned int Settings::windowHeight;

	unsigned int Settings::gameWidth;
	unsigned int Settings::gameHeight;
	float Settings::gameAR;

	std::string Settings::defaultCircle;
	std::string Settings::defaultSquare;
}