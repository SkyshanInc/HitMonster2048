var ATTACK_BULLET = 0;
var DECELERATE_BULLET = 1;

var guardTowerLayer = cc.Layer.extend({
    // this.spriteSheet = undefined;
    // this.map = undefined;
    // this.bgLayer = undefined;
    // this.objects = undefined;
    // this.pointsVector = [];
    // this.instance = undefined;
    // this.offX = undefined;
    // this.groupCounter = 0;

    // this.isSuccessful = false;
    // this.isTouchEnable = false;
    // this.chooseTowerpanle = undefined;

    // this.towerPos = undefined;
    // this.towerMatrix = undefined;

    spriteSheet : undefined,
    map : undefined,
    bgLayer : undefined,
    objects : undefined,
    pointsVector : [],
    instance : undefined,
    offX : undefined,
    groupCounter : 0,

    isSuccessful : false,
    isTouchEnable : false,
    chooseTowerpanle : undefined,

    towerPos : undefined,
    towerMatrix : undefined,



    ctor: function() {
        this._super();

        var winSize = GetWinSize();
        this.instance = GameManager.getInstance();

        this.map = cc.TMXTiledMap.create("tilemap1.tmx");
        this.bgLayer = this.map.getLayer("bg");
        this.bgLayer.setAnchorPoint(cc.p(0.5, 0.5));
        this.bgLayer.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        this.objects = this.map.getObjectGroup("obj");
        this.addChild(this.map, -10);


        offX = (this.map.getContentSize().width - winSize.width) / 2;
        // this.initPointsVector(offX);

        // schedule(schedule_selector(PlayLayer.logic), 2.0f);

        // var  touchListener = EventListenerTouchOneByOne.create();
        // touchListener.onTouchBegan = CC_CALLBACK_2(PlayLayer.onTouchBegan, this);
        // _eventDispatcher.addEventListenerWithSceneGraphPriority(touchListener, this);

//        scheduleUpdate();

        // var arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
        // towerMatrix = (TowerBase **)malloc(arraySize);
        // memset((void*)towerMatrix, 0, arraySize);

        // for (int row = 0; row < MAP_HEIGHT; row++) {
        //     for (int col = 0; col < MAP_WIDTH; col++) {
        //         towerMatrix[row * MAP_WIDTH + col] = undefined;
        //     }
        // }

        return true;
    }
});

guardTowerLayer.prototype.currentGroup = function()
{
	var groupEnemy;
	if(this.instance.groupVector.size() != 0)
	{
		groupEnemy = this.instance.groupVector.at(this.groupCounter);
	}
	else{
		groupEnemy = undefined;
	}
	return groupEnemy;
}

guardTowerLayer.prototype.nextGroup = function()
{
	if(this.instance.groupVector.size() == 0)
	{
		return undefined;
	}
    
	if (this.groupCounter < this.instance.getGroupNum() - 1)
	{
		this.groupCounter++;
	}
	else{
		// 游戏升级，下一关游戏数据
		//groupCounter = 0;
		this.isSuccessful = true;
	}
    var groupEnemy = this.instance.groupVector.at(this.groupCounter);
    return groupEnemy;
    
}

guardTowerLayer.prototype.initPointsVector = function(offX)
{
    var runOfPoint = undefined;
	var count = 0;
	var point;
	point = this.objects.getObject(count);
	while (point != undefined)
	{
		var x = point.x;
		var y = point.y;
		runOfPoint = cc.Node.create();
		runOfPoint.setPosition(cc.p(x - offX , y  ));
		this.pointsVector.push(runOfPoint);
		count++;
		point = objects.getObject( count);
	}
	runOfPoint = undefined;
}

guardTowerLayer.prototype.addEnemy = function()
{
    var groupEnemy = this.currentGroup();
	if(groupEnemy == undefined)
	{
		return;
	}
	var restEnemyNum = groupEnemy.getEnemyTotal();
    if( restEnemyNum <= 0){
		groupEnemy.setIsFinishedAddGroup(true);
		return;
	}
    
	restEnemyNum--;
	groupEnemy.setEnemyTotal(restEnemyNum);
    
	var enemy = undefined;
	
	if(groupEnemy.getType1Total() > 0){
		enemy = Thief.createThief(pointsVector, groupEnemy.getType1Hp());
		groupEnemy.setType1Total(groupEnemy.getType1Total() - 1);
		}
	else if(groupEnemy.getType2Total() > 0){
		enemy = Pirate.createPirate(pointsVector, groupEnemy.getType2Hp());
		groupEnemy.setType2Total(groupEnemy.getType2Total() - 1);
	}
	else if(groupEnemy.getType3Total() > 0){
		enemy = Bandit.createBandit(pointsVector, groupEnemy.getType3Hp());
		groupEnemy.setType3Total(groupEnemy.getType3Total() - 1);
	}
    
	this.addChild(enemy, 10);
    this.instance.enemyVector.push(enemy);
}

guardTowerLayer.prototype.logic = function(dt){
	var groupEnemy = this.currentGroup();
    
	if(groupEnemy == undefined)
	{
		return;
	}
	if(groupEnemy.getIsFinishedAddGroup() ==true  && this.instance.enemyVector.length() == 0 && groupCounter < this.instance.getGroupNum()/*groupEnemy.getCurrEnemyNum() <= 0*/)
	{
		groupEnemy = this.nextGroup();
	}
	var lastTimeTargetAdded = 0;
	var now = 0;
	if(lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= 10 * 1000){
		this.addEnemy();
		lastTimeTargetAdded = now;
	}
}

guardTowerLayer.prototype.onTouchBegan = function(touch, event)
{
	this.removeChild(this.chooseTowerpanle);
	this.chooseTowerpanle = undefined;
    var location = touch.getLocation();
    
	this.checkAndAddTowerPanle(location);
	return true;
}

guardTowerLayer.prototype.addTowerChoosePanle = function(point)
{
    this.chooseTowerpanle = TowerPanleLayer.create();
    this.chooseTowerpanle.setPosition(point);
    this.addChild(this.chooseTowerpanle);
}

guardTowerLayer.prototype.convertTotileCoord = function( position)
{
	var x = (position.x + this.offX)/ this.map.getContentSize().width * this.map.getMapSize().width;
	var y =map.getMapSize().height- position.y / this.map.getContentSize().height * this.map.getMapSize().height;
    
	return cc.p(x, y);
}
guardTowerLayer.prototype.convertToMatrixCoord = function(position)
{
	var x = (position.x + this.offX)/ this.map.getContentSize().width * this.map.getMapSize().width;
	var y = position.y / this.map.getContentSize().height * this.map.getMapSize().height;
	return cc.p(x, y);
}

guardTowerLayer.prototype.checkAndAddTowerPanle = function(position)
{
	var towerCoord = this.convertTotileCoord(position);
	var matrixCoord = this.convertToMatrixCoord(position);
	var MatrixIndex = parseInt( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
    
	var gid = this.bgLayer.getTileGIDAt(towerCoord);
    
    var tileTemp = this.map.getPropertiesForGID(gid);
	
	var tileWidth = this.map.getContentSize().width /	this.map.getMapSize().width;
	var tileHeight = this.map.getContentSize().height / this.map.getMapSize().height;
	var TouchVaule;
	if (tileTemp.length() == 0)
	{
		TouchVaule = 0;
	}
	else
	{
		TouchVaule = tileTemp["canTouch"];
	}
	towerPos = cc.p((towerCoord.x * tileWidth) + tileWidth/2 -this.offX, this.map.getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
	if (1 == TouchVaule && this.towerMatrix[MatrixIndex]==undefined)
	{
		this.addTowerChoosePanle(towerPos);
	}
	else
	{
		var tips = cc.Sprite.createWithSpriteFrameName("no.png");
		tips.setPosition(towerPos);
		this.addChild(tips);
		tips.runAction(cc.Sequence.create(cc.DelayTime.create(0.8),
                                         cc.RemoveSelf.create()
                                         ));
	}
}

guardTowerLayer.prototype.CollisionDetection = function()
{
    var bulletVector = this.instance.bulletVector;
    var enemyVector = this.instance.enemyVector;
    
	if(bulletVector.length == 0 || enemyVector.length == 0 ){
		return;
	}
    
	var enemyNeedToDelete;
	var bulletNeedToDelete;
    for (var i = 0; i < bulletVector.length; i++)
	{
		var  bullet = bulletVector[i];
		var  bulletRect = cc.rect(bullet.getPositionX() +bullet.getParent().getPositionX() - bullet.getContentSize().width / 2,
                                bullet.getPositionY() +bullet.getParent().getPositionY() - bullet.getContentSize().height / 2,
                                bullet.getContentSize().width,
                                bullet.getContentSize().height );
        
		for (var j = 0; j < enemyVector.length; j++)
		{
			var enemy = enemyVector[j];
			//auto enemyRect = enemy.sprite.getBoundingBox();
			// 缩小一半
            var enemyRect = cc.rect(enemy.sprite.getPositionX() - enemy.sprite.getContentSize().width / 4,
                                  enemy.sprite.getPositionY()  - enemy.sprite.getContentSize().height / 4,
                                  enemy.sprite.getContentSize().width / 2,
                                  enemy.sprite.getContentSize().height / 2 );
			if (bulletRect.intersectsRect(enemyRect))
			{
				if( ATTACK_BULLET == bullet.getTag()){
					var currHp = enemy.getCurrHp();
					currHp--;
					enemy.setCurrHp( currHp );
                    
					var currHpPercentage = enemy.getHpPercentage();
					var offHp = 100 / enemy.getMaxHp();
					currHpPercentage -= offHp;
					if(currHpPercentage < 0){
						currHpPercentage = 0;
					}
					enemy.setHpPercentage(currHpPercentage);
					enemy.getHpBar().setPercentage(currHpPercentage);
                    
					if(currHp <= 0)
					{
						enemyNeedToDelete.push(enemy);
                        var valueMoney = enemy.getVaule();
					}
				}
				else if(DECELERATE_BULLET == bullet.getTag())
				{
					enemy.decelerate();
				}
                bulletNeedToDelete.push( bullet);
				break;
			}
		}
		for (var k = 0;k<enemyNeedToDelete.length;k++)
		{
            var enemyTemp = enemyNeedToDelete[k];
            enemyTemp.enemyExpload();
            this.instance.enemyVector.unshift(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}
	
	for (var k = 0;k<bulletNeedToDelete.length;k++)
	{
        var bulletTemp = bulletNeedToDelete[k];
		this.instance.bulletVector.unshift(bulletTemp);
        bulletTemp.removeFromParent();
	}
	bulletNeedToDelete.clear();
}

guardTowerLayer.prototype.enemyIntoHouse = function()
{
    var enemyVector = this.instance.enemyVector;
    for (var i = 0; i < enemyVector.length; i++)
    {
        var enemy = enemyVector[i];
        if( enemy.getEnemySuccessful() == true)
        {
			this.instance.enemyVector.unshift(enemy);
            enemy.removeFromParent();
        }
    }
}

guardTowerLayer.prototype.update = function(dt)
{
    var bulletVector = this.instance.bulletVector;
    var enemyVector = this.instance.enemyVector;
    var towerVector = this.instance.towerVector;
    
    if(this.chooseTowerpanle != undefined )
	{
		var type = this.chooseTowerpanle.getChooseTowerType();
		var matrixCoord = this.convertToMatrixCoord(towerPos);
		var MatrixIndex = parseInt( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
		var noMoneyTips = false;
		if( type == TowerType.ARROW_TOWER )
        {
            var tower = ArrowTower.create();
            tower.setPosition(towerPos);
            tower.runAction(cc.Sequence.create(cc.FadeIn.create(1.0)));
            this.addChild(tower);
            this.instance.towerVector.push(tower);
            this.towerMatrix[MatrixIndex] =  tower;
            
			type =  TowerType.ANOTHER;
			this.chooseTowerpanle.setChooseTowerType(type);
            this.removeChild(this.chooseTowerpanle);
            this.chooseTowerpanle = undefined;
		}
        else if( type == TowerType.DECELERATE_TOWER )
        {
            var tower = DecelerateTower.create();
            tower.setPosition(towerPos);
            tower.runAction(cc.Sequence.create(cc.FadeIn.create(1.0)));
            this.addChild(tower);
            this.instance.towerVector.push(tower);
            this.towerMatrix[MatrixIndex] =  tower;
            
			type =  TowerType.ANOTHER;
			this.chooseTowerpanle.setChooseTowerType(type);
            this.removeChild(this.chooseTowerpanle);
            this.chooseTowerpanle = undefined;
		}
		else if( type == TowerType.MULTIDIR_TOWER )
        {
            var tower = MultiDirTower.create();
            tower.setPosition(towerPos);
            tower.runAction(cc.Sequence.create(cc.FadeIn.create(1.0)));
            this.addChild(tower);
            this.instance.towerVector.push(tower);
            this.towerMatrix[MatrixIndex] =  tower;
            
			type =  TowerType.ANOTHER;
			this.chooseTowerpanle.setChooseTowerType(type);
            this.removeChild(this.chooseTowerpanle);
            this.chooseTowerpanle = undefined;
		}
        
        
		if( noMoneyTips == true )
		{
			// SimpleAudioEngine.getInstance().playEffect(FileUtils.getInstance().fullPathForFilename("sound/tip.wav").c_str(), false);
			// auto tips = Sprite.createWithSpriteFrameName("nomoney_mark.png");
			// tips.setPosition(towerPos);
			// this.addChild(tips);
			// tips.runAction(Sequence.create(DelayTime.create(0.5f),
   //                                           CallFunc.create(CC_CALLBACK_0(Sprite.removeFromParent, tips)),
   //                                           undefined));
		}
	}
    this.CollisionDetection();
    this.enemyIntoHouse();
}


