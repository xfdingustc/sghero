#include "SGCorpsRepo.h"
#include "SGGlobalSettings.h"
#include <vector>

NS_CC_BEGIN

SGCorpsRepo *SGCorpsRepo::__pInstance = NULL;

SGCorpsRepo::SGCorpsRepo() {
	__all_corps.clear();
}

SGCorpsRepo *SGCorpsRepo::instance() {
	if(0 == __pInstance) {
		static SGCorpsRepo real_repo;
		if (false == real_repo.initCorpsRepo()) {
			log("Fail to get the corps repo!");
			return NULL;
		}
		__pInstance = &real_repo;
	}

	return __pInstance;
}

bool SGCorpsRepo::initCorpsRepo() {
	
	std::string corps_repo_json_file = FileUtils::getInstance()->fullPathForFilename(CORPS_REPO_TEXT_JSON_FILE);
	std::string json_data = FileUtils::getInstance()->getStringFromFile(corps_repo_json_file.c_str());

	text_json.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (text_json.HasParseError()) {
    log("Parsing corps info text json file error!! %s", text_json.GetParseError());
    return false;
	} else if (text_json.IsObject()) {
		const rapidjson::Value &res_list = text_json["CorpsList"];
		if (res_list.IsArray()) {
			for (int i=0; i < res_list.Size(); i++) {
				Corps_Info *corps_item = new Corps_Info;
				memset(corps_item, 0, sizeof(Corps_Info));
				const rapidjson::Value &item = res_list[i];
				registerToCorpsRepo(corps_item, item);
			}
		}
	}
	return true;
}

SGCorpsRepo::Corps_Info *SGCorpsRepo::loadCorpsItemInfoByName(std::string name) {
	for ( std::vector<Corps_Info *>::iterator iter = __all_corps.begin(); iter != __all_corps.end(); iter++ ) {
		if (NULL != *iter) 
		{
			if ((*iter)->code_name == name.c_str()) {				
				return (*iter);
			}
		}	
	}
	log("Fail to find the specified corps %s", name.c_str());
	return NULL;
}

SGCorpsRepo::Corps_Info *SGCorpsRepo::loadCorpsItemInfoById(int id) {
	for ( std::vector<Corps_Info *>::iterator iter = __all_corps.begin(); iter != __all_corps.end(); iter++ ) {
		if (NULL != *iter) 
		{
			if ((*iter)->corps_id == id) {				
				return (*iter);
			}
		}	
	}
	log("Fail to find the specified corps %d", id);
	return NULL;
}

void SGCorpsRepo::registerToCorpsRepo(Corps_Info *corps_info, const rapidjson::Value &item) {
	corps_info->display_name = item["Category"].GetString();
	corps_info->code_name = item["Abbreviation"].GetString();
	corps_info->corps_id = item["CorpsId"].GetInt();
	
	if (item.HasMember("Level")) {
		const rapidjson::Value &curve = item["Level"];
		int level_num = curve.Size();
		for (int i=0; i< level_num; i++) {
			corps_info->level_name.push_back(curve[i].GetString());
		}
	}
	if (item.HasMember("Range")) {
		const rapidjson::Value &curve = item["Range"];
		int level_num = curve.Size();
		for (int i=0; i< level_num; i++) {
			corps_info->level_range.push_back(curve[i].GetInt());
		}
	}
	if (item.HasMember("Move")) {
		const rapidjson::Value &curve = item["Move"];
		int level_num = curve.Size();
		for (int i=0; i< level_num; i++) {
			corps_info->level_movement.push_back(curve[i].GetInt());
		}
	}
	
	__all_corps.push_back(corps_info);
}

SGCorpsRepo::~SGCorpsRepo() {
	for ( std::vector<Corps_Info*>::iterator iter = __all_corps.begin(); iter != __all_corps.end(); iter++) {
		if (NULL != *iter) 
		{
			delete *iter; 
			*iter = NULL;
		}	
	}
	__all_corps.clear();
	// since we destruct the SGCorpsRepo here
	// there's no need to do a vector().swap
}

NS_CC_END
