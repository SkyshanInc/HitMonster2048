//
//  MultiDirTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "MultiDirTower.h"
#include "GameManager.h"
#include <algorithm>

bool MultiDirTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(60);
	setTowerValue(600);
    setLethality(0.5);
    setRate(3);
    tower= Sprite::createWithSpriteFrameName("deceleratetower.png");
    addChild(tower);
    
    schedule(schedule_selector(MultiDirTower::createBullet6), 0.8f);
	return true;
}


Sprite* MultiDirTower::MultiDirTowerBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    bullet->setPosition(0, tower->getContentSize().height /4 );
	bullet->setTag(ATTACK_BULLET);
    //bullet->setRotation(rotateArrow->getRotation());
    addChild(bullet);
    
    return bullet;
}

void MultiDirTower::createBullet6(float dt)
{
	GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
	checkNearestEnemy();
	if(nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0 )
    {
		for(int i = 0; i < 6; i++)
		{
			auto currBullet = MultiDirTowerBullet();
			instance->bulletVector.pushBack(currBullet);
        
			auto moveDuration = getRate();
		
			Point shootVector;
			shootVector.x = 1;
			shootVector.y = tan( 60 * i * 2 * M_PI /360 );
			Point normalizedShootVector;
			if( 60 * i >= 180 )
			{
				normalizedShootVector = shootVector.getNormalized();
			}else{
				normalizedShootVector = -shootVector.getNormalized();
			}       
			auto farthestDistance = Director::getInstance()->getWinSize().width;
			Point overshotVector = normalizedShootVector * farthestDistance;
			Point offscreenPoint = (currBullet->getPosition() - overshotVector);
        
			currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
												   CallFuncN::create(CC_CALLBACK_1(MultiDirTower::removeBullet, this)),
												   NULL));
			currBullet = NULL;
		}
	}
}


void MultiDirTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();  
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}