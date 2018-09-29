#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <stack>
using namespace std;

stack<lua_State *> Lstack;

//usage of create table
//setfield and settable will call pop automatically,so is setglobal
void createtable(lua_State* L)
{
    lua_newtable(L);
	lua_pushstring(L,"Zhuhao");
	lua_setfield(L,-2,"name");
	lua_pushinteger(L,25);
	lua_setfield(L,-2,"age");
	lua_setglobal(L,"Person");
    //also can be writed as
//    lua_newtable(L);
//	lua_pushstring(L,"name");
//	lua_pushstring(L,"Zhuhao");
//	lua_settable(L,-3);
//	lua_pushstring(L,"age");
//	lua_pushinteger(L,25);
//	lua_settable(L,-3);
//	lua_setglobal(L,"Person");
}

void LUAHook(lua_State* L, lua_Debug *ar)
{
	//lua_getinfo(L, "S", ar);
    //cout<<ar->short_src<<" "<<ar->currentline<<endl;
    //CheckStack(L);
	//lua_yield(L, 0);
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int ret = luaL_dofile(L, "test.lua");
	if (ret != 0)
	{
		// Error loading script. Return.
		printf("luaL_dofile error \n");
		return -1;
	}

	// Add a count hook that will trigger after "count" number instructions
	//lua_sethook(L, LUAHook, LUA_MASKLINE, 0);//LUAHook will be called while event trigger
	lua_newtable(L);//make a table to save thread object
	Lstack.push(lua_newthread(L));//this calling will push a thread object into L stack
	int init = 1,index = 1,gc = 0;
	lua_rawseti(L, -2, index++);//push thread into table
	do{
		lua_getglobal(Lstack.top(), "heavy_function");//get the heavy_function
		lua_pushinteger(Lstack.top(),init);//push value into function

		ret = lua_resume(Lstack.top(),L,1);//the first parameter is new thread state,the second is the base state,the third is the number of parameters to push
		if(ret == LUA_YIELD)
		{
			init = luaL_checkinteger(Lstack.top(),-1);
			Lstack.push(lua_newthread(L));
			lua_rawseti(L, -2, index++);
			//lua_checkstack(L,10);//this api will make stack larger
			//cout<<"stack size : "<<lua_gettop(L)<<endl;
			//cout<<"Memory Usage:"<<lua_gc(L,LUA_GCCOUNT,0)<<endl;//print the memory size lua used
		}
		else if(ret == 0)
		{
			//lua_close(Lstack.top());
			if(gc++>100){
				lua_gc(L,LUA_GCCOLLECT,0);//this will collect garbage
				gc=0;
			}
            //free the thread
			lua_pushnil(L);
			lua_rawseti(L,-2,--index);

			Lstack.pop();
		}
		else{
			cout<<"error"<<endl;
			return -1;
		}
    }while(Lstack.size()>0);
	lua_settop (L, 0);//clean the stack
	lua_close(L);
	return 0;
}

