/* Start Header**********************************************************************************/
/*
@file    GUI.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    16/06/2021
\brief
This file contain the GUI declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GUI_H
#define GUI_H

struct GLFWwindow;

namespace Editor {
	class GUI {
	public:
		static bool Create(GLFWwindow* window, const char* glsl_version);
		static void Destroy();

		static void Update();
		static void Draw();

		static void SetGameFBO();
		static void SetSceneFBO();

	private:
		static GUI* m_instance;
		static unsigned int gameWinFBO, sceneWinFBO;
	};
}

#endif