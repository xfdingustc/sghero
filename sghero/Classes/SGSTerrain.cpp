#include "SGGlobalSettings.h"
#include "SGSTerrain.h"
#include "json/document.h"

NS_CC_BEGIN
int SGSTerrain::SteminaConsuming[SGSTerrain::TERRAIN_MAX][SGSHero::HERO_CATEGORY_MAX] =
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

int SGSTerrain::MovementConsuming[SGSTerrain::TERRAIN_MAX][CORPS_MAX_TYPE_NUM] = {0};
int SGSTerrain::CorpsAdaptation[SGSTerrain::TERRAIN_MAX][CORPS_MAX_TYPE_NUM] = {0};

SGSTerrain::SGSTerrain(std::string& terrain_file, Size size)
  : __width(size.width),
    __height(size.height)
{
  __terrain_info = new TERRAIN_TYPE[__width * __height];
  loadTerrain(terrain_file);
}

SGSTerrain::~SGSTerrain()
{
  delete __terrain_info;
}

bool SGSTerrain::loadCorpsTerrainAdapt() {
	std::string corps_terrain_json_file = FileUtils::getInstance()->fullPathForFilename(CORPS_TERRAIN_ADAPTATION_JSON_FILE);
	std::string json_data = FileUtils::getInstance()->getStringFromFile(corps_terrain_json_file.c_str());
	rapidjson::Document text_json;
	text_json.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (text_json.HasParseError()) {
    log("Parsing corps terrain text json file error!! %s", text_json.GetParseError());
    return false;
	} else if (text_json.IsObject()) {
		const rapidjson::Value &res_list = text_json["CorpsTerrainList"];
		if (res_list.IsArray()) {
			for (int i=0; i < res_list.Size(); i++) {
				const rapidjson::Value &item = res_list[i];
				int corps_id = item["CorpsId"].GetInt();
				const rapidjson::Value &move_consume = item["MoveConsuming"];
				if(move_consume.IsArray()) {
					for(int j=0; j < move_consume.Size(); j++) {
						MovementConsuming[j][corps_id] = move_consume[j].GetInt();
					}
				}
				const rapidjson::Value &corps_adapt = item["CorpsAdapt"];
				if(corps_adapt.IsArray()) {
					for(int j=0; j < corps_adapt.Size(); j++) {
						CorpsAdaptation[j][corps_id] = corps_adapt[j].GetInt();
					}
				}
			}
		}
	}
	return true;
}

SGSPointList& SGSTerrain::calcHeroAvailabePath(SGSHero* hero)
{
  static SGSPointList valid_path_list; 
  SGSPointList::iterator path_list_iter;
  // clear the list;
  for (path_list_iter = valid_path_list.begin(); path_list_iter != valid_path_list.end();) {
    path_list_iter = valid_path_list.erase(path_list_iter);
  }

  int hero_stamina = hero->getStamina();
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

    for (int i = STEP_RIGHT; i <= STEP_UP; i++) {
      Step temp_move = moveHero(hero, (STEP_DIRECTION) i, open_step);
      if (temp_move.__stamina >=0 ) { // valid move
        if (!isInStepList(temp_move, open_list) && !isInStepList(temp_move, close_list)) {
          open_list.push_back(temp_move);
        } else if(isInStepList(temp_move, open_list)) { // in Open list
          StepList::iterator iter;
          if (open_list.size()) {
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
          }
        } else { // in close list
          StepList::iterator iter;
          for (iter = close_list.begin(); iter != close_list.end(); iter++) {
            Step one_step_in_closelist = *iter;
            if (one_step_in_closelist.__pos == temp_move.__pos) {
              if (one_step_in_closelist.__stamina < temp_move.__stamina) {
                close_list.remove(one_step_in_closelist);
                open_list.push_back(temp_move);
              }
            } 

          }
        }

      } 
    }
    close_list.push_back(open_step);
  }

  StepList::iterator iter;
  for (iter = close_list.begin(); iter != close_list.end(); iter++) {
    Step one_step = *iter;
    valid_path_list.push_back(one_step.__pos);

  }
  return valid_path_list;

}


SGSPointList& SGSTerrain::calcShortestPath(SGSHero* hero, SGSPoint& target_pos)
{
  static SGSPointList shortest_path_list; 
  SGSPointList::iterator shortest_path_list_iter;
  // clear the list;
  for (shortest_path_list_iter = shortest_path_list.begin(); shortest_path_list_iter != shortest_path_list.end();) {
    shortest_path_list_iter = shortest_path_list.erase(shortest_path_list_iter);
  }
  // A* algorithm
  StepPtrList open_list;
  StepPtrList close_list;

  Step* start_step = new Step;
  start_step->__pos = hero->getMapPosition();

  start_step->__stamina = 100;
  start_step->__parent = NULL;
  open_list.push_back(start_step);

  Step* last_step = NULL;

  while(!open_list.empty()) {
    Step* open_step = open_list.front();
    open_list.pop_front();
    if (open_step->__pos == target_pos) {
      last_step = open_step;
      break;
    }
    for (int i = STEP_RIGHT; i <= STEP_UP; i++) {
      Step* temp_move = new Step;
      *temp_move = moveHero(hero, (STEP_DIRECTION) i, *open_step);
      if (temp_move->__stamina >=0 ) { // valid move
        if (!isInStepPtrList(temp_move, open_list) && !isInStepPtrList(temp_move, close_list)) {
          temp_move->__parent = open_step;
          open_list.push_back(temp_move);
        } else if(isInStepPtrList(temp_move, open_list)) { // in Open list
          StepPtrList::iterator iter;
          for (iter = open_list.begin(); iter != open_list.end(); iter++) {
            Step* one_step_in_openlist = *iter;
            if (one_step_in_openlist->__pos == temp_move->__pos) {
              if (one_step_in_openlist->__stamina < temp_move->__stamina) {
                //iter = open_list.erase(iter);
                open_list.remove(one_step_in_openlist);
                delete one_step_in_openlist;
                open_list.push_back(temp_move);
                break;
              }
            } 
          }
        } else { // in close list
          StepPtrList::iterator iter;
          for (iter = close_list.begin(); iter != close_list.end(); iter++) {
            Step* one_step_in_closelist = *iter;
            if (one_step_in_closelist->__pos == temp_move->__pos) {
              if (one_step_in_closelist->__stamina < temp_move->__stamina) {
                close_list.remove(one_step_in_closelist);
                delete one_step_in_closelist;
                open_list.push_back(temp_move);
                break;
              }
            } 

          }
        }
        
      } else {
        delete temp_move;
      }
      
    }
    close_list.push_back(open_step);
  }
  while(last_step)
  {
    shortest_path_list.insert(shortest_path_list.begin(), last_step->__pos);
    last_step = last_step->__parent;
  }


  // clear the list;
  StepPtrList::iterator ptr_list_iter;
  for (ptr_list_iter = open_list.begin(); ptr_list_iter != open_list.end();) {
    Step* one_step_in_openlist = *ptr_list_iter;
    ptr_list_iter = open_list.erase(ptr_list_iter);
    delete one_step_in_openlist;
  }
  for (ptr_list_iter = close_list.begin(); ptr_list_iter != close_list.end();) {
    Step* one_step_in_closelist = *ptr_list_iter;
    ptr_list_iter = close_list.erase(ptr_list_iter);
    delete one_step_in_closelist;
  }  
  return shortest_path_list;

}


SGSTerrain* SGSTerrain::create(std::string& terrain_file, Size size)
{
  SGSTerrain* terrain = new SGSTerrain(terrain_file, size);
  return terrain;
}




SGSHero* SGSTerrain::findEnemyHeroInArea(SGSArea* area, SGSHero* hero)
{
  SGSPointList* point_list = &area->__point_list;
  SGSPointList::iterator iter;

  for (iter = point_list->begin(); iter != point_list->end(); iter++) {
    SGSPoint pos = *iter;
    SGSHero* one_hero = findHeroByPosition(pos);
    if (one_hero && hero->isRival(one_hero)) {
      return one_hero;
    }
  }
  return NULL;

}


SGSHero* SGSTerrain::findHeroByPosition(Vec2& pos)
{
  Vector<SGSHero*>::iterator iter;
  for (iter = __heroes.begin(); iter != __heroes.end(); iter++) {
    SGSHero* hero = *iter;
    Rect rect = hero->getBoundingBox();

    if(rect.containsPoint(pos)){
      return hero;
    }  
  }
  return NULL;

}
SGSHero* SGSTerrain::findHeroByPosition(SGSPoint& map_pos)
{
  Vec2 pos = SGSPoint::mapPos2OpenGLPos(map_pos);
  return findHeroByPosition(pos);
}




SGSHero* SGSTerrain::findNearestEnemyHero(SGSHero* hero)
{
  Vector<SGSHero*>::iterator iter;
  int distance = 65535;
  SGSHero* nearest_enemy_hero = NULL;
  for (iter = __heroes.begin(); iter != __heroes.end(); iter++) {
    SGSHero* enemy_hero = *iter;
    if (hero->isRival(enemy_hero)){
      int hero_distance;
      SGSPoint hero_pos = hero->getMapPosition();
      SGSPoint enemy_pos = enemy_hero->getMapPosition();
      hero_distance = (hero_pos.x - enemy_pos.x) * (hero_pos.x - enemy_pos.x)
                       + (hero_pos.y - enemy_pos.y) * (hero_pos.y - enemy_pos.y);
      if (hero_distance < distance) {
        distance = hero_distance;
        nearest_enemy_hero = enemy_hero;
      }
    }
  }
  return nearest_enemy_hero;
}


void SGSTerrain::loadTerrain(std::string& terrain_file)
{
  ssize_t size;
  unsigned char* terrain = FileUtils::getInstance()->getFileData(terrain_file, "rb", &size);
  for (int i = 0; i < __width * __height; i++) {
    __terrain_info[i] = static_cast<TERRAIN_TYPE>(terrain[i]);
  }
}

void SGSTerrain::notify(const char* reason, void* ptr)
{
  std::string notify_reason = reason;
  if (notify_reason == "hero_add") {
    SGSHero* hero = reinterpret_cast<SGSHero*>(ptr);
    __heroes.pushBack(hero);
  } else if (notify_reason == "object_add") {
    SGSObj* object = reinterpret_cast<SGSObj*>(ptr);
    __objects.pushBack(object);
  }
  return ;
}

bool SGSTerrain::isInStepList(Step& step, StepList& step_list)
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
bool SGSTerrain::isInStepPtrList(Step* step, StepPtrList& step_list)
{
  StepPtrList::iterator iter;
  for (iter = step_list.begin(); iter != step_list.end(); iter++) {
    Step* one_step = *iter;
    if (step->__pos == one_step->__pos) {
      return true;
    }
  }
  return false;

}


int SGSTerrain::getSteminaConsume(SGSHero::HERO_category category, TERRAIN_TYPE terrain)
{
  return SteminaConsuming[terrain][category];
}

SGSTerrain::Step SGSTerrain::moveHero(SGSHero* hero, STEP_DIRECTION one_step, Step step_from)
{
  Step step_to = step_from;

  Step current_step = step_from;
  SGSPoint origin_pos = hero->getMapPosition();

  SGSPoint left_pos = current_step.__pos;
  SGSPoint right_pos = current_step.__pos;
  SGSPoint up_pos = current_step.__pos;
  SGSPoint down_pos = current_step.__pos;

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
  case STEP_RIGHT:
    step_to.__pos.x++;
    if (findHeroByPosition(right_pos) || getObj(right_pos)) {
      valid_move = false;
    }

    if (!is_original_pos) {
      if (hero->isRival(findHeroByPosition(up_pos)) || hero->isRival(findHeroByPosition(down_pos))) {
        valid_move = false;
      }
    }
    break;
  case STEP_DOWN:
    step_to.__pos.y++;
    if (findHeroByPosition(down_pos) || getObj(down_pos)) {
      valid_move = false;
    }

    if (!is_original_pos) {
      if (hero->isRival(findHeroByPosition(up_pos)) || hero->isRival(findHeroByPosition(right_pos))) {
        valid_move = false;
      }
    }
    break;
  case STEP_LEFT:
    step_to.__pos.x--;
    if (findHeroByPosition(left_pos) || getObj(left_pos)) {
      valid_move = false;
    }
    if (!is_original_pos) {
      if (hero->isRival(findHeroByPosition(up_pos)) || hero->isRival(findHeroByPosition(down_pos))) {
        valid_move = false;
      }
    }
    
    break;
  case STEP_UP:
    step_to.__pos.y--;
    if (findHeroByPosition(up_pos) || getObj(up_pos)) {
      valid_move = false;
    }
    if (!is_original_pos) {
      if (hero->isRival(findHeroByPosition(left_pos)) || hero->isRival(findHeroByPosition(right_pos))) {
        valid_move = false;
      }
    }
    break;
  default:
    break;
  }

 
  if (step_to.__pos.x < 0 || step_to.__pos.y < 0 || 
      step_to.__pos.x >= __width || step_to.__pos.y >= __height ||
      valid_move == false) {
    step_to.__stamina = -100;
  } else {
    step_to.__stamina -= getSteminaConsume(hero->getcategory(), getTerrainAt(step_to.__pos));
  }

  return step_to;
}

SGSTerrain::TERRAIN_TYPE SGSTerrain::getTerrainAt(SGSPoint& pos)
{
  int x = pos.x;
  int y = pos.y;
  return static_cast<TERRAIN_TYPE>(__terrain_info[y * __width + x]);
}


SGSObj* SGSTerrain::getObj(SGSPoint& pos)
{
  Vector<SGSObj*>::iterator iter;
  for (iter = __objects.begin(); iter != __objects.end(); iter++) {
    SGSObj* obj = *iter;
    if (obj->getMapPosition() == pos) {
      return obj;
    }
  }
  return NULL;
}
NS_CC_END
