var MsgMgr = {
    msgTable: {},
    bindMsg: function (msg, msgObj) {
        msgObj = msgObj || arguments.callee.caller;
        if(msgObj.onClientMsg == undefined)
            throw new Error("["+msg+"] onClientMsg() is undefined");
        if( this.msgTable[msg] != null){ 
			if(this.msgTable[msg].indexOf(msgObj)<0)
            {
                if(this.msgTable[msg].length>0)
				    cc.log("[MsgMgr] '"+msg+"' is a shared msg");
                this.msgTable[msg].push(msgObj);
				cc.log("[MsgMgr] '"+msg+"' "+this.msgTable[msg].join(","));
			}
        }
        else {
            this.msgTable[msg] = [msgObj];
			cc.log("[MsgMgr]bindNewMsg: "+ msg +" obj: "+ msgObj.mID);
		}
    },
    postMsg:function(msg){
        if(this.msgTable[msg] == null){
            cc.log("[MsgMgr]没有对象注册此消息:" + msg);
            return;
        }
        var objs = this.msgTable[msg]
        for(i=0;i<objs.length;i++)
        {
            cc.log("PosMsg: '" + msg + "'to: " + objs[i].mID);
            objs[i].onClientMsg.apply(objs[i],arguments);
        }
    },
    unbindMsg:function(msg,msgObj){

        cc.log("[MsgMgr]unbindMsg: "+msg)
        if(msgObj == null) 
            this.msgTable[msg] = null
        else
        {
        	var objs = this.msgTable[msg]
			for (var i = 0; i < objs.length; i++) {
				if (objs[i] == msgObj) {
					objs.splice(i, 1);
					cc.log("[MsgMgr]MsgUnbind: "+msg+"-"+msgObj.mID);
					return;
				}
			}
		}
    },
	unbindObj:function(obj){
		for(var k in this.msgTable)
		{
			var objs = this.msgTable[k]
			if(objs.length>0)
			{
				for(var i=0;i<objs.length;i++)
				{
					cc.log("[MsgMgr]" + objs[i].mID);
					if(obj == objs[i])
					{
						objs.splice(i, 1);
						cc.log("[MsgMgr]ObjUnbind:"+obj.mID);
						break;
					}
				}
			}
		}
	}
}

