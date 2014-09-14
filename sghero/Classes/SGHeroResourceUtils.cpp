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
    const rapidjson::Value &res_list = hero_res["Resource"];
    if (res_list.IsArray()) {
      for (int i = 0; i < res_list.Size(); i++) {
        const rapidjson::Value &val = res_list[i];
        SGHeroResourceObject* new_hero = new SGHeroResourceObject;
        new_hero->name = val["name"].GetString();
        if (val.HasMember("catagory")) {
          new_hero->catagory = val["catagory"].GetString();
        }
        if (val.HasMember("res_name")) {
          new_hero->res_name = val["res_name"].GetString();
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
