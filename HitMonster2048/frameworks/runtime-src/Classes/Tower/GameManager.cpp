//
//  GameManager.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#include "GameManager.h"
#include "SimpleAudioEngine.h" 

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();
	return instance;
}

bool GameManager::init()
{
	bool bRet = false;
	do
	{


		bRet = true;
	} while (0);
	return bRet;
}

void GameManager::setCurMapID(int curID)
{
    _curMapId = curID;
}

int GameManager::getCurMapID()
{
    return _curMapId;
}

void GameManager::clear()
{
	enemyVector.clear();
	bulletVector.clear();
	//towerVector.clear();
	groupVector.clear();
}