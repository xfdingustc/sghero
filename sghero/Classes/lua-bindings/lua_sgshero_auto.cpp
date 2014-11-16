#include "lua_sgshero_auto.hpp"
#include "SGSHero.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_SGSHero_SGSHero_moveTo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

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
int lua_SGSHero_SGSHero_getStatus(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getStatus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getStatus();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getStatus",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getStatus'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_initAttackActions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_initAttackActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->initAttackActions();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initAttackActions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_initAttackActions'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getcategory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getcategory'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getcategory();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getcategory",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getcategory'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getStrength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getStrength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getStrength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getStrength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getStrength'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_doAttackAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_doAttackAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->doAttackAction();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "doAttackAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_doAttackAction'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getLuck(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getLuck'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLuck();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLuck",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getLuck'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getRelativeDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getRelativeDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SGSHero* arg0;

        ok &= luaval_to_object<cocos2d::SGSHero>(tolua_S, 2, "cc.SGSHero",&arg0);
        if(!ok)
            return 0;
        int ret = (int)cobj->getRelativeDirection(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRelativeDirection",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getRelativeDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_isRival(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_isRival'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SGSHero* arg0;

        ok &= luaval_to_object<cocos2d::SGSHero>(tolua_S, 2, "cc.SGSHero",&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->isRival(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isRival",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_isRival'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_setActionFinishedCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_setActionFinishedCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        cobj->setActionFinishedCallback(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setActionFinishedCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_setActionFinishedCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getWalkAnimate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getWalkAnimate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SGSHero::HERO_DIRECTION arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cocos2d::Animate* ret = cobj->getWalkAnimate(arg0);
        object_to_luaval<cocos2d::Animate>(tolua_S, "cc.Animate",(cocos2d::Animate*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getWalkAnimate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getWalkAnimate'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_setDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_setDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SGSHero::HERO_DIRECTION arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setDirection(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDirection",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_setDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getAI(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getAI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getAI();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getAI'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_oneAIMove(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_oneAIMove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::function<void ()> arg0;
        cocos2d::SGSTerrain* arg1;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

        ok &= luaval_to_object<cocos2d::SGSTerrain>(tolua_S, 3, "cc.SGSTerrain",&arg1);
        if(!ok)
            return 0;
        cobj->oneAIMove(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "oneAIMove",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_oneAIMove'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_moveOneStepFinished(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_moveOneStepFinished'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        void* arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        #pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->moveOneStepFinished(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "moveOneStepFinished",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_moveOneStepFinished'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getIntelligence(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getIntelligence'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getIntelligence();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIntelligence",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getIntelligence'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_setStatus(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_setStatus'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::SGSHero::HERO_STATUS arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

            if (!ok) { break; }
            cobj->setStatus(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            cobj->setStatus(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setStatus",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_setStatus'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::SGSHero::HERO_SIDE arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        bool ret = cobj->init(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_init'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_setActive(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_setActive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setActive(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setActive",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_setActive'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_attackActionFinished(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_attackActionFinished'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        void* arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        #pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->attackActionFinished(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "attackActionFinished",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_attackActionFinished'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_initDataNum(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_initDataNum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initDataNum();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initDataNum",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_initDataNum'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_setTerrain(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_setTerrain'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SGSTerrain* arg0;

        ok &= luaval_to_object<cocos2d::SGSTerrain>(tolua_S, 2, "cc.SGSTerrain",&arg0);
        if(!ok)
            return 0;
        cobj->setTerrain(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTerrain",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_setTerrain'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_initActions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_initActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->initActions();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initActions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_initActions'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getSide(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getSide'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getSide();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSide",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getSide'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_update'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_attackHero(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_attackHero'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SGSHero* arg0;

        ok &= luaval_to_object<cocos2d::SGSHero>(tolua_S, 2, "cc.SGSHero",&arg0);
        if(!ok)
            return 0;
        cobj->attackHero(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "attackHero",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_attackHero'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_setAI(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_setAI'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            cobj->setAI(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::SGSHero::HERO_AI arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

            if (!ok) { break; }
            cobj->setAI(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAI",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_setAI'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_initCategory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_initCategory'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initCategory();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initCategory",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_initCategory'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_initSpecActions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_initSpecActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->initSpecActions();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSpecActions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_initSpecActions'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_faceTo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_faceTo'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::SGSHero::HERO_DIRECTION arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

            if (!ok) { break; }
            cobj->faceTo(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            cobj->faceTo(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "faceTo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_faceTo'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_isActive(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_isActive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isActive();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isActive",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_isActive'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getStamina(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getStamina'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getStamina();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getStamina",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getStamina'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getAgility(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getAgility'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAgility();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAgility",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getAgility'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getAttackAnimate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getAttackAnimate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Animate* ret = cobj->getAttackAnimate();
        object_to_luaval<cocos2d::Animate>(tolua_S, "cc.Animate",(cocos2d::Animate*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttackAnimate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getAttackAnimate'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_getCommand(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_getCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getCommand();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCommand",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_getCommand'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_doAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_doAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->doAction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "doAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_doAction'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_moveOneStep(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_moveOneStep'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<SGSPoint, std::allocator<SGSPoint> >* arg0;

        ok &= luaval_to_object<std::vector<SGSPoint, std::allocator<SGSPoint> >>(tolua_S, 2, "std::vector<SGSPoint, std::allocator<SGSPoint> >*",&arg0);
        if(!ok)
            return 0;
        cobj->moveOneStep(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "moveOneStep",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_moveOneStep'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_counterAttackFinished(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SGSHero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SGSHero_SGSHero_counterAttackFinished'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        void* arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        #pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->counterAttackFinished(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "counterAttackFinished",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_counterAttackFinished'.",&tolua_err);
#endif

    return 0;
}
int lua_SGSHero_SGSHero_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SGSHero",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        const char* arg0;
        cocos2d::SGSHero::HERO_SIDE arg1;
        SGObserver* arg2;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        ok &= luaval_to_object<SGObserver>(tolua_S, 4, "SGObserver",&arg2);
        if(!ok)
            return 0;
        cocos2d::SGSHero* ret = cocos2d::SGSHero::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::SGSHero>(tolua_S, "cc.SGSHero",(cocos2d::SGSHero*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_create'.",&tolua_err);
#endif
    return 0;
}
int lua_SGSHero_SGSHero_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SGSHero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        SGObserver* arg0;

        ok &= luaval_to_object<SGObserver>(tolua_S, 2, "SGObserver",&arg0);
        if(!ok)
            return 0;
        cobj = new cocos2d::SGSHero(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SGSHero");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SGSHero",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_SGSHero_SGSHero_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_SGSHero_SGSHero_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SGSHero)");
    return 0;
}

int lua_register_SGSHero_SGSHero(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SGSHero");
    tolua_cclass(tolua_S,"SGSHero","cc.SGSHero","SGSObj",nullptr);

    tolua_beginmodule(tolua_S,"SGSHero");
        tolua_function(tolua_S,"new",lua_SGSHero_SGSHero_constructor);
        tolua_function(tolua_S,"moveTo",lua_SGSHero_SGSHero_moveTo);
        tolua_function(tolua_S,"getStatus",lua_SGSHero_SGSHero_getStatus);
        tolua_function(tolua_S,"initAttackActions",lua_SGSHero_SGSHero_initAttackActions);
        tolua_function(tolua_S,"getcategory",lua_SGSHero_SGSHero_getcategory);
        tolua_function(tolua_S,"getStrength",lua_SGSHero_SGSHero_getStrength);
        tolua_function(tolua_S,"doAttackAction",lua_SGSHero_SGSHero_doAttackAction);
        tolua_function(tolua_S,"getLuck",lua_SGSHero_SGSHero_getLuck);
        tolua_function(tolua_S,"getRelativeDirection",lua_SGSHero_SGSHero_getRelativeDirection);
        tolua_function(tolua_S,"isRival",lua_SGSHero_SGSHero_isRival);
        tolua_function(tolua_S,"setActionFinishedCallback",lua_SGSHero_SGSHero_setActionFinishedCallback);
        tolua_function(tolua_S,"getWalkAnimate",lua_SGSHero_SGSHero_getWalkAnimate);
        tolua_function(tolua_S,"setDirection",lua_SGSHero_SGSHero_setDirection);
        tolua_function(tolua_S,"getAI",lua_SGSHero_SGSHero_getAI);
        tolua_function(tolua_S,"oneAIMove",lua_SGSHero_SGSHero_oneAIMove);
        tolua_function(tolua_S,"moveOneStepFinished",lua_SGSHero_SGSHero_moveOneStepFinished);
        tolua_function(tolua_S,"getIntelligence",lua_SGSHero_SGSHero_getIntelligence);
        tolua_function(tolua_S,"setStatus",lua_SGSHero_SGSHero_setStatus);
        tolua_function(tolua_S,"init",lua_SGSHero_SGSHero_init);
        tolua_function(tolua_S,"setActive",lua_SGSHero_SGSHero_setActive);
        tolua_function(tolua_S,"attackActionFinished",lua_SGSHero_SGSHero_attackActionFinished);
        tolua_function(tolua_S,"initDataNum",lua_SGSHero_SGSHero_initDataNum);
        tolua_function(tolua_S,"setTerrain",lua_SGSHero_SGSHero_setTerrain);
        tolua_function(tolua_S,"initActions",lua_SGSHero_SGSHero_initActions);
        tolua_function(tolua_S,"getSide",lua_SGSHero_SGSHero_getSide);
        tolua_function(tolua_S,"update",lua_SGSHero_SGSHero_update);
        tolua_function(tolua_S,"attackHero",lua_SGSHero_SGSHero_attackHero);
        tolua_function(tolua_S,"setAI",lua_SGSHero_SGSHero_setAI);
        tolua_function(tolua_S,"initCategory",lua_SGSHero_SGSHero_initCategory);
        tolua_function(tolua_S,"initSpecActions",lua_SGSHero_SGSHero_initSpecActions);
        tolua_function(tolua_S,"faceTo",lua_SGSHero_SGSHero_faceTo);
        tolua_function(tolua_S,"isActive",lua_SGSHero_SGSHero_isActive);
        tolua_function(tolua_S,"getStamina",lua_SGSHero_SGSHero_getStamina);
        tolua_function(tolua_S,"getAgility",lua_SGSHero_SGSHero_getAgility);
        tolua_function(tolua_S,"getAttackAnimate",lua_SGSHero_SGSHero_getAttackAnimate);
        tolua_function(tolua_S,"getCommand",lua_SGSHero_SGSHero_getCommand);
        tolua_function(tolua_S,"doAction",lua_SGSHero_SGSHero_doAction);
        tolua_function(tolua_S,"moveOneStep",lua_SGSHero_SGSHero_moveOneStep);
        tolua_function(tolua_S,"counterAttackFinished",lua_SGSHero_SGSHero_counterAttackFinished);
        tolua_function(tolua_S,"create", lua_SGSHero_SGSHero_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::SGSHero).name();
    g_luaType[typeName] = "cc.SGSHero";
    g_typeCast["SGSHero"] = "cc.SGSHero";
    return 1;
}
TOLUA_API int register_all_SGSHero(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_SGSHero_SGSHero(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

