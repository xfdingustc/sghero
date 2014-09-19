#include "SGSceneBase.h"
#include "SGSceneHeroSpeakScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void SGSceneBase::onHandleEventSoundEffect(tinyxml2::XMLElement* event)
{
  const char* sound_effect = event->Attribute("effect");
  SimpleAudioEngine::getInstance()->playEffect(sound_effect, false);
  __event_list.pop_front();
}

void SGSceneBase::onHandleEventSoundTrack(tinyxml2::XMLElement* event)
{
  std::string track = event->Attribute("track");
  SimpleAudioEngine::getInstance()->playBackgroundMusic(track.c_str());
  __event_list.pop_front();
}

void SGSceneBase::onHandleEventDialog(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  std::string speak = event->Attribute("content");

  formatString(speak);

  
  Scene* scene = SGSceneHeroSpeakScene::creatScene(hero_name.c_str(), speak.c_str());
  Director::getInstance()->pushScene(scene);
 
  __event_list.pop_front();
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