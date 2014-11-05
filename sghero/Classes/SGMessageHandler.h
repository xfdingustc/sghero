#ifndef SG_MESSAGE_HANDLE_H
#define SG_MESSAGE_HANDLE_H
#include "cocos2d.h"
USING_NS_CC;
#include "SGMessage.h"

class SGMessage;
class SGMessageHandler 
{
public:
  virtual ~SGMessageHandler();
  void postMessage(SGMessage* message);

private:
  std::list<SGMessage*> __msg_list;
};


#endif