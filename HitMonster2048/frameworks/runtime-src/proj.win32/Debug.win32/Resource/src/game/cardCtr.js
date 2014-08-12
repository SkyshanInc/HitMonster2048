GamePlay.prototype.cardRunAction = function(cardAct,actIndex){
    // this.cardRunActionFalg = false;
    
    this.allCardActStopMaps[actIndex] = true;
    var card1 = cardAct.card1;
    var card2 = cardAct.card2;
    
    var card1pos = card1.getPosition();
    var card2pos = card2.getPosition();
    
    var moveCard = card1.clone();
    moveCard.setPosition(card1.getPosition());
    this.allCardsNode.addChild(moveCard);
    
    card1.setNumber(0,false);//不改变temp值
//    var offSet = 0.05;
//    if(this.mDirection == SimpleGesturesLeft || this.mDirection == SimpleGesturesRight){//左右
//        offSet = Math.abs(card1pos.x - card2pos.x);
//        
//    }else{
//         offSet = Math.abs(card1pos.y - card2pos.y);
//    }   
//    var actTime = offSet/(140/0.05);
     var actTime = 0.08;
    
    
    var moveAction = cc.MoveTo.create(actTime,card2pos);
    var fadeOutAction = cc.FadeOut.create(actTime);
    var self = this;
    moveCard.runAction(fadeOutAction);
    moveCard.runAction(cc.Sequence.create(
        moveAction,
        cc.RemoveSelf.create(),
        cc.CallFunc.create(function(){
        var tempNum1 = card1.getTempNumber();
        var Num1 = card1.getNumber();
        var tempNum2 = card2.getTempNumber();
        var Num2 = card2.getNumber();
        
        card1.setNumber(tempNum1);
        card2.setNumber(tempNum2);

        if(Num1 != 0 && Num1 * 2 == tempNum1 ){
             // self.mFightMonster.hitMonster.call(self.mFightMonster,card1);
            self.hitValueArr.push(tempNum1);
            card1.runLargenAction();
        }
        if(Num2 != 0 && Num2 * 2 == tempNum2 ){
             // self.mFightMonster.hitMonster.call(self.mFightMonster,card2);
            self.hitValueArr.push(tempNum2);
            card2.runLargenAction();
        }
        
        //重置动画执行为false
        self.allCardActStopMaps[actIndex] = false;

        //执行所有位置移动
        if(self.cardsActions.length <= 0 && self.cardRunActionFalg){
            self.checkCardActStopFlag = true;
        }

        })
    ));
}