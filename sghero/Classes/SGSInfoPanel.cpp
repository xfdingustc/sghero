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

  Size panel_size = this->getContentSize();
  __top_half = Layer::create();
  __top_half->setContentSize(Size(panel_size.width, panel_size.height/2));

  __top_half->setAnchorPoint(Vec2::ZERO);
  __top_half->setPosition(Vec2(0.0f, panel_size.height/2));
  this->addChild(__top_half);

  __bottom_half = Layer::create();
  __bottom_half->setContentSize(Size(panel_size.width, panel_size.height/2));
  __bottom_half->setAnchorPoint(Vec2::ZERO);
  __bottom_half->setPosition(Vec2::ZERO);
  this->addChild(__bottom_half);

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

  showHeroInfo(__top_half, hero);
  return;
}

void SGSInfoPanel::showSecondHeroInfo(SGSHero* hero)
{
  showHeroInfo(__bottom_half, hero);
  return;
}


void SGSInfoPanel::showHeroInfo(Layer* layer, SGSHero* hero)
{
  char number[20];

  layer->removeAllChildren();

  std::string hero_face_image = SGHeroResourceUtils::getInstance()->getHeroFaceImage(hero->getName());
  Sprite* hero_face = Sprite::create(hero_face_image);
  hero_face->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  Size size = layer->getContentSize();
  hero_face->setScale(2);
  hero_face->setPosition(Vec2(size.width * 0.15, size.height * 0.5));
  layer->addChild(hero_face);

  const int font_size = 30;

  // add force
  Label *force = Label::create(__force_text,TEXT_FONT_NAME, font_size);
  force->setColor(Color3B::BLACK);
  force->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  force->setPosition(Vec2(size.width * 0.3, size.height * 0.7));
  layer->addChild(force);

  std::string force_num;
  sprintf(number, "%d", hero->getStrength());
  force_num = number;
  Label *force_text = Label::create(force_num,TEXT_FONT_NAME, font_size);
  force_text->setColor(Color3B::BLACK);
  force_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  force_text->setPosition(Vec2(size.width * 0.475, size.height * 0.7));
  layer->addChild(force_text);

  // add command
  Label *command = Label::create(__command_text,TEXT_FONT_NAME, font_size);
  command->setColor(Color3B::BLACK);
  command->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  command->setPosition(Vec2(size.width * 0.65,  size.height * 0.7));
  layer->addChild(command);

  std::string command_num;
  sprintf(number, "%d", hero->getCommand());
  command_num = number;
  Label *command_text = Label::create(command_num,TEXT_FONT_NAME, font_size);
  command_text->setColor(Color3B::BLACK);
  command_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  command_text->setPosition(Vec2(size.width * 0.825, size.height * 0.7));
  layer->addChild(command_text);

  // add intelligence
  Label *intelligence = Label::create(__intelligence_text,TEXT_FONT_NAME, font_size);
  intelligence->setColor(Color3B::BLACK);
  intelligence->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  intelligence->setPosition(Vec2(size.width * 0.3, size.height * 0.6));
  layer->addChild(intelligence);

  std::string intelligence_num;
  sprintf(number, "%d", hero->getIntelligence());
  intelligence_num = number;
  Label *intelligence_text = Label::create(intelligence_num,TEXT_FONT_NAME, font_size);
  intelligence_text->setColor(Color3B::BLACK);
  intelligence_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  intelligence_text->setPosition(Vec2(size.width * 0.475, size.height * 0.6));
  layer->addChild(intelligence_text);

  // add agility
  Label *agility = Label::create(__agility_text,TEXT_FONT_NAME, font_size);
  agility->setColor(Color3B::BLACK);
  agility->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  agility->setPosition(Vec2(size.width * 0.65, size.height * 0.6));
  layer->addChild(agility);

  std::string agility_num;
  sprintf(number, "%d", hero->getAgility());
  agility_num = number;
  Label *agility_text = Label::create(agility_num,TEXT_FONT_NAME, font_size);
  agility_text->setColor(Color3B::BLACK);
  agility_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  agility_text->setPosition(Vec2(size.width * 0.825, size.height * 0.6));
  layer->addChild(agility_text);

  // add luck
  Label *luck = Label::create(__luck_text,TEXT_FONT_NAME, font_size);
  luck->setColor(Color3B::BLACK);
  luck->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  luck->setPosition(Vec2(size.width * 0.3, size.height * 0.5));
  layer->addChild(luck);

  std::string luck_num;
  sprintf(number, "%d", hero->getLuck());
  luck_num = number;
  Label *luck_text = Label::create(luck_num,TEXT_FONT_NAME, font_size);
  luck_text->setColor(Color3B::BLACK);
  luck_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  luck_text->setPosition(Vec2(size.width * 0.475, size.height * 0.5));
  layer->addChild(luck_text);



  return;
}
