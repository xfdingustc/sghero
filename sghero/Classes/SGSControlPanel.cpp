#include "SGGlobalSettings.h"
#include "SGSControlPanel.h"

SGSControlPanel* SGSControlPanel::create()
{
  SGSControlPanel* control_panel = new SGSControlPanel;
  if (control_panel && control_panel->init()) {
    control_panel->autorelease();
    return control_panel;
  } else {
    delete control_panel;
    return NULL;
  }
}

bool SGSControlPanel::init()
{
  if (!Sprite::initWithFile(DIALOG_WINDOW_BACKGROUND)) {
    return false;
  }
  Size win_size = Director::getInstance()->getVisibleSize();
  Size dialog_size(win_size.height/3, win_size.height/3);
  setTextureRect(Rect(0, 0, dialog_size.width, dialog_size.height));
  Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
  getTexture()->setTexParameters(params);
  setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
  setPosition(Vec2(win_size.width, win_size.height/3));
  return true;
}
