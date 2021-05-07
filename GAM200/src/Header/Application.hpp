#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.hpp"

class Application {
public:
	static void Create();
	static void Run();
	static void Destroy();

	~Application();
private:
	static Application* s_instance;
	static Window* window;

	Application() = default;
};

#endif