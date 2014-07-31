function Clone(obj)
{
	return JSON.parse(JSON.stringify(obj));
}

function Rand(min,max)
{
    var rand = Math.random()*(max-min)+min;
    cc.log("rand:"+rand);
	return parseInt(rand);
}

function StringWithFormat(str)
{
    var result = str;
    for (var i=1; i < arguments.length; i++) {
        result = result.replace("@"+i, arguments[i]);
    }
    return result;
}

function AutoEnter(label ,maxSize,oldStr/*=null*/)
{
	var isTTF = label.setString != undefined;
	
	var w = maxSize.width||maxSize;
	var h = maxSize.height;
	this.setString = function(str){
		isTTF?label.setString(str):label.setText(str);
	}
	this.getString = function(){
		return isTTF?label.getString():label.getStringValue();
	}
	this.getContentSize = function(){
		return isTTF?label.getContentSize():label.getContentSize();
	}
	if(!oldStr){
		oldStr = this.getString();
	}
	else {
		this.setString(oldStr);
	}
	var conSize = this.getContentSize();
	if(conSize.width <= w) 
	{
		return oldStr;
	}
    var testStr = "";
    var idx = 0;
    var size = cc.size(0,0);
	
    while(idx < oldStr.length) {
		char = oldStr.substr(idx,1);
		this.setString(char);
       	conSize = this.getContentSize();
        size.width += conSize.width;
		
        if(size.width > w){ 
        	testStr = testStr + char + "\n";
			if(h){
				size.height += conSize.height;
				if(size.height > h)
				{
					testStr += "...";
					break;
				}
			}
        	size.width = 0;
		}
        else 
        	testStr = testStr + char;
		idx++;
	}
	this.setString(testStr);
	cc.log("AutoEnter:\n"+testStr);
    return testStr;
}

function Rand(min,max)
{
	return Math.random()*(max-min)+min;
}

function StringJoinComma(v)
{
	var str = v+"";
	var strList = str.split("").reverse();
	var l = strList.length;
	var result = "";
	for(var i = 0;i<l;i++){
		if(i>0&&i%3==0){
			result = ","+result;
		}
		result = strList[i] + result;
	}
	return result;
}

function ShowMsg(msg,opt)
{	
	var parent = opt&&opt.parent
	var pos = cc.p(0,0);
	
	if(opt&&opt.pos) pos = opt.pos;	
	else if(!parent){
		parent = cc.director.getRunningScene();
		var vsize  = cc.director.getVisibleSize();
		pos = cc.p(vsize.width/2,vsize.height/2);
	}
	
	var col    = opt&&opt.color||cc.color.RED;
	var fsize  = opt&&opt.size||32;
	
	var lbl = cc.LabelTTF.create(msg,FONT_TYPE,fsize);
	if(parent.addNode) 
		parent.addNode(lbl,10000);
	else
		parent.addChild(lbl,10000);
	lbl.setPosition(pos);
	lbl.setColor(col);
	
	var acts = [cc.DelayTime.create(0.3),cc.Spawn.create([cc.MoveTo.create(0.5,cc.p(pos.x,pos.y+80)),cc.FadeOut.create(0.5)]),cc.RemoveSelf.create()];
	lbl.runAction(cc.Sequence.create(acts));
}

function DeltaTimeString(endTime)
{
    var localTime = GetCurrentSecondsTime();
    var deltaTime = endTime - localTime;
    var days = Math.floor(deltaTime / 86400);
    var hours = Math.floor(deltaTime % 86400 / 3600);
    var minutes = Math.floor(deltaTime % 3600 / 60);
    var seconds = Math.floor(deltaTime % 60);
    //cc.log(days + "d:" + hours + "h:" + minutes + "m:" + seconds + "s");

    if (deltaTime < 5 * 60) {
        return "< 5m";
    }
    if (days > 0) {
        return days + "d:" + hours + "h";
    } else if (hours > 0) {
        return hours + "h:" + minutes + "m";
    } else if (minutes > 0) {
        return minutes + "m:" + seconds + "s";
    } else {
        return seconds + "s";
    }
}

function GetCurrentSecondsTime()
{
    return Math.floor(new Date().getTime() / 1000);
}

function DeltaTimeToChString(deltaTime) {
    //var days = Math.floor(deltaTime / 86400);
    var hours = Math.floor(deltaTime / 3600);
    var minutes = Math.floor(deltaTime % 3600 / 60);
    var seconds = Math.floor(deltaTime % 60);
    var result = "";
//    if (days > 0) {
//        result += days + "天";
//    }
    if (hours > 0) {
        result += hours + "小时";
    }
    if (minutes > 0) {
        result += minutes + "分钟";
    }
    result += seconds + "秒";
    return result;
}
//Date必须为new Date()对象
//format为  yyyy-MM-dd hh:mm:ss 或则  自定义
function DateFormat(dateTime,format){ 
    format = format || "yyyy-MM-dd hh:mm:ss"
    var o = { 
        "M+" : dateTime.getMonth()+1, //月 
        "d+" : dateTime.getDate(), //天
        "h+" : dateTime.getHours(), //小时 
        "m+" : dateTime.getMinutes(), //分 
        "s+" : dateTime.getSeconds(), //秒 
        "q+" : Math.floor((dateTime.getMonth()+3)/3), //quarter 
        "S" : dateTime.getMilliseconds() //millisecond 
    } 

    if(/(y+)/.test(format)) { 
        format = format.replace(RegExp.$1, (dateTime.getFullYear()+"").substr(4 - RegExp.$1.length)); 
    } 

    for(var k in o) { 
        if(new RegExp("("+ k +")").test(format)) { 
            format = format.replace(RegExp.$1, RegExp.$1.length==1 ? o[k] : ("00"+ o[k]).substr((""+ o[k]).length)); 
        } 
    } 
    return format; 
} 

var BS_SELF_REMOVE = function(node){
    try{
        if(node != undefined && node.getParent() != undefined){
            node.getParent().removeChild(node,true)
            node = null
            cc.log("#  REMOVE SUCCESS #");
        }
    }catch(e){
        cc.log("#  REMOVE FAIL #");
    }
}
 
//公共方法刷新武将星级的显示
var REFERSH_GRLSTARBAR = function(bar_pan,star,isCenter){
    if(isCenter == undefined) isCenter = true

    bar_pan.removeAllNodes()
    star = star >= 10 ? 10 : star;
    var starWidth = cc.Sprite.createWithSpriteFrameName("img_xingkuang.png").getContentSize().width
    var contentSize = bar_pan.getContentSize()

    var newStar = parseInt( star/2 )
    var lastStarIndex = -1
    if(star % 2 != 0){
        lastStarIndex = newStar
        newStar += 1 
    }

    var begPosX = starWidth/2;


    cc.log("begPosX:"+begPosX)
    if(isCenter){
        begPosX = contentSize.width/2 - starWidth/2 *(newStar - 1)
    }
    

    for(var i = 0;i<newStar;i++){
        var imgPath = "img_xing.png"
        if(i == lastStarIndex){
            imgPath = "img_xingkuang.png"
        }
        var starSprite = cc.Sprite.createWithSpriteFrameName(imgPath)
        starSprite.setPosition(cc.p(begPosX+starWidth*i,contentSize.height/2))
        bar_pan.addNode(starSprite)
    }
}

function GetWinSize() {
    return cc.director.getVisibleSize();
}
var GeneralSortFun = function(a,b){
    if(a.getDataValue("quality") != b.getDataValue("quality")){
            return a.getDataValue("quality") < b.getDataValue("quality") ? 1 : -1
    }else {
        if(a.getUpdateATK() != b.getUpdateATK()){ 
            return a.getUpdateATK() < b.getUpdateATK() ? 1 : -1
        }else{
            if(a.get("star") != b.get("star")){
                return a.get("star") < b.get("star") ? 1 : -1
            }else{
                if(a.get("level") != b.get("level")){
                    return a.get("level")<b.get("level") ? 1 : -1
                }else{
                    if(a.get("typeID") != b.get("typeID")){
                        return a.get("typeID") < b.get("typeID") ? 1 : -1           
                    }
                }
            }
        }                          
    }        
    return -1
}

function FindNodeChild(findNode, name) {
    var spl = name.split('/');
    for(var i=0;i<spl.length;i++)
    {
        findNode = findNode.getChildByName(spl[i]);
        
        if(findNode == null)
        {
            cc.log("[Error] Node not find " + spl[i]);
            return null;
        }
    }
    return findNode;
}

function LockScreen(isLock,who)
{
	AppCtrl.lockScreen(isLock,who);
}

function GetItemName(itemId) {
    if (itemId === exports.configs.gold_ID.value) {
        return GetText(70014);
    } else if (itemId === exports.configs.dimond_ID.value) {
        return GetText(70013);
    } else {
        return exports.items[itemId].name;
    }
}

function GetText(textId) {
    var text = DataMgr.getData("texts",textId)["text"];
    if (arguments.length <= 1) return text;
    var args = [];
    for (var i=0; i < arguments.length; i++) {
        args.push(arguments[i]);
    }
    args.splice(0, 1, text);
    return StringWithFormat.apply(text, args);
}

//给当前label 赋值 附带动画 func每次数字变动都调用 参数是否结束 
function SetLabelStringWithAnimation(label,number,hasComma,preStr,callback){
    if(!label) return;

    if (!preStr) preStr = "";
    var setStringFunc;
    var getStringFunc;

    if(label instanceof ccui.Text){
        setStringFunc = label.setText;
        getStringFunc = label.getStringValue;
    }else if(label instanceof ccui.TextAtlas){
        setStringFunc = label.setStringValue;
        getStringFunc = label.getStringValue;
    }else if(label instanceof ccui.TextBMFont){
        setStringFunc = label.setText;
        getStringFunc = label.getStringValue;
    }else if(label instanceof cc.LabelTTF){
        setStringFunc = label.setString;
        getStringFunc = label.getString;
    }

    var str = number+"";
    var targetNumber = str.split(",").join("");

    var currentStr = getStringFunc.call(label);
    if(!currentStr){
        currentStr = "";
    } else {
        currentStr = currentStr.substr(preStr.length);
    }
    var currentNumber = currentStr.split(",").join("");
    if (!Number(currentNumber)){
        currentNumber = 0;
    }else{
        currentNumber = parseInt(currentNumber);
    }

    var gap = parseInt(targetNumber) - parseInt(currentNumber);

    if(gap==0){
        if(callback){
            callback(true);
        }
        return;
    }else{
        if(callback){
            callback(false);
        }
    }

    var labelString = currentNumber+Math.floor(gap/2);
    if(Math.abs(labelString-number)<=1){
        labelString = number;
    }

    if(hasComma){
        labelString = StringJoinComma(labelString);
    }
    setStringFunc.call(label,preStr+labelString);

    label.stopActionByTag(10000);

    var act = cc.Sequence.create(cc.DelayTime.create(0.05),cc.CallFunc.create(function(node){
        SetLabelStringWithAnimation(this,number,hasComma,preStr,callback);
    },label));
    act.setTag(10000);

    label.runAction(act);
	
}

function GetNodeFindStr(node){
	var names = [node.getName()];
	var parent = node.getParent();
	while(parent){
		if(!parent.getName) break;
		names.unshift(parent.getName());
		parent = parent.getParent();
	}
	cc.log("[FindName] "+names.join("/"));
}

function UsedBMLanbelVerticalStr(str){

    var verStr = "";
    var strLength = str.length;
    for(var i =0;i<strLength;i++){
        verStr += str.substring(i,i+1)

        if(i<(strLength-1)){
            verStr += '\n';
        }
    }

    return verStr;
}


function ObjToString(obj){
    //return "";
    return JSON.stringify(obj);
}
//获取武将或者怪物的骨骼
function GetGeneralNode(autoPlay){
    autoPlay = autoPlay==undefined ? true:autoPlay;
    
//    var info = exports.generals[typeID];
//    if(!info){
//        info = exports.monsters[typeID];
//    }
    var icon = "";
    //临时用的
//	var tempList = ResourceMgr.generalBoneList;
    icon = res.Wujiang_diaochan_Json;
    
    ccs.armatureDataManager.addArmatureFileInfo(res.Wujiang_diaochan_Json);
    
    var armature = ccs.Armature.create("wujiang_diaochan");
    if(autoPlay){
        armature.getAnimation().playWithIndex(0);
    }
    return armature;
}



