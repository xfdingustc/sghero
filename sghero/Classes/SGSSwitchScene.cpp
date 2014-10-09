#include "SGSSwitchScene.h"
#include "SGGlobalSettings.h"


rapidjson::Document SGSSwitchScene::__text_json_doc;
bool SGSSwitchScene::__json_parsed = false;

Scene* SGSSwitchScene::createScene(int round, int turn)
{
  Scene* scene = Scene::create();

  SGSSwitchScene* layer = SGSSwitchScene::create();

  Size win_size = Director::getInstance()->getVisibleSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 

  layer->addChild(render_texture);


  // Parse the text json file;
  if (!__json_parsed) {
    std::string text_json_file = FileUtils::getInstance()->fullPathForFilename(SKIRMISH_SCENE_SWITCH_TEXT_JSON_FILE);
    std::string json_data = FileUtils::getInstance()->getStringFromFile(text_json_file.c_str());
    __text_json_doc.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
    if (__text_json_doc.HasParseError()) {
      CCLOG("Parsing json file error!! %s", __text_json_doc.GetParseError());
      return NULL;
    } else {
      __json_parsed = true;
    }
  }

  const rapidjson::Value &res_list = __text_json_doc["Round"];
  const rapidjson::Value &val = res_list[round-1];
  std::string content = val["text"].GetString();
  content.append("\n\n");

  const rapidjson::Value &turn_text_list = __text_json_doc["Turn"];
  const rapidjson::Value &turn_val = turn_text_list[turn];

  content.append(turn_val["text"].GetString());

  Size size = Director::getInstance()->getVisibleSize();
  
  layer->__content_ttf = LabelTTF::create(content, TEXT_FONT_NAME, CHAPTER_TEXT_FONT_SIZE);
  layer->__content_ttf->setColor(Color3B::BLACK);
  layer->__content_ttf->setPosition(Vec2(size.width/2, size.height/2));
  layer->addChild(layer->__content_ttf);

  scene->addChild(layer);

  return scene;
}

bool SGSSwitchScene::init()
{
  if (!LayerColor::initWithColor(Color4B::BLACK)) {
    return false;
  }

  // add touch event handler:
  scheduleOnce(schedule_selector(SGSSwitchScene::exitScene), 3.0f);
}

void SGSSwitchScene::exitScene(float dt)
{
  Director::getInstance()->popScene();
}