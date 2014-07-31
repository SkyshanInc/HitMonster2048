var AppCtrl = {
	MSG_BACKGROUND:"msg_background",
	MSG_FOREGROUND:"msg_foreground",
	SCREEN_LOCK_RETAIN:0,
	isLogin:false,
	isEnterGame:false,
	serverTime:0,
	delayTime:0,
	
	onStart:function(){
//		DataMgr.init();
//		NetWork.init();
		CocosFactory.init();
		SceneMgr.init();
//		MusicMgr.init();
		
		SceneMgr.showScene("mainScene");
	},
	
	onEnter:function(){
		
         UIMgr.add("gamePlay");
        
	},
	
	onLogin:function(userData){
	
		if(userData){
			
		}
	},
	
	onEnterGame:function(){
		this.isEnterGame = true;
		UIMgr.clean();
		//this.resetScreenLock();
	},
	onExitGame:function(){
//		var self = this;
//		this.isEnterGame = false;
//		
//		NetWork.send("getServerTime",function(sevData){
//			self.serverTime = sevData.result.nowTime;
//		});
	},
	
	loginOut:function(){
	
//		this.isLogin = false;
//		this.clean();
//		NetWork.stopPoll();
//		UIMgr.add("uiLogin");
	},
	
	onUpdate:function(dt){
	
//		UIMgr.update(dt);
//		
//		if(this.isEnterGame)
//			return;
//			
//		NetWork.update(dt);
//		
//		if(!this.isLogin){
//			return;
//		}
//		
//		this.serverTime += dt*1000;
//		NoticeMgr.update(dt);
	},
	
	clean:function(){
	
//		MainPlayer.clean();
//		UIMgr.clean();
	},
	
	lockScreen : function(isLock,who,isClean){
	
		if(isLock){
			if(this.SCREEN_LOCK_RETAIN === 0){
				var scene = cc.director.getRunningScene();
				scene.getEventDispatcher().setEnabled(false);
			}
			this.SCREEN_LOCK_RETAIN += 1;
		}
		else{
			if(this.SCREEN_LOCK_RETAIN<=0)
				throw new Error("ScreenLockRetain Error: "+SCREEN_LOCK_RETAIN);
			this.SCREEN_LOCK_RETAIN -= 1;
			if(this.SCREEN_LOCK_RETAIN === 0){
				var scene = cc.director.getRunningScene();
				scene.getEventDispatcher().setEnabled(true);
			}
		}	
		who = who||"";
		cc.log(who+" -[Screen is " + (isLock?"Lock]- ":"unLock]- ")+this.SCREEN_LOCK_RETAIN);
	},
	
	resetScreenLock:function(){
	
		this.SCREEN_LOCK_RETAIN = 0;
		var scene = cc.director.getRunningScene();
		scene.getEventDispatcher().setEnabled(false);
	},
	
	applicationDidEnterBackground : function(){
		
		cc.log("进入后台!");
        MsgMgr.postMsg(AppCtrl.MSG_BACKGROUND,"");
		//android系统需要
		if(cc.sys.os==cc.sys.OS_ANDROID){
			MusicMgr.pauseBackgroundMusic();
		}	
	},
	
	applicationWillEnterForeground : function(){
		
		cc.log("进入前台!");
		var runScene = cc.director.getRunningScene();
		MsgMgr.postMsg(AppCtrl.MSG_FOREGROUND,"");
		//android系统需要
		if(cc.sys.os==cc.sys.OS_ANDROID){
			MusicMgr.resumeBackgroundMusic()
		}
	
		
		var self = this;
		runScene.runAction(
            cc.Sequence.create(
                cc.CallFunc.create(function(){

                	cc.log("进入后台! 并且获取焦点之后回调");

                	MsgMgr.postMsg(AppCtrl.MSG_FOREGROUND,"");

                	
					//android系统需要
					if(cc.sys.os==cc.sys.OS_ANDROID){
						MusicMgr.resumeBackgroundMusic()
					}
					
					
                                   
                                   
                                   
                                   
                                   
                    

                    }
                  )
                )
            );


		
	}
};

