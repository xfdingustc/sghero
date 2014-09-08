#include "SGDramaScene.h"
#include "SGDramaSceneHero.h"
#include "SGDramaSceneSelectScene.h"
#include "SimpleAudioEngine.h"
#include "xxhash/xxhash.h"

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
  startSceneScript(0.0f);
  __has_pending_event = false;
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
        __event_list.push_back(one_event);
        one_event = one_event->NextSiblingElement();
      }
      event = event->NextSiblingElement();
    }
    section = section->NextSiblingElement();
  }

  return true;

}

void SGDramaScene::parseDrameSceneSubEvents(tinyxml2::XMLElement* sub_event)
{
  SGDramaSceneEventList sub_event_list;
  tinyxml2::XMLElement* one_sub_event = sub_event->FirstChildElement();
  while(one_sub_event) {
    sub_event_list.push_back(one_sub_event);
    one_sub_event = one_sub_event->NextSiblingElement();
  }

  SGDramaSceneEventList::reverse_iterator reverse_iter = sub_event_list.rbegin();
  for (; reverse_iter != sub_event_list.rend(); reverse_iter++) {
    tinyxml2::XMLElement* one_sub_event = (tinyxml2::XMLElement*)(*reverse_iter);
    __event_list.push_front(one_sub_event);
  }
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

void SGDramaScene::update(float dt) {
  handleDramaSceneScriptEvent(__event_list);
}

void SGDramaScene::handleDramaSceneScriptEvent(SGDramaSceneEventList& event_list)
{
  // TODO: no event list, we need move to the next scene
  if (event_list.size() == 0) {
    return ;
  } 
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
    SimpleAudioEngine::getInstance()->playEffect(sound_effect, true);
    event_list.pop_front();
  } else if (!strcmp(name, "HeroAppear")) {
    std::string hero_name = event->Attribute("hero");
    int x = atoi(event->Attribute("x"));
    int y = atoi(event->Attribute("y"));
    SGDramaSceneHero* hero = SGDramaSceneHero::create(hero_name.c_str());
    hero->setAnchorPoint(Vec2(1.0f, 1.0f));
    hero->setPosition(convertCoordinate(Vec2(x,y)));
    this->addChild(hero);
    event_list.pop_front();
  } else if (!strcmp(name, "HeroMove")) {

	  std::string hero_name = event->Attribute("hero");
    std::string direction = event->Attribute("face");

	  int target_x = atoi(event->Attribute("x"));
	  int target_y = atoi(event->Attribute("y"));
    //CCLOG("hero move name = %s %d %d", hero_name.c_str(), target_x, target_y);

     
    SGDramaSceneHero* hero = (SGDramaSceneHero*)this->getChildByName(hero_name.c_str());
    if (hero) {
      hero->moveTo(convertCoordinate(Vec2(target_x,target_y)), direction.c_str());
    }
    event_list.pop_front();

  } else if (!strcmp(name, "Delay")) {
    float time = float(atoi(event->Attribute("time"))) * 0.5f;
    unscheduleUpdate();
    scheduleOnce(schedule_selector(SGDramaScene::startSceneScript), time);
    event_list.pop_front();
  } else if (!strcmp(name, "Dialog")) {
    std::string hero_name = event->Attribute("hero");
    std::string speak = event->Attribute("content");

    // replace "\\n" to "\n"
    std::string::size_type pos = 0;
    std::string src_str = "\\n";
    std::string des_str = "\n";
    std::string::size_type srcLen = src_str.size();  
    std::string::size_type desLen = src_str.size();  
    while ((pos = speak.find(src_str, pos)) != std::string::npos){
      speak.replace( pos, srcLen, des_str );
      pos += desLen;
    }

    CCLOG("%s said: %s", hero_name.c_str(), speak.c_str());
    SGDramaSceneHero* hero = (SGDramaSceneHero*)this->getChildByName(hero_name.c_str());
    if (hero) {
      hero->speak(speak.c_str());
    }
    event_list.pop_front();
  } else if (!strcmp(name, "SoundTrack")) {
    std::string track = event->Attribute("track");
    SimpleAudioEngine::getInstance()->playBackgroundMusic(track.c_str());
    event_list.pop_front();
  } else if (!strcmp(name, "Select")) {
    std::string hero_name = event->Attribute("hero");
    std::string content = event->Attribute("content");
    
    if (!__has_pending_event) {
      Scene* select_scene = SGDramaSceneSelectScene::creatScene(hero_name.c_str(), content.c_str(), &__ret_value);
      Director::getInstance()->pushScene(select_scene);
      __has_pending_event = true;
      return;
    }

    CCLOG("select here, ret = %d", __ret_value);
    std::string case_name;
    switch (__ret_value)
    {
    case 1:
      case_name = "Case1";
      break;
    case 2:
      case_name = "Case2";
      break;
    case 3:
      case_name = "Case3";
      break;
    default:
      break;
    }
    event_list.pop_front();
    
    tinyxml2::XMLElement* sub_event = event->FirstChildElement(case_name.c_str());
    parseDrameSceneSubEvents(sub_event);
    __has_pending_event = false;
    
  } else if (!strcmp(name, "ValueSet")) {
    std::string val_name = event->Attribute("val_name");
    int val = atoi(event->Attribute("val"));
    __internal_val_map[val_name] = val;
    event_list.pop_front();

  } else if (!strcmp(name, "ValueTest")) {
    std::string val_name = event->Attribute("val_name");
    int val_test = atoi(event->Attribute("val"));
    int val = __internal_val_map[val_name];
    if (val == val_test) {
      event_list.pop_front();
      parseDrameSceneSubEvents(event);
    } else {
      event_list.pop_front();
    }
  } else {
    event_list.pop_front();
  }
  
  
  
  
}

Vec2 SGDramaScene::convertCoordinate(Vec2 origin)
{
  Vec2 new_pos;
  
  float zero_x = 54;
  float zero_y = 95;

  float sina = 0.53f;
  float cosa = 0.848f;

  float scale = 10;

  new_pos.x = ((origin.x - zero_x) * sina - (origin.y - zero_y) * cosa) * scale;
  new_pos.y = ((zero_x - origin.x) * cosa + (zero_y - origin.y) * sina) * scale;

  //CCLOG("new pos = %f %f", new_pos.x, new_pos.y);
  return new_pos;
}

void SGDramaScene::startSceneScript(float dt)
{
  scheduleUpdate();
}