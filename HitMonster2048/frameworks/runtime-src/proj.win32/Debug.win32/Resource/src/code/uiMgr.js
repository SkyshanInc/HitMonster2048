
var UIMgr = {
    mUIArray  : [],
	mUnCtrlUI : "uiTop,uiLoading,uiNotice,uiRewardTip",
	mCurrentUI    : null,
	_zorder	  : ZOrder_UITop,
	mLock	  : false,
	mUIWaitList:[],
	//创建界面
    add : function (uiID) 
    {
        var isShow = true;
        var sliceIdx = 1;
        if (arguments.length > 1) {
            if (typeof (arguments[1]) == "boolean") {
                isShow = arguments[1];
                sliceIdx = 2;
            }
        }
        var args = Array.prototype.slice.call(arguments, sliceIdx);
        Array.prototype.unshift.call(args, isShow);
		
		
        var newDlg = UIMgr.findUI(uiID);
        if (newDlg == null) {
            newDlg = CocosFactory.create(uiID);
            newDlg.createFinish.apply(newDlg, args);
            UIMgr.mUIArray.push(newDlg);
            if (!isShow) {
                newDlg.setVisible(false);
                return newDlg;
            }
        }
		
		if(isShow){
			this.dealUIShow(newDlg,args);
		}
		else newDlg.showFinish(false);
        return newDlg;
    },
	
	//["uiID",{"id":"uiID",params:[],callback:func}]
	addList:function(list) {
		if(this.mUIWaitList.length == 0) {
			this.mUIWaitList = list;
			this._showNextWaitUI();
		}
		else {
			this.mUIWaitList = this.mUIWaitList.concat(list);
		}
	},
	
	_showNextWaitUI:function(){
		if(this.mUIWaitList.length>0){
			var uiCfg = this.mUIWaitList.shift();
			var ui = null;
			if(typeof(uiCfg)=="string"){
				ui = this.add(uiCfg);
			}
			else {
				var params = uiCfg["params"]||true;
				params.unshift(uiCfg.id);
				ui = this.add.apply(this,params);
			}
			
			ui._waitUIConfig = uiCfg;
			cc.log("[UIMgr]addWaitUI :"+ObjToString(uiCfg));
		}		
	},
	
	//处理界面显示情况
	dealUIShow:function(dlg,args)
	{
		if(!dlg.getParent()){
			var zOrder = dlg.uiOpt.zOrder||this._zorder++;
			dlg.uiOpt.parent.addChild(dlg);
			dlg.release();
		}
		//已经显示的窗口 直接返回
		var isCanShow = dlg.isCanShow(args[0]);
		cc.log("[UIMgr]ui show state: "+isCanShow);
		
		if(!isCanShow)
			return;

		//touch锁定
		if(this.mUnCtrlUI.indexOf(dlg.getID())<0)
			LockScreen(true,dlg.mID);
		dlg.show.apply(dlg, args);
		
		if(dlg.uiOpt.isHideMainUI){
			this.hideAll(dlg);
		}
		if(dlg.uiOpt.isHideOther){
			this.hideOthers(dlg);
		}
		//排序 0 -> max 
		if (this.mUIArray.length > 1) {
			this.mUIArray.sort(function (l, r) {
				return (l.getLocalZOrder() > r.getLocalZOrder());
			});
		}
		
		if(dlg.uiOpt.uiShowMode == DSM_Normal) {
			dlg.showFinish(true);
		}
		if( dlg.isNormal() && this.mUnCtrlUI.indexOf(dlg.mID)<0)
			this.mCurrentUI = dlg.mID;
		cc.log("[UIMgr]topUI:"+this.mCurrentUI);
	},
	
    update:function(ftime)
    {
        for(var i=0;i<UIMgr.mUIArray.length;i++){
            UIMgr.mUIArray[i].uiUpdate(ftime);
        }
    },
    findUI:function(uiID)
    {
        for(var i=0;i<UIMgr.mUIArray.length;i++)
        {
            if (UIMgr.mUIArray[i].mID == uiID)
                return UIMgr.mUIArray[i];
        }
        return null;
    },
	
    showUI:function( ui ){
		var dlg = ui;
        if(typeof(ui)=="string")
            dlg = UIMgr.findUI(ui)
        if( null == dlg )
            return 

		var args = Array.prototype.slice.call(arguments, 1);
        Array.prototype.unshift.call(args, true);
		this.dealUIShow(dlg,args);
    },

    hideUI: function (ui,backUI) {
		if(ui == null) return;
        var dlg = ui;
        if(typeof(ui)=="string")
            dlg = UIMgr.findUI(ui);
        if( null == dlg ){
			cc.log("[Warning] hideui not find "+ ui);
            return ;
		}
		if(this.mCurrentUI == dlg.mID)
			this.mCurrentUI = "";
		
		var isCanShow = dlg.isCanShow(false);
		if(!isCanShow)
			return;
		
		//隐藏时锁定
		if(this.mUnCtrlUI.indexOf(dlg.getID())<0)
			LockScreen(true,dlg.mID);
		dlg.show(false);
		
		if(backUI){
			UIMgr.add(backUI);
		}
//		if(dlg.uiOpt.isHideMainUI){
//			UIMgr.add("uiTop");
//		}
//		
//		if(dlg.uiOpt.isHideTopBtns){
//			UIMgr.findUI("uiTop").setTopButtonsVisible(true);
//		}
    },
	
	hideOthers: function (butDlg) {
        if(this.mCurrentUI!=""&&this.mCurrentUI!=butDlg){
			this.hideUI(this.mCurrentUI);
		}
    },
	
    hideAll:function(butDlg)
    {
        for (var i = 0; i < this.mUIArray.length; i++)
		{
			if(this.mUIArray[i].mIsShow&&this.mUIArray[i].mID!=butDlg.mID)
				this.mUIArray[i].forceHide();
		}
    },
	
    showPrevUI:function(){
	
    },
	
    removeUI: function (ui, clean) {
        clean = clean || true;
        var id = ui;
        if (ui&&typeof (ui) != "string")
            id = ui.mID;
        for (var i = 0; i < UIMgr.mUIArray.length; i++) {
            if (UIMgr.mUIArray[i].mID == id)
            {
                var dlg = UIMgr.mUIArray[i];
                UIMgr.mUIArray.splice(i, 1);
				dlg.remove();
				cc.log("[UIMgr] UI removed "+id);
                break;
            }
        } 
    },
	
	onUIShowFinish:function(dlg,isShow){
		if(dlg.uiOpt.isHideTopBtns&&isShow){
//			UIMgr.findUI("uiTop").setTopButtonsVisible(!isShow);
		}
		//touch 释放
		if(this.mUnCtrlUI.indexOf(dlg.getID())<0)
			LockScreen(false,dlg.mID);
		
		var lastPos = cc.p(0,0);
		if(!isShow){
			//处理序列
			if(dlg._waitUIConfig){
				var callback = dlg._waitUIConfig["callback"];
				if(callback)
					callback(dlg.getID());
				this._showNextWaitUI();
			}
			
			if (dlg.uiOpt.isAutoRelease){
				UIMgr.removeUI(dlg);
				//cc.spriteFrameCache.removeUnusedSpriteFrames();
				//cc.textureCache.removeUnusedTextures();
			}
			else {
				dlg.setVisible(false);
				//处理穿透bug
				dlg.setPosition(cc.p(10000,10000));
				// 特殊处理 此版本 必须从父节点移除 解决touch优先级的问题
				dlg.retain();
				var parent = dlg.getParent();
				if(parent)
					parent.removeChild(dlg,false);
			}
		}
		else
			dlg.setPosition(cc.p(0,0));
		
	},
	getCurrentUI:function(){
		return this.mCurrentUI;
	},
	clean:function(){
		for(var i=0;i<this.mUIArray.length;i++){
			var ui = this.mUIArray[i];
			ui.remove();
		}
		this.mUIArray = [];
		
		//cc.spriteFrameCache.removeSpriteFrames();
		//cc.textureCache.removeUnusedTextures();
		//cc.textureCache.removeAllTextures();
		cc.log("=========== ui clean =========");
	}
}
