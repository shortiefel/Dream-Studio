#ifndef PHYSICMANAGER_H
#define PHYSICMANAGER_H

class PhysicManager {
public:
	static void Create();
	static void Get();
	static void Run();
	static void Destroy();
private:
	static PhysicManager* s_instance;
};

#endif