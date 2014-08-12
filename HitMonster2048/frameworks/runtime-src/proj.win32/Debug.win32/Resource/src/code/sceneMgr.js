
var SceneMgr = 
{
    mCurScene: null,
    init:function(){},
    showScene:function(sceneID,showMode)
    {
        var scene = CocosFactory.create(sceneID);
        var director = cc.director;
        var curScene = director.getRunningScene();
        if (curScene)
        {
            //curScene.exit();
            director.runScene(scene);
        }
        else
            director.runScene(scene);
        this.mCurScene = scene;
        return scene;
    },
    getScene:function(){
        return this.mCurScene;
    },
    getSceneRoot:function(){
        return this.mCurScene.mRoot;
    },
    getUIRoot:function(){
        return this.mCurScene;
    },
	setSceneVisible:function(isShow){
		this.mCurScene.mRoot.setVisible(isShow);
	}
}
