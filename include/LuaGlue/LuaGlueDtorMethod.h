#ifndef LUAGLUE_DTOR_METHOD_H_GUARD
#define LUAGLUE_DTOR_METHOD_H_GUARD

#include <lua.hpp>
#include <string>
#include <tuple>
#include <utility>

#include "LuaGlue/LuaGlueApplyTuple.h"

class LuaGlue;
template<typename _Class>
class LuaGlueClass;

template<typename _Class>
class LuaGlueDtorMethod : public LuaGlueMethodBase
{
	public:
		typedef _Class ClassType;
		typedef void (_Class::*MethodType)();
		
		LuaGlueDtorMethod(LuaGlueClass<_Class> *luaClass, const std::string &name, MethodType &&fn) : glueClass(luaClass), name_(name), fn(std::forward<MethodType>(fn))
		{ }
		
		~LuaGlueDtorMethod() {}
		
		std::string name() { return name_; }
		
		bool glue(LuaGlue *luaGlue)
		{
			lua_pushlightuserdata(luaGlue->state(), this);
			lua_pushcclosure(luaGlue->state(), &lua_call_func, 1);
			lua_setfield(luaGlue->state(), -2, name_.c_str());
			return true;
		}
		
	private:
		LuaGlueClass<_Class> *glueClass;
		std::string name_;
		MethodType fn;
		
		int invoke(lua_State *state)
		{
			ClassType *obj = *(ClassType **)luaL_checkudata(state, 1, glueClass->name().c_str());
			(obj->*fn)();

			return 0;
		}
		
		static int lua_call_func(lua_State *state)
		{
			auto mimp = (LuaGlueDtorMethod<_Class> *)lua_touserdata(state, lua_upvalueindex(1));
			return mimp->invoke(state);
		}
};

#endif /* LUAGLUE_DTOR_METHOD_H_GUARD */
