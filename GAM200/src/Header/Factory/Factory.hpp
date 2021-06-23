/* Start Header**********************************************************************************/
/*
@file    Factory.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
This file contain declaraction of Factory class with it functions

*/
/* End Header **********************************************************************************/

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Math/MathLib.hpp"

class Factory {
public:
	static void Create();
	static void InstantiateSquare(MathD::Vec2 pos = MathD::Vec2{ 0.f, 0.f }, MathD::Vec2 scale = MathD::Vec2{ 20.f, 20.f }, bool isMoveable = false);
	static void InstantiateCircle(MathD::Vec2 pos = MathD::Vec2{ 0.f, 0.f }, MathD::Vec2 scale = MathD::Vec2{ 20.f, 20.f }, bool isMoveable = false);
};

#endif