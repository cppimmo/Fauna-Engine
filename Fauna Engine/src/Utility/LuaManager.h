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
namespace Fuana
{
	
	class LuaManager
	{
	public:
		LuaManager();
		LuaManager(const LuaManager&) = delete;
		LuaManager& operator=(const LuaManager&) = delete;
		LuaManager(LuaManager&&) = delete;
		LuaManager&& operator=(LuaManager&&) = delete;
		~LuaManager();

		lua_State* GetState() const { return lua_state; }
		int GetGlobal(const std::string& name);
		int DoFile(const std::string& file_path);
		bool Check(int result, int stackLoc = -1);
		int Pop(int stackLoc = -1);
		int IsTable(int stackLoc = -1);
		
		bool IsNil();
		bool IsTable();
		bool IsUserData();
		bool IsUserData();
		bool IsCFunction();
		bool IsNumber();
		bool IsString();
		bool IsWString();
		bool IsConvertibleToNumber();
		bool IsConvertibleToString();
		bool IsConvertibleToWString();
		bool IsFunction();
		bool IsNone();
		bool IsLightUserData();
		bool IsBool();
		
		// Getters
		int GetInteger() const noexcept;
		float GetFloat() const noexcept;
		double GetDouble() const noexcept;
		std::string& GetString() const;
		std::wstring& GetWString() const;
		void* GetUserData() const;
		void* GetLightUserData() const;
		bool GetBool() const noexcept;
		
		// Setters
		void SetNil(const std::string& name);
		void SetBool(const std::string& name);
		void SetInteger(const std::string& name);
		void SetNumber(const std::string& name);
		void SetString(const std::string& name);
		void SetWString(const std::string& name);
		void SetUserData(const std::string& name);
		void SetLightUserData(const std::string& name);
		void SetObject(const std::string& name);
		
	private:
		lua_State* lua_state = nullptr;
	};

}


