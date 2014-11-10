#include "SGCorpsRange.h"

SGCorpsAttackRange *SGCorpsAttackRange::__pInstance = NULL;

SGCorpsAttackRange::SGCorpsAttackRange() {

}

SGCorpsAttackRange::~SGCorpsAttackRange() {

}

SGCorpsAttackRange *SGCorpsAttackRange::instance() {
	if(0 == __pInstance) {
		static SGCorpsAttackRange real_range_repo;
		if (false == real_range_repo.initAttackRange()) {
			log("Fail to init the corps range!");
			return NULL;
		}
		__pInstance = &real_range_repo;
	}

	return __pInstance;
}

bool SGCorpsAttackRange::initAttackRange() {

	int i = 0;
	SGSPointList shortcut_list1;
	SGSPointList shortcut_list2;

	shortcut_list1.push_back(SGSPoint(-4, 0));
	shortcut_list1.push_back(SGSPoint(-3, 1));
	shortcut_list1.push_back(SGSPoint(-3, -1));
	shortcut_list1.push_back(SGSPoint(-2, 2));
	shortcut_list1.push_back(SGSPoint(-2, -2));
	shortcut_list1.push_back(SGSPoint(-1, 3));
	shortcut_list1.push_back(SGSPoint(-1, -3));
	shortcut_list1.push_back(SGSPoint(0, 4));
	shortcut_list1.push_back(SGSPoint(0, -4));
	shortcut_list1.push_back(SGSPoint(1, 3));
	shortcut_list1.push_back(SGSPoint(1, -3));
	shortcut_list1.push_back(SGSPoint(2, 2));
	shortcut_list1.push_back(SGSPoint(2, -2));
	shortcut_list1.push_back(SGSPoint(3, 1));
	shortcut_list1.push_back(SGSPoint(3, -1));
	shortcut_list1.push_back(SGSPoint(4, 0));


	shortcut_list2.push_back(SGSPoint(-3, 0));
	shortcut_list2.push_back(SGSPoint(-1, 2));
	shortcut_list2.push_back(SGSPoint(-1, -2));
	shortcut_list2.push_back(SGSPoint(-2, 1));
	shortcut_list2.push_back(SGSPoint(-2, -1));
	shortcut_list2.push_back(SGSPoint(0, 3));
	shortcut_list2.push_back(SGSPoint(0, -3));
	shortcut_list2.push_back(SGSPoint(1, 2));
	shortcut_list2.push_back(SGSPoint(1, -2));
	shortcut_list2.push_back(SGSPoint(2, 1));
	shortcut_list2.push_back(SGSPoint(2, -1));
	shortcut_list2.push_back(SGSPoint(3, 0));

	// CORPS_RANGE_HERO
	rangeList[0].push_back(SGSPoint(-1, 0));
	rangeList[0].push_back(SGSPoint(0, -1));
	rangeList[0].push_back(SGSPoint(1, 0));
	rangeList[0].push_back(SGSPoint(0, 1));

	// CORPS_RANGE_INFANTRY
	for (i = 0; i < rangeList[0].size(); i++) {
		rangeList[1].push_back(rangeList[0].at(i));
	}
	rangeList[1].push_back(SGSPoint(-1, -1));
	rangeList[1].push_back(SGSPoint(1, -1));
	rangeList[1].push_back(SGSPoint(-1, 1));
	rangeList[1].push_back(SGSPoint(1, 1));

	// CORPS_RANGE_MOYU
	for (i = 0; i < rangeList[1].size(); i++) {
		rangeList[2].push_back(rangeList[1].at(i));
	}
	rangeList[2].push_back(SGSPoint(-2, 0));
	rangeList[2].push_back(SGSPoint(0, -2));
	rangeList[2].push_back(SGSPoint(2, 0));
	rangeList[2].push_back(SGSPoint(0, 2));

	// CORPS_RANGE_BROAD_SWORD
	for (i = 0; i < rangeList[2].size(); i++) {
		rangeList[3].push_back(rangeList[2].at(i));
	}
	rangeList[3].push_back(SGSPoint(-2, 1));
	rangeList[3].push_back(SGSPoint(-2, -1));
	rangeList[3].push_back(SGSPoint(2, 1));
	rangeList[3].push_back(SGSPoint(2, -1));
	rangeList[3].push_back(SGSPoint(1, -2));
	rangeList[3].push_back(SGSPoint(-1, -2));
	rangeList[3].push_back(SGSPoint(1, 2));
	rangeList[3].push_back(SGSPoint(-1, 2));

	// CORPS_RANGE_BIG_MOYU
	for (i = 0; i < rangeList[3].size(); i++) {
		rangeList[4].push_back(rangeList[3].at(i));
	}
	rangeList[4].push_back(SGSPoint(-3, 0));
	rangeList[4].push_back(SGSPoint(3, 0));
	rangeList[4].push_back(SGSPoint(0, 3));
	rangeList[4].push_back(SGSPoint(0, -3));

	// CORPS_RANGE_SUPER_BIG_MOYU
	for (i = 0; i < rangeList[4].size(); i++) {
		rangeList[5].push_back(rangeList[4].at(i));
	}
	for (i = 0; i< shortcut_list1.size(); i++) {
		rangeList[5].push_back(shortcut_list1.at(i));
	}

	// CORPS_RANGE_NORMAL_SWORD
	rangeList[6].push_back(SGSPoint(-2, 0));
	rangeList[6].push_back(SGSPoint(0, -2));
	rangeList[6].push_back(SGSPoint(2, 0));
	rangeList[6].push_back(SGSPoint(0, 2));
	rangeList[6].push_back(SGSPoint(-2, 1));
	rangeList[6].push_back(SGSPoint(-2, -1));
	rangeList[6].push_back(SGSPoint(2, 1));
	rangeList[6].push_back(SGSPoint(2, -1));
	rangeList[6].push_back(SGSPoint(1, -2));
	rangeList[6].push_back(SGSPoint(-1, -2));
	rangeList[6].push_back(SGSPoint(1, 2));
	rangeList[6].push_back(SGSPoint(-1, 2));

	// CORPS_RANGE_SPEAR
	for (i = 0; i < rangeList[0].size(); i++) {
		rangeList[7].push_back(rangeList[0].at(i));
	}
	rangeList[7].push_back(SGSPoint(-2, 0));
	rangeList[7].push_back(SGSPoint(2, 0));
	rangeList[7].push_back(SGSPoint(0, 2));
	rangeList[7].push_back(SGSPoint(0, -2));

	// CORPS_RANGE_LONG_SPEAR
	for (i = 0; i < rangeList[7].size(); i++) {
		rangeList[8].push_back(rangeList[7].at(i));
	}
	rangeList[8].push_back(SGSPoint(-3, 0));
	rangeList[8].push_back(SGSPoint(3, 0));
	rangeList[8].push_back(SGSPoint(0, 3));
	rangeList[8].push_back(SGSPoint(0, -3));

	// CORPS_RANGE_GENERAL
	for (i = 0; i < rangeList[1].size(); i++) {
		rangeList[9].push_back(rangeList[1].at(i));
	}
	rangeList[9].push_back(SGSPoint(-2, 2));
	rangeList[9].push_back(SGSPoint(2, 2));
	rangeList[9].push_back(SGSPoint(2, -2));
	rangeList[9].push_back(SGSPoint(-2, -2));

	// CORPS_RANGE_HORSEARCHER
	rangeList[10].push_back(SGSPoint(-2, 0));
	rangeList[10].push_back(SGSPoint(0, 2));
	rangeList[10].push_back(SGSPoint(0, -2));
	rangeList[10].push_back(SGSPoint(2, 0));
	rangeList[10].push_back(SGSPoint(-1, 1));
	rangeList[10].push_back(SGSPoint(1, 1));
	rangeList[10].push_back(SGSPoint(1, -1));
	rangeList[10].push_back(SGSPoint(-1, -1));

	// CORPS_RANGE_GREAT_HORSEARCHER
	for (i = 0; i < rangeList[10].size(); i++) {
		rangeList[11].push_back(rangeList[10].at(i));
	}
	for (i = 0; i< shortcut_list2.size(); i++) {
		rangeList[11].push_back(shortcut_list2.at(i));
	}

	// CORPS_RANGE_BALLISTA
	for (i = 0; i < rangeList[11].size(); i++) {
		rangeList[12].push_back(rangeList[11].at(i));
	}
	for (i = 0; i< shortcut_list1.size(); i++) {
		rangeList[12].push_back(shortcut_list1.at(i));
	}

	// CORPS_RANGE_SHORTBOW
	rangeList[13].push_back(SGSPoint(-3, 0));
	rangeList[13].push_back(SGSPoint(3, 0));
	rangeList[13].push_back(SGSPoint(-2, 1));
	rangeList[13].push_back(SGSPoint(-2, -1));
	rangeList[13].push_back(SGSPoint(0, 3));
	rangeList[13].push_back(SGSPoint(0, -3));
	rangeList[13].push_back(SGSPoint(2, 1));
	rangeList[13].push_back(SGSPoint(2, -1));
	rangeList[13].push_back(SGSPoint(1, 2));
	rangeList[13].push_back(SGSPoint(1, -2));
	rangeList[13].push_back(SGSPoint(-1, 2));
	rangeList[13].push_back(SGSPoint(-1, -2));

	// CORPS_RANGE_LONGBOW
	for (i = 0; i < rangeList[13].size(); i++) {
		rangeList[14].push_back(rangeList[13].at(i));
	}
	for (i = 0; i< shortcut_list1.size(); i++) {
		rangeList[14].push_back(shortcut_list1.at(i));
	}

	// CORPS_RANGE_STRONGBOW
	for (i = 0; i < rangeList[14].size(); i++) {
		rangeList[15].push_back(rangeList[14].at(i));
	}	
	rangeList[15].push_back(SGSPoint(-4, 1));
	rangeList[15].push_back(SGSPoint(-4, -1));
	rangeList[15].push_back(SGSPoint(-3, 2));
	rangeList[15].push_back(SGSPoint(-3, -2));
	rangeList[15].push_back(SGSPoint(-2, 3));
	rangeList[15].push_back(SGSPoint(-2, -3));
	rangeList[15].push_back(SGSPoint(-1, 4));
	rangeList[15].push_back(SGSPoint(-1, -4));
	rangeList[15].push_back(SGSPoint(1, 4));
	rangeList[15].push_back(SGSPoint(1, -4));
	rangeList[15].push_back(SGSPoint(2, 3));
	rangeList[15].push_back(SGSPoint(2, -3));
	rangeList[15].push_back(SGSPoint(3, 2));
	rangeList[15].push_back(SGSPoint(3, -2));
	rangeList[15].push_back(SGSPoint(4, 1));
	rangeList[15].push_back(SGSPoint(4, -1));
	rangeList[15].push_back(SGSPoint(5, 0));
	rangeList[15].push_back(SGSPoint(-5, 0));
	rangeList[15].push_back(SGSPoint(0, 5));
	rangeList[15].push_back(SGSPoint(0, -5));

	// CORPS_RANGE_REMOTE_GUN_CARRIAGE
	for (i = -2; i < 3; i++) {
		rangeList[16].push_back(SGSPoint(-4, i));
		rangeList[16].push_back(SGSPoint(4, i));
		rangeList[16].push_back(SGSPoint(i, -4));
		rangeList[16].push_back(SGSPoint(i, 4));
	}
	rangeList[16].push_back(SGSPoint(3, 3));
	rangeList[16].push_back(SGSPoint(3, -3));
	rangeList[16].push_back(SGSPoint(-3, 3));
	rangeList[16].push_back(SGSPoint(-3, -3));

	// CORPS_RANGE_GUN_CARRIAGE
	for (i = 0; i < rangeList[16].size(); i++) {
		rangeList[17].push_back(rangeList[16].at(i));
	}	
	for (i = -2; i < 3; i++) {
		rangeList[17].push_back(SGSPoint(-3, i));
		rangeList[17].push_back(SGSPoint(3, i));
		rangeList[17].push_back(SGSPoint(i, -3));
		rangeList[17].push_back(SGSPoint(i, 3));
	}

	for (i = 0; i < static_cast<int>(CORPS_RANGE_MAX); i++) {
		rangeList[i].shrink_to_fit();
	}

	/*
	shortcut_list1.clear();
	shortcut_list1.shrink_to_fit();
	shortcut_list2.clear();
	shortcut_list2.shrink_to_fit();
	*/
	return true;
}