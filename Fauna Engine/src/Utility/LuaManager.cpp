#include "Utility/LuaManager.h"
#include "Utility/Log.h"

Fauna::LuaManager::LuaManager()
{
	lua_state = luaL_newstate();
}

Fauna::LuaManager::~LuaManager()
{
	lua_close(this->lua_state);
}

int Fauna::LuaManager::GetGlobal(const std::string& name)
{
	return 0;
}

int Fauna::LuaManager::DoFile(const std::string& file_path)
{
	return luaL_dofile(GetState(), file_path.c_str());
}

bool Fauna::LuaManager::Check(int result, int stackLoc)
{
	if (result != LUA_OK)
	{
		std::string errormsg = lua_tostring(this->lua_state, stackLoc);
		Fauna::Log::Get().DebugPrint(errormsg);
		return false;
	}
	return true;
}

int Fauna::LuaManager::Pop(int stackLoc)
{
	return 0;
}

int Fauna::LuaManager::IsTable(int stackLoc)
{
	return 0;
}
