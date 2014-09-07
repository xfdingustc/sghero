#include "SGDramaSceneHeroSpeakScene.h"

USING_NS_CC;


Scene* SGDramaSceneHeroSpeakScene::creatScene()
{
  Scene* scene = Scene::create();

  SGDramaSceneHeroSpeakScene* speak_layer = SGDramaSceneHeroSpeakScene::create();
  Size win_size = Director::getInstance()->getWinSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 

  speak_layer->addChild(render_texture);

  scene->addChild(speak_layer);

  

  return scene;
}


bool SGDramaSceneHeroSpeakScene::init()
{
  if (!Layer::init()) {
    return false;
  }

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  event_listener = EventListenerTouchOneByOne::create();
  event_listener->onTouchBegan = CC_CALLBACK_2(SGDramaSceneHeroSpeakScene::onTouchBegin, this);
  event_listener->setSwallowTouches(true);
  dispatcher->addEventListenerWithSceneGraphPriority(event_listener,this);
  return true;
}

bool SGDramaSceneHeroSpeakScene::onTouchBegin(Touch *touch, Event *unused_event)
{
  Director::getInstance()->getEventDispatcher()->removeEventListener(event_listener);
  Director::getInstance()->popScene();
  return true;
}

