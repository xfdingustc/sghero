#include "lua_sgshero_auto.hpp"
#include "SGSHero.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_SGSHero_SGSHero_moveTo(lua_State* tolua_S)
{
    int argc = 0;
    SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_moveTo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        SGSPoint* arg0;

        ok &= luaval_to_object<SGSPoint>(tolua_S, 2, "SGSPoint",&arg0);
        if(!ok)
            return 0;
        cobj->moveTo(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "moveTo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_moveTo'.",&tolua_err);
#endif

    return 0;
}
