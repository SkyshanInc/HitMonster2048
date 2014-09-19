//
//  MultiDirTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__MultiDirTower__
#define __thiefTD__MultiDirTower__

#include "TowerBase.h"


class MultiDirTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(MultiDirTower);
    
    //void rotateAndShoot(float dt);
    void shoot(float dt){//donoting
        
    };
    void removeBullet(Node* pSender);
    Sprite* MultiDirTowerBullet();
    void createBullet6(float dt);
private:
    Sprite* rotateArrow;
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__MultiDirTower__) */
