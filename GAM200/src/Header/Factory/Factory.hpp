/* Start Header**********************************************************************************/
/*!
\file Factory.hpp
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
Factory.hpp: This header file defines a Game Object Factory system.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/
#pragma once

#include "../pch.hpp"
#include "../System/System.hpp"
#include "../Composition/Composition.hpp"

#ifndef FACTORY_H
#define FACTORY_H

class Factory : public System
{
private:

public:
	Factory();
	~Factory();

	//Create intialize and ID from data file.
	GOC* Create_ID(const std::string& filename);

	//Add GOC to the destroy list
	void Destroy(GOC* GameObject);

	//Update the game object factory, destroying used objects
	virtual void Update(float dt);

	//Name of the system
	virtual std::string GetName() { return "Game Object Factory"; }

	//Message Interface
	virtual void SendMessage(Message* message);

	//Destroy all the Game Componenets in the game.
	void DestroyAll();

private:
	//Objects to be deleted
	std::set<GOC*> Objects_TBD;

};

extern Factory* GameObjectFactory;

#endif