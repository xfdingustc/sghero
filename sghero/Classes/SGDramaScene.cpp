
#include "SGDramaScene.h"


USING_NS_CC;


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
        parseDrameSceneEvents(one_event);
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

  if(!strcmp(name, "HeroAppear")) {
    //const tinyxml2::XMLAttribute* attribute = event->Attribute("hero");
    const char* hero_name = event->Attribute("hero");
    CCLOG("hero name = %s", hero_name);
  } 
  return true;
}