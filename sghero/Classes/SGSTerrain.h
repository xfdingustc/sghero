#ifndef SG_SKIRMISH_SCENE_TERRAIN_H
#define SG_SKIRMISH_SCENE_TERRAIN_H

#include "cocos2d.h"
#include "SGObserver.h"
#include "SGSHero.h"
#include "SGSArea.h"
USING_NS_CC;


class SGSTerrain : public SGObserver
{
public:
  static SGSTerrain* create(std::string& terrain_file, Size size);

  SGSTerrain(std::string& terrain_file, Size size); 
  ~SGSTerrain();


  SGSPointList&    calcHeroAvailabePath(SGSHero* hero);
  SGSPointList&    calcShortestPath(SGSHero* hero, SGSPoint& target_pos);
  SGSHero*         findEnemyHeroInArea(SGSArea* area, SGSHero* hero);
  SGSHero*         findHeroByPosition(Vec2& pos);
  SGSHero*         findHeroByPosition(SGSPoint& pos);
  SGSHero*         findNearestEnemyHero(SGSHero* hero);

  void                    notify(const char* reason, void* ptr);
private:
  typedef enum
  {
    TERRAIN_PLAIN = 0x00,
    TERRAIN_GRASS = 0x01,
    TERRAIN_FOREST = 0x02,
    TERRAIN_BARREN = 0x03,
    TERRAIN_MOUNTAIN = 0x04,
    TERRAIN_ROCK = 0x05,
    TERRAIN_CLIFF = 0x06,
    TERRAIN_SNOWFIELD = 0x07,
    TERRAIN_BRIDGE = 0x08,
    TERRAIN_SHALLOW = 0x09,
    TERRAIN_SWAMP = 0x0A,
    TERRAIN_POND = 0x0B,
    TERRAIN_CREEK = 0x0C,
    TERRAIN_RIVER = 0x0D,
    TERRAIN_BARRIER = 0x0E,
    TERRAIN_WALL = 0x0F,
    TERRAIN_INSIDECITY = 0x10,
    TERRAIN_GATE = 0x11,
    TERRAIN_CITY = 0x12,
    TERRAIN_PASS = 0x13,
    TERRAIN_ABATIS = 0x14,
    TERRAIN_VILLAGE = 0x15,
    TERRAIN_BARRACK = 0x16,
    TERRAIN_HOUSE = 0x17,
    TERRAIN_TREASURY = 0x18,
    TERRAIN_POOL = 0x19,
    TERRAIN_FIRE = 0x1A,
    TERRAIN_SHIP = 0x1B,
    TERRAIN_ALTAR = 0x1C,
    TERRAIN_UNDERGROUND = 0x1D,
    TERRAIN_MAX,
  } TERRAIN_TYPE;

  typedef enum {
    STEP_RIGHT,
    STEP_DOWN,
    STEP_LEFT,
    STEP_UP,
  } STEP_DIRECTION;

  
  typedef struct Step{
    bool operator ==(const Step& a) const {
      if (this->__pos == a.__pos && this->__stamina == a.__stamina) {
        return true;
      } else {
        return false;
      }
    }
    SGSPoint __pos;
    int __stamina;
    Step* __parent;
  };
  
  typedef std::list<Step> StepList;
  typedef std::list<Step*> StepPtrList;
  SGSObj*          getObj(SGSPoint& pos);
  TERRAIN_TYPE   getTerrainAt(SGSPoint& pos);
  int                     getSteminaConsume(SGSHero::HERO_category category, TERRAIN_TYPE terrain);
  bool                    isInStepList(Step& step, StepList& step_list);
  bool                    isInStepPtrList(Step* step, StepPtrList& step_list);
  void                    loadTerrain(std::string& terrain_file);
  Step                    moveHero(SGSHero* hero, STEP_DIRECTION one_step, Step from);

  static int              SteminaConsuming[TERRAIN_MAX][SGSHero::HERO_CATEGORY_MAX];
  int                     __width;
  int                     __height;

  Vector<SGSObj*>  __objects;
  TERRAIN_TYPE*  __terrain_info;
  SGSHeroList      __heroes;
};

#endif