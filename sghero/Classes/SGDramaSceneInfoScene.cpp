#include "SGDramaSceneInfoScene.h"
#include "SGGlobalSettings.h"
USING_NS_CC;

Scene* SGDramaSceneInfoScene::createScene(const char* content)
{
  Scene* scene = Scene::create();

  SGDramaSceneInfoScene* layer = SGDramaSceneInfoScene::create();
  
  
  Size win_size = Director::getInstance()->getWinSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 

  layer->addChild(render_texture);


  // Create the info window

  // step 1: create the dialog window backgound texture;
  Sprite* dialog_win = Sprite::create(DIALOG_WINDOW_BACKGROUND);
  Size dialog_size(win_size.width * 0.5f, win_size.height * 0.5f);
  dialog_win->setTextureRect(Rect(0, 0, dialog_size.width, dialog_size.height));
  Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
  dialog_win->getTexture()->setTexParameters(params);
  dialog_win->setAnchorPoint(Vec2(0.5f, 0.5f));
  dialog_win->setPosition(Vec2(win_size.width/2, win_size.height/2));

  // step2: show the info content:
  // step4: create dialog content TTF
  LabelTTF* content_ttf = LabelTTF::create(content, TEXT_FONT_NAME, TEXT_FONT_SIZE);
  content_ttf->setHorizontalAlignment(TextHAlignment::LEFT);
  content_ttf->setColor(Color3B::BLACK);
  content_ttf->setAnchorPoint(Vec2(0.0f, 1.0f));
  content_ttf->setPosition(Vec2(40.0f, dialog_win->getContentSize().height - 20.0f));
  dialog_win->addChild(content_ttf);

  layer->addChild(dialog_win);

  scene->addChild(layer);
  return scene;
}

bool SGDramaSceneInfoScene::init()
{
  if (!Layer::init()) {
    return false;
  }

  


  // add touch event handler:
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  __event_listener = EventListenerTouchOneByOne::create();
  __event_listener->onTouchBegan = CC_CALLBACK_2(SGDramaSceneInfoScene::onTouchBegin, this);
  __event_listener->setSwallowTouches(true);
  dispatcher->addEventListenerWithSceneGraphPriority(__event_listener,this);
  return true;
}

bool SGDramaSceneInfoScene::onTouchBegin(Touch *touch, Event *unused_event)
{
  Director::getInstance()->getEventDispatcher()->removeEventListener(__event_listener);
  Director::getInstance()->popScene();
  return true;
}