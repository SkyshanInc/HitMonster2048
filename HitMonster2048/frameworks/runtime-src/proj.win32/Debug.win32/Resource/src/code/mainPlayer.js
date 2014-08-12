/*var playerData = 
 {
    result: {
        __v: 0, 
        device_hash: "gpnjkjvgvy", 
        _id: "5358cf05f6b7f03f73a30d00", 
        items: [
            {
                typeID: 41001, 
                amount: 9999
            }, 
            {
                typeID: 41002, 
                amount: 9999
            }, 
            {
                typeID: 41003, 
                amount: 9999
            }
        ], 
        generals: [
            {
                typeID: 12005, 
                _id: "5358cf05f6b7f03f73a30d01", 
                lvUpLimit: 1, 
                star: 0, 
                exp: 0, 
                level: 1, 
                armedIndex: 0
            }, 
            {
                typeID: 13003, 
                _id: "5358cf05f6b7f03f73a30d02", 
                lvUpLimit: 1, 
                star: 0, 
                exp: 0, 
                level: 1, 
                armedIndex: 1
            }, 
            {
                typeID: 13004, 
                _id: "5358cf05f6b7f03f73a30d03", 
                lvUpLimit: 1, 
                star: 0, 
                exp: 0, 
                level: 1, 
                armedIndex: 2
            }, 
            {
                typeID: 14001, 
                _id: "5358cf05f6b7f03f73a30d04", 
                lvUpLimit: 1, 
                star: 0, 
                exp: 0, 
                level: 1, 
                armedIndex: -1
            }, 
            {
                typeID: 14002, 
                _id: "5358cf05f6b7f03f73a30d05", 
                lvUpLimit: 1, 
                star: 0, 
                exp: 0, 
                level: 1, 
                armedIndex: -1
            }
        ], 
        lastHuntTime: "2014-04-24T08:41:28.370Z", 
		pvpPoint: 10,
		pvePoint: 10,
        gold: 1000, 
        gem: 1000, 
        nickname: "gpnjkjvgvy"
    }
}
*/

//////////////////////////////////

/*
能够升级物品类型是 3
*/
var ITEMTYPE = {
    UPGRLITEMTYPE : 3,
};


var MainPlayer = {
    data: null,
    isPuzzleTaskFinished:false,//是否需要跳转到贺卡界面
    builds:{},
	generals:{},
	items:{},
    _lvConsumeExps:new Map(),
    mailDatas:new Map(),
	isLogin:false,
    init: function (jsonData) {
        this.data  = {};
		this.createGenerals(jsonData);
		for(var k in jsonData.items){
			var item = Clone(jsonData.items[k]);
			this.items[item.typeID] = item;
		}
        for(var k in jsonData){
			if(k == "achievements"){
				var achievements = {};
				for(var i=0;i<jsonData.achievements.length;i++){
					var anc = jsonData.achievements[i];
					achievements[anc.typeID] = anc;
				}
				this.data["achievements"] = achievements;
			}
			else
				this.data[k] = jsonData[k];
		}
		this.data["mailRealCount"] = 0,//消息的实时数量
		this.isLogin = true;
		//if(this.data["level"]>80) this.data["level"] = 80;
		//TalkingData 
        GameAnalytics.setAccountInfo(this.data.device_hash, this.data.nickname, this.data.level);
    },
    get:function(key){
		cc.log("[MainPlayer] get('"+key+"') = "+ObjToString(this.data[key]));
        return this.data[key];
    },
    set: function (key, value, isAdd) {
		if(isAdd){
			if(typeof(value) == "number") {
				this.data[key] += value;
			}
			else if(typeof(this.data[key]) == "array"){
				this.data[key].push(value);
			}
			else throw new Error("[MainPlayer] set('"+key+"') ");
		}
        else
            this.data[key] = value;
			
		cc.log("PlayerData set('"+key+"') = "+ ObjToString(this.data[key]));
        MsgMgr.postMsg("msg_playerUpdate", key);
    },
	resetData:function(jsonData){

		for(var k in this.data)
		{
			var val = jsonData[k];
            cc.log("k:"+k+",val:"+val)
			if(val!=undefined){
				//道具
				if(k == "items"){
					for(var itemKey in jsonData["items"]){
						var item = Clone(jsonData["items"][itemKey]);
						this.items[item.typeID] = item;
					}
				}
				//武将
				else if(k == "generals"){
					this.createGenerals(jsonData);
				}
				else if(k === "mails"){
                    this.setMailDatas(val)
                }
				// 成就在network里设置
				else if(k == "achievements"){
					continue;
				}
                else if(typeof(val) != "Function")
                    this.data[k] = Clone(val);

				cc.log("[MainPlayer]data reset ["+k+"] = " + val);
                MsgMgr.postMsg("msg_playerUpdate",k);
			}
		}
	},
	setAchievements:function(newAchs){
		var achs = this.get("achievements");
		if(!achs) return;
		for(var i=0;i<newAchs.length;i++){
			if(!newAchs[i]) throw new Error("achievements is null idx"+i + "achs:"+ObjToString(newAchs));
			var id = newAchs[i]["typeID"];
			achs[id] = newAchs[i];
			cc.log("[MainPlayer]set achievements["+id+"] : " + ObjToString(newAchs[i]));
		}
		MsgMgr.postMsg("msg_playerUpdate","achievements");
	},
	setItems: function(itemJson)
	{
		if(itemJson.length)
		for(var i = 0;i<itemJson.length;i++){
			MainPlayer.items[itemJson[i]["typeID"]] = Clone(itemJson[i]);
		}
		else if(itemJson.typeID)
			MainPlayer.items[itemJson.typeID] = itemJson;
			
		MsgMgr.postMsg("msg_playerUpdate","items");
	},
    createGenerals:function(jsonData)
    {
		var tName = "generals";
        var wjList = jsonData[tName];

		if(wjList)
		{
			for(var i=0;i<wjList.length;i++)
			{
				var data = Clone(wjList[i]);
				data.typeName = tName;
				var wj = new general(data);
				this.generals[data.typeID+""] = wj;
			}
		}
    },
	getArmedGenerals:function()
	{
		var list = [];
		for(var key in this.generals)
		{
			var g = this.generals[key];
			if(g.get("armedIndex")>=0)
			list.push(g);
		}
		list.sort(function(l,r){
			return l.get("armedIndex")-r.get("armedIndex");
		})
		cc.log("armedGenerals:"+list.join(","));
		return list;
	},
    getAllItemsWithType : function(type){
        var upItems = [];
        var items = this.items;
        for(var k in items){
            var item = items[k]
            if(item != undefined){
                var dataItem = DataMgr.getData("items",item["typeID"]);
                if(dataItem == undefined ||( type != undefined && dataItem["type"] != type) ){ 
                   continue
                }
                item.dataItem = dataItem;
                var amount = item["amount"]
                cc.log("amount:"+amount)
                for(var i = 0;i<amount;i++){
                    var it = Clone(item)
                    it.orderID = k+""+(i+1)
                    upItems.push(it)
                }
            }
        }
        return upItems;
    },
	getNextLevelExp:function(){
		var lev = MainPlayer.get("level")||"1";
		var playerLevelData = DataMgr.getData("playerLevels",lev);
		if(playerLevelData)
			return playerLevelData["nextLvExp"];
		else return -1;
	},
    hasEnoughMoney: function(currency, money) {
        if (currency == CURRENCY_TYPE.GOLD) {
            return this.hasEnoughGold(money);
        } else {
            return this.hasEnoughGem(money);
        }
    },
    hasEnoughGold: function(gold) {
        if (this.get("gold") >= gold) return true;
        uiTip.showGoldNotEnough();
        return false;
    },
    hasEnoughGem: function(gem) {
        if (this.get("gem") >= gem) return true;
        uiTip.showGemNotEnough();
        return false;
    },
	getName:function(){
		return this.get("device_hash");
	},
	clean:function(){
		this.data		= {};
		this.generals	= {};
		this.items		= {};
		this.builds		= {};
		this.mailDatas.clear();
		this.isLogin    = false;
	},
    //获取武将达到等级时所需要消耗的经验值
    getGeneralLvConsumeExp:function(lv){

        var exp = 0
        exp = this._lvConsumeExps.get(lv)
        if(exp != undefined){
            cc.log("****  内存变量里取出   *****  exp : " + exp)
            return exp;
        }
        exp = 0;
        var cardLvData = DataMgr.getData("cardLevels")
        for(var k in cardLvData){
            var lvK = parseInt(k)
            this._lvConsumeExps.put(k,exp)
            if(lvK >= lv){
                return exp
            }
            exp += cardLvData[k]["nextLvExp"]
            
        }
        return exp;
    },
    setMailDatas:function(mailJsonDatas){
        for(var i = 0;i < mailJsonDatas.length;i++){
            var mailItemData = mailJsonDatas[i]
            cc.log("mailItemData[id]:"+mailItemData["id"])
            this.mailDatas.removeByKey(mailItemData["id"])
            this.mailDatas.put(mailItemData["id"],mailItemData)
        }
		this.set("mailRealCount",this.mailDatas.size());
    },
	getMails:function(){
		return this.mailDatas;
	},
    getFriendPowerMaxCount:function(){
        return POWERRECIEVETIMES;
    },
    isGetFriendPower:function(){
        return this.getFriendPowerMaxCount() > this.get("pveReTimes")
    },
	getMaxPvePointCount:function(){
		var lv = this.get("level")||80;
		if(lv>80) lv = 80;
		return DataMgr.getData("playerLevels",lv).maxPoint;
	}
}