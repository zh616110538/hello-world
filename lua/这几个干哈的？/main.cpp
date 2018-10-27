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
#include <ctime>
#include <stdio.h>
#include <list>
using namespace std;

list<pthread_t> l1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* fun1(void *arg)
{
    lua_State *Lold = (lua_State *)arg;
    lua_State *Lnew = luaL_newstate();
    luaL_openlibs(Lnew);
    int top = lua_gettop(Lold);
    luaL_checktype(Lold, 1, LUA_TFUNCTION);
    //lua_State *Lnew = lua_newthread(Lold);
    lua_pushvalue(Lold, 1);  /* move function to top */
    lua_xmove(Lold, Lnew, 1);  /* move function from L to NL */
    for (int i = 2; i <= top; i++) { /* repeat for each level */
	int t = lua_type(Lold, i);
	switch (t) {
	    case LUA_TSTRING: /* strings */
	    	lua_pushstring(Lnew,luaL_checkstring(Lold,i));
	    break;
	    case LUA_TBOOLEAN: /* booleans */
	    	//printf(lua_toboolean(L, i) ? "true" : "false");
	    	//lua_pushboolean(L,luaL_checkboolean(L,i));
	    break;
	    case LUA_TNUMBER: /* numbers */
	    	lua_pushnumber(Lnew,luaL_checknumber(Lold,i));
	    break;
	    default: /* other values */
	    	//printf("%s", lua_typename(L, t));
	    break;
	}
    }
    pthread_cond_signal(&cond);
    int error = lua_pcall(Lnew,top - 1,0,0);
    if(error){
	cerr<<lua_tostring(Lnew,-1)<<endl;
    }
    lua_close(Lnew);
    pthread_exit(0);
}

static int mythread(lua_State *L)
{
    pthread_t tid = 0;
    pthread_create(&tid,NULL,fun1,(void *)L);
    l1.push_back(tid);
    pthread_cond_wait(&cond,&lock);
    return 1;
}

/*
static int myjoin(lua_State *L)
{
    void *tret;
    pthread_t *tid = (pthread_t *)lua_touserdata(L,1);
    printf("tidj = %p\n",*tid);
    pthread_join(*tid,&tret);
    cout<<__func__<<"2"<<endl;
    return 0;
}



static int myadd(lua_State *L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1+op2);
    return 1;
}

static int mysub(lua_State *L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1-op2);
    return 1;
}

static int regestermylib(lua_State *L)
{
    luaL_Reg mylibs[]={
	{"myprint",myprint},
	{"myadd",myadd},
	{"mysub",mysub},
	{NULL,NULL}
    };
    luaL_newlib(L,mylibs);
    return 1;

}
*/
int main(int argc,char *argv[])
{
	if(argc<2 || argc >3){
	    cerr<<"error arguement"<<endl;
	    return 0;
	}
	void *tret;
	lua_State *L = NULL;
	L = luaL_newstate();
	if(L == NULL){
	    cerr<<"error"<<endl;
	    return 0;
	}
	luaL_openlibs(L);
	//luaL_requiref(L,"mylibs",regestermylib,1);
	lua_register(L,"mythread",mythread);
	//lua_register(L,"myjoin",myjoin);
	int error = luaL_loadfile(L,argv[1]);
	if(error){
	    cerr<<lua_tostring(L,-1)<<endl;
	    return 0;
	}
	clock_t start,end;
	start = clock();
	error = lua_pcall(L,0,0,0);
	end = clock();
	cout<<"run time is "<<(double)(end - start)<<"us"<<endl;
	if(error){
	    cerr<<lua_tostring(L,-1)<<endl;
	    pthread_exit(0);
	}
	sleep(1);
	while(l1.begin()!=l1.end())
	{
	    for(auto it = l1.begin();it != l1.end();++it)
	    {
		pthread_join(*it,&tret);
		it = l1.erase(it);
	    }
	}
	lua_close(L);
	pthread_exit(0);
}
