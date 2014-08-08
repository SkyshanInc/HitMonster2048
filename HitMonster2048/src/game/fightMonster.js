function fightMonster (mainGame) {
	this.mainGame = mainGame;
}

fightMonster.prototype.hitMonster = function(card){
	var moveCard = card.clone();
	this.mainGame.addChild(moveCard,10000);

	var rotateAction = cc.RepeatForever.create(cc.RotateTo.create(0.5,720));
	moveCard.runAction(rotateAction);
	var moveAction = cc.MoveTo.create(0.5,cc.p(200,GetWinSize().height - 200));
    moveCard.runAction(cc.Sequence.create(
        moveAction,
        cc.RemoveSelf.create()
        )
    )

	
}