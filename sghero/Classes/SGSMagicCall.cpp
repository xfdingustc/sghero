#include "SGSMagicCall.h"
#include "SGGlobalSettings.h"

Scene* SGSMagicCall::createScene(std::string& magic, Vec2& pos)
{
  Scene* scene = Scene::create();

  SGSMagicCall* layer = SGSMagicCall::create(magic, pos);

  scene->addChild(layer);
  return scene;
}

SGSMagicCall* SGSMagicCall::create(std::string& magic, Vec2& pos)
{
  SGSMagicCall* magic_call = new SGSMagicCall;
  if (magic_call && magic_call->init(magic, pos)) {
    magic_call->autorelease();
    return magic_call;
  } else {
    delete magic_call;
    return NULL;
  }
}
bool SGSMagicCall::init(std::string& magic, Vec2& pos)
{
  if (!Layer::init()) {
    return false;
  }

  Size win_size = Director::getInstance()->getVisibleSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 

  this->addChild(render_texture);

  Sprite* magic_sprite = Sprite::create();
  magic_sprite->setPosition(pos);
  this->addChild(magic_sprite);

  Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>;

  for (int i = 1; i <= 30; i++) {
    std::string res_name = SG_SKIRMISH_SCENE_MAGIC_CALL_RES_PATH;
    res_name.append(magic);
    char index[10];
    sprintf(index, "-%d", i);
    res_name.append(index);
    res_name.append(".png");
    std::string obj_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(res_name);
    SpriteFrame* frame = SpriteFrame::create(obj_res_file_full_path, 
      Rect(0, 0, SG_SKIRMISH_SCENE_MAGIC_CALL_RES_WIDTH, SG_SKIRMISH_SCENE_MAGIC_CALL_RES_HEIGHT));
    animFrames->pushBack(frame);

  }
  Animation* animation = Animation::createWithSpriteFrames(*animFrames, 0.1f);
  Animate* animate = Animate::create(animation);
  CallFunc * funcall= CallFunc::create(this, callfunc_selector(SGSMagicCall::actionFinished));
  FiniteTimeAction* magicWithCallback = Sequence::create(animate, funcall, NULL);
  magic_sprite->runAction(magicWithCallback);
  return true;
}

void SGSMagicCall::actionFinished()
{
  Director::getInstance()->popScene();
}