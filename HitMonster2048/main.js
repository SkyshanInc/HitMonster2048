cc.game.onStart = function(){
    
    var glView = cc.view;
    var winSize = cc.winSize;
    var bsSize = cc.size(640.0, 960.0);
    var scaleX = winSize.width / bsSize.width;
    var scaleY = winSize.height / bsSize.height;
    
    var scale = 0.0; // MAX(scaleX, scaleY);
    if (scaleX > scaleY) {
        scale = scaleX / (winSize.height / bsSize.height);
        bsSize.width *= scale;
    } else {
        scale = scaleY / (winSize.width / bsSize.width);
        bsSize.height *= scale;
    }
    cc.view.setDesignResolutionSize(bsSize.width, bsSize.height, cc.ResolutionPolicy.SHOW_ALL);
	cc.view.resizeWithBrowserSize(true);
    
    
    var g_resources = [];
    try{
        var txt = cc.FileUtils.getInstance().getStringFromFile("resource.json");
        g_resources = JSON.parse(txt);
    }catch(e){
        cc.log("**** 解析resource.json 出错 *******");
    }
	
//	for(var k in res){
//		cc.log("res[k]:"+res[k])
//		g_resources.push(res[k]);
//	}
    //load resources
    cc.LoaderScene.preload(g_resources, function () {
//        cc.director.runScene(new HelloWorldScene());
        AppCtrl.onStart();
    }, this);
};
cc.game.run();