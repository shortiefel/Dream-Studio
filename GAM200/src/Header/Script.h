#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//just putting RapidJson includes to see if it working
typedef JSONDOC;

class Script
{
private:
	std::string mID;
	std::vector<std::string> mParameters;
public:
	Script() {};
	Script(const Script& src);
	Script(const std::string& input_str);

	const std::string& Get_ID() const {return mID;}
	const std::vector<std::string>& GetParameters() const {return mParameters;}


	//Called After System is Initialized
	bool Script_Initialize(void);

	//Called every frame
	void Script_Update(float dt);
};

typedef std::vector<Script> ScriptInfo;

void LoadLevelFile(int* mapData, const std::string& filename);
void WriteLevelFile(int* mapData, const std::string& filename, int width, int height);

//Functions

//Load a Script.
Script LoadFileInfo(const std::string& filename);

//Parse a JSON Script.
void GetJSONObject(JSONDOC* doc, const std::string& filename);