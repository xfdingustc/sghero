#ifndef SG_SKIRMISH_SCENE_TERRAIN_H
#define SG_SKIRMISH_SCENE_TERRAIN_H

#include "cocos2d.h"
#include "SGObserver.h"
#include "SGSkirmishHero.h"
#include "SGSkirmishArea.h"
USING_NS_CC;


class SGSkirmishTerrain : public SGObserver
{
public:
  typedef SGSkirmishHero::SGSkirmishHeroList HeroList;
  typedef SGSkirmishMapPos::SGSkirmishPointList PointList;
  static SGSkirmishTerrain* create(std::string& terrain_file, Size size);

  SGSkirmishTerrain(std::string& terrain_file, Size size); 
  ~SGSkirmishTerrain();


  SGSkirmishArea&         calcHeroAvailabePath(SGSkirmishHero* hero);
  HeroList*               findAssaultableEnemyHeroes(SGSkirmishHero* hero);
  SGSkirmishHero*         findEnemyHeroInArea(SGSkirmishArea* area, SGSkirmishHero* hero);
  SGSkirmishHero*         findHeroByPosition(Vec2& pos);
  SGSkirmishHero*         findHeroByPosition(SGSkirmishMapPos& pos);
  SGSkirmishHero*         findNearestEnemyHero(SGSkirmishHero* hero);

  void                    notify(const char* reason, void* ptr);
private:
  typedef enum
  {
    SG_SKIRMISH_TERRAIN_PLAIN = 0x00,
    SG_SKIRMISH_TERRAIN_GRASS = 0x01,
    SG_SKIRMISH_TERRAIN_FOREST = 0x02,
    SG_SKIRMISH_TERRAIN_BARREN = 0x03,
    SG_SKIRMISH_TERRAIN_MOUNTAIN = 0x04,
    SG_SKIRMISH_TERRAIN_ROCK = 0x05,
    SG_SKIRMISH_TERRAIN_CLIFF = 0x06,
    SG_SKIRMISH_TERRAIN_SNOWFIELD = 0x07,
    SG_SKIRMISH_TERRAIN_BRIDGE = 0x08,
    SG_SKIRMISH_TERRAIN_SHALLOW = 0x09,
    SG_SKIRMISH_TERRAIN_SWAMP = 0x0A,
    SG_SKIRMISH_TERRAIN_POND = 0x0B,
    SG_SKIRMISH_TERRAIN_CREEK = 0x0C,
    SG_SKIRMISH_TERRAIN_RIVER = 0x0D,
    SG_SKIRMISH_TERRAIN_BARRIER = 0x0E,
    SG_SKIRMISH_TERRAIN_WALL = 0x0F,
    SG_SKIRMISH_TERRAIN_INSIDECITY = 0x10,
    SG_SKIRMISH_TERRAIN_GATE = 0x11,
    SG_SKIRMISH_TERRAIN_CITY = 0x12,
    SG_SKIRMISH_TERRAIN_PASS = 0x13,
    SG_SKIRMISH_TERRAIN_ABATIS = 0x14,
    SG_SKIRMISH_TERRAIN_VILLAGE = 0x15,
    SG_SKIRMISH_TERRAIN_BARRACK = 0x16,
    SG_SKIRMISH_TERRAIN_HOUSE = 0x17,
    SG_SKIRMISH_TERRAIN_TREASURY = 0x18,
    SG_SKIRMISH_TERRAIN_POOL = 0x19,
    SG_SKIRMISH_TERRAIN_FIRE = 0x1A,
    SG_SKIRMISH_TERRAIN_SHIP = 0x1B,
    SG_SKIRMISH_TERRAIN_ALTAR = 0x1C,
    SG_SKIRMISH_TERRAIN_UNDERGROUND = 0x1D,
    SG_SKIRMISH_TERRAIN_MAX,
  } SGSkirmishTerrainType;

  typedef enum {
    SG_MOVE_STEP_RIGHT,
    SG_MOVE_STEP_DOWN,
    SG_MOVE_STEP_LEFT,
    SG_MOVE_STEP_UP,
  } SGMoveStep;

  
  typedef struct Step{
    bool operator ==(const Step& a) const {
      if (this->__pos == a.__pos && this->__stamina == a.__stamina) {
        return true;
      } else {
        return false;
      }
    }
    SGSkirmishMapPos __pos;
    int __stamina;
    
  };
  
  typedef std::list<Step> StepList;
  SGSkirmishObj*          getObj(SGSkirmishMapPos& pos);
  SGSkirmishTerrainType   getTerrainAt(SGSkirmishMapPos& pos);
  int                     getSteminaConsume(SGSkirmishHero::HERO_CATAGORY catagory, SGSkirmishTerrainType terrain);
  bool                    isInStepList(Step& step, StepList& step_list);
  void                    loadTerrain(std::string& terrain_file);
  Step                    moveHero(SGSkirmishHero* hero, SGMoveStep one_step, Step from);

  static int              SteminaConsuming[SG_SKIRMISH_TERRAIN_MAX][SGSkirmishHero::HERO_CATAGORY_MAX];
  int                     __width;
  int                     __height;

  Vector<SGSkirmishObj*>  __objects;
  SGSkirmishTerrainType*  __terrain_info;
  HeroList  __heroes;
};

#endif