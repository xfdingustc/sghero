#include "SGGlobalSettings.h"
#include "SGSInfoPanel.h"

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

  return true;
}
