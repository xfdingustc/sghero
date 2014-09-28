#include "SGSceneBase.h"
#include "SGSceneHeroSpeakScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool SGSceneBase::onHandleEventSoundEffect(tinyxml2::XMLElement* event)
{
  const char* sound_effect = event->Attribute("effect");
  SimpleAudioEngine::getInstance()->playEffect(sound_effect, false);
  return true;
}

bool SGSceneBase::onHandleEventSoundTrack(tinyxml2::XMLElement* event)
{
  std::string track = event->Attribute("track");
  SimpleAudioEngine::getInstance()->playBackgroundMusic(track.c_str());
  return true;
}

bool SGSceneBase::onHandleEventDialog(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  std::string speak = event->Attribute("content");
  double x = 0, y = 0;
  event->QueryDoubleAttribute("x", &x);
  event->QueryDoubleAttribute("y", &y);

  Vec2 win_pos(x, y);

  formatString(speak);

  Scene* scene = SGSceneHeroSpeakScene::creatScene(hero_name.c_str(), speak.c_str(), win_pos);
  SGSceneHeroSpeakScene* layer = (SGSceneHeroSpeakScene*)scene->getChildByName("dialog_layer");
  layer->setObserver(this);
  Director::getInstance()->pushScene(scene);
 
  return true;
}

void SGSceneBase::formatString(std::string& str)
{
  // replace "\\n" to "\n"
  std::string::size_type pos = 0;
  std::string src_str = "\\n";
  std::string des_str = "\n";
  std::string::size_type srcLen = src_str.size();  
  std::string::size_type desLen = src_str.size();  
  while ((pos = str.find(src_str, pos)) != std::string::npos){
    str.replace( pos, srcLen, des_str );
    pos += desLen;
  }
}