#ifndef SG_SKIRMISH_CONTROL_PANEL_H
#define SG_SKIRMISH_CONTROL_PANEL_H

#include "cocos2d.h"
USING_NS_CC;

class SGSControlPanel : public Sprite
{
public:
  static SGSControlPanel* create();
  bool init();
};




#endif