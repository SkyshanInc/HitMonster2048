//
//  DecelerateTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "ElectricityTower.h"
#include "GameManager.h"

bool ElectricityTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);
    setLethality(1);
    setRate(2);
    tower= Sprite::createWithSpriteFrameName("mftower.png");
    addChild(tower);
    
    schedule(schedule_selector(ElectricityTower::shoot), 0.8f);
	return true;
}


Sprite* ElectricityTower::ElectricityTowerBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("bullet.png");
    bullet->setPosition(0, tower->getContentSize().height /4 );
	bullet->setTag(DECELERATE_BULLET);
    //bullet->setRotation(rotateArrow->getRotation());
    addChild(bullet);
    
    return bullet;
}

void ElectricityTower::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    checkNearestEnemy();
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = ElectricityTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector.getNormalized();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (currBullet->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ElectricityTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void ElectricityTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}