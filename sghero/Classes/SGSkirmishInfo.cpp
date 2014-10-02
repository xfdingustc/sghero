#include "SGGlobalSettings.h"
#include "SGSkirmishInfo.h"
#include "json/document.h"

Scene* SGSkirmishInfo::createScene(std::string& content)
{
  Scene* scene = Scene::create();

  SGSkirmishInfo* info_layer = SGSkirmishInfo::create();
  Size win_size = Director::getInstance()->getVisibleSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 
  info_layer->addChild(render_texture);

  // step 1: create the dialog window backgound texture;
  Sprite* dialog_win = Sprite::create(DIALOG_WINDOW_BACKGROUND);
  Size dialog_size(win_size.width * 0.25f, win_size.height * 0.25f);
  dialog_win->setTextureRect(Rect(0, 0, dialog_size.width, dialog_size.height));
  Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
  dialog_win->getTexture()->setTexParameters(params);
  dialog_win->setAnchorPoint(Vec2(0.5f, 0.5f));
  dialog_win->setPosition(Vec2(win_size.width/2, win_size.height/2));

  // step2: show the info content:
  std::string chinese_content;
  rapidjson::Document info_json;
  std::string res_json_file = FileUtils::getInstance()->fullPathForFilename(INFO_TEXT_JSON_FILE);
  std::string json_data = FileUtils::getInstance()->getStringFromFile(res_json_file.c_str());

  info_json.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (info_json.HasParseError()) {
    log("Parsing info_json resource json file error!! %s", info_json.GetParseError());
    return NULL;
  } else if (info_json.IsObject()) {
    const rapidjson::Value &res_list = info_json["Info"];
    if (res_list.IsArray()) {
      for (int i = 0; i < res_list.Size(); i++) {
        const rapidjson::Value &val = res_list[i];
        if (content == val["name"].GetString()) {
          chinese_content = val["text"].GetString();
          break;
        }
      }
    }

  }
  LabelTTF* content_ttf = LabelTTF::create(chinese_content, TEXT_FONT_NAME, TEXT_FONT_SIZE);
  content_ttf->setHorizontalAlignment(TextHAlignment::LEFT);
  content_ttf->setColor(Color3B::BLACK);
  content_ttf->setAnchorPoint(Vec2(0.0f, 1.0f));
  content_ttf->setPosition(Vec2(40.0f, dialog_win->getContentSize().height - 20.0f));
  dialog_win->addChild(content_ttf);

  info_layer->addChild(dialog_win);

  scene->addChild(info_layer);
  return scene;
}

bool SGSkirmishInfo::init()
{
  if (!Layer::init()) {
    return false;
  }
  // add touch event handler:
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  __event_listener = EventListenerTouchOneByOne::create();
  __event_listener->onTouchBegan = CC_CALLBACK_2(SGSkirmishInfo::onTouchBegin, this);
  __event_listener->setSwallowTouches(true);
  dispatcher->addEventListenerWithSceneGraphPriority(__event_listener,this);
  return true;
  return true;
}

bool SGSkirmishInfo::onTouchBegin(Touch *touch, Event *unused_event)
{
  Director::getInstance()->getEventDispatcher()->removeEventListener(__event_listener);
  Director::getInstance()->popScene();
  return true;
}
