//Script.h
#pragma once
#include "Advanced2D.h"
#include "Includes.h"

namespace Advanced2D
{
	class Script
	{
		public:
			Script();
			Script(const std::string& filename);
			virtual ~Script();

			bool LoadScript(const std::string& scriptFile);
			const std::string GetGlobalString(const std::string& name)const;
			float GetGlobalNumber(const std::string& name)const;
			bool GetGlobalBoolean(const std::string& name)const;

			void SetGlobalString(const std::string& name,const std::string& value);
			void SetGlobalNumber(const std::string& name,float value);
			void SetGlobalBoolean(const std::string& name,bool value);

			void RunFunction(const std::string& name);

			
		private:
			lua_State* luaState;
	};
};