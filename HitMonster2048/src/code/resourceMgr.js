
var ResourceLoadType = {
	FIGHT:1,
	UI:2,
}	

var ResourceMgr = {
	resourceMap:{},//保存引用计数 key:number,
	
    generalBoneList: [
            "guaiwu_nvqibing_1",
            "guaiwu_nvqibing_3",
            "guaiwu_wuji_1",
            "wujian_guojia",
            "wujiang_chengpu",
            "wujiang_diaochan",
            "wujiang_dongzhuo",
            "wujiang_zhangbao",
            "wujiang_zhangliang"
      ],


	init:function(){
	
		var list = this.foreverList;
		for(var i = 0;i<list.length;i++){
			ResourceMgr.addForeverPlist(list[i]);
		}
		
		//加载骨骼文件
		var gugeList = this.generalBoneList;

		for(var i = 0;i<gugeList.length;i++){
			ccs.armatureDataManager.addArmatureFileInfo(gugeList[i]+".ExportJson");
		}

	},	
	addPlist:function(name){

        var fullPath = cc.FileUtils.getInstance().fullPathForFilename(name+".plist");
		cc.spriteFrameCache.addSpriteFrames(fullPath);
		if(this.resourceMap[name]==undefined||this.resourceMap[name]==null){
			this.resourceMap[name] = 0;
		}
		this.resourceMap[name]++;
	},

	removeUnusedPlist:function(name){
		for(var i = 0;i<this.foreverList.length;i++){
			if(this.foreverList[i]==name){
				return;
			}
		}

		if(this.resourceMap[name]){
			this.resourceMap[name]--;
			if(this.resourceMap[name]==0){
				cc.log("清除了资源:"+name);
				AnimationMgr.clear();
                var fullPath = cc.FileUtils.getInstance().fullPathForFilename(name+".plist");
				cc.spriteFrameCache.removeSpriteFramesFromFile(fullPath);
			}
		}
	},

	addForeverPlist:function(name){
		var fullPath = cc.FileUtils.getInstance().fullPathForFilename(name+".plist");
		cc.spriteFrameCache.addSpriteFrames(fullPath);
	},

	removeUnusedPlistByList:function(list){
		AnimationMgr.clear();
		for(var i = 0;i<list.length;i++){
			this.removeUnusedPlist(list[i]);
		}
		cc.textureCache.removeUnusedTextures();
		cc.sys.garbageCollect();
	},

	addUIWithLoadList:function(callBack,type){
		UIMgr.clean();
		var list ;
		if(type==ResourceLoadType.FIGHT){
			this.removeUnusedPlistByList(this.uiList);
			list = this.fightList;
		}else{
			this.removeUnusedPlistByList(this.fightList);
			list = this.uiList;
		}		

		cc.log("加载列表:"+ObjToString(list));

		var panel = UIMgr.add("uiLoadResource",list);
		panel.onShowCall(function(isShow){
			if(!isShow){
            	if(type==ResourceLoadType.UI){
            		UIMgr.add("uiTop");
            	}
				callBack();
			}
		});
	},
}
