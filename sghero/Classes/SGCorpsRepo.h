#ifndef SG_CORPS_BASE_H
#define SG_CORPS_BASE_H

#include "SGCorpsType.h"
#include "cocos2d.h"
#include "SGObserver.h"
#include <vector>
#include "json/document.h"

class SGCorpsRepo {
public:
	static SGCorpsRepo *instance();
	SGCorpsRepo();
	~SGCorpsRepo();
	bool initCorpsRepo();
	Corps_Info *loadCorpsItemInfo(std::string name);
	//TODO: this API may save the time of item search
	//Corps_Info *getCorpsnItemInfoByIdx(CORPS_GROUP group, int index);		

private:
	static SGCorpsRepo *__pInstance;
	void registerToCorpsRepo(Corps_Info *wp_info, const rapidjson::Value &val);
	std::vector<Corps_Info*> __all_corps;
	rapidjson::Document text_json;
};

#endif