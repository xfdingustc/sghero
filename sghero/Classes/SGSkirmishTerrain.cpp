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