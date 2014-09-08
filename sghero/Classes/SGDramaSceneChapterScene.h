#ifndef SG_DRAMA_SCENE_CHAPTER_SCENE_H
#define SG_DRAMA_SCENE_CHAPTER_SCENE_H


#include "cocos2d.h"

USING_NS_CC;

class SGDramaSceneChapterScene : public LayerColor 
{
public:
  static Scene* createScene(const char* chapter_num, const char* chapter_title);
  CREATE_FUNC(SGDramaSceneChapterScene);
  virtual bool init();
private:
  void showChapterTitle(float dt);
  void exitChapter(float dt);
  std::string __chapter_num;
  std::string __chapter_title;
  LabelTTF* __content_ttf;
};

#endif // !SG_DRAMA_SCENE_CHAPTER_SCENE_H