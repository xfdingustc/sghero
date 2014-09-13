#include "SGSkirmishScene.h"



Scene* SGSkirmishScene::createScene()
{
  Scene* scene = Scene::create();

  SGSkirmishScene* layer = SGSkirmishScene::create();

  scene->addChild(layer);

  return scene;
}


bool SGSkirmishScene::init()
{
  if (!Layer::init()) {
    return false;
  }

  parseSkirmishSceneXmlFile("Skirmish/YingChuanZhiZhan.xml");
  return true;
}

bool SGSkirmishScene::parseSkirmishSceneXmlFile(const char* file_name)
{
  tinyxml2::XMLDocument* skirmish_scene_xml = new tinyxml2::XMLDocument();
  if (NULL == skirmish_scene_xml) {
    return false;
  }


  tinyxml2::XMLError error = skirmish_scene_xml->LoadFile(file_name);
  if (tinyxml2::XML_SUCCESS != error) {
    return false;
  }

  tinyxml2::XMLElement* scene = skirmish_scene_xml->RootElement();
  tinyxml2::XMLElement* section = scene->FirstChildElement("Section");
  tinyxml2::XMLElement* settings = section->FirstChildElement();
  while (settings) {
    parseSkirmishSettings(settings);
    settings = settings->NextSiblingElement();
  }
  return true;
}

bool SGSkirmishScene::parseSkirmishSettings(tinyxml2::XMLElement* setting)
{
  const char* name = setting->Name();
  if (!strcmp(name, "Map")) {
    onHandleSettingMap(setting);
  }
  return true;
}

void SGSkirmishScene::onHandleSettingMap(tinyxml2::XMLElement* setting)
{
  std::string map = setting->Attribute("map");

  std::string map_full_path = FileUtils::getInstance()->fullPathForFilename(map);
  Sprite* bg_map = Sprite::create(map_full_path);
  bg_map->setAnchorPoint(Vec2(0.0f, 1.0f));
  Size size = Director::getInstance()->getVisibleSize();
  bg_map->setPosition(Vec2(0.0f, size.height));
  this->addChild(bg_map);
}