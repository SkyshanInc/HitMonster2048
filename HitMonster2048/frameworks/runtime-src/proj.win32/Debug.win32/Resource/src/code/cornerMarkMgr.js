
var CornerMarkConfig = {
	//突破
	"Mark_QiangHua":{
		getNum:function(){		
			var num = 0;
			var generals = MainPlayer.getArmedGenerals();
			for(var i=0;i<generals.length;i++){
				var wj = generals[i];
				if(wj.get("level") >= wj.getMaxLv() && uiGeneralBreak.isAbleBreakFormItems(wj))
					num++;
			}
			return num;
		}
	},
	//活跃度
	"Mark_LivenessTask":{
		getNum:function(){
			var num = 0;
			var liveness = MainPlayer.get("liveness");
			num = parseInt(liveness/20);
			var gots = MainPlayer.get("livenessGotAwards");
			return num - gots.length;
		}
	},
	"Mark_TangGuo":{
		getNum:function() {
			var num = this.lastNum||0;
			var lv = MainPlayer.get("soldierLv");
			var soldierData = DataMgr.getData("soldiers",lv);
			var costGold = soldierData["goldCost"];
			var gold = MainPlayer.get("gold");
			if(gold>costGold)
				return num++;
			else return num;
		}
	},
	//贺卡
	"Mark_PazzleTask":{
		getNum:function() {
			var num = this.lastNum||0;
			var isPazzle = MainPlayer.get("isPuzzleTaskFinished");
			return isPazzle? num++ : num;
		}
	},
	//成就
	"Mark_TaskReward":{
		getNum:function() {
			var gotNum = 0;
			var okNum  = 0;
			var rewards = MainPlayer.get("achievements");
			for(var k in rewards){
				var got = rewards[k]["isGotAward"];
				if(got)
					gotNum++;
				var staticData = DataMgr.getData("achievements",rewards[k]["typeID"]);
				if(rewards[k]["count"] >= staticData["condition"])
					okNum++;
			}
			var changeNum = okNum - gotNum
			var taskRewardUI = UIMgr.findUI("uiTaskReward");
			if(taskRewardUI && taskRewardUI.isShown()){
				this.lastNum = changeNum;
			}
			return changeNum;
		}
	},
	"Mark_Mails":{
		getNum:function(){
			var num = this.lastNum || 0;
			var curMailNum = MainPlayer.getMails().size();
			var realMailCount = MainPlayer.get("mailRealCount");
			if(realMailCount != curMailNum)
				num++;
			return num;
		}
	}
}

var CornerMark = function(markCfg,cornerIcon){
	this.mIcon		= cornerIcon,
	this.mMarkCfg	= markCfg,
	this.show = function(isShow) {
		isShow = isShow == undefined? true: isShow ;
		var curNum = this.mMarkCfg.getNum();
		cc.log("[Mark]curNum" + curNum+" <==> lastNum"+this.mMarkCfg.lastNum);
		if(isShow){
			if(curNum < this.mMarkCfg.lastNum)
				this.mMarkCfg.lastNum = curNum;
			this.mMarkCfg.mCurNum = curNum;
			var isChanged = curNum != this.mMarkCfg.lastNum;
			this.mIcon.setVisible(isChanged);
		}
		else {
			var idx = this.mMarkCfg.markBtns.indexOf(this.mIcon.getParent().getName());
			this.mMarkCfg.markBtns.splice(idx,1);
			if(this.mMarkCfg.markBtns.length == 0){
				this.mIcon.setVisible(false);
				this.mMarkCfg.lastNum = curNum;
			}
		}
		cc.log("MarkBtns:[ "+this.mMarkCfg.markBtns.join("*")+" ]");
	}	
}

// 角标管理
var CornerMarkMgr = {
	mIconFile:"img_shuzitiaoda.png",
	// btn:显示icon的按钮
	// add(btn,markID) markID:类型
	showMark:function(btn,markID) {
		var markCfg = CornerMarkConfig[markID];
		if(!btn.cornerMark) {
			if(markCfg.lastNum == undefined) 
				markCfg.lastNum = 0;
			
			var icon = markCfg.iconFile || this.mIconFile;
			if(!markCfg.markBtns) 
				markCfg.markBtns = [btn.getName()];
			else if(markCfg.markBtns.indexOf(btn.getName())<0)
				markCfg.markBtns.push(btn.getName());
			btn.cornerMark = new CornerMark(markCfg,this.createIcon(icon,btn));
			markCfg.mark = btn.cornerMark;
			cc.log("[Mark]New cornerMark " + markID);
		}		
		btn.cornerMark.show(true);
	},
	createIcon:function(icon,parent){
		var img = ccui.ImageView.create();
		img.loadTexture(icon,ccui.Widget.PLIST_TEXTURE);
		//img.setScale9Enabled(true);
		//var lbl = cc.LabelTTF.create("0","Arail",20);
		//img.addNode(lbl,0,100);
		if(!parent) return img;
		
		parent.addChild(img);
		var bsize = parent.getContentSize();
		img.setPosition(bsize.width/2-5,bsize.height/2-5);
		return img;
	},
	isMarkChanged:function(id,isSet){
		isSet = isSet == undefined? false : isSet;
		var markCfg = CornerMarkConfig[id];
		
		var curNum = markCfg.getNum();
		cc.log("[Mark]id: "+id+" lastNum: "+markCfg.mCurNum+",curNum: "+ curNum);
		var isChange = markCfg.mCurNum < curNum;// markCfg.lastNum < markCfg.mCurNum;
		if(isSet){
			markCfg.lastNum = curNum;
		}
		return isChange;
	}
}