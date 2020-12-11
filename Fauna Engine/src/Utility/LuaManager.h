#pragma once

#include <string>
extern "C"
{
#include "../lua535/include/lua.h"
#include "../lua535/include/lauxlib.h"
#include "../lua535/include/lualib.h"
}

//#define TOP_OF_STACK int stackLoc = -1

class Log;

class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	static LuaManager& Get() { return instance; }
	lua_State* GetState() const { return lua_state; }
	int GetGlobal(const std::string& name);
	int DoFile(const std::string& file_path);
	bool Check(int result, int stackLoc = -1);
	int Pop(int stackLoc = -1);
	int IsTable(int stackLoc = -1);
private:
	static LuaManager instance;
	lua_State* lua_state;
};

LuaManager LuaManager::instance;
