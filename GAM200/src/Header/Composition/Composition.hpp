/* Start Header**********************************************************************************/
/*!
\file Composition.hpp
\team name Dream Studio
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 13/05/2021
\brief
Composition.hpp: This header file defines the Game Object Composition class.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/
#pragma once

#include "../System/Message.hpp"
#include "../Serialization/Serialization.hpp"
#include "../Component/Component.hpp"

//Game object ID type
typedef unsigned int GOC_ID;

class GameObjectComposition
{
public:
	//create and destroy game object using Game Object factory class
	friend class Factory;

	//Message interface
	void SendMessage(Message* message);

	//getting Component
	GameComponent* GetComponent();

	//Initialization for all components
	void Initialize();


};
