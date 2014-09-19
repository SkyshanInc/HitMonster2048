//
//  GameManager.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#ifndef __thiefTD__GameManager__
#define __thiefTD__GameManager__

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h" 

USING_NS_CC;
using namespace CocosDenshion; 

class GameManager
{
public:
    
    Vector<EnemyBase*> enemyVector;
    Vector<Sprite*> bulletVector;
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;

	CC_SYNTHESIZE(float, blood, Blood);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	CC_SYNTHESIZE(const char*, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
	CC_SYNTHESIZE(const char*, curBgName, CurBgName);
	
	//CC_SYNTHESIZE(int, enemyType, EnemyType);
	//CC_SYNTHESIZE(int, enemyCount, EnemyCount);

	//GroupEnemy* initGroup(int type, int count);

	int _curMapId;
	void setCurMapID(int curID);
    int getCurMapID();

	static GameManager* getInstance();
    bool init();
	void clear();
private:
	static GameManager *instance;
};
#endif /* defined(__thiefTD__GameManager__) */
