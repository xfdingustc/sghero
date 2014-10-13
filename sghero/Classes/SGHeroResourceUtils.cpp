#include "SGHeroResourceUtils.h"
#include "SGGlobalSettings.h"
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;



static SGHeroResourceUtils* s_SharedHeroResourceUtils = NULL;


SGHeroResourceUtils* SGHeroResourceUtils::getInstance()
{
  if (!s_SharedHeroResourceUtils)
  {
    s_SharedHeroResourceUtils = new  SGHeroResourceUtils();
    s_SharedHeroResourceUtils->init();
  }

  return s_SharedHeroResourceUtils;
}

void SGHeroResourceUtils::init()
{
  rapidjson::Document hero_res;
  std::string res_json_file = FileUtils::getInstance()->fullPathForFilename(HERO_RESOURCE_JSON_FILE);
  std::string json_data = FileUtils::getInstance()->getStringFromFile(res_json_file.c_str());

  hero_res.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (hero_res.HasParseError()) {
    CCLOG("Parsing hero resource json file error!! %s", hero_res.GetParseError());
    return;
  } else if (hero_res.IsObject()) {
    const rapidjson::Value &res_list = hero_res["entities"];
    if (res_list.IsArray()) {
      for (int i = 0; i < res_list.Size(); i++) {
        const rapidjson::Value &entity = res_list[i];
        const rapidjson::Value &val = entity["entity"];
        SGHeroResourceObject* new_hero = new SGHeroResourceObject;
        new_hero->name = val["name"].GetString();
        log("parsing %s", new_hero->name.c_str());
        if (val.HasMember("category")) {
          new_hero->category = val["category"].GetString();
        }
        if (val.HasMember("res_name")) {
          new_hero->res_name = val["res_name"].GetString();
        }
        if (val.HasMember("force")) {
          new_hero->force = static_cast<int>(val["force"].GetDouble());
        }
        if (val.HasMember("command")) {
          new_hero->command = static_cast<int>(val["command"].GetDouble());
        }
        if (val.HasMember("intelligence")) {
          new_hero->intelligence = static_cast<int>(val["intelligence"].GetDouble());
        }
        if (val.HasMember("luck")) {
          new_hero->luck = static_cast<int>(val["luck"].GetDouble());
        }
        if (val.HasMember("hp")) {
          new_hero->hp = static_cast<int>(val["hp"].GetDouble());
        }
        if (val.HasMember("mp")) {
          new_hero->mp = static_cast<int>(val["mp"].GetDouble());
        }
        
        heroes_map.insert(HERO_MAP_TYPE::value_type(new_hero->name, new_hero));
      }
    }

  }
}

SGHeroResourceUtils::SGHeroResourceObject* SGHeroResourceUtils::getHeroResObj(std::string name)
{
  HERO_MAP_TYPE::iterator iter;
  iter = heroes_map.find(name);
  if (iter != heroes_map.end()) {
     return iter->second;
  }
  CCLOG("Cannot found resouce info for hero %s", name.c_str());
  return NULL;
}
