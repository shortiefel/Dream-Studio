#ifndef APPLICATION_H
#define APPLICATION_H

//Declaration of class and struct that are used in class Application function declaration
//header file need not know its data member yet since it is not used
class Event;
class WindowCloseEvent;
struct GLFWwindow;

class Application {
public:
	static void Create();
	static void Update();
	static void Destroy();

	~Application();

	void OnEvent(Event& event);
	void SetEventCallBack();

	bool OnWindowClose(WindowCloseEvent& e);
private:
	static Application* s_app_instance;
	//static GLFWwindow* s_glfw_window;
	static bool app_run_bool;

	Application() = default;
};

#endif