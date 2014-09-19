
var PARAM_SPLIT = "###"
var BS_JSB = {
}

/*
	这个方法为js调用c方法
	func为调用c方法的方法标识
	param为想c方法中调用需传递的参数以  *****多个参数用“###”拼接   例：jiecao#diaoL
*/
 BS_JSB.ToCFun = function(func,param){
    var JSB = new BS.BS_JSBFun()
    JSB.retain()
    JSB.js2c(func,param)
    JSB.release()
}

/*
	这个方法为c++回调js
	func为js分发调用方法标识
	param为向js方法中传递的参数  *****参数是以“###”拼接  使用时以#拆分得到每个参数
*/
BS_JSB.performC_command =  function(func,param){

	if(typeof(func) != "string" || typeof(param) != "string") return

	log("JSB performC_command:" + func +"：" + param)

	var args = param.split(PARAM_SPLIT)

	//处理分发c++ 回调
	if(func == "startGame developer"){//测试
		for(i = 0;i < args.length;i++){
			cc.log(args[i]+";")
		}

	}else if(func === "CloseAPP"){
		cc.director.end()
		throw "退出"
	}else if(func == "playGame"){
        SceneMgr.showScene("mainScene");
    } else {
        eval(func).apply(null, args);
    }
    
}
