var MusicMgr = {

    res: "",
	isMusicOn:true,
	isEffectOn:true,
    lastBackgroundMusicFile:"normal.mp3",//初始化的背景音乐
	init: function(){
        this.isMusicOn  = cc.sys.localStorage.getItem("MusicOn") != "off";
		this.isEffectOn = cc.sys.localStorage.getItem("EffectOn")  != "off";

        cc.log("初始化:"+cc.sys.localStorage.getItem("MusicOn"));
        cc.log(cc.sys.localStorage.getItem("EffectOn"));
    },
    playBackgroundMusic: function (file) {//file参数如果不传，就播放上一次的背景音乐
        cc.log("MusicMgr.isMusicOn:"+MusicMgr.isMusicOn);

        var _file = file || lastBackgroundMusicFile
        lastBackgroundMusicFile = _file

		if(MusicMgr.isMusicOn)
			cc.audioEngine.playMusic(this.res + _file,true);
    },

    pauseBackgroundMusic:function(){
        if(MusicMgr.isMusicOn)
            cc.audioEngine.pauseMusic();
    },

    resumeBackgroundMusic:function(){
        if(MusicMgr.isMusicOn)
            cc.audioEngine.resumeMusic();
    },

    setMusicVolume: function(volume) {
        cc.audioEngine.setMusicVolume(volume);
    },

    stopBackgroundMusic:function(v) {
        cc.audioEngine.stopMusic(v);
    },

    playEffect: function (file, loop) {
		if(!this.isEffectOn) return;
		
        if (loop == undefined) {
            loop = false;
        }
        var sID = cc.audioEngine.playEffect(this.res + file, loop);

        //cc.log("音效id:"+sID);

        return sID;
    },

    stopEffect: function(sID){
        cc.audioEngine.stopEffect(sID);  
    }
};





