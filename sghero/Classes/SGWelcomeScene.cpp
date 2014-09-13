#include "SGWelcomeScene.h"
#include "SGDramaScene.h"
#include "SGSkirmishScene.h"

USING_NS_CC;

Scene* SGWelcomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SGWelcomeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SGWelcomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto startNewGameItem = MenuItemImage::create(
                                           "StartNewGame.png",
                                           "StartNewGame.png",
                                           CC_CALLBACK_1(SGWelcomeScene::startNewGameCallback, this));
    
	  startNewGameItem->setPosition(Vec2(visibleSize.width / 2 ,
                                visibleSize.height / 2 + startNewGameItem->getContentSize().height));

    auto quickSkirmishItem = MenuItemImage::create("QuickSkirmish.png",
      "QuickSkirmish.png",
      CC_CALLBACK_1(SGWelcomeScene::quickSkirmishCallback, this));

    quickSkirmishItem->setPosition(Vec2(visibleSize.width / 2 ,  visibleSize.height / 2 ));


    auto endGameItem = MenuItemImage::create(
      "EndGame.png",
      "EndGame.png",
      CC_CALLBACK_1(SGWelcomeScene::menuCloseCallback, this));

    


    endGameItem->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 - endGameItem->getContentSize().height));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startNewGameItem, quickSkirmishItem, endGameItem,  NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    // add "WelcomeScene" splash screen"
    auto sprite = Sprite::create("WelcomeScene.png");

    sprite->setAnchorPoint(Vec2(0,0));

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(0,0));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void SGWelcomeScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void SGWelcomeScene::startNewGameCallback(Ref* pSender)
{
  auto drama_scene = SGDramaScene::createScene();
  Director::getInstance()->replaceScene(drama_scene);
}

void SGWelcomeScene::quickSkirmishCallback(Ref* pSender)
{
  auto skirmish_scene = SGSkirmishScene::createScene();
  Director::getInstance()->replaceScene(skirmish_scene);
}
