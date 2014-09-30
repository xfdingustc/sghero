#include "SGSkirmishTerrain.h"

SGSkirmishTerrain* SGSkirmishTerrain::create(std::string& terrain_file, Size size)
{
  SGSkirmishTerrain* terrain = new SGSkirmishTerrain(terrain_file, size);
  return terrain;
}

SGSkirmishTerrain::SGSkirmishTerrain(std::string& terrain_file, Size size)
  : __width(size.width),
    __height(size.height)
{
  __terrain_info = new SGSkirmishTerrainType[__width * __height];
  loadTerrain(terrain_file);
}

SGSkirmishTerrain::~SGSkirmishTerrain()
{
  delete __terrain_info;
}

void SGSkirmishTerrain::loadTerrain(std::string& terrain_file)
{
  ssize_t size;
  unsigned char* terrain = FileUtils::getInstance()->getFileData(terrain_file, "rb", &size);
  for (int i = 0; i < __width * __height; i++) {
    __terrain_info[i] = (SGSkirmishTerrainType)terrain[i];
  }
}

SGSkirmishArea& SGSkirmishTerrain::calcHeroAvailabePath(SGSkirmishHero* hero)
{
  SGSkirmishArea* area = SGSkirmishArea::create();

  int hero_stamina = 6;
  // A* algorithm

  typedef std::list<Step> StepList;
  StepList* open_list = new StepList;
  StepList* close_list = new StepList;

  Step start_step;
  start_step.__pos = Vec2(10.0f,6.0f);
  start_step.__stamina = hero_stamina;

  while(!open_list->empty()) {
    Step open_step = open_list->front();
    open_list->pop_front();

    for (int i = SG_MOVE_STEP_RIGHT; i <= SG_MOVE_STEP_UP; i++) {
      //Step temp_move = moveHero((SGMoveStep) i, open_step);
    }
  }


  return *area;

}

SGSkirmishTerrain::Step SGSkirmishTerrain::moveHero(SGSkirmishHero* hero, SGMoveStep one_step, Step step_from)
{
  Step step_to = step_from;

  Step current_step = step_from;
  Vec2 origin_pos = hero->getMapPosition();

  return step_to;
}