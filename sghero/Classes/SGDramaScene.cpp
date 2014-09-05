
#include "SGDramaScene.h"
#include "SGDramaSceneHero.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SGDramaScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = SGDramaScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

bool SGDramaScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }

  parseDramaSceneXmlFile("DramaScenes/DramaScene00.xml");
  scheduleUpdate();
  
  return true;
}


bool SGDramaScene::parseDramaSceneXmlFile(const char* file_name)
{
  tinyxml2::XMLDocument* drama_scene_xml = new tinyxml2::XMLDocument();
  if (NULL == drama_scene_xml) {
    return false;
  }


  tinyxml2::XMLError error = drama_scene_xml->LoadFile(file_name);
  if (tinyxml2::XML_SUCCESS != error) {
    return false;
  }


  tinyxml2::XMLElement* scene = drama_scene_xml->RootElement();
  tinyxml2::XMLElement* section = scene->FirstChildElement("Section");
  while(section) {
    tinyxml2::XMLElement* event = section->FirstChildElement("Event");
    while(event) {
      tinyxml2::XMLElement* one_event = event->FirstChildElement();
      while(one_event) {
        //parseDrameSceneEvents(one_event);
        event_list.push_back(one_event);
        one_event = one_event->NextSiblingElement();
      }
      event = event->NextSiblingElement();
    }
    section = section->NextSiblingElement();
  }

  return true;

}

bool SGDramaScene::parseDrameSceneEvents(tinyxml2::XMLElement* event)
{
  const char* name = event->Name();
  CCLOG("event name = %s", name);

  if (!strcmp(name, "BackgroundImage")) {
    const char* map_name = event->Attribute("image");
    auto bg_image = Sprite::create(map_name);
    bg_image->setAnchorPoint(Vec2(0,0));
    bg_image->setPosition(Vec2::ZERO);
    this->addChild(bg_image);

  } else if (!strcmp(name, "HeroAppear")) {
    //const tinyxml2::XMLAttribute* attribute = event->Attribute("hero");
    const char* hero_name = event->Attribute("hero");
    CCLOG("hero name = %s", hero_name);
  } 
  return true;
}

void SGDramaScene::update(float dt)
{
  tinyxml2::XMLElement* event = event_list.front();
  const char* name = event->Name();
  if (!strcmp(name, "BackgroundImage")) {
    const char* map_name = event->Attribute("image");
    auto bg_image = Sprite::create(map_name);
    bg_image->setAnchorPoint(Vec2(0,0));
    bg_image->setPosition(Vec2::ZERO);
    this->addChild(bg_image);
    event_list.pop_front();
  } else if (!strcmp(name, "SoundEffect")) {
    const char* sound_effect = event->Attribute("effect");
    SimpleAudioEngine::sharedEngine()->playEffect(sound_effect);
    event_list.pop_front();
  } else if (!strcmp(name, "HeroAppear")) {
    const char* hero_name = event->Attribute("hero");
    int x = atoi(event->Attribute("x"));
    int y = atoi(event->Attribute("y"));
    SGDramaSceneHero* hero = SGDramaSceneHero::create(hero_name);
    hero->setAnchorPoint(Vec2(1.0f, 1.0f));

    hero->setPosition(convertCoordinate(Vec2(x,y)));
    this->addChild(hero);
    event_list.pop_front();
  }
}

Vec2 SGDramaScene::convertCoordinate(Vec2 origin)
{
  Vec2 new_pos;
  Size visibleSize = Director::getInstance()->getVisibleSize();
  new_pos.x = visibleSize.width - (origin.x - 35) * 38.4f;
  new_pos.y = visibleSize.height - (origin.y - 5) * 28.8f;
  return new_pos;
}