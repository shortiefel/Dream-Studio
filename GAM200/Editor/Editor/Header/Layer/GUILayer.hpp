/* Start Header**********************************************************************************/
/*
@file    GUILayer.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file contain the GUILayer declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GUILAYER_H
#define GUILAYER_H

#include "Engine/Header/Layer/Layer.hpp"

struct GLFWwindow;

class GUILayer : public Layer{
public:
	static bool Create(GLFWwindow* window, const char* glsl_version); 
	static void Destroy();
	inline static GUILayer* Get() { return m_instance; }

	virtual void Draw() override;
	virtual void Update() override;
	virtual bool OnEvent(Event& e) override;
private:
	static GUILayer* m_instance;
};

#endif