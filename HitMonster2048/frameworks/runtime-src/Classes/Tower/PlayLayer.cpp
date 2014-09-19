//
//  PlayLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//
#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "PlayLayer.h"
#include "GameManager.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC_EXT;
using namespace CocosDenshion;

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
,chooseTowerpanle(NULL)
,towerMatrix(NULL)
,groupCounter(0)
,isSuccessful(false)
{
}

PlayLayer::~PlayLayer()
{
	if (towerMatrix) {
        free(towerMatrix);
    }
	pointsVector.clear();
}

Scene *PlayLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

bool PlayLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    instance = GameManager::getInstance();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
    
    map = TMXTiledMap::create("tilemap0.tmx");
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    this->addChild(map, -10);
	
    
    offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
	//addGroupEnemy();
    schedule(schedule_selector(PlayLayer::logic), 2.0f);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
	int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
    towerMatrix = (TowerBase **)malloc(arraySize);
    memset((void*)towerMatrix, 0, arraySize);
    
	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
            towerMatrix[row * MAP_WIDTH + col] = NULL;
        }
    }
    return true;
}

GroupEnemy* PlayLayer::currentGroup()
{
	GroupEnemy* groupEnemy;
	if(instance->groupVector.size() != 0)
	{
		groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
	}
	else{
		groupEnemy =NULL;
	}
	return groupEnemy;
}

GroupEnemy* PlayLayer::nextGroup()
{
	if(instance->groupVector.size() == 0)
	{
		return NULL;
	}
    
	if (groupCounter < instance->getGroupNum() - 1)
	{
		groupCounter++;
	}
	else{
		// 游戏升级，下一关游戏数据
		//groupCounter = 0;
		isSuccessful = true;
	}
    GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
    return groupEnemy;
    
}

void PlayLayer::initPointsVector(float offX)
{
    Node *runOfPoint = NULL;
	int count = 0;
	ValueMap point;
	point = objects->getObject(std::to_string(count));
	while (point.begin()!= point.end())
	{
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		runOfPoint = Node::create();
		runOfPoint->setPosition(Point(x - offX , y  ));
		this->pointsVector.pushBack(runOfPoint);
		count++;
		point = objects->getObject( std::to_string(count));
	}
	runOfPoint = NULL;
}

void PlayLayer::addEnemy()
{
    SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
	GroupEnemy* groupEnemy = this->currentGroup();
	if(groupEnemy == NULL)
	{
		return;
	}
	auto restEnemyNum = groupEnemy->getEnemyTotal();
    if( restEnemyNum <= 0){
		groupEnemy->setIsFinishedAddGroup(true);
		return;
	}
    
	restEnemyNum--;
	groupEnemy->setEnemyTotal(restEnemyNum);
    
	EnemyBase* enemy = NULL;
	
	if(groupEnemy->getType1Total() > 0){
		enemy = Thief::createThief(pointsVector, groupEnemy->getType1Hp());
		groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
	}
	else if(groupEnemy->getType2Total() > 0){
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Pirate::createPirate(pointsVector, groupEnemy->getType2Hp());
		groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
	}
	else if(groupEnemy->getType3Total() > 0){
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Bandit::createBandit(pointsVector, groupEnemy->getType3Hp());
		groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
	}
    
	this->addChild(enemy, 10);
    instance->enemyVector.pushBack(enemy);
}

void PlayLayer::logic(float dt){
	GroupEnemy* groupEnemy = this->currentGroup();
    
	if(groupEnemy == NULL)
	{
		return;
	}
	if(groupEnemy->getIsFinishedAddGroup() ==true  && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum()/*groupEnemy->getCurrEnemyNum() <= 0*/)
	{
		groupEnemy = this->nextGroup();
	}
	static long lastTimeTargetAdded = 0;
	long now = 0;
	if(lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= 10 * 1000){
		this->addEnemy();
		lastTimeTargetAdded = now;
	}
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
	this->removeChild(chooseTowerpanle);
	chooseTowerpanle = NULL;
    auto location = touch->getLocation();
    
	checkAndAddTowerPanle(location);
	return true;
}

void PlayLayer::addTowerChoosePanle(Point point)
{
    chooseTowerpanle = TowerPanleLayer::create();
    chooseTowerpanle->setPosition(point);
    this->addChild(chooseTowerpanle);
}

Point PlayLayer::convertTotileCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;
    
	return Vec2(x, y);
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y = position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{
	Point towerCoord = convertTotileCoord(position);
	Point matrixCoord = convertToMatrixCoord(position);
	int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
    
	int gid = bgLayer->getTileGIDAt(towerCoord);
    
    auto TmxProV = map->getPropertiesForGID(gid);
	ValueMap tileTemp;
    if(TmxProV.getType() != Value::Type::NONE){
        tileTemp = TmxProV.asValueMap();
    }
    
	auto tileWidth = map->getContentSize().width /	map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
	int TouchVaule;
	if (tileTemp.size() == 0)
	{
		TouchVaule = 0;
	}
	else
	{
		TouchVaule = tileTemp.at("canTouch").asInt();
	}
	towerPos = Point((towerCoord.x * tileWidth) + tileWidth/2 -offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
	if (1 == TouchVaule && towerMatrix[MatrixIndex]==NULL)
	{
		addTowerChoosePanle(towerPos);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
		auto tips = Sprite::createWithSpriteFrameName("no.png");
		tips->setPosition(towerPos);
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                         CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                         NULL));
	}
}

void PlayLayer::CollisionDetection()
{
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    
	if(bulletVector.size() == 0 || enemyVector.size() == 0 ){
		return;
	}
    
	Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
    for (int i = 0; i < bulletVector.size(); i++)
	{
		auto  bullet = bulletVector.at(i);
		auto  bulletRect = Rect(bullet->getPositionX() +bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        
		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//auto enemyRect = enemy->sprite->getBoundingBox();
			// 缩小一半
            auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
                                  enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 4,
                                  enemy->sprite->getContentSize().width / 2,
                                  enemy->sprite->getContentSize().height / 2 );
			if (bulletRect.intersectsRect(enemyRect))
			{
				if( ATTACK_BULLET == bullet->getTag()){
					auto currHp = enemy->getCurrHp();
					currHp--;
					enemy->setCurrHp( currHp );
                    
					auto currHpPercentage = enemy->getHpPercentage();
					auto offHp = 100 / enemy->getMaxHp();
					currHpPercentage -= offHp;
					if(currHpPercentage < 0){
						currHpPercentage = 0;
					}
					enemy->setHpPercentage(currHpPercentage);
					enemy->getHpBar()->setPercentage(currHpPercentage);
                    
					if(currHp <= 0)
					{
						enemyNeedToDelete.pushBack(enemy);
                        auto valueMoney = enemy->getVaule();
					}
				}
				else if(DECELERATE_BULLET == bullet->getTag())
				{
					enemy->decelerate();
				}
                bulletNeedToDelete.pushBack( bullet);
				break;
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)
		{
            enemyTemp->enemyExpload();
            instance->enemyVector.eraseObject(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}
	
	for (Sprite* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}

void PlayLayer::enemyIntoHouse()
{
    auto enemyVector = instance->enemyVector;
    for (int i = 0; i < enemyVector.size(); i++)
    {
        auto enemy = enemyVector.at(i);
        if( enemy->getEnemySuccessful() == true)
        {
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.mp3").c_str(), false);
            instance->enemyVector.eraseObject(enemy);
            enemy->removeFromParent();
        }
    }
}

void PlayLayer::update(float dt)
{
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    auto towerVector = instance->towerVector;
    
    if(chooseTowerpanle != NULL )
	{
		auto type = chooseTowerpanle->getChooseTowerType();
		Point matrixCoord = convertToMatrixCoord(towerPos);
		int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
		bool noMoneyTips = false;
		if( type == TowerType::ARROW_TOWER )
        {
				TowerBase* tower = ArrowTower::create();
				tower->setPosition(towerPos);
				tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
				this->addChild(tower);
				instance->towerVector.pushBack(tower);
				towerMatrix[MatrixIndex] =  tower;
				
			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            this->removeChild(chooseTowerpanle);
            chooseTowerpanle = NULL;
		}
        else if( type == TowerType::DECELERATE_TOWER )
        {
				DecelerateTower* tower = DecelerateTower::create();
				tower->setPosition(towerPos);
				tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
				this->addChild(tower);
				instance->towerVector.pushBack(tower);
				towerMatrix[MatrixIndex] =  tower;
            
			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            this->removeChild(chooseTowerpanle);
            chooseTowerpanle = NULL;
		}
		else if( type == TowerType::MULTIDIR_TOWER )
        {
				MultiDirTower* tower = MultiDirTower::create();
				tower->setPosition(towerPos);
				tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
				this->addChild(tower);
				instance->towerVector.pushBack(tower);
				towerMatrix[MatrixIndex] =  tower;
				
			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            this->removeChild(chooseTowerpanle);
            chooseTowerpanle = NULL;
		}
        
        
		if( noMoneyTips == true )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
			auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
			tips->setPosition(towerPos);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                             NULL));
		}
	}
    CollisionDetection();
    enemyIntoHouse();
}


