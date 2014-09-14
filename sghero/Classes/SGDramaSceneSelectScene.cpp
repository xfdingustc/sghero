#include "SGDramaSceneSelectScene.h"
#include "SGGlobalSettings.h"
#include "SGHeroResourceUtils.h"

USING_NS_CC;

Scene* SGDramaSceneSelectScene::creatScene(const char* hero_name, const char* content, int* ret_add)
{
  Scene* scene = Scene::create();

  SGDramaSceneSelectScene* select_layer = SGDramaSceneSelectScene::create();
  Size win_size = Director::getInstance()->getWinSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 

  select_layer->addChild(render_texture);

  // Create the select dialog window

  // step 1: create the dialog window backgound texture;
  Sprite* dialog_win = Sprite::create(SELECT_WINDOW_BACKGROUND);
  Size dialog_size(win_size.width * 0.666f, win_size.height * 0.1928f);
  dialog_win->setTextureRect(Rect(0, 0, dialog_size.width, dialog_size.height));
  Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
  dialog_win->getTexture()->setTexParameters(params);
  dialog_win->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  dialog_win->setPosition(Vec2(win_size.width/2, win_size.height/2));

  // step 2: create hero face image;
  std::string hero_face_res = SG_HERO_FACE_RES_PATH;
  hero_face_res.append(SGHeroResourceUtils::getInstance()->getHeroResObj(hero_name)->res_name);
  hero_face_res.append(".png");
  Sprite* face = Sprite::create(hero_face_res);
  face->setPosition(Vec2(dialog_size.width * 0.1f ,dialog_size.height/2));
  dialog_win->addChild(face);


  // step 3: create dialog content background
  LayerColor* content_bg_layer = LayerColor::create(Color4B::WHITE, dialog_size.width * 0.75f ,dialog_size.height * 0.6667f);
  content_bg_layer->setPosition(Vec2(dialog_size.width * 0.2333f ,dialog_size.height * 0.0714f));
  Size content_bg_layer_size = content_bg_layer->getContentSize();
  dialog_win->addChild(content_bg_layer);

  // step 4: create each menu item
  std::string select_items = content;
  std::string::size_type start_pos = 0;
  std::string::size_type pos = 0;
  std::string separator = "\\n";
  std::string null_str = " ";
  Menu* select_menu;
  int menu_size = 0;
  MenuItemLabel *menu_item1, *menu_item2, *menu_item3;
  while ((pos = select_items.find(separator, start_pos)) != std::string::npos){
    //speak.replace( pos, srcLen, des_str );
    std::string one_item_content = select_items.substr(start_pos, pos - start_pos);
    
    //one_item_content.replace(one_item_content.find(separator, 0), separator.size(), null_str);
    LabelTTF* label = LabelTTF::create(one_item_content, TEXT_FONT_NAME, TEXT_FONT_SIZE);
    label->setColor(Color3B::BLACK);
    menu_size++;
    switch (menu_size)
    {
    case 1:
      menu_item1 = MenuItemLabel::create(label, CC_CALLBACK_1(SGDramaSceneSelectScene::menuItem1Callback, select_layer));
      break;
    case 2:
      menu_item2 = MenuItemLabel::create(label, CC_CALLBACK_1(SGDramaSceneSelectScene::menuItem2Callback, select_layer));
      break;
    case 3:
      menu_item3 = MenuItemLabel::create(label, CC_CALLBACK_1(SGDramaSceneSelectScene::menuItem3Callback, select_layer));
    default:
      break;
    }
    start_pos = pos + separator.size();
  }
  
  switch (menu_size)
  {
  case 2:
    select_menu = Menu::create(menu_item1, menu_item2, NULL);
    break;
  case 3:
    select_menu = Menu::create(menu_item1, menu_item2, menu_item3, NULL);
    break;
  default:
    break;
  }
  select_menu->alignItemsVertically();
  
  select_menu->setPosition(content_bg_layer_size.width/2, content_bg_layer_size.height/2);
  content_bg_layer->addChild(select_menu);
  

  select_layer->addChild(dialog_win);

  scene->addChild(select_layer);

  select_layer->__ret = ret_add;


  return scene;
}


bool SGDramaSceneSelectScene::init()
{
  if (!Layer::init()) {
    return false;

  }
  return true;
}

void SGDramaSceneSelectScene::menuItem1Callback(cocos2d::Ref* pSender)
{
  *__ret = 1;
  Director::getInstance()->popScene();
}
void SGDramaSceneSelectScene::menuItem2Callback(cocos2d::Ref* pSender)
{
  *__ret = 2;
  Director::getInstance()->popScene();
}
void SGDramaSceneSelectScene::menuItem3Callback(cocos2d::Ref* pSender)
{
  *__ret = 3;
  Director::getInstance()->popScene();
}