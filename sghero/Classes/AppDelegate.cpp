#include "AppDelegate.h"
#include "SGWelcomeScene.h"
#include "CCLuaEngine.h"
#include "SGGlobalSettings.h"
#include "lua-bindings/lua_sgshero_auto.hpp"
using namespace CocosDenshion;
using namespace std;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Èý¹úÓ¢ÐÛ´«Ææ");
        glview->setFrameSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    pEngine->addSearchPath(SG_LUA_SCRIPTS_PATH);
    register_all_SGSHero(pEngine->getLuaStack()->getLuaState());
    
    pEngine->executeScriptFile("DeprecatedEnum.lua");
    pEngine->executeScriptFile("DeprecatedClass.lua");
    pEngine->executeScriptFile("Deprecated.lua");
    pEngine->executeScriptFile("init_sg.lua");

    // create a scene. it's an autorelease object
    auto scene = SGWelcomeScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
