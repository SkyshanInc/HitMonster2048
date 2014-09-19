//
//  ThiefBase.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#ifndef __thiefTD__ThiefBase__
#define __thiefTD__ThiefBase__

#include <iostream>
#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;

class Thief : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Thief* createThief(Vector<Node*> points, int hp);
    void changeDirection(float dt);
    void enemyExpload();
};

class Pirate : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Pirate* createPirate(Vector<Node*> points, int hp);
    void changeDirection(float dt);
    void enemyExpload();
};

class Bandit : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Bandit* createBandit(Vector<Node*> points, int hp);
    void changeDirection(float dt);
    void enemyExpload();
};
#endif /* defined(__thiefTD__ThiefBase__) */
