//
//  TowerBase.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#ifndef __thiefTD__TowerBase__
#define __thiefTD__TowerBase__

#include <iostream>
#include "cocos2d.h"

#include "EnemyBase.h"


USING_NS_CC;

typedef enum  {
	ATTACK_BULLET = 0,
	DECELERATE_BULLET,

}BULLET_TPYE;

class TowerBase: public Sprite
{
public:
    TowerBase();
    
    virtual bool init();
    CREATE_FUNC(TowerBase);
    
    void checkNearestEnemy();
    
    CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线范围
	CC_SYNTHESIZE(int, towerValue, TowerValue);  // 
    CC_SYNTHESIZE(float, lethality, Lethality);   // 杀伤力
    CC_SYNTHESIZE(float, rate, Rate);  //
    
	//bool onTouchBegan(Touch *touch, Event *event);
	//void onTouchEnded(Touch* touch, Event* event);

protected:
    EnemyBase* nearestEnemy;    // 塔子视野内最近的敌人
    
};


#endif /* defined(__thiefTD__TowerBase__) */
