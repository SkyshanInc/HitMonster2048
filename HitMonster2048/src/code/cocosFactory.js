
var CocosFactory = {
    mConfig:null,
    init : function()
    {
        this.mConfig = {
            mainScene:			[null, function () { return new mainScene() }],
            gamePlay:    [res.None_Json, function () { return new GamePlay() }],
            
        }
    },
    create : function(id,jsonPath) //1280 * 720
    {
        var winSize = GetWinSize();
        var isRetain = winSize.width >= 720 || winSize.height >= 1280;
        //var folder = isRetain ? "res/hd/" : "res/sd/";
        var folder = "";
		if(!cc.sys.isNative) folder = "web_res/sd/"
        
		if(!jsonPath){
			var opt = this.mConfig[id];
			if(!opt) throw new Error("[CocoFactroy]ui not find in mConfig id:"+id);
			var cocosFile = opt[0] ;
			var layoutClass = opt[1]();
			var layoutRoot = null;
			if(cocosFile)// 可以没有布局文件 
			{
				cc.log("[CocoFactroy]jsonFile :"+cocosFile);
				layoutRoot = ccs.uiReader.widgetFromJsonFile( folder + cocosFile);
				layoutRoot.setSize(cc.director.getVisibleSize());
				layoutClass.setContentSize(winSize);
				this.bindTouchEvent(layoutRoot,layoutClass);
			}
			layoutClass.create(id, layoutRoot, cocosFile);
			return layoutClass;
		}
		//只加载布局文件
		else {
			var layoutRoot = ccs.uiReader.widgetFromJsonFile( folder + jsonPath);
			if(layoutRoot == null){
				throw new Error("[CocoFactroy] ui json 没找到 "+jsonPath);
			}
			var ui = UIMgr.findUI(id);
			cc.log(id+">>>");
			if(ui){
				
				this.bindTouchEvent(layoutRoot,ui);}
			return layoutRoot;
		}
    },
    bindTouchEvent: function (root, owner)
    {
        var children = root.getChildren();
        for (var i = 0; i < children.length; i++) {
            if (children[i] instanceof ccui.Button)
            {
                children[i].addTouchEventListener(owner.buttonEvent, owner);
				if(children[i].getName().toLowerCase().indexOf("close")>0)
					owner.mCloseBtn = children[i];
            }
			else if (children[i] instanceof ccui.CheckBox)
			{
				children[i].addEventListenerCheckBox(owner.checkBoxEvent,owner)
			}
            else if (children[i] instanceof ccui.Slider || children[i] instanceof ccui.LoadingBar)
            {
                children[i].addTouchEventListener(owner.valueChangedEvent, owner);
            }
            else if (children[i] instanceof ccui.Text || children[i] instanceof ccui.TextField)
            {
                children[i].addTouchEventListener(owner.textInputEvent, owner);
            }
            else if(children[i] instanceof ccui.ScrollView)
            {
                //this is a bug
                //children[i].setClippingType(1);
                if(owner.scrollEvent)
                    children[i].addEventListenerScrollView(owner.scrollEvent, owner);
                    
                this.bindTouchEvent(children[i],owner);
            } 
			else if(children[i] instanceof ccui.PageView)   
			{
				//children[i].setTouchEnabled(true);
				if(owner.onPageEvent)
                    children[i].addEventListenerPageView(owner.onPageEvent, owner);
                    
                this.bindTouchEvent(children[i],owner);
			}
            else
                this.bindTouchEvent(children[i],owner);
        }
    }
}

