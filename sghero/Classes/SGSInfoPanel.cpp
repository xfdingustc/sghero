#include "SGGlobalSettings.h"
#include "SGSInfoPanel.h"
#include "SGHeroResourceUtils.h"


bool SGSInfoPanel::init()
{
  std::string info_panel_bg = FileUtils::getInstance()->fullPathForFilename(INFO_PANEL_BACKGROUND);
  if (!Sprite::initWithFile(info_panel_bg)) {
    return false;
  }
  Size win_size = Director::getInstance()->getVisibleSize();
  this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
  setScale(GLOBAL_SCALE);

  setPosition(Vec2(win_size.width, 0.0f));

  rapidjson::Document text_json;
  std::string res_json_file = FileUtils::getInstance()->fullPathForFilename(HERO_INFO_TEXT_JSON_FILE);
  std::string json_data = FileUtils::getInstance()->getStringFromFile(res_json_file.c_str());

  text_json.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (text_json.HasParseError()) {
    log("Parsing hero info text json file error!! %s", text_json.GetParseError());
    return false;
  } else if (text_json.IsObject()) {
    const rapidjson::Value &res_list = text_json["Info"];
    if (res_list.IsArray()) {
      for (int i = 0; i < res_list.Size(); i++) {
        const rapidjson::Value &val = res_list[i];
        std::string name = val["name"].GetString();
        if (name == "force") {
          __force_text = val["text"].GetString();
        } else if (name == "command") {
          __command_text = val["text"].GetString();
        } else if (name == "intelligence") {
          __intelligence_text = val["text"].GetString();
        }else if (name == "agility") {
          __agility_text = val["text"].GetString();
        }else if (name == "luck") {
          __luck_text = val["text"].GetString();
        }
      }
    }

  }


  return true;
}


void SGSInfoPanel::showFirstHeroInfo(SGSHero* hero)
{
  char number[20];
  this->removeChildByName("first_hero");

  std::string hero_face_image = SGHeroResourceUtils::getInstance()->getHeroFaceImage(hero->getName());
  Sprite* hero_face = Sprite::create(hero_face_image);
  hero_face->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  Size size = this->getContentSize();
  hero_face->setScale(2);
  hero_face->setPosition(Vec2(size.width * 0.191, size.height * 0.75));
  hero_face->setName("first_hero");
  this->addChild(hero_face);

  // add force
  Label *force = Label::create(__force_text,TEXT_FONT_NAME, 30);
  force->setColor(Color3B::BLACK);
  force->setPosition(Vec2(size.width * 0.4335, size.height * 0.8125));
  this->addChild(force);

  std::string force_num;
  sprintf(number, "%d", hero->getForce());
  force_num = number;
  Label *force_text = Label::create(force_num,TEXT_FONT_NAME, 30);
  force_text->setColor(Color3B::BLACK);
  force_text->setPosition(Vec2(size.width * 0.5365, size.height * 0.8125));
  this->addChild(force_text);

  // add command
  Label *command = Label::create(__command_text,TEXT_FONT_NAME, 30);
  command->setColor(Color3B::BLACK);
  command->setPosition(Vec2(size.width * 0.6395,  size.height * 0.8125));
  this->addChild(command);

  std::string command_num;
  sprintf(number, "%d", hero->getCommand());
  command_num = number;
  Label *command_text = Label::create(command_num,TEXT_FONT_NAME, 30);
  command_text->setColor(Color3B::BLACK);
  command_text->setPosition(Vec2(size.width * 0.7425, size.height * 0.8125));
  this->addChild(command_text);

  // add intelligence
  Label *intelligence = Label::create(__intelligence_text,TEXT_FONT_NAME, 30);
  intelligence->setColor(Color3B::BLACK);
  intelligence->setPosition(Vec2(size.width * 0.8455, size.height * 0.8125));
  this->addChild(intelligence);

  std::string intelligence_num;
  sprintf(number, "%d", hero->getIntelligence());
  intelligence_num = number;
  Label *intelligence_text = Label::create(intelligence_num,TEXT_FONT_NAME, 30);
  intelligence_text->setColor(Color3B::BLACK);
  intelligence_text->setPosition(Vec2(size.width * 0.9485, size.height * 0.8125));
  this->addChild(intelligence_text);

  // add agility
  Label *agility = Label::create(__agility_text,TEXT_FONT_NAME, 30);
  agility->setColor(Color3B::BLACK);
  agility->setPosition(Vec2(size.width * 0.4335, size.height * 0.7));
  this->addChild(agility);

  std::string agility_num;
  sprintf(number, "%d", hero->getAgility());
  agility_num = number;
  Label *agility_text = Label::create(agility_num,TEXT_FONT_NAME, 30);
  agility_text->setColor(Color3B::BLACK);
  agility_text->setPosition(Vec2(size.width * 0.5365, size.height * 0.7));
  this->addChild(agility_text);

  // add luck
  Label *luck = Label::create(__luck_text,TEXT_FONT_NAME, 30);
  luck->setColor(Color3B::BLACK);
  luck->setPosition(Vec2(size.width * 0.6395, size.height * 0.7));
  this->addChild(luck);

  std::string luck_num;
  sprintf(number, "%d", hero->getLuck());
  luck_num = number;
  Label *luck_text = Label::create(luck_num,TEXT_FONT_NAME, 30);
  luck_text->setColor(Color3B::BLACK);
  luck_text->setPosition(Vec2(size.width * 0.7425, size.height * 0.7));
  this->addChild(luck_text);

  return;
}

