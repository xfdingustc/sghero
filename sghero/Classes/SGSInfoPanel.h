#ifndef SGS_INFO_PANEL_H
#define SGS_INFO_PANEL_H

#include "cocos2d.h"
USING_NS_CC;

#include "SGSHero.h"
#include "json/document.h"

class SGSInfoPanel : public Sprite
{
public:
  CREATE_FUNC(SGSInfoPanel);
  bool init();

  void showFirstHeroInfo(SGSHero* hero);
  void showSecondHeroInfo(SGSHero* hero);
private:
  void showHeroInfo(Layer* layer, SGSHero* hero);
  Layer* __top_half;
  Layer* __bottom_half;
  std::string __force_text;
  std::string __command_text;
  std::string __intelligence_text;
  std::string __agility_text;
  std::string __luck_text;

};


#endif