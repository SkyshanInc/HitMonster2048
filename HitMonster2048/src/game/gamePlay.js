function GamePlay() {
    this.cellSpace = 10,
    this.cellSize = 0,
    this.cardArr = [];
    this.mDirection = -1;
    this.cardsActions = [];
    this.cardRunActionFalg = false;
    this.score = 0;
    this.allCardsNode = null;
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
	
    for(var i = 0;i<10;i++){
        this.cardArr[i] = [];
    }

    cc.spriteFrameCache.addSpriteFrames(res.main_plist);
    cc.spriteFrameCache.addSpriteFrames(res.General_guge_plist);
    
    
    this.allCardsNode = cc.Layer.create();
    this.allCardsNode.setPosition(cc.p(0,10));
    this.addChild(this.allCardsNode,10);
    

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
    
    var visibleSize = cc.Director.getInstance().getVisibleSize();
    //Point origin = Director::getInstance().getVisibleOrigin();
    
    
//    var bgSprite = cc.Sprite.createWithSpriteFrameName("gameplalybg.png");
//    bgSprite.setAnchorPoint(cc.p(0.5,0));
//    bgSprite.setPosition(cc.p(visibleSize.width/2,0));
//    this.allCardsNode.addChild(bgSprite);
    
    //加入游戏背景
//    var layerColorBG = cc.LayerColor.create(cc.color(180, 170, 160, 255));
//    this.addChild(layerColorBG);
    
    
    var sceneName = "xueshan";
    ccs.armatureDataManager.addArmatureFileInfo(res.Xueshan_Json);
    
    var scene = ccs.Armature.create(sceneName);
    scene.setAnchorPoint(0.1,0);
    scene.getAnimation().playWithIndex(0,0,0);
    this.addChild(scene,0);
    

//    //pause
//    cc.MenuItemFont.setFontName("Consolas");
//    cc.MenuItemFont.setFontSize(80);
//    // var menuItemPause = cc.MenuItemFont.create("PAUSE", CC_CALLBACK_1(GameScene::onPause, this));
//    var menuItemPause = cc.MenuItemFont.create("PAUSE", function(){
//        cc.log("PAUSE");
//    });    
//    
//    var menu = cc.Menu.create(menuItemPause);
//    this.addChild(menu);
    
    
    var generalNode = GetGeneralNode(true);
    generalNode.setPosition(cc.p(200, visibleSize.height - 250));
    this.addChild(generalNode);
    
    //创建分数
//    var cardNumberTitle = cc.Label.createWithSystemFont("SCORE:","Consolas",80);
//    cardNumberTitle.setPosition(cc.p(200, visibleSize.height - 100));
//    this.addChild(cardNumberTitle);
    
    this.score = 0;
//    this.cardNumberTTF = cc.Label.createWithSystemFont("0", "Consolas", 70);
//    this.cardNumberTTF.setPosition(cc.p(400, visibleSize.height - 100));
//    this.addChild(this.cardNumberTTF);
    
    //设置触摸事件监听
    // var touchListener = EventListenerTouchOneByOne::create();
    // touchListener.onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    // touchListener.onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    // touchListener.onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    // _eventDispatcher.addEventListenerWithSceneGraphPriority(touchListener, this);
    
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
	var beginPoint = pSender.getTouchStartPos();
    
    cc.log("beginPoint->x:"+beginPoint.x+",y:"+beginPoint.y);
    this.recognizer.beginPoint(beginPoint);
    
    return true;
}

GamePlay.prototype.onTouchMoved = function(pSender)
{
    var pos = pSender.getTouchMovePos();
    cc.log("MovePoint->x:"+pos.x+",y:"+pos.y);
    this.recognizer.movePoint(pos);
}

GamePlay.prototype.onTouchEnded = function(pSender)
{
    var pos = pSender.getTouchEndPos();
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
            log("not support or error touch,use geometricRecognizer!!");
            break;
            
        default:
            break;
    }
    this.cardRunActionFalg = true;
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
                        //改变分数
                        this.score += this.cardArr[x][y].getTempNumber();
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
                        //改变分数
                        this.score += this.cardArr[x][y].getTempNumber();
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
                        //改变分数
                        this.score += this.cardArr[x][y].getTempNumber();
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
                        //改变分数
                        this.score += this.cardArr[x][y].getTempNumber();
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

GamePlay.prototype.setScore = function(score)
{
//    this.cardNumberTTF.setString(score);
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
            this.cardRunAction(cardAct);
            cc.log("等待操作");
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

GamePlay.prototype.cardRunAction = function(cardAct){
    // this.cardRunActionFalg = false;
    
    var card1 = cardAct.card1;
    var card2 = cardAct.card2;
    
    var card1pos = card1.getPosition();
    var card2pos = card2.getPosition();
    
    var moveCard = card1.clone();
    moveCard.setPosition(card1.getPosition());
    this.allCardsNode.addChild(moveCard);
    
    
    card1.setNumber(card1.getTempNumber());
    
    
//    var offSet = 0.05;
//    if(this.mDirection == SimpleGesturesLeft || this.mDirection == SimpleGesturesRight){//左右
//        offSet = Math.abs(card1pos.x - card2pos.x);
//        
//    }else{
//         offSet = Math.abs(card1pos.y - card2pos.y);
//    }
    
//    var actTime = offSet/(140/0.05);
     var actTime = 0.05;
    
    
    var moveAction = cc.MoveTo.create(actTime,card2pos);
    var fadeOutAction = cc.FadeOut.create(actTime);
    var self = this;
    moveCard.runAction(fadeOutAction);
    moveCard.runAction(cc.Sequence.create(
        moveAction,
        cc.RemoveSelf.create(),
        cc.CallFunc.create(function(){
        var num = card2.getTempNumber();
        card2.setNumber(num);
        // card2.runNewNumberAction();
        // self.cardRunActionFalg = true;
         //执行所有位置移动
        if(self.cardsActions.length <= 0 && self.cardRunActionFalg){
            cc.log("可以继续操作")
            self.doCheck();
            self.setScore(self.score);
            self.cardRunActionFalg = false;
        }
                                                
        })
    ));
}

// void GameScene::removeSuccessLayer()
// {
//     successLayer.removeFromParent();
// }