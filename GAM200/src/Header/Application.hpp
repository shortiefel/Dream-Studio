#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.hpp"
#include "Event/EventDispatcher.hpp"

class Application {
public:
	static void Create();
	static void Run();
	static void Destroy();

	~Application();

	void OnEvent(Event& event);
	void SetEventCallBack();

	bool OnWindowClose(WindowCloseEvent& e);
private:
	static Application* s_instance;
	static Window* window;
	static bool app_run_bool;

	Application() = default;
};

#endif