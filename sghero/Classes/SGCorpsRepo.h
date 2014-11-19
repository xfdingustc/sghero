#ifndef SG_CORPS_BASE_H
#define SG_CORPS_BASE_H

#include "cocos2d.h"
#include "SGObserver.h"
#include "SGCorpsRange.h"
#include <vector>
#include "json/document.h"

NS_CC_BEGIN

class SGCorpsRepo {
public:
	typedef struct {
		std::string code_name;
		std::string display_name;
		int	corps_id;
		std::vector<std::string> level_name;
		std::vector<int> level_range;
		std::vector<int> level_movement;
	} Corps_Info;
	static SGCorpsRepo *instance();
	SGCorpsRepo();
	~SGCorpsRepo();
	bool initCorpsRepo();
	Corps_Info *loadCorpsItemInfoByName(std::string name);
	Corps_Info *loadCorpsItemInfoById(int id);		

private:
	static SGCorpsRepo *__pInstance;
	void registerToCorpsRepo(Corps_Info *wp_info, const rapidjson::Value &val);
	std::vector<Corps_Info*> __all_corps;
	rapidjson::Document text_json;
};
NS_CC_END
#endif