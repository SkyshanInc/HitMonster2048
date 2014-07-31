
var AnimationMgr = {

	animationMap:{},

	loadSpriteFrameAnimation: function(plist,startIndex,count,timeGap){
		var ani = this.animationMap[plist];
	    if(ani){
	        return ani;
	    }

	    startIndex = startIndex||0;
	    count = count||100;
	    timeGap = timeGap||0.05;

	    cc.spriteFrameCache.addSpriteFrames(plist+".plist");
	    var list = [];
	    for (var i = 0; i < startIndex+count; i++) {
	    	var sf = cc.spriteFrameCache.getSpriteFrame(plist+"_"+ i + ".png");
	    	if(!sf){
	    		break;
	    	}
	        list.push(sf);
	    }
	    var animation = cc.Animation.create(list, timeGap);
	    this.animationMap[plist] = animation;

	    cc.animationCache.addAnimation(animation, plist);
	    return animation;
	},

	clear:function(){
		for(var key in this.animationMap){
			cc.animationCache.removeAnimation(key);
		}
		this.animationMap = {};
	}

}