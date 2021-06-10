#pragma once

#include "../System/Message.hpp"
#include "../Serialization/Serialization.hpp"

//Forward declaration of GameObjectComposition class
class GameObjectComposition;
//short name for GameObjectComposition
typedef GameObjectComposition GOC;

class GameComponent
{
public:
	friend class GameObjectComposition;
};
