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
private:
  std::string __force_text;
  std::string __command_text;
  std::string __intelligence_text;
  std::string __agility_text;
  std::string __luck_text;
  std::string getAttributeText(const char* attribute);

};


#endif