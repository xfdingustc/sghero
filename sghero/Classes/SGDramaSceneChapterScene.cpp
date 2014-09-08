#include "SGDramaSceneChapterScene.h"
#include "SGGlobalSettings.h"

Scene* SGDramaSceneChapterScene::createScene(const char* chapter_num, const char* chapter_title)
{
  Scene* scene = Scene::create();

  SGDramaSceneChapterScene* layer = SGDramaSceneChapterScene::create();
  layer->__chapter_num = chapter_num;
  layer->__chapter_title = chapter_title;

  Size size = Director::getInstance()->getVisibleSize();
  layer->__content_ttf = LabelTTF::create(layer->__chapter_num, TEXT_FONT_NAME, CHAPTER_TEXT_FONT_SIZE);
  layer->__content_ttf->setPosition(Vec2(size.width/2, size.height/2));
  layer->addChild(layer->__content_ttf);

  scene->addChild(layer);

  return scene;
}

bool SGDramaSceneChapterScene::init()
{
  if (!LayerColor::initWithColor(Color4B::BLACK)) {
    return false;
  }


  scheduleOnce(schedule_selector(SGDramaSceneChapterScene::showChapterTitle), 3.0f);
  scheduleOnce(schedule_selector(SGDramaSceneChapterScene::exitChapter), 6.0f);
  return true;
}

void SGDramaSceneChapterScene::showChapterTitle(float dt)
{
  __content_ttf->setString(__chapter_title);
}
void SGDramaSceneChapterScene::exitChapter(float dt)
{
  Director::getInstance()->popScene();
}