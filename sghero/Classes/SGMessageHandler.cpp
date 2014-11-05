#include "SGMessageHandler.h"

SGMessageHandler::~SGMessageHandler()
{
  std::list<SGMessage*>::iterator iter;
  for (iter = __msg_list.begin(); iter != __msg_list.end(); iter++) {
    SGMessage* msg = *iter;
    if (msg) {
      free(msg);
    }
  }
  __msg_list.clear();
}


void SGMessageHandler::postMessage(SGMessage* message)
{
  __msg_list.push_back(message);
}