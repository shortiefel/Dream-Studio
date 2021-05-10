#ifndef WINDOW_H
#define WINDOW_H

#include "pch.hpp"
#include "Event/Event.hpp"

class Window {
public:
	static Window* Create(const std::string& ttitle = "Cel", unsigned int twidth = 1280, unsigned int theight = 720);
	static void Destroy();
	static GLFWwindow* GetGLFWwindow();

	unsigned int GetWidth();
	unsigned int GetHeight();

	void OnUpdate();

	void SetEventCallBack(const std::function<void(Event&)> callback);

	
private:
	static GLFWwindow* glfw_window;
	static Window* s_instance;

	struct WinData {
		std::string title;
		unsigned int width, height;

		std::function<void(Event&)> eventCallBack;
	};

	WinData w_data;

	Window(const std::string& ttitle, unsigned int twidth, unsigned int theight);
};


#endif