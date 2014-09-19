//
//  JSB_AUTO.cpp
//  pokoSanguo
//
//  Created by Shan Shikai on 4/11/14.
//
//

#include "JSB_AUTO.hpp"
#include "cocos2d_specifics.hpp"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include <iostream>
#include "BS_JSBFun.h"

// Binding specific object
JSClass*        jsb_class;
JSObject*       jsb_prototype;


bool js_js2c(JSContext* cx, uint32_t argc, jsval* vp){
    
    
    jsval *argv = JS_ARGV(cx, vp);
    
    bool ok = true;
    JSObject* obj = NULL;
    BS::JSBFun* cobj = NULL;
    obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t* proxy = jsb_get_js_proxy(obj);
    cobj = (BS::JSBFun* )(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2(cobj, cx, false, "Invalid Native Object");
    
    if (argc == 2) {
        std::string arg0_tmp;
        ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp);
        
        std::string arg1_tmp;
        ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp);
        
        cobj->js2c(arg0_tmp.c_str(),arg1_tmp.c_str());
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return ok;
    }
    JS_ReportError(cx, "参 数 无 效");
    return false;
}

bool js_constructor(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JS Constructor...");
    if (argc == 0) {
        BS::JSBFun* cobj = new BS::JSBFun();
        
        cocos2d::Ref* ccobj = dynamic_cast<cocos2d::Ref*>(cobj);
        
        if (ccobj) {
            ccobj->autorelease();
        }
        TypeTest<BS::JSBFun> t;
        js_type_class_t* typeClass;
        std::string typeName = t.s_name();
        auto typeMapIt = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIt != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIt->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
        
        js_proxy_t* p = jsb_new_proxy(cobj, obj);
        JS_AddNamedObjectRoot(cx, &p->obj, "BS::JSBFun");
        
        return true;
    }
    
    JS_ReportError(cx, "参 数 无 效");
    
    return false;
}

bool js_create(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("js is creating...");
    if (argc == 0) {
        BS::JSBFun* ret = BS::JSBFun::create();
        jsval jsret;
        do{
            if (ret) {
                js_proxy_t* proxy = js_get_or_create_proxy<BS::JSBFun>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            }
            else{
                jsret = JSVAL_NULL;
            }
        } while(0);
        JS_SET_RVAL(cx, vp, jsret);
        
        return false;
    }
    
    JS_ReportError(cx, "参 数 无 效");
    
    return false;
}

void js_finalize(JSFreeOp* fop, JSObject* obj){
    CCLOGINFO("JSBindings: finallizing JS object %p BS", obj);
}

void js_register(JSContext* cx, JSObject* global){
    jsb_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_class->name = "BS_JSBFun";
    jsb_class->addProperty = JS_PropertyStub;
    jsb_class->delProperty = JS_DeletePropertyStub;
    jsb_class->getProperty = JS_PropertyStub;
    jsb_class->setProperty = JS_StrictPropertyStub;
    jsb_class->enumerate = JS_EnumerateStub;
    jsb_class->resolve = JS_ResolveStub;
    jsb_class->convert = JS_ConvertStub;
    jsb_class->finalize = js_finalize;
    jsb_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };
    
    // 绑定js2c方法
    static JSFunctionSpec funcs[] = {
        JS_FN("js2c", js_js2c, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    // 绑定create方法
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    jsb_prototype = JS_InitClass(
                                 cx, global,
                                 NULL,
                                 jsb_class,
                                 js_constructor, 0,
                                 properties,
                                 funcs,
                                 NULL,
                                 st_funcs);
    
    TypeTest<BS::JSBFun> t;
    js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
        p = (js_type_class_t* )malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_class;
        p->proto = jsb_prototype;
        p->parentProto = NULL;
       _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

bool JSB_cocos2dx_retain(JSContext* cx, uint32_t argc, jsval *vp){
    JSObject* thisObj = JS_THIS_OBJECT(cx, vp);
    
    if (thisObj) {
        js_proxy_t* proxy = jsb_get_js_proxy(thisObj);
        
        if (proxy) {
            ((cocos2d::Ref* )proxy->ptr)->retain();
            CCLOG("Retain succeed!");
            return true;
        }
    }
    
    JS_ReportError(cx, "Invaild native object");
    return false;
}

bool JSB_cocos2dx_release(JSContext* cx, uint32_t argc, jsval *vp){
    JSObject* thisObj = JS_THIS_OBJECT(cx, vp);
    
    if (thisObj) {
        js_proxy_t* proxy = jsb_get_js_proxy(thisObj);
        
        if (proxy) {
            ((cocos2d::Ref* )proxy->ptr)->release();
            CCLOG("Release succeed!");
            return true;
        }
    }
    
    JS_ReportError(cx, "Invaild native object");
    return false;
}

void register_all(JSContext* cx, JSObject* obj){
    
    JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "BS", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "BS", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;
    js_register(cx, obj);
    
    JS_DefineFunction(cx, jsb_prototype, "retain", JSB_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_prototype, "release", JSB_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
