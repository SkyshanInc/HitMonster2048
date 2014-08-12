var CardSprite = cc.Sprite.extend({
                                  number : 0,
                                  tempNumber : 0,
                                  ctor: function() {
                                  this._super();
                                  },
                                  
                                  });

CardSprite.createCardSprite = function(number)
{
	//这里是创建一个自定义精灵类，格式很规范化
	var card = new CardSprite();
	if (card && card.init())
	{
		card.initCard(number);
		return card;
	}
	// CC_SAFE_DELETE(card);
    
	return NULL;
}

CardSprite.prototype.runNewNumberAction = function()
{
    var action = cc.ScaleBy.create(0.1,0.8);
    this.runAction(cc.Sequence.create(action, action.reverse()));
}
CardSprite.prototype.runNewNumberAction = function()
{
    var action = cc.ScaleBy.create(0.1,0.8);
    this.runAction(cc.Sequence.create(action, action.reverse()));
}
CardSprite.prototype.runLargenAction = function()
{
    var action = cc.ScaleBy.create(0.1,0.8);
    this.runAction(cc.Sequence.create(action.reverse(),action));
}
//获取数据
CardSprite.prototype.getTempNumber = function()
{
	return this.tempNumber;
}

//设置数据
CardSprite.prototype.setTempNumber = function(num)
{
    this.tempNumber = num;
}


//获取数据
CardSprite.prototype.getNumber = function()
{
	return this.number;
}

//设置数据
CardSprite.prototype.setNumber = function(num,isChangTempNum)
{
	isChangTempNum = isChangTempNum != undefined ? isChangTempNum : true;
	this.number = num;
    if(isChangTempNum){
    	this.setTempNumber(num);
	}
    cc.log("this.number:"+this.number);
	//更新显示的数字
	if (num > 0)
	{
		this.labelCardNumber.setString(num);
	}
	else
	{
		this.labelCardNumber.setString("");
	}
    
	//设置数字大小
	if (num >= 0)
	{
		this.labelCardNumber.setSystemFontSize(100);
	}
	if (num >= 16)
	{
		this.labelCardNumber.setSystemFontSize(90);
	}
	if (num >= 128)
	{
		this.labelCardNumber.setSystemFontSize(60);
	}
	if (num >= 1024)
	{
		this.labelCardNumber.setSystemFontSize(40);
	}
    
	//判断数字的大小来调整颜色
	var number = this.number;
    cc.log("number:"+number);
    this.setSpriteFrame("card_"+number+".png");
	
}

//初始化
CardSprite.prototype.initCard = function( number)
{
	//初始化数字
	this.number = number;
    this.tempNumber = number;

    this.setSpriteFrame("card_"+number+".png");
 
	//判断如果大于0就显示，否则就不显示
	var labelTxt = "";
	if (number > 0)
	{
		labelTxt = number;
	}
	//加入字体
	this.labelCardNumber = cc.Label.createWithSystemFont(labelTxt,"Consolas",100);
	this.labelCardNumber.setPosition(cc.p(this.width/2, this.height/2));
	this.labelCardNumber.setTag(8);
	this.addChild(this.labelCardNumber);
    
	// this.addChild(this.colorBackground);
}
CardSprite.prototype.clone = function(){
    
    cc.log("clone this.number:"+this.number);
    var cloneCard = CardSprite.createCardSprite(this.number);
    cloneCard.setPosition(this.x,this.y);
    return cloneCard;
    
}
