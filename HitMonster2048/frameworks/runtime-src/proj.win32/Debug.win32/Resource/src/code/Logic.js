
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

