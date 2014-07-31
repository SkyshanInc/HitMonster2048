
var ErrorTip = {
    "-40000":"武将已经上证",
}
var Logic = {
    
    
updatePlay:function(jsonData){

    //索要移除的数据
    if(jsonData["removedMails"] != undefined){
        for(var i = 0;i<jsonData["removedMails"].length;i++){
            MainPlayer.mailDatas.removeByKey(jsonData["removedMails"][i])
        }
    }
	MainPlayer.resetData(jsonData);
},
errorTip:function(jsonData){
    
    UIMgr.add("uiWarning",jsonData.errorInfo)
}
    
}
 
//上针
Logic.armGeneral = function (generalID, index) {
    
    cc.log("generalTypeID:"+generalID)
    
    //进行客户端预先判定
    
    var sevData = NetWorkData.armGeneral(generalID,index);
    NetWork.send(sevData,this.armGeneralEnd,this)
}
Logic.armGeneralEnd = function(jsonData){
    
    var result = jsonData["result"]
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("ARMEDSUCCESS")
        
    }else{
        //失败
        MsgMgr.postMsg("ARMEDFAIL")
        this.errorTip(jsonData)
    }
    
    
    
    
}

//武将升级
Logic.upgradeGeneral =  function (generalID, itemTypeID){
    
    cc.log("itemTypeID:"+itemTypeID)
    //进行客户端预先判定
    var sevData = NetWorkData.upgradeGeneral(generalID,itemTypeID);
    NetWork.send(sevData,this.upgradeGeneralEnd,this)
}
Logic.upgradeGeneralEnd = function(jsonData){
    
    var result = jsonData["result"]
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("WJUPSUCCESS")
        
    }else{
        //失败
        this.errorTip(jsonData)
    }
    
}
//开坑
Logic.addGeneralGroove = function () {
    
    
    
    var sevData = NetWorkData.addGeneralGroove()
    NetWork.send(sevData,this.addGeneralGrooveEnd,this)
    
    
}
Logic.addGeneralGrooveEnd = function(jsonData){
    
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("ADDGROOVESUCCESS")
        
    }else{
        //失败
        this.errorTip(jsonData)
    }
    
}
//武将突破
Logic.generalAdvance = function(generalID){
    
    
    var sevData = NetWorkData.generalAdvance(generalID)
    NetWork.send(sevData,this.generalAdvanceEnd,this)
}
Logic.generalAdvanceEnd = function(jsonData){
    
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("WJBREAKSUCCESS")
        
    }else{
        //失败
        this.errorTip(jsonData)
    }
    
}
//送体力
Logic.sendNormalMail = function (_aimDevice_hash) {
    cc.log("_aimDevice_hash:"+ _aimDevice_hash)
    var sevData = NetWorkData.sendNormalMail(_aimDevice_hash)
    NetWork.send(sevData,this.sendNormalMailEnd,this)
    
}
Logic.sendNormalMailEnd = function(jsonData){
    
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        //成功
        // this.updatePlay(result)
        
        
    }else{
        //失败
        this.errorTip(jsonData)
    }
    
}
//获取邮件
Logic.getMails = function () {
    var sevData = NetWorkData.getMails();
    NetWork.send(sevData,this.getMailsEnd,this)
}
Logic.getMailsEnd = function (jsonData) {
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("GETMAILSUCCESS")
    }else{
        //失败
        this.errorTip(jsonData)
    }
}
//领取好友体力
Logic.recieveNormalMail = function (_mailID) {
    var sevData = NetWorkData.recieveNormalMail(_mailID);
    NetWork.send(sevData,this.recieveNormalMailEnd,this)
}
//删除 超越好友的消息
Logic.deleteShowOffMail = function (_mailID) {
    var sevData = NetWorkData.deleteShowOffMail(_mailID)
    NetWork.send(sevData,this.recieveNormalMailEnd,this)
}
//领取所有好友体力
Logic.recieveAllNormalMails = function () {
    var sevData = NetWorkData.recieveAllNormalMails()
    NetWork.send(sevData,this.recieveNormalMailEnd,this)
}
Logic.recieveNormalMailEnd = function (jsonData) {
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("RECIEVEPOWERSUCCESS",result)
    }else{
        //失败
        this.errorTip(jsonData)
    }
}
//收取系统邮件
Logic.getSysMailAwards = function (_mailID) {
    var sevData = NetWorkData.getSysMailAwards(_mailID)
    NetWork.send(sevData,this.getSysMailAwardsEnd,this)
}
Logic.getSysMailAwardsEnd = function (jsonData) {
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        
        var awards = [];
        var itemDatas = result["items"] || []
        for(var i = 0;i<itemDatas.length;i++){
            var data = itemDatas[i]
            var typeID = data["typeID"]
            var amount = data.amount - MainPlayer.items[typeID].amount
            //生成新对象
            var award = {}
            award.typeID = typeID
            award.amount = amount
            awards.push(award)
        }
        
        //成功
        this.updatePlay(result)
        
        MsgMgr.postMsg("RECIEVESYSMAILSUCCESS",awards)
    }else{
        //失败
        this.errorTip(jsonData)
    }
}


// 招募武将
Logic.recruitGeneral = function (type) {
    if (type == 1) {
        GameAnalytics.onRecruitWithGold();
    } else if (type == 2) {
        GameAnalytics.onRecruitWithGem();
    }
    var sevData = NetWorkData.recruitGeneral(type)
    NetWork.send(sevData,this.recruitGeneralEnd,this)
}
Logic.recruitGeneralEnd = function(jsonData){
    if(jsonData.error) {
        MusicMgr.playBackgroundMusic("normal.mp3");
        UIMgr.add("uiWarning",jsonData.errorInfo);
        return;
    }
    var result = jsonData["result"];
    this.updatePlay(result);
    MainPlayer.set("gold",result.gold);
    MainPlayer.set("gem",result.gem);
    MsgMgr.postMsg("WJRECRUITSUCCESS", jsonData["result"]);
}

Logic.addBasicInfo = function(_type,_increment){
    
    
    var sevData = NetWorkData.addBasicInfo(_type,_increment)
    NetWork.send(sevData,this.addBasicInfoEnd,this)
}
Logic.addBasicInfoEnd = function(jsonData){
    
    var result = jsonData["result"]
    
    cc.log("result:"+result)
    if(result != undefined){
        //成功
        this.updatePlay(result)
        
        
    }else{
        //失败
        this.errorTip(jsonData)
    }
    
}
//重置
Logic.resetInfo = function (_type) {
    
    var sevData = {
    method: 'resetInfo',
    params: {
    device_hash: MainPlayer.getName(),
    type: _type,
    }
    }
    NetWork.send(sevData,this.addBasicInfoEnd,this)
    
}
Logic.addItem = function (_typeID, _amount) {
    var sevData = {
    method: 'addItem',
    params: {
    device_hash: MainPlayer.getName(),
    typeID: _typeID,
    amount:_amount,
    }
    }
    NetWork.send(sevData,this.addBasicInfoEnd,this)
}


Logic.addGeneral = function (_typeID) {
    var sevData = {
    method: 'addGeneral',
    params: {
    device_hash: MainPlayer.getName(),
    typeID: _typeID,
    }
    }
    NetWork.send(sevData,this.addBasicInfoEnd,this)
    
}
//通通有奖
Logic.addItemsForTest = function(){
    var sevData = {
    method: 'addItemsForTest',
    params: {
    device_hash: MainPlayer.getName(),
    }
    }
    NetWork.send(sevData,this.addBasicInfoEnd,this)
    
}

