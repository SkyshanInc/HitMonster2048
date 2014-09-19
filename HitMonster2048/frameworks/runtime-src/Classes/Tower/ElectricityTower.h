//
//  DecelerateTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__ElectricityTower__
#define __thiefTD__ElectricityTower__

#include "TowerBase.h"


class ElectricityTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ElectricityTower);
    
    //void rotateAndShoot(float dt);
    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* ElectricityTowerBullet();
    
private:
    Sprite* rotateArrow;
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__ElectricityTower__) */
