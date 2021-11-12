/* Start Header**********************************************************************************/
/*
@file    GraphicOptions.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    16/09/2021
\brief
This file has the graphic options


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRAPHIC_OPTIONS
#define GRAPHIC_OPTIONS

namespace Engine 
{
	enum class GraphicShape 
	{
		SQUARE = 0,
		CIRCLE
	};

	enum class GraphicShader 
	{
		DEFAULT = 0, // Game objects
		COLLISION,
		FONT_DRAW
	};
}

#endif