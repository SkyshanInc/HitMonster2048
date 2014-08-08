var mainScene = cc.Scene.extend({
    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Scene); 
        this.mID = "";
        this.mRoot = null;
        this.schedule(this.onUpdate, 1 / 60);
    },
    create:function(id,root){
        this.mID = id;
                                
        this.mRoot = root||ccui.Widget.create();
        this.mRoot.setTouchEnabled(true);
        // this.mRoot.addTouchEventListener(this.touchEvent, this);
        this.mRoot.setContentSize(GetWinSize());
        this.addChild(this.mRoot, ZOrder_Scene, 0);

        //android键盘监听
        // var _this = this;
        // cc.eventManager.addListener({
        //     event: cc.EventListener.KEYBOARD,
        //     onKeyReleased: _this.onKeyReleased
        // }, this);

    

    },
    onEnter: function () {
        this._super();
       AppCtrl.onEnter();
    },
    onUpdate: function (dt)
    {
//		AppCtrl.onUpdate(dt);
    },
    touchEvent:function(touch,evt)
    {
        switch (evt) {
            case ccui.Widget.TOUCH_BAGAN:
                this.touchBegan(touch);
                break;
            case ccui.Widget.TOUCH_MOVED:
                this.touchMoved(touch);
                break;
            case ccui.Widget.TOUCH_ENDED:
            //case ccui.TouchEventType.canceled:
                this.touchEnded(touch);
                break;
            default:
                break;
        }
    },
    touchBegan: function (touch)
    {
        cc.log(this.mID + "touch begin");
        return true;
    },
    touchMoved: function (touch) {
        cc.log(this.mID + "touch moved");
    },
    touchEnded: function (touch) {
        
    },
    exit:function()
    {
        this.unschedule(this.onUpdate);
    },
    buttonEvent:function(sender,evt)
    {
        if (evt == ccui.Widget.TOUCH_ENDED)
        {
            BuildMgr.onBuildClick(sender);
        }
    },
//    scrollEvent:function(sender,evt)
//    {
//        if (evt == ccui.Widget.TOUCH_ENDED)
//        {
//            cc.log(this.mID + " ScrollEvent: touch ended");
//            var mainUI = UIMgr.findUI("mainUI");
//            mainUI.showBtm(0);
//			var pos = sender.getTouchEndPos()
//			var node = EffectMgr.create("dianji.plist", this);
//            node.setPosition(pos);
//			node.play(0.05);
//        }
//		else if(evt == ccui.Widget.TOUCH_BAGAN)
//		{
//			
//		}
//    },
	findChild : function (name) {
		var spl = name.split('/');
		var findNode = this.mRoot;
		for(var i=0;i<spl.length;i++)
		{
			cc.log("findChild:"+spl[i]);
			findNode = findNode.getChildByName(spl[i]);
			
			if(findNode == null)
			{
				cc.log("[Error] Node not find " + spl[i]);
				return null;
			}
		}
		return findNode;
	}
});
//监听回调
// mainScene.prototype.onKeyReleased = function(keyCode, event){
//     cc.log("Key " + keyCode.toString() + " was released!")
//     CtrWin = null
//     //查找出当前显示的win
//     for(var i = UIMgr.mUIArray.length-1;i >= 0; i--){
//         win = UIMgr.mUIArray[i]
//         if(win.mIsShow){
//             CtrWin = win
//             break
//         }
//     }
//     if(CtrWin == undefined) return

//     cc.log("CtrWin.mID:"+CtrWin.mID)
            
//     if(CtrWin.mID == "uiLoading" ) return

//     if(CtrWin.mID == "mainUI" || CtrWin.mID == "uiLogin"){
//        UIMgr.add("uiWarning","确定要退出游戏吗！！",function(){

//             cc.log("退出游戏回调")
//             cc.director.end()

//             throw "退出"

//         })
        
//         return
//     }
//     if(parseInt(keyCode) == 8){//监听8返回键
//         CtrWin.close()
//     }
// }

