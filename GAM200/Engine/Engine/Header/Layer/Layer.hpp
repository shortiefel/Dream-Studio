/* Start Header**********************************************************************************/
/*
@file    Layer.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file contain the Layer declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef LAYER_H
#define LAYER_H

class Event;

class Layer {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool OnEvent(Event& e) = 0;
//private:
//	bool isActive = true;
// instead can check if graphic component is active or not
};

#endif