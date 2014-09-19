//
//  BS_JSBFun.cpp
//  pokoSanguo
//
//  Created by Shan Shikai on 4/11/14.
//
//

#include "BS_JSBFun.h"
#include "ScriptingCore.h"
#include "GameManager.h"

static BS::JSBFun *jsbFun = nullptr;

BS::JSBFun* BS::JSBFun::create()
{
    if(!jsbFun){
        jsbFun = new BS::JSBFun();
        if (jsbFun->init())
        {
            jsbFun->autorelease();
            return jsbFun;
        }
        else
        {
            delete jsbFun;
            jsbFun = NULL;
            return NULL;
        }
    }
    
    return jsbFun;
}

bool BS::JSBFun::init(){
    bool bRef = false;
    do{
        CCLOG("JSB init...");
        
        bRef = true;
    } while (0);
    
    return bRef;
}




void BS::JSBFun::js2c(const char *func,const char* param){
    CCLOG("js2c ... func:%s,args:%s",func,param);
    
    if(strcmp(func,"playOver") == 0){
        int score = std::atoi(param);
        char str[255];
        sprintf(str, "     基础分值:%d\r\n     属于一般水平！",score);
        deGameManager->gameOver(score, "", 0, str);
        return;
    }
}





std::string BS::JSBFun::JsNativefunc(const char *func,const char* param){
    
    CCLOG("command func %s,param :%s",func,param);
    ScriptingCore* sc = ScriptingCore::getInstance();
    JS::RootedValue nsval(sc->getGlobalContext());
    JS_GetProperty(sc->getGlobalContext(), sc->getGlobalObject(), "BS_JSB", &nsval);
    
    jsval retval;
    jsval v[] = {
        v[0] = std_string_to_jsval(sc->getGlobalContext(), func),
        v[1] = std_string_to_jsval(sc->getGlobalContext(), param)
    };
    
    if(nsval != JSVAL_VOID)
    {
        sc->executeFunctionWithOwner(nsval,"performC_command",2,v,&retval);
    }
    
    return "";
}
std::string BS::JSBFun::androidCom_interceptor(const char *func, const char *param){
     CCLOG("android command func %s,param :%s",func,param);
    if(strcmp(func, "updateJsc") == 0){

    }else{
        BS::JSBFun::create()->JsNativefunc(func, param);
    }

    return "";
}

