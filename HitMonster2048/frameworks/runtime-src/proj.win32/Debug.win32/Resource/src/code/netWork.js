
var NetError = {
	"10000":"参数不合法",
	"10001":"没有足够的金币",
	"10002":"没有足够的钻石",
	"10003":"系统错误",
	"10004":"没有足够的令牌",
    "10005":"服务器崩溃了！",
	"20000":"用户不存在",
    "20001":"用户已存在",
    "20002":"用户等级不足",
    "20003":"令牌数超过上限",
	"30000":"武将不存在",
	"30001":"武将等级超出上限",
	"30002":"武将已经上阵",
	"30003":"科技等级不足",
	"30004":"突破已经满级",
	"30005":"所有武将已经满级",
    "30006":"武将等级不够",
	"40000":"材料不足",
	"50000":"关卡未开启或不存在",
	"50001":"超出挑战次数",
	"50002":"已经领取过奖励",
	"60000":"科技不存在",
	"60001":"小球等级达到最高",
	"70000":"此道具只能单选",
	"80000":"此贺卡没有解锁",
	"80001":"此贺卡已经完成",
	"80002":"贺卡还没过期",
	"90000":"活跃度不足",
	"90001":"已经领取活跃度奖励",
	"90002":"超出当日抽奖次数",
    "90002":"当日不可以再玩老虎机",
    "90003":"该成就奖励已经获得",
    "90004":"成就值不够领取奖励",
    "100000":"当日已经给该人发送邮件",
    "100001":"邮件不存在",
    "100002":"邮件的类型不对",
    "100004":"邮件中奖励id和个数没有一一对应",
    "100005":"没有送体力邮件",
    "100006":"该用户已经关闭收取体力邮件功能",
	"sysError":[10000,10003,10005,30001,30002,30005,50001,70000,90002],
}

var NetWork = {
    curIp: "",
    connectDelay:0,
	// pollDelay:NETWORK_POLL_TIME,
	isReqest:false,
	isComplate:true,
	lastSendData:null,
	pollMsgs:["getMailCount"],
	curPollIdx:-1,
	isPolling:false,
	
	testIPs:["http://117.121.25.155:8345","http://117.121.25.155:8350","http://10.0.0.233:3000","http://10.0.0.233:4000","192.168.1.126:3000","http://10.3.0.138:3000"],
    ipConfig :{
    	
        login: "http://117.121.25.155:8345",//外网地址
		//login: "http://10.3.0.138:3000",
        // login: "http://10.0.0.233:3000",

        //login:"http://10.0.0.233:4000",//赵晨
        //login:"http://10.3.0.138:3000", //范长勇
        //login:"http://192.168.1.108:3000", //范长勇

    },
	forceLoginList:["slotMachine","getLivenessAward","getAchieveAward","upgradeSoldier"],
	
    init: function (cfgJson) {
        if(cfgJson)
            this.ipConfig = cfgJson;
        this.curIp = this.ipConfig.login;
		sys.localStorage.setItem("LoginIP",this.curIp);
    },
	
	setCurIp:function(ip){
		this.curIp = ip;
	},
	
    send: function (data, param0,param1)
    {
		var callback = param0;
		var owner	 = param1;
		var args     = null;
		
		//如果直接传入id 获取参数列表 生成 ServerData
		if(typeof(data)=="string"){
			var dataID = data;
			args = Array.prototype.slice.call(arguments, 1);
			if(args.length>0){
				if(typeof(args[args.length-1]) == "function"){
					callback = args[args.length-1];
					args.splice(args.length-1,1);
				}	
				else if(args.length>1 && typeof(args[args.length-2]) == "function"){
					callback = args[args.length-2];
					owner = args[args.length-1];
					args.splice(args.length-2,2);
				}
			}
			data = NetWorkData[dataID].apply(NetWorkData,args);
		}
		//锁屏
		LockScreen(true,"[NetWork]");
		this.lastSendData = data;
		this.isReqest = true;
		this.isComplate = false;
		
        var self = this;
        var xhr = cc.loader.getXMLHttpRequest();
        xhr.open("POST", this.curIp);
        xhr.onreadystatechange = function () {
            var httpStatus = xhr.statusText;
            var response = xhr.responseText;
			
			cc.log("==============NetWork==============")
			cc.log("[NetWork] ip:"			+ self.curIp);
            cc.log("[NetWork] status:"		+ xhr.status);
            cc.log("[NetWork] readyState:"  + xhr.readyState);
			cc.log("[NetWork] response:"	+ response);
			
            if (xhr.status == 0) {
			cc.log("==============NetWork==============")
				self.isReqest = false;
				self.connectDelay = 0;
                LockScreen(false,"[NetWork]");
				var severData;
				try{
					severData = JSON.parse(response);
				} catch(e) {
					var err = "readyState:" + xhr.readyState+"\n";
					err += "status:"+xhr.status+"\n";
					err += "xhr:"+ObjToString(xhr)+"\n";
					//UIMgr.add("uiWarning",err);
					cc.log("[NetWork] net reset error netWork retry...");
					self.retry(callback,owner);
					return;
				}
				
				if(severData.error) {
                    var str = NetError[severData.error+""];
					
                    if(str==null||str==undefined){
                        str = "unknown error";
                    }
					cc.log("网络成功 有错误:"+str);

					if(severData.error==10001){
						uiTip.showGoldNotEnough();
						return;
					}else if(severData.error==10002){
						uiTip.showGemNotEnough();
						return;
					}

					//系统错误直接弹窗
					if(NetError.sysError.indexOf(severData.error)>=0){
						UIMgr.add("uiWarning",str);
					}
					else {
						UIMgr.add("uiWarning",str);
						severData.errorInfo = str;
						if (owner)
							callback.call(owner,severData);
						else if(callback)
							callback(severData);
					}
				}
				else {
					cc.log("网络请求成功");
					self.globalDataCtrl(severData);
					if (owner)
						callback.call(owner,severData);
					else if(callback)
						callback(severData);
				}
				
            }
            else
            {
				cc.log("==============NetWork==============")
                LockScreen(false,"[NetWork]");
				var needRetry = false;
				if(xhr.status == 6||xhr.status==7||self.forceLoginList.indexOf(self.lastSendData.method)<0)
					needRetry = true;
				var msg = needRetry?"请求超时! 是否重新连接?":"网络不给力,请重新登录!";
				UIMgr.add("uiWarning",msg,function(flag){
					if(!needRetry||!flag)
						AppCtrl.loginOut();
					else {
						self.retry(callback,owner);
					}
				},!needRetry);	
				
				cc.log("请求超时或没有网络");
            } 

			self.isComplate = true;
			self.isReqest = false;
			self.connectDelay = 0;
        };
		
        if (typeof (data) == "object")
            data = JSON.stringify(data);
        xhr.send(data);
		
		cc.log("[NetWork] send "+(new Date()) + data);
    },
    setServer:function(key)
    {
        this.curIp = ipConfig[key];
    },
    update:function(ftime)
    {
		//轮询
		if(this.isPolling)
			this.polling(ftime);
		
		if(this.isComplate && this.loadui){ 
			this.loadui = null;
			UIMgr.hideUI("uiLoading");
		}
		if(!this.isReqest) return;
        this.connectDelay += ftime;
        if(this.connectDelay>0.5)
        {
            this.loadui = UIMgr.add("uiLoading");
			this.connectDelay = 0.0;
			this.isReqest = false;
        }
    },
	
	startPoll:function(){
		this.pollDelay = NETWORK_POLL_TIME;
		this.isPolling = true;
	},
	
	stopPoll:function(){
		this.isPolling = false;
	},

	//轮询
	polling:function(dt) {
		if(this.curPollIdx < 0)
			this.pollDelay -= dt;
			
		if(this.pollDelay <0 ){
			this.curPollIdx += 1;
			if(this.curPollIdx == this.pollMsgs.length){
				this.curPollIdx = -1;
				this.pollDelay  = NETWORK_POLL_TIME;
				return;
			}
			
			var self = this;
			var curMsg = this.pollMsgs[this.curPollIdx];	
			var xhr = cc.loader.getXMLHttpRequest();
			xhr.open("POST", this.curIp);
			xhr.onreadystatechange = function (){
				cc.log(xhr.status);
				if(!self.isPolling) 
					return;
				if (xhr.status == 0) {
					var response = xhr.responseText;
					var severData = JSON.parse(response);
					self.onPollEnd(curMsg,severData);
					
					cc.log("[NetWork PollEnd]" + response);
				}
				else {
					cc.log("[NetWork PollError]" + curMsg);
				}	
			}
			var sevData = NetWorkData[curMsg]();
			cc.log("[NetWork Poll] "+JSON.stringify(sevData));
			xhr.send(JSON.stringify(sevData));
		}
	},
	
	retry:function(callback,owner){
		this.send(this.lastSendData,callback,owner);
	},
	
	//设置 需要全局处理的数据
	globalDataCtrl:function(sevData){
		if(MainPlayer.data){
			var achievements = sevData["result"]["achievements"];
			if(achievements&&achievements.length>0){
				MainPlayer.setAchievements(achievements);
			}
		}
	},
	//轮询消息处理
	onPollEnd:function(msg,sevData){
		cc.log(msg);
		if(msg == "getMailCount"){
			var mailCount = sevData.result.mailcount;
			var curMailCount = MainPlayer.get("mailRealCount");
			if(mailCount == -1 || mailCount == curMailCount) 
				return;
			MainPlayer.set("mailRealCount",mailCount);
		}
	},
	
	//获取打折信息
	getSale:function(goodsType,callback){
		var sale = Shop.getSale(goodsType);
		if(sale)
			callback(sale);
		else {
			this.send( "sendDiscountInfo",function(sevData){
				Shop.setSaleOption(sevData.result);
				var saleInfo = Shop.getSale(goodsType);
				callback(saleInfo);
			});
		}
	}
}

