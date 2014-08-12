
var ParticleSystemPlistCache = {};

var EffectMgr = {
	//frames   :(plist,parent,speed) if speed != null auto play
	//particle :(plist,isRealse,parent)
	create:function(p0,p1,p2) {
		var node ;
		if(typeof(p1) == "boolean"){
		    node = cc.ParticleSystem.create(p0);
			if (p1)
				node.setAutoRemoveOnFinish(true);
            if(p2&&p2.addNode)
                p2.addNode(node,10000);
			else if(p2)
				p2.addChild(node,10000);
		}
		else{
            cc.spriteFrameCache.addSpriteFrames(p0);
		    node = plistData.create(p0.replace(".plist",""),p2);
			if(p1&&p1.addNode)
                p1.addNode(node);
			else if(p1)
				p1.addChild(node);
		}
        return node;
	},

	//创建闪电对象
	createLightning: function(p0){
		cc.spriteFrameCache.addSpriteFrames(p0);
		var node = lightning.create(p0.replace(".plist",""));
		return node;
	},
}

var plistData = cc.Sprite.extend({
	sprName:"",
    callfunc:null,
})

plistData.create = function(sprName,speed)
{
    var pd = new plistData();
    pd.setSpriteFrame(sprName + "_0.png");
    pd.sprName = sprName;
	if(speed!=undefined)
		pd.play(speed);
    return pd;
}
plistData.prototype.play = function (speed,isLoop,isAutoRemove,startIdx, endIdx) {
	startIdx = startIdx||0;
	endIdx	 = endIdx||100;
	speed = speed || 0.08;
    if(isLoop === undefined)
	    isLoop = false;

	if(isAutoRemove === undefined){
		isAutoRemove = true;
	}

	var frames = [];
	for(var i=startIdx;i<endIdx;i++)
	{
	    var frame = cc.spriteFrameCache.getSpriteFrame(this.sprName+"_"+i+".png");
		if(frame)
			frames.push(frame);
		else
			break;
	}
	if(frames.length>0)
	{
	    var act = cc.Animate.create(cc.Animation.create(frames, speed));
		if(isLoop){
		    act = cc.RepeatForever.create(act);
		}
	    else if(this.callfunc){
	    	var arr = [];
	    	arr.push(act);
	    	arr.push(cc.CallFunc.create(this.callfunc));
	    	if(isAutoRemove){
	    		arr.push(cc.RemoveSelf.create());
	    	}
            act = cc.Sequence.create(arr)
        }
        else{
        	var arr = [];
	    	arr.push(act);
	    	if(isAutoRemove){
	    		arr.push(cc.RemoveSelf.create());
	    	}
            act = cc.Sequence.create(arr);
		}
		this.runAction(act);
	}
}
plistData.prototype.onFinish = function(func)
{
    this.callfunc = func;
}


var lightning = cc.Sprite.extend({
	sprName:"",
	callFunc:null,
	endPosition:null,
	startPosition:null,
	distance:null,
	mHeight:null,
	beginContactFunc:null,
	isExeBegin:false,
	endContactFunc:null,
	progressTimer:null,
})

lightning.create = function(sprName){
	var ln = new lightning();
	ln.sprName = sprName;
	var f = cc.spriteFrameCache.getSpriteFrame(sprName+".png");
	if(f){
		ln.setSpriteFrame(f);
	}else{
		ln.setSpriteFrame(sprName + "_0.png");
	}
    return ln;
}

lightning.prototype.play = function(speed,endPosition,startPosition){
	
	if(startPosition!=null||startPosition!=undefined){
		this.setPosition(startPosition);
	}
	this.startPosition = this.getPosition();
	this.endPosition = endPosition;
	var width = this.getPositionX() - this.endPosition.x;
	var height = this.getPositionY() - this.endPosition.y;
	var rad = Math.atan2(height,width);
	this.setRotation(-180.0/Math.PI * rad+90);
	this.mHeight = this.getContentSize().height;
	var r2 = this.mHeight*(1.0-this.getAnchorPoint().y);
	var offsetW = r2*Math.cos(rad);
	var offsetH = r2*Math.sin(rad);

	//cc.log("end"+"[" +this.endPosition.x+"," +this.endPosition.y+ "]");

	this.startPosition = cc.p(this.startPosition.x+offsetW,this.startPosition.y+offsetH);

	this.setAnchorPoint(0.5,1.0);

	//this.endPosition = cc.p(this.endPosition.x-offsetW,this.endPosition.y-offsetH);

	//cc.log("end"+"[" +this.endPosition.x+"," +this.endPosition.y+ "]");

	this.distance = this.getDistance();
	this.moveTotalTime = this.distance/speed;
	this.moveTime = 0;
	// cc.log(this.distance);
	// if(this.endContactFunc){
	// 	this.runAction(cc.Sequence.create(cc.MoveTo.create(this.distance/speed,this.endPosition),cc.CallFunc.create(this.endContactFunc),cc.RemoveSelf.create()));
	// }else{
	// 	this.runAction(cc.Sequence.create(cc.MoveTo.create(this.distance/speed,this.endPosition),cc.RemoveSelf.create()));
	// }
	
	this.scheduleUpdate();

	var loop = true;
	var frames = [];
	var f = cc.spriteFrameCache.getSpriteFrame(this.sprName+".png")
	if(f){
		frames.push(f);
	}else{
		for(var i=0;i<100;i++)
		{
		    var frame = cc.spriteFrameCache.getSpriteFrame(this.sprName+"_"+i+".png");
			if(frame)
				frames.push(this.sprName+"_"+i+".png");
			else
				break;
		}
	}
	
	// if(frames.length>0)
	// {
	//     var act = cc.Animate.create(cc.Animation.create(frames, 0.05));
	// 	 act = cc.RepeatForever.create(act);
	// 	this.runAction(act);
	// }
	this.timeGap = 0.1;
	this.currentTime = 0;
	this.currentIndex = 0;
	this.updateFrames = frames;
}

lightning.prototype.update = function(ft){

	this.currentTime +=ft;

	if(this.updateFrames.length>1){
		if(this.currentTime>this.timeGap){
			this.currentTime = 0;
			this.currentIndex ++;
			if(this.currentIndex>this.updateFrames.length-1){
				//this.currentIndex = this.updateFrames.length-1;
				this.currentIndex = 0;
			}
			var frame = this.updateFrames[this.currentIndex];
			this.setSpriteFrame(frame);
		}
	}
	
	this.moveTotalTime = Math.max(this.moveTotalTime,ft);
	this.moveTime+=ft;

	var width = (this.endPosition.x - this.startPosition.x)*this.moveTime/this.moveTotalTime;
	var height = (this.endPosition.y - this.startPosition.y)*this.moveTime/this.moveTotalTime;
	this.setPosition(this.startPosition.x+width,this.startPosition.y+height);

	if(this.moveTime<=this.moveTotalTime){
		var dis = this.getDistance();
		if(dis<this.mHeight){
			 dis = Math.max(dis,0)
			 var rect = this.getTextureRect();
	         rect.height = dis;
	         this.setTextureRect(rect, this.isTextureRectRotated(), cc.size(rect.width,rect.height));
	         if(this.isTextureRectRotated()){
	         	this.setFlippedY(true);
	         }else{
	         	this.setFlippedY(false);
	         }
	         if(!this.isExeBegin){
	         	this.isExeBegin = true;
	         	if(this.beginContactFunc){
	         		this.runAction(cc.CallFunc.create(this.beginContactFunc));
	         	}
	         }
		}
	}else{
		if(this.endContactFunc){
			this.runAction(cc.CallFunc.create(this.endContactFunc));
		}
		this.removeFromParent();
	}
	
}

lightning.prototype.getDistance = function(){
	var width = this.getPositionX() - this.endPosition.x;
	var height = this.getPositionY() - this.endPosition.y;
	var r = Math.sqrt(Math.pow(width,2)+Math.pow(height,2));
	return r;
}

lightning.prototype.onBeginContact = function(func){
	this.beginContactFunc = func;
}

lightning.prototype.onEndContact = function(func){
	this.endContactFunc = func;
}



