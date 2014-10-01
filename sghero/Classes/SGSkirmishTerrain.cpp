#include "SGSkirmishTerrain.h"


int SGSkirmishTerrain::SteminaConsuming[SGSkirmishTerrain::SG_SKIRMISH_TERRAIN_MAX][SGSkirmishHero::HERO_CATAGORY_MAX] =
{
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {3, 2, 2, 3, 3, 2, 2, 1, 2, 2, 2, 3, 2 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1 },
  {3, 2, 2, 3, 3, 2, 2, 2, 2, 2, 2, 3, 1 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {2, 1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {3, 2, 2, 3, 3, 2, 2, 2, 2, 2, 2, 3, 2 },
  {2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
  {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535 },
};

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

void SGSkirmishTerrain::notify(const char* reason, void* ptr)
{
  std::string notify_reason = reason;
  if (notify_reason == "hero_add") {
    SGSkirmishHero* hero = reinterpret_cast<SGSkirmishHero*>(ptr);
    __heroes.pushBack(hero);
  } else if (notify_reason == "object_add") {
    SGSkirmishObj* object = reinterpret_cast<SGSkirmishObj*>(ptr);
    __objects.pushBack(object);
  }
  
}

bool SGSkirmishTerrain::isInStepList(Step& step, StepList& step_list)
{
  StepList::iterator iter;

  for (iter = step_list.begin(); iter != step_list.end(); iter++) {
    Step one_step = *iter;
    if (step.__pos == one_step.__pos) {
      return true;
    }
  }
  return false;
}

SGSkirmishArea& SGSkirmishTerrain::calcHeroAvailabePath(SGSkirmishHero* hero)
{
  SGSkirmishArea* area = SGSkirmishArea::create();

  int hero_stamina = 6;
  // A* algorithm

  
  StepList open_list;
  StepList close_list;


  Step start_step;
  start_step.__pos = hero->getMapPosition();
  start_step.__stamina = hero_stamina;
  open_list.push_back(start_step);

  while(!open_list.empty()) {
    Step open_step = open_list.front();
    open_list.pop_front();

    for (int i = SG_MOVE_STEP_RIGHT; i <= SG_MOVE_STEP_UP; i++) {
      Step temp_move = moveHero(hero, (SGMoveStep) i, open_step);
      if (temp_move.__stamina >=0 ) { // valid move
        if (!isInStepList(temp_move, open_list) && !isInStepList(temp_move, close_list)) {
          open_list.push_back(temp_move);
          log("insert into open list x = %d y = %d", temp_move.__pos.x, temp_move.__pos.y);
        } else if(isInStepList(temp_move, open_list)) { // in Open list
          StepList::iterator iter;
          for (iter = open_list.begin(); iter != open_list.end(); iter++) {
            Step one_step_in_openlist = *iter;
            if (one_step_in_openlist.__pos == temp_move.__pos) {
              if (one_step_in_openlist.__stamina < temp_move.__stamina) {
                open_list.remove(one_step_in_openlist);
                open_list.push_back(temp_move);
                log("replace open list x = %d y = %d", temp_move.__pos.x, temp_move.__pos.y);
              }
            }
          }
        } else { // in close list
          StepList::iterator iter;
          for (iter = close_list.begin(); iter != close_list.end(); iter++) {
            Step one_step_in_closelist = *iter;
            if (one_step_in_closelist.__pos == temp_move.__pos) {
              if (one_step_in_closelist.__stamina < temp_move.__stamina) {
                close_list.remove(one_step_in_closelist);
                open_list.push_back(temp_move);
                log("reinsert open list x = %d y = %d", temp_move.__pos.x, temp_move.__pos.y);
              }
            } 

          }
        }

      } 
    }
    log("insert close list x = %d y = %d", open_step.__pos.x, open_step.__pos.y);
    close_list.push_back(open_step);
  }

  StepList::iterator iter;
  for (iter = close_list.begin(); iter != close_list.end(); iter++) {
    Step one_step = *iter;
    area->addOnePoint(one_step.__pos);

  }
  return *area;

}



int SGSkirmishTerrain::getSteminaConsume(SGSkirmishHero::HERO_CATAGORY catagory, SGSkirmishTerrainType terrain)
{
  return SteminaConsuming[terrain][catagory];
}

SGSkirmishTerrain::Step SGSkirmishTerrain::moveHero(SGSkirmishHero* hero, SGMoveStep one_step, Step step_from)
{
  Step step_to = step_from;

  Step current_step = step_from;
  SGSkirmishMapPos origin_pos = hero->getMapPosition();

  SGSkirmishMapPos left_pos = current_step.__pos;
  SGSkirmishMapPos right_pos = current_step.__pos;
  SGSkirmishMapPos up_pos = current_step.__pos;
  SGSkirmishMapPos down_pos = current_step.__pos;

  left_pos.x--;
  right_pos.x++;
  up_pos.y--;
  down_pos.y++;

  bool is_original_pos = false;
  bool valid_move = true;

  if (origin_pos == current_step.__pos) {
    is_original_pos = true;
  }


  switch (one_step)
  {
  case SG_MOVE_STEP_RIGHT:
    step_to.__pos.x++;
    if (getHero(right_pos) || getObj(right_pos)) {
      valid_move = false;
    }

    if (!is_original_pos) {
      if (hero->isRival(getHero(up_pos)) || hero->isRival(getHero(down_pos))) {
        valid_move = false;
      }
    }
    break;
  case SG_MOVE_STEP_DOWN:
    step_to.__pos.y++;
    if (getHero(down_pos) || getObj(down_pos)) {
      valid_move = false;
    }

    if (!is_original_pos) {
      if (hero->isRival(getHero(up_pos)) || hero->isRival(getHero(right_pos))) {
        valid_move = false;
      }
    }
    break;
  case SG_MOVE_STEP_LEFT:
    step_to.__pos.x--;
    if (getHero(left_pos) || getObj(left_pos)) {
      valid_move = false;
    }
    if (!is_original_pos) {
      if (hero->isRival(getHero(up_pos)) || hero->isRival(getHero(down_pos))) {
        valid_move = false;
      }
    }
    
    break;
  case SG_MOVE_STEP_UP:
    step_to.__pos.y--;
    if (getHero(up_pos) || getObj(up_pos)) {
      valid_move = false;
    }
    if (!is_original_pos) {
      if (hero->isRival(getHero(left_pos)) || hero->isRival(getHero(right_pos))) {
        valid_move = false;
      }
    }
    break;
  default:
    break;
  }

 
  if (step_to.__pos.x < 0 || step_to.__pos.y < 0 || valid_move == false) {
    step_to.__stamina = -100;
  } else {
    step_to.__stamina -= getSteminaConsume(hero->getCatagory(), getTerrainAt(step_to.__pos));
  }

  return step_to;
}

SGSkirmishTerrain::SGSkirmishTerrainType SGSkirmishTerrain::getTerrainAt(SGSkirmishMapPos& pos)
{
  int x = pos.x;
  int y = pos.y;
  return (SGSkirmishTerrainType)(__terrain_info[y * __width + x]);
}

SGSkirmishHero* SGSkirmishTerrain::getHero(SGSkirmishMapPos& pos)
{
  
  Vector<SGSkirmishHero*>::iterator iter;
  for (iter = __heroes.begin(); iter != __heroes.end(); iter++) {
    SGSkirmishHero* hero = *iter;
      if (hero->getMapPosition() == pos) {
      return hero;
    }
  }
  return NULL;
}
SGSkirmishObj* SGSkirmishTerrain::getObj(SGSkirmishMapPos& pos)
{
  Vector<SGSkirmishObj*>::iterator iter;
  for (iter = __objects.begin(); iter != __objects.end(); iter++) {
    SGSkirmishObj* obj = *iter;
    if (obj->getMapPosition() == pos) {
      return obj;
    }
  }
  return NULL;
}