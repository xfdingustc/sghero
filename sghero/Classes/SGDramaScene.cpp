#include "SGDramaScene.h"
#include "SGDramaSceneHero.h"
#include "SGDramaSceneSelectScene.h"
#include "SGDramaSceneChapterScene.h"
#include "SGDramaSceneInfoScene.h"
#include "SGHeroResourceUtils.h"
#include "SGGlobalSettings.h"
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

  parseDramaSceneXmlFile("DramaScenes/DramaScene01.xml");
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

void SGDramaScene::formatString(std::string& str)
{
  // replace "\\n" to "\n"
  std::string::size_type pos = 0;
  std::string src_str = "\\n";
  std::string des_str = "\n";
  std::string::size_type srcLen = src_str.size();  
  std::string::size_type desLen = src_str.size();  
  while ((pos = str.find(src_str, pos)) != std::string::npos){
    str.replace( pos, srcLen, des_str );
    pos += desLen;
  }
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
  } else if (!strcmp(name, "Chapter")) {
    std::string chapter = event->Attribute("num");
    std::string title = event->Attribute("title");
    Scene* scene = SGDramaSceneChapterScene::createScene(chapter.c_str(), title.c_str());
    Director::getInstance()->pushScene(scene);
    event_list.pop_front();
  } else if (!strcmp(name, "Info")) {
    std::string info = event->Attribute("content");
    formatString(info);
    Scene* scene = SGDramaSceneInfoScene::createScene(info.c_str());
    Director::getInstance()->pushScene(scene);
    event_list.pop_front();
  } else if (!strcmp(name, "HeroFaceShow")) {
    onHandleEventHeroFaceShow(event);
  } else if (!strcmp(name, "MapInfoShow")) {
    onHandleEventMapInfoShow(event);
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
    
    SGDramaSceneHero* hero = (SGDramaSceneHero*)this->getChildByName(hero_name.c_str());
    if (hero) {
      hero->moveTo(convertCoordinate(Vec2(target_x,target_y)), direction.c_str());
    }
    event_list.pop_front();

  } else if (!strcmp(name, "HeroTurn")) {
    std::string hero_name = event->Attribute("hero");
    std::string direction = event->Attribute("face");
    SGDramaSceneHero* hero = (SGDramaSceneHero*)this->getChildByName(hero_name.c_str());
    if (hero) {
      hero->faceTo(direction.c_str());
    }
    event_list.pop_front();
  } else if (!strcmp(name, "HeroAction")) {
    std::string hero_name = event->Attribute("hero");
    std::string action = event->Attribute("action");
    SGDramaSceneHero* hero = (SGDramaSceneHero*)this->getChildByName(hero_name.c_str());
    if (hero) {
      hero->doAction(action.c_str());
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

    formatString(speak);

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

void SGDramaScene::onHandleEventHeroFaceShow(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  int x = atoi(event->Attribute("x"));
  int y = atoi(event->Attribute("y"));
  std::string hero_face_resource = SGHeroResourceUtils::getInstance()->getHeroResObj(hero_name.c_str())->face;

  Sprite* hero_face = Sprite::create(hero_face_resource);
  hero_face->setPosition(Vec2(x, y));
  hero_face->setName(hero_name);
  this->addChild(hero_face);
  __event_list.pop_front();
}
void SGDramaScene::onHandleEventMapInfoShow(tinyxml2::XMLElement* event)
{
  std::string content = event->Attribute("content");
  const char* page_change = event->Attribute("page_change");
  formatString(content);
  Size size = Director::getInstance()->getVisibleSize();
  LayerColor* map_info = (LayerColor*)this->getChildByName("MapInfoWin");
  if (!map_info) {
    map_info = LayerColor::create(Color4B(0, 0, 0, 100), size.width ,size.height * 0.2f);
    map_info->setAnchorPoint(Vec2::ZERO);
    map_info->setPosition(Vec2::ZERO);
    map_info->setName("MapInfoWin");
    this->addChild(map_info);
  }

  LabelTTF* content_text = (LabelTTF*)map_info->getChildByName("content");
  if (!content_text) {
    content_text = LabelTTF::create(content, TEXT_FONT_NAME, TEXT_FONT_SIZE);
    content_text->setColor(Color3B::WHITE);
    content_text->setAnchorPoint(Vec2(0.0f, 1.0f));
    Size size = map_info->getContentSize();
    content_text->setPosition(Vec2(size.width * 0.2f, size.height * 0.8f));
    content_text->setName("content");
    map_info->addChild(content_text);
  } else {
    if (!strcmp(page_change, "true")) {
      content_text->setString(content);
    } else {
      std::string new_string = content_text->getString();
      new_string.append(content);
      content_text->setString(new_string);
    }
  }
  __event_list.pop_front();
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