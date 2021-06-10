/* Start Header**********************************************************************************/
/*!
\file Factory.cpp
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
Factory.cpp: This file defines a Game Object Factory system.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Factory.hpp"

Factory* GameObjectFactory = NULL;

//Factory constructor
Factory::Factory()
{
	//ErrorIf( GameObjectFactory != NULL, "Factory already created");

	//Creating Game Object Factory
	GameObjectFactory = this;
}

//Factory deconstructor
Factory::~Factory()
{
	//Delete all Game Object component 
}

void Factory::Update(float dt)
{
	//To delete all objects in the ObjectsToBeDelete list
}

//Destroy all Objects in the game
void Factory::DestroyAll()
{

}