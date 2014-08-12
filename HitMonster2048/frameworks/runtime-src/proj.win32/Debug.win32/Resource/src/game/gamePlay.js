function GamePlay() {

    this.lll = "skyshan";
    this.cellSpace = 10;
    this.cellSize = 0;
    this.cardArr = [];
    this.mDirection = -1;
    this.cardsActions = [];
    this.cardRunActionFalg = false;

    this.allCardsNode = null;
    this.allCardActStopMaps = {};
    this.checkCardActStopFlag = false;

    this.score = 0;
    //城堡
    this.chengbaoNode = undefined;

    //节点
    this.panScene = undefined;
    this.panGame = undefined;
    this.allCardsNode = undefined;
    //Monster
    this.monsPos = undefined;
    this.panMonsterInitPos = undefined;
    this.panMonster = undefined;
    this.monsAnmation = "loading";

    //攻击相关的
    this.hitValueArr = [];
    this.checkHitValue = true;

    uiBase.call(this);

}
Class.extend(GamePlay, uiBase);

GamePlay.prototype.setOption = function () {
    this.uiOpt.uiModelType = DMT_Model;
	this.uiOpt.uiShowMode = DlgZoomFadeIn;
    this.uiOpt.uiHideMode = DlgZoomFadeOut;
	this.uiOpt.isHideOther = false;
	//this.uiOpt.isvarRelease = false;
}
GamePlay.prototype.onCreate = function (isShow,itemList) {


    this.panScene = this.findChild("node/pan_scene");
    this.panGame = this.findChild("node/pan_game");
    this.panFight = this.panGame.getChildByName("pan_fight");
    this.generalHitSprite = this.panFight.getChildByName("img_general");
    this.integrationLabel = this.findChild("node/pan_game/pan_playinfo/lab_fenshu");
    this.chengbaoNode = this.panFight.getChildByName("img_chengbao");
    this.panMonster = this.panFight.getChildByName("pan_monster");



	
    for(var i = 0;i<10;i++){
        this.cardArr[i] = [];
    }

    cc.spriteFrameCache.addSpriteFrames("card.plist");
    cc.spriteFrameCache.addSpriteFrames("general_guge_1.plist");
    
    
    this.allCardsNode = cc.Layer.create();
    this.allCardsNode.setPosition(cc.p(0,10));
    this.panGame.addChild(this.allCardsNode,10);

    this.init();
}

// Scene* GameScene::createScene()
// {
//     // 'scene' is an varrelease object
//     var scene = Scene::create();
    
//     // 'layer' is an varrelease object
//     var layer = GameScene::create();
    
//     // add layer as a child to scene
//     scene.addChild(layer);
    
//     // return the scene
//     return scene;
// }

// GameScene::~GameScene()
// {
//     delete recognizer;
    
//     HighScore::destroyInstance();
// }

// on "init" you need to initialize your instance
GamePlay.prototype.init = function()
{
    
    var visibleSize = GetWinSize();
    //Point origin = Director::getInstance().getVisibleOrigin();
    
    
//    var bgSprite = cc.Sprite.createWithSpriteFrameName("gameplalybg.png");
//    bgSprite.setAnchorPoint(cc.p(0.5,0));
//    bgSprite.setPosition(cc.p(visibleSize.width/2,0));
//    this.allCardsNode.addChild(bgSprite);
    
    //加入游戏背景
//    var layerColorBG = cc.LayerColor.create(cc.color(180, 170, 160, 255));
//    this.addChild(layerColorBG);
    
    
    var sceneName = "xueshan";
    ccs.armatureDataManager.addArmatureFileInfo("xueshan.ExportJson");
    
    var scene = ccs.Armature.create(sceneName);
    scene.setAnchorPoint(0.1,0);
    scene.getAnimation().playWithIndex(0,0,0);
    this.panScene.addChild(scene,0);

    ccs.armatureDataManager.addArmatureFileInfo("tauren.ExportJson");
    this.monsterNode = ccs.Armature.create("tauren");;
    this.monsterNode.setAnchorPoint(cc.p(0,0));
    this.monsterNode.getAnimation().play(this.monsAnmation);
    // this.monsterNode.setPosition(this.monsPos);

    this.panMonsterInitPos  = this.panMonster.getPosition();
    this.monsPos =  cc.p(this.panMonster.x+this.monsterNode.width/2,this.panMonster.y+this.monsterNode.height/2);
    this.panMonster.addChild(this.monsterNode);

    this.monsterNode.getAnimation().setMovementEventCallFunc(this.onMovementEvent,this);
        
    this.score = 0;
    
    //创建4X4卡片
    this.createCardSprite(visibleSize);
    if (sys.localStorage.getItem("history")) {
        this.resumeStatus();
    }
    else
    {
        //初始时生成两个2
        this.createCardNumber(false);
        this.createCardNumber(false);
    }
    
    this.recognizer = new SimpleRecognizer();
    
    
    
    this.scheduleUpdate();

    this.schedule(this.monsterHitPlayer,10);
    
    return true;
}

// void GameScene::onPause(Ref* pSender)
// {
//     PopLayer *poplayer = PopLayer::create(Color4B(0,0,0,180));
//     getParent().addChild(poplayer);
//     Director::getInstance().pause();
// }

GamePlay.prototype.onTouchBegin = function(pSender)
{
	var beginPoint = pSender.getTouchBeganPosition();
    
    cc.log("beginPoint->x:"+beginPoint.x+",y:"+beginPoint.y);
    this.recognizer.beginPoint(beginPoint);
    
    return true;
}

GamePlay.prototype.onTouchMoved = function(pSender)
{
    var pos = pSender.getTouchMovePosition();
    cc.log("MovePoint->x:"+pos.x+",y:"+pos.y);
    this.recognizer.movePoint(pos);
}

GamePlay.prototype.onTouchEnded = function(pSender)
{
    var sceneLockFlag = true;
    var pos = pSender.getTouchEndPosition();
    cc.log("endPoint->x:"+pos.x+",y:"+pos.y);
    var rtn = this.recognizer.endPoint(pos);
    this.mDirection = rtn;
    
    switch (rtn) {
        case SimpleGesturesLeft:
            if(!this.doLeft()){
                return;
            };
            break;
        case SimpleGesturesRight:
            if(!this.doRight()){
                return;
            };
            break;
        case SimpleGesturesUp:
            if(!this.doUp()){
                return;
            };
            break;
        case SimpleGesturesDown:
            if(!this.doDown()){
                return;
            };
            break;
            
        case SimpleGesturesNotSupport:
        case SimpleGesturesError:
            sceneLockFlag = false;
            log("not support or error touch,use geometricRecognizer!!");
            break;
            
        default:
            sceneLockFlag = false;
            break;
    }
    this.cardRunActionFalg = true;
    this.allCardActStopMaps = {};
    LockScreen(sceneLockFlag,"[GamePlay]");
}

//根据屏幕大小创建卡片
GamePlay.prototype.createCardSprite = function(size)
{
    //求出单元格的宽和高
    //左右边距 this.cellSpace
    this.cellSize = (size.width - 3*this.cellSpace - 40)/4;
    
    
    //绘制出4X4的单元格
    for (var i = 0; i < 4; i++)
    {
        for (var j = 0; j < 4; j++)
        {
            //需要屏幕分辨率适配
            
            var pX = 20 + this.cellSpace/2 + i*(this.cellSize+this.cellSpace);
            var pY = this.cellSize/2 + j*(this.cellSize+this.cellSpace);
            
            cc.log("px:"+pX+",py:"+pY);
            var pos = cc.p(pX,pY);
            var card = CardSprite.createCardSprite(0);
            var cardContSize = card.getContentSize();
             cc.log("cardContSize.width:"+cardContSize.width+",cardContSize.height:"+cardContSize.height);
            card.setPosition(cc.p(pos.x+cardContSize.width/2,pos.y));
            this.cardArr[i][j] = card;
            this.allCardsNode.addChild(card);
        }
    }
}

// //创建生成随机卡片
GamePlay.prototype.createCardNumber = function(animation)
{
    animation = true;
    while (1) {
        // var i = Math.random()* * 4;        //生成0~3随机数
        // var j = CCRANDOM_0_1() * 4;


        var i =  parseInt(Rand(0,4));        //生成0~3随机数
        var j = parseInt(Rand(0,4));
        
        cc.log("******   random i:"+i+",j:"+j+"   ******");
        
        if (this.cardArr[i][j].getNumber() == 0)
        {
            //2和4的生成率为9:1
            this.cardArr[i][j].setNumber(parseInt(Rand(0,10)) < 1 ? 4 : 2);
            if(animation)
            {
                this.cardArr[i][j].runNewNumberAction();
            }
            break;
        }
        
        if (!this.shouldCreateCardNumber()) {
            break;
        }
    }
}

GamePlay.prototype.shouldCreateCardNumber = function()
{
    var isCreate = false;
    for (var i = 0; i < 4; i++)
    {
        for (var j = 0; j < 4; j++)
        {
            if( 0 == this.cardArr[i][j].getNumber() )
            {
                isCreate = true;
                break;
            }
        }
    }
    
    return isCreate;
}

GamePlay.prototype.isWin = function()
{
    var win = false;
    for (var i = 0; i < 4; i++)
    {
        for (var j = 0; j < 4; j++)
        {
            if( 2048 == this.cardArr[i][j].getNumber() )
            {
                win = true;
                break;
            }
        }
    }
    
    return win;
}

// //左滑动
GamePlay.prototype.doLeft = function()
{
    //判断有没有发生移动
    var isMove = false;
    for (var y = 0; y < 4; y++)
    {
        for (var x = 0; x < 4; x++)
        {
            for (var x1 = x+1; x1<4; x1++)
            {
                if (this.cardArr[x1][y].getTempNumber() > 0)
                {
                    if (this.cardArr[x][y].getTempNumber() <= 0)
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x1][y].getTempNumber());
                        this.cardArr[x1][y].setTempNumber(0);
                        
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x1][y];
                        this.pushCardsAction(card2,card1);
                        x--;
                        isMove = true;
                    }
                    else if(this.cardArr[x][y].getTempNumber() == this.cardArr[x1][y].getTempNumber())
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x][y].getTempNumber() * 2);
                        this.cardArr[x1][y].setTempNumber(0);
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x1][y];
                        this.pushCardsAction(card2,card1);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

// //右滑动
GamePlay.prototype.doRight = function()
{
    //判断有没有发生移动
    var isMove = false;
    for (var y = 0; y < 4; y++)
    {
        for (var x = 3; x >= 0; x--)
        {
            for (var x1 = x-1; x1>=0; x1--)
            {
                if (this.cardArr[x1][y].getTempNumber() > 0)
                {
                    if (this.cardArr[x][y].getTempNumber() <= 0)
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x1][y].getTempNumber());
                        this.cardArr[x1][y].setTempNumber(0);
                        
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x1][y];
                        this.pushCardsAction(card2,card1);
                        x++;
                        isMove = true;
                    }
                    else if(this.cardArr[x][y].getTempNumber() == this.cardArr[x1][y].getTempNumber())
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x][y].getTempNumber() * 2);
                        this.cardArr[x1][y].setTempNumber(0);
                        
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x1][y];
                        this.pushCardsAction(card2,card1);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

// //上滑动
GamePlay.prototype.doUp = function()
{
    //判断有没有发生移动
    var isMove = false;
    for (var x = 0; x < 4; x++)
    {
        for (var y = 3; y >= 0; y--)
        {
            for (var y1 = y-1; y1>=0; y1--)
            {
                if (this.cardArr[x][y1].getTempNumber() > 0)
                {
                    if (this.cardArr[x][y].getTempNumber() <= 0)
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x][y1].getTempNumber());
                        this.cardArr[x][y1].setTempNumber(0);
                        
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x][y1];
                        this.pushCardsAction(card2,card1);
                        y++;
                        isMove = true;
                    }
                    else if(this.cardArr[x][y].getTempNumber() == this.cardArr[x][y1].getTempNumber())
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x][y].getTempNumber() * 2);
                        this.cardArr[x][y1].setTempNumber(0);
                        
                        
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x][y1];
                        this.pushCardsAction(card2,card1);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

// //下滑动
GamePlay.prototype.doDown = function()
{
    //判断有没有发生移动
    var isMove = false;
    for (var x = 0; x < 4; x++)
    {
        for (var y = 0; y <4; y++)
        {
            for (var y1 = y+1; y1<4; y1++)
            {
                if (this.cardArr[x][y1].getTempNumber() > 0)
                {
                    if (this.cardArr[x][y].getTempNumber() <= 0)
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x][y1].getTempNumber());
                        this.cardArr[x][y1].setTempNumber(0);
                        
                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x][y1];
                        this.pushCardsAction(card2,card1);
                        y--;
                        isMove = true;
                    }
                    else if(this.cardArr[x][y].getTempNumber() == this.cardArr[x][y1].getTempNumber())
                    {
                        this.cardArr[x][y].setTempNumber(this.cardArr[x][y].getTempNumber() * 2);
                        this.cardArr[x][y1].setTempNumber(0);

                        var card1 = this.cardArr[x][y];
                        var card2 = this.cardArr[x][y1];
                        this.pushCardsAction(card2,card1);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

GamePlay.prototype.setScore = function()
{
    SetLabelStringWithAnimation(this.integrationLabel,this.score,true);
}

GamePlay.prototype.doCheck = function()
{
    var isGameOver = true;

    //结束边界  4*4的card数值>0 且  相邻card没有相同数值
    //4*4的card数值>0 不能在创建Number
    //判断每一个的上下左右和自己是否相同
    for (var y = 0; y < 4; y++)
    {
        for (var x = 0; x < 4; x++)
        {
            if (this.cardArr[x][y].getNumber() == 0 ||
                (x<3 && this.cardArr[x][y].getNumber() == this.cardArr[x+1][y].getNumber()) ||
                (x>0 && this.cardArr[x][y].getNumber() == this.cardArr[x-1][y].getNumber()) ||
                (y<3 && this.cardArr[x][y].getNumber() == this.cardArr[x][y+1].getNumber()) ||
                (y>0 && this.cardArr[x][y].getNumber() == this.cardArr[x][y-1].getNumber()) )
            {
                isGameOver = false;
            }
        }
    }

    if (this.isWin()) {
        
        // successLayer = LayerColor::create(Color4B(0, 0, 0, 180));
        // Size winSize = Director::getInstance().getWinSize();
        // Point centerPos = Point(winSize.width / 2, winSize.height / 2);
        // var gameOverTitle = Label::createWithSystemFont("YOU WIN","Consolas",80);
        // gameOverTitle.setPosition(centerPos);
        // successLayer.addChild(gameOverTitle);
        
        // getParent().addChild(successLayer,1);
        
        // scheduleOnce(SEL_SCHEDULE(&GameScene::removeSuccessLayer), 2);
        return;
    }
    
    //isGameOver = true;
    if (isGameOver)
    {
        // log("game over");
        // UserDefault::getInstance().setItem("history", false);

        // HighScore::getInstance().setScore(score);
        // GameOverLayer *gameoverLayer = GameOverLayer::create(Color4B(0, 0, 0, 180));
        // getParent().addChild(gameoverLayer,1);
        
        // Director::getInstance().pause();
    }
    else
    {
        if (this.shouldCreateCardNumber()) {
            this.createCardNumber();
            
            this.saveStatus();
        }
    }
    
}


GamePlay.prototype.saveStatus = function()
{
//    var temp;
//    //4*4
//    for (var i = 0; i<4; i++) {
//        for(var j = 0; j<4; j++)
//        {
//            temp = i+""+j;
//            sys.localStorage.setItem(temp, this.cardArr[i][j].getNumber());
//        }
//    }
//    
//    sys.localStorage.setItem("score", score);
//    
//    sys.localStorage.setItem("history", true);
    
}

GamePlay.prototype.resumeStatus = function()
{
    var temp;
    //4*4
    for (var i = 0; i<4; i++) {
        for(var j = 0; j<4; j++)
        {
            temp = i+""+j;
            var number = sys.localStorage.getItem(temp);
            this.cardArr[i][j].setNumber(number);
        }
    }
    
    this.score = sys.localStorage.getItem("score");
    this.setScore(this.score);
    
    sys.localStorage.setItem("history", false);
}
GamePlay.prototype.update = function(dt){
    
    if(this.cardRunActionFalg){
        
        if(this.cardsActions.length > 0){
            var cardAct = this.cardsActions.shift();
            this.cardRunAction(cardAct,this.cardsActions.length);
            cc.log("等待操作");
        }
    }

    //检测所有卡牌动画是否结束
    if(this.checkCardActStopFlag){

        var isStop = true;
        for(var key in this.allCardActStopMaps){
            var cardActValue = this.allCardActStopMaps[key];
            if(cardActValue){
                isStop = false;
                break;
            }
        }

        if(isStop){
            cc.log("可以继续操作")
            this.cardRunActionFalg = false;
            this.doCheck();
            this.checkCardActStopFlag = false;
            //本次操作结束解锁
            LockScreen(false,"[GamePlay]");
        }

    }

    //攻击Monster
    if(this.checkHitValue){
        if(this.hitValueArr.length > 0){
            var hitValue = this.hitValueArr.shift();

            this.outGeneralHitMonster(hitValue);
        }
    }
    
    

}
GamePlay.prototype.pushCardsAction = function(cardOne,cardTwo){
    var cardAct = {
        card1 : cardOne,
        card2 : cardTwo,
    }
    
    this.cardsActions.push(cardAct);
}





// void GameScene::removeSuccessLayer()
// {
//     successLayer.removeFromParent();
// }