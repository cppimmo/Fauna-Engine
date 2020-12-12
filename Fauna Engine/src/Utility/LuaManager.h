#pragma once

#include <string>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

// LuaManager is a singlton that holds a single
// luaState for use when loading scripts. It
// may be useful to have more than one for multithreading.
class LuaManager
{
public:
	LuaManager();
	LuaManager(const LuaManager&) = delete;
	LuaManager& operator=(const LuaManager&) = delete;
	~LuaManager();

	static LuaManager& Get();
	lua_State* GetState() const { return lua_state; }
	int GetGlobal(const std::string& name);
	int DoFile(const std::string& file_path);
	bool Check(int result, int stackLoc = -1);
	int Pop(int stackLoc = -1);
	int IsTable(int stackLoc = -1);
private:
	lua_State* lua_state;
};
