#ifndef SG_HERO_RESOURCE_UTILS_H
#define SG_HERO_RESOURCE_UTILS_H

#include "cocos2d.h"

class SGHeroResourceUtils {
public:
  static SGHeroResourceUtils* getInstance();

  void init();

  class SGHeroResourceObject {
  public:
    std::string name;
    std::string category;
    std::string res_name;
    int force;
    int command;
    int intelligence;
    int agility;
    int luck;
    int hp;
    int mp;

  };

  SGHeroResourceObject* getHeroResObj(std::string name);

private:
  typedef std::map<std::string, SGHeroResourceObject*> HERO_MAP_TYPE;
  HERO_MAP_TYPE heroes_map;

};

#endif