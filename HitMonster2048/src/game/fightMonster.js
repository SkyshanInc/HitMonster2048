GamePlay.prototype.outGeneralHitMonster = function(hitValue){


    this.checkHitValue = false;

    var moveGeneral = this.generalHitSprite.clone();
    moveGeneral.setVisible(true);
    moveGeneral.setOpacity(0);
    moveGeneral.loadTexture("general_"+hitValue+".png",LOADRESPLIST)
    this.panFight.addChild(moveGeneral);
    cc.log("hitValue:"+hitValue);   

    var monsPos = cc.p(this.panMonster.x+this.monsterNode.width/2,this.panMonster.y+this.monsterNode.height/2);

    var moveAction = cc.MoveTo.create(0.5,monsPos);
    var fadeInAction = cc.FadeIn.create(0.1);
    var scalAction = cc.ScaleTo.create(0.1,0.5);
    var self = this;
    moveGeneral.runAction(scalAction);
    moveGeneral.runAction(cc.Sequence.create(
        fadeInAction,
        moveAction,
        cc.CallFunc.create(function(){
        	self.score += hitValue;
        	self.setScore();
            cc.log("动画结束回调");
            
            self.monsterNode.getAnimation().play("smitten");

            self.hitValueFontAct(hitValue,monsPos);

            self.checkHitValue = true;

        }),
        cc.DelayTime.create(0.5),
        cc.RemoveSelf.create()
        )
    )

}	
GamePlay.prototype.hitValueFontAct = function(hitValue,monsPos){
	var hitValueLab = this.panFight.getChildByName("lab_hitvalue").clone();
	var offX = Rand(-50,50);
	var offY = Rand(-50,50);
	hitValueLab.setName("lab_hitvalueClone");
	hitValueLab.setPosition(monsPos);
	hitValueLab.x += offX;
	hitValueLab.y += offY;
	hitValueLab.setVisible(true);
	hitValueLab.setScale(0);
	hitValueLab.setString(hitValue);
	this.panFight.addChild(hitValueLab);


	var offScale = Rand(0.8,1.3);
    var self = this;
    hitValueLab.runAction(cc.Sequence.create(
        cc.ScaleTo.create(0.2,offScale),
        cc.DelayTime.create(0.3),
        cc.ScaleTo.create(0.2,0),
        cc.RemoveSelf.create()
        )
    )


}
//怪物骨骼动画回调
GamePlay.prototype.onMovementEvent = function(armature,type,movementID){


	switch(type){

        case ccs.MovementEventType.loopComplete:
        	if(movementID != "loading" && movementID != "run"){
            	this.monsterNode.getAnimation().stop();
        	}
        	if(movementID === "smitten"){
        		this.monsterBackToInitPos();
        	}
        	if(movementID  == "attack"){
       //  		this.monsterNode.getAnimation().play("loading");
       //  		var moveAction = cc.MoveTo.create(0.1,this.panMonsterInitPos);
			    // var self = this;
			   	// this.panMonster.runAction(cc.Sequence.create(
			    //     moveAction
       //  			)
    			// )
				this.monsterBackToInitPos();			
        	}

            break;
        default:

            break;

    }

    // cc.log("*** onMovementEvent **");
    // cc.log(armature);
    // cc.log(type);
    // cc.log(movementID);
    // if(this.smittenCount == undefined){
    //     this.smittenCount = 1;
    // }
    // if(this.smittenCount >= 2 && movementID === "smitten"){
    //     this.monsterNode.getAnimation().stop();
    //     this.monsterNode.getAnimation().play("run");
    //     this.smittenCount = 0;
    // }
    // if(movementID === "smitten"){
    //     this.smittenCount ++;
    // }

    // if(this.attackCount == undefined){
    //     this.attackCount = 0;
    // }
    // if(movementID === "attack"){
    //     this.monsterNode.getAnimation().stop();
    //     this.monsterNode.getAnimation().play("run");
    //     this.attackCount = 0;
    // }
    // if(movementID === "attack"){
    //     this.attackCount ++;
    // }
}

//随机怪物攻击
GamePlay.prototype.monsterHitPlayer = function(ft){

	cc.log(" ====    monsterHitPlayer    ====  ");
    this.monsterNode.getAnimation().play("run");


    var moveAction = cc.MoveBy.create(0.5,cc.p(-200,0));
    var self = this;
   	this.panMonster.runAction(cc.Sequence.create(
        moveAction,
        cc.CallFunc.create(function(){

        	self.monsterNode.getAnimation().play("attack");

        	})
        )
    )

}

//怪物回到原点
GamePlay.prototype.monsterBackToInitPos = function(){
	var moveAction = cc.MoveTo.create(0.1,this.panMonsterInitPos);
	var self = this;
	this.panMonster.runAction(cc.Sequence.create(
			    moveAction,
			    cc.CallFunc.create(function(){

			    	self.monsterNode.getAnimation().play("loading");
		        	

		        	})
        	)
    	)

}
