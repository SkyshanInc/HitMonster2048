//DlgModelMode
DMT_Normal      = 0       // 普通窗口
DMT_Model       = 1       // 模态窗口
DMT_Transparent = 2       // 透明窗口
//DlgShowMode
DSM_Normal = 0;			  // 简单的显示 隐藏
//DlgActions			  // 其他显示方式 参考 uiActions.js

//窗口属性
var uiOption = function () {
    this.zOrder = null;					// 可以自定义窗口层 默认最高层
    this.parent = null;					// 自定义父节点 默认当前 scene (widget 此版本 不支持)
    this.uiModelType = DMT_Normal;		// 窗口模态类型
    this.uiShowMode = DSM_Normal;		// 窗口显示动画 (参考 uiActions.js)
    this.uiHideMode = DSM_Normal;		// 窗口隐藏动画
    this.exitButtonTag = TAG_CloseBtn;	// 默认的退出按钮tag TAG_CloseBtn = 10001
    this.isAutoRelease = true;			// 自动释放
    this.initPos = null;				// 初始化位置
    this.isClickOutClose = false;		// 点击空白处隐藏
    this.autoHideTime = -1;				// 自动隐藏延迟时间 默认不自动隐藏
    this.isForceShow  = false;			// 是否强制显示 显示状态的窗口 强制刷新
    this.isHideOther  = true;			// 是否隐藏其他窗口
    this.isHideMainUI = false;			// 隐藏主界面
	this.isHideTopBtns= false;			// 自定义属性
	this.isShowTopBar = false;
}

///////////////////////////////////////
var uiBase = cc.Layer.extend({
    mShowFinish: true,
    mIsShow: false,
    mID: null,
    mRoot: null,
    mWinNode: null,			//窗口节点 实际的窗口大小 tag = 10000
    mDelayTime: -1,
    mLoadFinish: false,
    mLastPos: cc.p(0, 0),
    uiOpt:null,
	mCallBack:null,
	mCallBackObj:null,
	mColorLayer : null,
	mCloseBtn:null,
})

uiBase.prototype.create = function (id, root, jsonFile) {
    root = root || ccui.Widget.create();
    this.mID = id;
    this.resourceList = [];
    this.mIsShow = false;
    this.mJsonFile = jsonFile;
    this.mWinNode = root.getChildByTag(TAG_WinNode);
    this.uiOpt = new uiOption();
    this.addChild(root,10);
    this.setOption();
    this.setupUIMode();
	this.mDelayTime = this.uiOpt.autoHideTime;

	if(this.uiOpt.uiShowMode == DlgZoomFadeIn||this.uiOpt.uiHideMode == DlgZoomFadeOut) {		
		var uiRoot = this.getRoot();
		uiRoot.setBackGroundColorType(0);
		this.mColorLayer = cc.LayerColor.create(cc.color(0,0,0,150));
		this.mColorLayer.setContentSize(GetWinSize());
		cc.Layer.prototype.addChild.call(this, this.mColorLayer, -1, 0);
	}
}

uiBase.prototype.setupUIMode = function () {
    if (this.uiOpt.uiModelType == DMT_Transparent) {
        if (this.mWinNode)
            this.mWinNode.setTouchEnabled(false);
        this.mRoot.setTouchEnabled(false);
    }
    else if (this.uiOpt.uiModelType == DMT_Normal) {
        if (this.mWinNode) {
            this.mWinNode.setTouchEnabled(true);
            this.mWinNode.addTouchEventListener(this.touchEvent, this);
			this.mRoot.setTouchEnabled(false);
        }
//        else {
//            this.mRoot.setTouchEnabled(true);
//            this.mRoot.addTouchEventListener(this.touchEvent, this);
//        }
    }
    else {
        this.mRoot.setTouchEnabled(true);
        this.mRoot.addTouchEventListener(this.touchEvent, this);
    }
}

uiBase.prototype.createFinish = function () {
    if (this.uiOpt.autoHideTime > -1) {
        this.mDelayTime = this.uiOpt.autoHideTime;
    }
    this.uiOpt.parent = this.uiOpt.parent || cc.director.getRunningScene();
	if(this.uiOpt.parent.addNode)
		this.uiOpt.parent.addNode(this);
	else this.uiOpt.parent.addChild(this);
    this.onCreate.apply(this, Array.prototype.slice.call(arguments));
    this.mLoadFinish = true;
}

uiBase.prototype.addChild = function (node, zOrder, tag) {
    zOrder = zOrder==undefined? 0 :zOrder;
    tag = tag || -1;
    if (this.mRoot) {
        if (node instanceof ccui.Widget)
            this.mRoot.addChild(node, zOrder, tag);
        else this.mRoot.addNode(node, zOrder, tag);
    }
    else {
        cc.Layer.prototype.addChild.call(this, node, zOrder, tag);
        this.mRoot = node;
    }
}

uiBase.prototype.show = function () {
    var isShow = arguments[0];
    if (!this.isCanShow(isShow)) {//|| !this.mShowFinish
		cc.log("[Warning] uiShow is break id:"+this.getID());
        return false;
    }
    this.mShowFinish = false;
    this.mIsShow = isShow;
    if (isShow) {
        this.setVisible(true);
        if (this.uiOpt.uiShowMode != DSM_Normal){
            this.uiOpt.uiShowMode.run(this,true)
            
            
            //打开界面完成
//			MusicMgr.playEffect("FrameMove.mp3");
		}
    }
    else {
        this.stopAllActions()
        if (this.uiOpt.uiHideMode != DSM_Normal) {
            this.uiOpt.uiHideMode.run(this,false)
        }
        else this.showFinish(false);
    }
//	// 添加顶部ui
//	if(this.uiOpt.isShowTopBar && !this.uiTopBar){
//		this.uiTopBar = new ctrlUITopBar(this);
//	}
	
    this.onShow.apply(this, Array.prototype.slice.call(arguments));
	return true;
}
uiBase.prototype.forceHide = function()
{
	var isForce = this.uiOpt.isForceShow;
	this.uiOpt.isForceShow = true;
	this.close();
	
	this.uiOpt.isForceShow = isForce;
}
uiBase.prototype.showFinish = function (isShow) {
	UIMgr.onUIShowFinish(this,isShow);
    this.mShowFinish = true;
	this.onShowFinish(isShow);

	if(this.mCallBackObj){
		this.mCallBack.call(this.mCallBackObj,isShow);
	}else if(this.mCallBack) {
        this.mCallBack(isShow);
        cc.log("执行关闭事件");
    }
	if(isShow&&this.mCloseBtn){
		var rotateAct =  cc.RotateTo.create(0.5,10);
		this.mCloseBtn.runAction(cc.RepeatForever.create(cc.Sequence.create(cc.RotateTo.create(1,10),cc.RotateTo.create(1,0))));
	}
}
//注册回调事件
uiBase.prototype.onShowCall = function(callback,obj)
{
    cc.log("注册关闭事件");
	this.mCallBack = callback;
	this.mCallBackObj = obj;
}

uiBase.prototype.open = function (params) {
	var args = [];
	if(arguments.length>0){
		args = [this];
		for(var i =0;i<arguments.length;i++){
			args.push(arguments[i]);
		}
	}
	UIMgr.showUI.apply(UIMgr,args);
}

uiBase.prototype.close = function (backUI) {
    if (this.mDelayTime)
        this.mDelayTime = this.uiOpt.autoHideTime;
    UIMgr.hideUI(this, backUI);
}

uiBase.prototype.playAnimation = function (anim,jsonFile) {
	jsonFile = jsonFile||this.mJsonFile;
    if (typeof (anim) == "string")
        ccs.ActionManager.getInstance().playActionByName(jsonFile, anim);
}

uiBase.prototype.uiUpdate = function (dt) {	
    if (this.mLoadFinish && this.mIsShow) {
        if (this.mDelayTime && this.mDelayTime > -1) {
            this.mDelayTime -= dt
            if (this.mDelayTime <= 0) {
                this.close();
                this.mDelayTime = this.uiOpt.autoHideTime;
            }
        }
        this.onUpdate(dt);
    }
}

uiBase.prototype.remove = function () {
	MsgMgr.unbindObj(this);
	if(this.uiOpt.isShowTopBar)
		MsgMgr.unbindObj(this.uiTopBar);
    this.onRemove();
	this.stopAllActions();
	this.removeFromParent();
    this.releaseResource();
	cc.log(this.mID+" removed")
}

uiBase.prototype.touchEvent = function (sender, evt) {
    cc.log("uiBase:evt:"+evt);
    switch (evt) {
        case ccui.Widget.TOUCH_BEGAN:
            return this.touchBegan(sender);
            break;
        case ccui.Widget.TOUCH_MOVED:
            this.touchMoved(sender);
            break;
        case ccui.Widget.TOUCH_ENDED:
            this.touchEnded(sender);
            break;
        case ccui.Widget.TOUCH_CANCELED:
            this.onTouchCanceled && this.onTouchCanceled();
            this.touchEnded(sender);
            break;
        default:
            break;
    }
}
uiBase.prototype.touchBegan = function (sender) {
    cc.log(this.mID + " touchBegan " + sender.getName());
//	if(this.mID!="gameUI"){
//		var efx = EffectMgr.create("texiao_dianji_0.plist",false,this);
//		efx.setPosition(sender.getTouchStartPos());
//	}
    cc.log("this.mIsShow:"+this.mIsShow);
    if (!this.mIsShow)
        return false

    return this.onTouchBegin(sender);
}

uiBase.prototype.touchMoved = function (sender) {
    this.onTouchMoved(sender)
}

uiBase.prototype.touchEnded = function (sender) {
	if(this.uiOpt.isClickOutClose&&!this.mWinNode.hitTest(sender.getTouchStartPos()))
	{
		this.close();
		return;
	}
    this.onTouchEnded(sender)
}

//ui控件事件
//按钮
uiBase.prototype.buttonEvent = function (sender, event) {
    cc.log("[BtnClick] tag = " + sender.getTag() + " name = "+sender.getName())

	if(event == ccui.Widget.TOUCH_ENDED){
		if (sender.getTag() == this.uiOpt.exitButtonTag) {
			this.close();
		}
		else {
			if(this.uiOpt.isShowTopBar)
				this.uiTopBar.onButtonClick(sender, event);
			this.onButtonClick(sender, event);
		}
        
        //buttom点击音效
//        MusicMgr.playEffect("Button.mp3");
		//去角标
		sender.cornerMark && sender.cornerMark.show(false);
	}
	else if(event == ccui.Widget.TOUCH_BAGAN){
		this.buttonClickAction(sender);
		this.onButtonBegan&&this.onButtonBegan(sender, event);

	}
	else if(event == ccui.Widget.TOUCH_CANCELED){
		this.onButtonCanceled&&this.onButtonCanceled(sender, event);
	}
}
uiBase.prototype.addJsonNode = function(jsonFile,root,pos)
{
	root = root||this;
	var node = CocosFactory.create(this.getID(),jsonFile);
	if(node){
		root.addChild(node);
		if(pos)
			node.setPosition(pos);
	}
	return node;
}
uiBase.prototype.buttonClickAction = function (sender) {
    var scale = sender.originScale;
    if(scale==undefined){
        scale = sender.getScale();
        sender.originScale = scale;
    }
    
    sender.runAction(cc.Sequence.create(cc.ScaleTo.create(0.1,1.2*scale,scale*0.9),cc.ScaleTo.create(0.1,0.9*scale,scale*1.2),cc.ScaleTo.create(0.1,1.1*scale,scale*0.95),cc.ScaleTo.create(0.08,0.95*scale,scale*1.1),cc.ScaleTo.create(0.08,1.05*scale,scale*0.97),cc.ScaleTo.create(0.08,scale,scale)));
}
//选择框
uiBase.prototype.checkBoxEvent = function (sender,cbEventType) {
    if(!sender.isVisible()) return;
    
    cc.log("[checkBox] tag = " + sender.getTag())
//    MusicMgr.playEffect("Button.mp3");
    this.onCheckBoxClick(sender, cbEventType);
}
//输入框
uiBase.prototype.textInputEvent = function (sender, type) {
    //     switch (type) {
    //         case ccui.TextFiledEventType.attach_with_me:
    //             cc.log("attach with IME");
    //             break;
    //         case ccui.TextFiledEventType.detach_with_ime:
    //             cc.log("detach with IME");
    //             break;
    //         case ccui.TextFiledEventType.insert_text:
    //             cc.log("insert words");
    //             break;
    //         case ccui.TextFiledEventType.delete_backward:
    //             cc.log("delete word");
    //             break;
    //         default:
    //             break;
    //     }
}
//值变化事件
uiBase.prototype.valueChangedEvent = function (sender, type) {
    //     switch (type) {
    //         case ccui.SliderEventType.percent_changed:
    //             var slider = sender;
    //             var percent = slider.getPercent();
    //             cc.log("Percent " + percent.toFixed(0));
    //             break;
    //         default:
    //             break;
    //     }
}

//gets
uiBase.prototype.getRoot = function () {
    return this.mRoot;
}
uiBase.prototype.getID = function () {
    return this.mID;
}
uiBase.prototype.isShown = function () {
    return this.mIsShow && this.mShowFinish;
}
uiBase.prototype.isTransparent = function () {
    return this.uiOpt.uiModelType == DMT_Transparent
}
uiBase.prototype.isModel = function () {
    return this.uiOpt.uiModelType == DMT_Model
}
uiBase.prototype.isNormal = function () {
    return this.uiOpt.uiModelType == DMT_Normal
}
uiBase.prototype.isAutoHide = function () {
    return this.uiOpt.autoHideTime != -1
}
uiBase.prototype.getShowMode = function(){
	return this.uiOpt.uiShowMode;
}
uiBase.prototype.isCanShow = function(isShow){
	var cantShow = this.mIsShow == isShow || !this.mShowFinish && !this.uiOpt.isForceShow ;
	return !cantShow;
}
uiBase.prototype.findChild = function (name) {
    var spl = name.split('/');
    var findNode = this.mRoot;
    for(var i=0;i<spl.length;i++)
    {
        //cc.log("childName:"+spl[i])
        findNode = findNode.getChildByName(spl[i]);
        
        if(findNode == null)
        {
            cc.log("[Error] Node not find " + spl[i]);
            return null;
        }
    }
    return findNode;
}
uiBase.prototype.getChildByName = function (name) {
    return this.mRoot.getChildByName(name);
}
uiBase.prototype.getChildByTag = function (tag) {
    var node = this.mRoot.getChildByTag(tag)
    if (node == null) {
        cc.log("[Warning]" + this.mID + " Node ! found tag:" + tag)
        return null
    }

    return node
}

uiBase.prototype.removeChild = function (tagOrNode, isClean) {
    var node = tagOrNode
    if (typeof (tagOrNode) == "number") {
        node = this.mRoot.getChildByTag(tagOrNode)
    }
    if (node != null)
        this.mRoot.removeChild(node, isClean || true)
    else
        cc.log("[Warning] " + this.__cname + "removeChild() Node ! found.", node)
}

uiBase.prototype.scrollEvent = function(scroll,type){
    if(type==ccui.ScrollView.EVENT_SCROLLING){

        var container   = scroll.getInnerContainer();
        var contentSize = scroll.getInnerContainerSize();
        var scrollSize  = scroll.getSize();
		var scrollPos   = scroll.getPosition();
        if(scrollSize.height==contentSize.height){
            return;
        }

        if(!scroll.isShowScrollBar){
            var scrollBar = scroll.scrollBar;
            if(scrollBar==undefined||scrollBar==null){
                var r = cc.rect(2,3,1,1);
                scrollBar = cc.Scale9Sprite.createWithSpriteFrameName("img_gundongtiao.png",r);
                scrollBar.setAnchorPoint(cc.p(1.0,0.5));
                scroll.getParent().addNode(scrollBar,10000);
                scrollBar.setOpacity(0);
                scroll.scrollBar = scrollBar;
                return;
            }
            scrollBar.stopActionByTag(10);
            scrollBar.setOpacity(200);
			
            var barPer = scrollSize.height/contentSize.height;
            var barHeight = Math.min(barPer*scrollSize.height,scrollSize.height*0.5);
            var size = cc.size(7,barHeight);
			var moveDist = contentSize.height - scrollSize.height;
			var y = scrollPos.y + container.getPositionY()*-1 / moveDist * (scrollSize.height - barHeight) + barHeight/2;

			y = Math.max(scrollPos.y + barHeight/2,y);
			y = Math.min(scrollPos.y + scrollSize.height - barHeight/2,y);
            scrollBar.setPosition(cc.p(scrollPos.x + scrollSize.width-5,y));
            scrollBar.setPreferredSize(size);

            //cc.log("scrollWidth:"+size.width+"   scrollHeight:"+size.height);

            var act = cc.Sequence.create(cc.DelayTime.create(0.2),cc.FadeOut.create(0.1));
            act.setTag(10);
            scrollBar.runAction(act);
        }
    }
    this.onScrollEvent(scroll,type);
}

uiBase.prototype.addPlist = function(name){
//    ResourceMgr.addPlist(name);
//    this.resourceList.push(name);
}

uiBase.prototype.addForever = function(name){
//    ResourceMgr.addForeverPlist(name);
}

uiBase.prototype.releaseResource = function(){
//    for(var i = 0;i<this.resourceList.length;i++){
//        ResourceMgr.removeUnusedPlist(this.resourceList[i]);
//    }
    
    cc.textureCache.removeUnusedTextures();
    cc.sys.garbageCollect();
}

//gets
uiBase.prototype.getRoot = function () { return this.mRoot; }
uiBase.prototype.getWinNode = function () { return this.mWinNode; }
uiBase.prototype.getColorBg = function () { return this.mColorLayer; }
uiBase.prototype.getID = function () { return this.mID; }

//override
uiBase.prototype.setOption = function () { }
uiBase.prototype.onCreate = function (isShow, more) { }
uiBase.prototype.onShow = function (isShow, more) { }
uiBase.prototype.onShowFinish = function (isShow) { }
uiBase.prototype.onUpdate = function (dt) { }
uiBase.prototype.onRemove = function () { }

uiBase.prototype.onButtonClick = function (btn, evt) { }
uiBase.prototype.onCheckBoxClick = function(cbBtn,cbEventType){ }
uiBase.prototype.onTouchBegin = function (sender) { }
uiBase.prototype.onTouchMoved = function (sender) { }
uiBase.prototype.onTouchEnded = function (sender) { }

uiBase.prototype.onScrollEvent = function(scroll,type){}
