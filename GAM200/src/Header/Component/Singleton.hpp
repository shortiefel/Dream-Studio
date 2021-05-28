#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
public:
	static void Create();
	static void Destroy();

	static Singleton* Get();
private:
	static Singleton* s_instance;
};

#endif