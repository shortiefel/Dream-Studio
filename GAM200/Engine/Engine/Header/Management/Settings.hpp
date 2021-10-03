/* Start Header**********************************************************************************/
/*
@file    Settings.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    11/09/2021
\brief
This file stores the data for window and game screen size


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef SETTINGS_H
#define SETTINGS_H

namespace Engine 
{
	struct Settings 
	{
		static unsigned int windowWidth;
		static unsigned int windowHeight;

		static unsigned int gameWidth;
		static unsigned int gameHeight;
		static float gameAR;
	};
}

#endif