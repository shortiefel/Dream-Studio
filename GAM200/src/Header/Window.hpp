#ifndef WINDOW_H
#define WINDOW_H

#include "pch.hpp"
#include "Event/Event.hpp"



class Window {
public:
	static bool Create(const std::string& ttitle = "Cel", unsigned int twidth = 1280, unsigned int theight = 720);
	static void Destroy();
	static GLFWwindow* GetGLFWwindow();

	static unsigned int GetWidth();
	static unsigned int GetHeight();

	static void OnUpdate();

	static void SetEventCallBack(const std::function<void(Event&)> callback);

	
private:
	struct WinData {
		std::string title;
		unsigned int width, height;

		std::function<void(Event&)> eventCallBack;
	};

	static GLFWwindow* glfw_window;
	//static Window* s_instance;

	static WinData w_data;

	Window(const std::string& ttitle, unsigned int twidth, unsigned int theight);
};


#endif