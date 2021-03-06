#include "SGWeaponRepo.h"
#include "SGGlobalSettings.h"
#include <vector>
#include <stdlib.h>

NS_CC_BEGIN

SGWeaponRepo *SGWeaponRepo::__pInstance = NULL;

SGWeaponRepo::SGWeaponRepo() {
	__all_weapons.clear();
}

SGWeaponRepo *SGWeaponRepo::instance() {
	if(0 == __pInstance) {
		static SGWeaponRepo real_repo;
		if (false == real_repo.initWeaponRepo()) {
			log("Fail to get the weapon repo!");
			return NULL;
		}
		__pInstance = &real_repo;
	}

	return __pInstance;
}

bool SGWeaponRepo::initWeaponRepo() {
	
	std::string weapon_repo_json_file = FileUtils::getInstance()->fullPathForFilename(WEAPON_REPO_TEXT_JSON_FILE);
	std::string json_data = FileUtils::getInstance()->getStringFromFile(weapon_repo_json_file.c_str());
		
	text_json.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (text_json.HasParseError()) {
    log("Parsing weapon info text json file error!! %s", text_json.GetParseError());
    return false;
	} else if (text_json.IsObject()) {
		const rapidjson::Value &weapon_list = text_json["WeaponList"];
		if (weapon_list.IsArray()) {
			for (int i=0; i < weapon_list.Size(); i++) {
				Weapon_Full_Info *weapon_item = new Weapon_Full_Info;
				memset(weapon_item, 0, sizeof(Weapon_Full_Info));
				const rapidjson::Value &item = weapon_list[i];
				registerToWeaponRepo(weapon_item, item);
			}
		}

		const rapidjson::Value &curve_list = text_json["WeaponGrowthCurve"];
		if (curve_list.HasMember("Common")) {
			const rapidjson::Value &curve = curve_list["Common"];
			for(int i=0; i < curve.Size(); i++) {
				common_growth_curve.push_back(curve[i].GetInt());
			}
		}
		if (curve_list.HasMember("Super")) {
			const rapidjson::Value &curve = curve_list["Super"];
			for(int i=0; i < curve.Size(); i++) {
				super_growth_curve.push_back(curve[i].GetInt());
			}
		}				
	} 
	
	return true;
}

Weapon_Full_Info *SGWeaponRepo::loadWeaponItemInfo(std::string code_name) {
	for ( std::vector<Weapon_Full_Info *>::iterator iter = __all_weapons.begin(); iter != __all_weapons.end(); iter++ ) {
		if (NULL != *iter) 
		{
			if ((*iter)->code_name == code_name.c_str()) {				
				return (*iter);
			}
		}	
	}
	log("Fail to find the specified weapon %s", code_name.c_str());
	return NULL;
}

void SGWeaponRepo::registerToWeaponRepo(Weapon_Full_Info *wp_info, const rapidjson::Value &item) {
	wp_info->display_name = item["Name"].GetString();
	wp_info->code_name = item["Abbreviation"].GetString();
	wp_info->effect = item["Effect"].GetString();
	wp_info->description = item["Description"].GetString();
	wp_info->corps_avail_1 = strtol(item["CorpsAvail1"].GetString(), NULL, 16);
	wp_info->corps_avail_2 = strtol(item["CorpsAvail2"].GetString(), NULL, 16);
	wp_info->corps_avail_3 = strtol(item["CorpsAvail3"].GetString(), NULL, 16);
	wp_info->corps_avail_4 = strtol(item["CorpsAvail4"].GetString(), NULL, 16);
	wp_info->attribute = static_cast<WEAPON_ATTR>(item["Attr"].GetInt()); 

	if(item.HasMember("ResPic")) {
		std::string weapon_res_name = SG_WEAPON_REPO_RES_PATH;
		weapon_res_name.append(item["ResPic"].GetString());
		std::string weapon_item_res_path = 
			FileUtils::getInstance()->fullPathForFilename(weapon_res_name);
		wp_info->frame = SpriteFrame::create(weapon_item_res_path, 
					Rect(0, 0, SG_WEAPON_ITEM_RES_WIDTH, SG_WEAPON_ITEM_RES_HEIGHT));		
		wp_info->frame->retain();
	}	
	if (item.HasMember("Type")) {
		wp_info->type = static_cast<WEAPON_TYPE>(item["Type"].GetInt());
		if (wp_info->type == 0) {
			wp_info->growth_curve = common_growth_curve;
		}	else if (wp_info->type == 1) {
			wp_info->growth_curve = super_growth_curve;
		}	
	}
	if (item.HasMember("Category")) {
		wp_info->category = item["Category"].GetString();
	}
	if (item.HasMember("Attack")) {
		const rapidjson::Value &curve = item["Attack"];
		int level_num = curve.Size();
		for (int i=0; i< level_num; i++) {
			wp_info->attack.push_back(curve[i].GetInt());
		}
	}
	if (item.HasMember("Defense")) {
		const rapidjson::Value &curve = item["Defense"];
		int level_num = curve.Size();
		for (int i=0; i< level_num; i++) {
			wp_info->defense.push_back(curve[i].GetInt());
		}
	}
	if (item.HasMember("HPPercent")) {
		const rapidjson::Value &curve = item["HPPercent"];
		int level_num = curve.Size();
		for (int i=0; i< level_num; i++) {
			wp_info->hpPercent.push_back(curve[i].GetInt());
		}
	}

	// Shrink vector to fit
	wp_info->growth_curve.shrink_to_fit();
	wp_info->attack.shrink_to_fit();
	wp_info->defense.shrink_to_fit();
	wp_info->spirit.shrink_to_fit();
	wp_info->morale.shrink_to_fit();
	wp_info->explosive.shrink_to_fit();
	wp_info->move.shrink_to_fit();
	wp_info->hpPercent.shrink_to_fit();
	wp_info->hp.shrink_to_fit();
	wp_info->mp.shrink_to_fit();
	
	/*
	std::vector<int>(wp_info->attack).swap(wp_info->attack);
	std::vector<int>(wp_info->defense).swap(wp_info->defense);
	std::vector<int>(wp_info->spirit).swap(wp_info->spirit);
	std::vector<int>(wp_info->morale).swap(wp_info->morale);
	std::vector<int>(wp_info->explosive).swap(wp_info->explosive);
	std::vector<int>(wp_info->move).swap(wp_info->move);
	std::vector<int>(wp_info->hpPercent).swap(wp_info->hpPercent);
	std::vector<int>(wp_info->hp).swap(wp_info->hp);
	std::vector<int>(wp_info->mp).swap(wp_info->mp); 
	*/
	
	__all_weapons.push_back(wp_info);
}

SGWeaponRepo::~SGWeaponRepo() {
	for ( std::vector<Weapon_Full_Info*>::iterator iter = __all_weapons.begin(); iter != __all_weapons.end(); iter++) {
		if (NULL != *iter) {
			if ((*iter)->frame != NULL) {
				(*iter)->frame->release();
			}
			delete *iter; 
			*iter = NULL;
		}	
	}
	__all_weapons.clear();
}

NS_CC_END
