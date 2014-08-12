
var winSize = GetWinSize();

var DlgFromLeft = {
    run : function (dlg) {
        var startPos = cc.p(-winSize.width, 0)
        var endPos = cc.p(0, 0)
        DlgActions.MoveTo(dlg, startPos, endPos, true)
    }
}

var DlgMoveToRight = {
    run : function (dlg) {
        var endPos = cc.p(winSize.width, 0)
        var startPos = cc.p(0, 0)
        DlgActions.MoveTo(dlg, startPos, endPos)
    }
}

var DlgFromTop = {
    run : function (dlg) {
        var endPos = cc.p(0, 0)
        var startPos = cc.p(0, winSize.height)
        DlgActions.MoveTo(dlg, startPos, endPos, true)
    }
}

var DlgFromBtm = {
    run: function (dlg) {
        var endPos = cc.p(0, 0)
        var startPos = cc.p(0, -winSize.height)
        DlgActions.MoveTo(dlg, startPos, endPos, true)
    }
}
var DlgMoveToTop = {
    run : function (dlg) {
        var endPos = cc.p(0, winSize.height)
        var startPos = cc.p(0, 0)
        DlgActions.MoveTo(dlg, startPos, endPos, true);
    }
}
var DlgMoveToBtm = {
    run : function (dlg) {
        var endPos = cc.p(0, -winSize.height)
        var startPos = cc.p(0, 0)
        DlgActions.MoveTo(dlg, startPos, endPos, false);
    }
}

var DlgFadeIn = {
    run : function (dlg) {
        DlgActions.bugFadeTo(dlg, 0.1, 255, true)
    }
}

var DlgFadeOut = {
    run : function (dlg) {
        DlgActions.bugFadeTo(dlg, 255, 0.1, false)
    }
}

var DlgZoomIn = {
    run : function (dlg) {
		dlg.setPosition(0,0);
        DlgActions.ScaleTo(dlg, 0.2, 1, true)
    }
}

var DlgZoomOut = {
    run : function (dlg) {
        DlgActions.ScaleTo(dlg, 1, 0.2, false)
    }
}
var DlgMoveFadeIn = {
	run:function(dlg){
		var endPos = cc.p(0, 0)
		var startPos = cc.p(0, winSize.height)
		DlgActions.MoveWithFade(dlg, startPos, endPos, true)
	}
}

var DlgMoveUpFadeIn = {
    run:function(dlg){
        var endPos = cc.p(0, 0)
        var startPos = cc.p(0, -200)
        DlgActions.MoveWithFade(dlg, startPos, endPos, true)
    }
}
var DlgMoveFadeOut = {
	run:function(dlg){
		var startPos = cc.p(0, 0)
		var endPos = cc.p(0, winSize.height)
		DlgActions.MoveWithFade(dlg, startPos, endPos, false)
	}
}
var DlgZoomFadeIn = {
    run : function (dlg) {
        DlgActions.ScaleAndFade(dlg, 0.5, 1, true)
    }
}
var DlgZoomFadeOut = {
    run : function (dlg) {
        DlgActions.ScaleAndFade(dlg, 1, 0.5, false)
    }
}

var DlgZoomInFromBtm = {
    run : function (dlg) {
        var startPos = cc.p(0, -winSize.height)
        var endPos = dlg.uiOpt.initPos || cc.p(0, 0)
        DlgActions.ZoomMoveTo(dlg, startPos, endPos, true)
    }
}
var DlgZoomOutToBtm = {
    run: function (dlg) {
        var endPos = cc.p(0, -winSize.height);
        var startPos = dlg.uiOpt.initPos || cc.p(0, 0);
        DlgActions.ZoomMoveTo(dlg, startPos, endPos, false);

    }
}
var DlgSpringScaleIn = {
	run:function(dlg){
		DlgActions.ScaleTo(dlg,0.3,1,true);
	}
}
var DlgSpringScaleOut = {
	run:function(dlg){
		DlgActions.ScaleTo(dlg,1,0,false); 
	}
}

var DlgActions = {
    MoveTo: function (dlg, from, to, isShow) {
        dlg.setPosition(from);
        var action = cc.Sequence.create(
			cc.MoveTo.create(0.3, to),
            cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg));
        dlg.runAction(action);
    },
	MoveToEaseOut: function (dlg, from, to, isShow) {
        dlg.setPosition(from);
        var action = cc.Sequence.create(
			isShow?cc.EaseOut.create(cc.MoveTo.create(0.2, to),3)
			:cc.MoveTo.create(0.3, to),
            cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg));
        dlg.runAction(action);
    },
	MoveToEase: function (dlg, from, to, isShow) {
        dlg.setPosition(from);
        var action = cc.Sequence.create(
            cc.EaseElasticInOut.create(cc.MoveTo.create(1.0, to), 1.0),
            cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg));
        dlg.runAction(action);
    },
	
    FadeTo: function (dlg, from, to, isShow) {
        dlg.setVisible(true);
        dlg.setOpacity(from);
        var action = cc.Sequence.create(cc.FadeTo.create(0.3, to), cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg));
        dlg.runAction(action);
    },
	bugFadeTo: function(dlg, from, to, isShow) {
		dlg.setVisible(true);
		DeepFadeAction(dlg,from,to,cc.CallFunc.create(function () { dlg.showFinish(isShow || false);}));
	},
	MoveWithFade:function(dlg, from, to, isShow){
		this.MoveToEaseOut(dlg,from,to,isShow);
		var opcFrom = isShow?100:255;
		var opcTo	= isShow?255:0.1;
		DeepFadeAction(dlg.getRoot(),opcFrom,opcTo);
	},
	ScaleAndFade: function (dlg, from, to, isShow) {
		dlg.setPosition(0,0);
		var colorBg = dlg.getColorBg();
		if(!colorBg) throw new Error("ui colorBg is null");

		var opcFrom = isShow?0.1:150;
		var opcTo	= isShow?150:0.1;
		colorBg.setOpacity(opcFrom);
		colorBg.runAction(cc.FadeTo.create(0.5,opcTo));
		var winNode = dlg.getRoot();
		if(!winNode) winNode = dlg;
		
		winNode.setAnchorPoint(cc.p(0.5,0.5));
		winNode.setPosition(GetWinSize().width/2,GetWinSize().height/2);
        winNode.setScale(from);
        var action = cc.Sequence.create(isShow?cc.EaseElasticOut.create(cc.ScaleTo.create(0.3, to), 1.0):cc.EaseElasticIn.create(cc.ScaleTo.create(0.3, to),1.0),
            cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg))
        winNode.runAction(action);
    },
    ScaleTo: function (dlg, from, to, isShow) {
        dlg.setScale(from);
        var action = cc.Sequence.create(isShow?cc.EaseElasticOut.create(cc.ScaleTo.create(0.5, to), 1.0):cc.EaseElasticIn.create(cc.ScaleTo.create(0.5, to),1.0),
            cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg))
        dlg.runAction(action);
    },
	
    ZoomMoveTo: function (dlg, from, to, isShow) {
        var zoom = 1
        if (isShow) zoom = 0;

        dlg.setScale(zoom)
        dlg.setPosition(from)
        var spawnAct = cc.Spawn.create(
            cc.EaseElasticInOut.create(cc.MoveTo.create(0.8, to), 0.8),
        cc.EaseElasticInOut.create(cc.ScaleTo.create(0.8, 1 - zoom), 0.8)
              )
        var action = cc.Sequence.create(spawnAct,
            cc.CallFunc.create(function () { dlg.showFinish(isShow || false) }, dlg));
        dlg.runAction(action)
    },
}
var DeepFadeAction = function(node,from,to,callfunc){
	node.setOpacity(from);
	var act = cc.FadeTo.create(0.5,to);
	node.runAction(callfunc?cc.Sequence.create(act,callfunc):act);
	var nodes = node.getChildren();
	for(var i=0;i<nodes.length;i++){
		DeepFadeAction(nodes[i],from,to);
	}
}
//颤抖Action，且调且珍惜
function NodeShaky (node,callback){
    var actions = []
    actions.push(cc.MoveBy.create(0.1,cc.p(75,75)))
    actions.push(cc.MoveBy.create(0.1,cc.p(-115,-115)))
    actions.push(cc.MoveBy.create(0.1,cc.p(80,80)))
    actions.push(cc.MoveBy.create(0.1,cc.p(-60,-60)))
    actions.push(cc.MoveBy.create(0.1,cc.p(23,23)))
    actions.push(cc.MoveBy.create(0.1,cc.p(-3,-3)))
    
    if(callback != undefined && typeof(callback) == "function"){
        actions.push(cc.CallFunc.create(callback))
    }
    
    node.stopAllActions()
    node.runAction(cc.Sequence.create(actions))
}