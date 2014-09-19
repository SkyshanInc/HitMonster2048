#include "TowerJsb_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "TowerJsb.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return true;
	}

    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;	
}
JSClass  *jsb_EnemyBase_class;
JSObject *jsb_EnemyBase_prototype;

bool js_JsbTower_EnemyBase_decelerate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_decelerate : Invalid Native Object");
	if (argc == 0) {
		cobj->decelerate();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_decelerate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_setHpPercentage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setHpPercentage : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setHpPercentage : Error processing arguments");
		cobj->setHpPercentage(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setHpPercentage : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_setRunSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setRunSpeed : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setRunSpeed : Error processing arguments");
		cobj->setRunSpeed(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setRunSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_setEnemySuccessful(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setEnemySuccessful : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setEnemySuccessful : Error processing arguments");
		cobj->setEnemySuccessful(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setEnemySuccessful : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_setVaule(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setVaule : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setVaule : Error processing arguments");
		cobj->setVaule(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setVaule : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_getVaule(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getVaule : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getVaule();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getVaule : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_getRunSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getRunSpeed : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getRunSpeed();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getRunSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_createAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_createAnimation : Invalid Native Object");
	if (argc == 3) {
		std::string arg0;
		int arg1;
		double arg2;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_createAnimation : Error processing arguments");
		cocos2d::Animation* ret = cobj->createAnimation(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Animation>(cx, (cocos2d::Animation*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_createAnimation : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_JsbTower_EnemyBase_setPointsVector(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setPointsVector : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Vector<cocos2d::Node *> arg0;
		ok &= jsval_to_ccvector(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setPointsVector : Error processing arguments");
		cobj->setPointsVector(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setPointsVector : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_createAndSetHpBar(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_createAndSetHpBar : Invalid Native Object");
	if (argc == 0) {
		cobj->createAndSetHpBar();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_createAndSetHpBar : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_setCurrHp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setCurrHp : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setCurrHp : Error processing arguments");
		cobj->setCurrHp(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setCurrHp : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_enemyExpload(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_enemyExpload : Invalid Native Object");
	if (argc == 0) {
		cobj->enemyExpload();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_enemyExpload : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_getMaxHp(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getMaxHp : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getMaxHp();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getMaxHp : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_runFllowPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_runFllowPoint : Invalid Native Object");
	if (argc == 0) {
		cobj->runFllowPoint();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_runFllowPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_setMaxHp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_setMaxHp : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_setMaxHp : Error processing arguments");
		cobj->setMaxHp(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_setMaxHp : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_changeDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_changeDirection : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_EnemyBase_changeDirection : Error processing arguments");
		cobj->changeDirection(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_changeDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_EnemyBase_getEnemySuccessful(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getEnemySuccessful : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->getEnemySuccessful();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getEnemySuccessful : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_getHpPercentage(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getHpPercentage : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getHpPercentage();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getHpPercentage : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_currPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_currPoint : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Node* ret = cobj->currPoint();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_currPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_getCurrHp(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getCurrHp : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getCurrHp();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getCurrHp : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_getHpBar(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getHpBar : Invalid Native Object");
	if (argc == 0) {
		cocos2d::ProgressTimer* ret = cobj->getHpBar();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ProgressTimer>(cx, (cocos2d::ProgressTimer*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getHpBar : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_nextPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_nextPoint : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Node* ret = cobj->nextPoint();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_nextPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_getPointCounter(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EnemyBase* cobj = (EnemyBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_EnemyBase_getPointCounter : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getPointCounter();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_EnemyBase_getPointCounter : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_EnemyBase_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		EnemyBase* ret = EnemyBase::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<EnemyBase>(cx, (EnemyBase*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_EnemyBase_create : wrong number of arguments");
	return false;
}

bool js_JsbTower_EnemyBase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    EnemyBase* cobj = new EnemyBase();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<EnemyBase> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "EnemyBase");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_EnemyBase_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EnemyBase)", obj);
}

void js_register_JsbTower_EnemyBase(JSContext *cx, JSObject *global) {
	jsb_EnemyBase_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_EnemyBase_class->name = "EnemyBase";
	jsb_EnemyBase_class->addProperty = JS_PropertyStub;
	jsb_EnemyBase_class->delProperty = JS_DeletePropertyStub;
	jsb_EnemyBase_class->getProperty = JS_PropertyStub;
	jsb_EnemyBase_class->setProperty = JS_StrictPropertyStub;
	jsb_EnemyBase_class->enumerate = JS_EnumerateStub;
	jsb_EnemyBase_class->resolve = JS_ResolveStub;
	jsb_EnemyBase_class->convert = JS_ConvertStub;
	jsb_EnemyBase_class->finalize = js_EnemyBase_finalize;
	jsb_EnemyBase_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("decelerate", js_JsbTower_EnemyBase_decelerate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setHpPercentage", js_JsbTower_EnemyBase_setHpPercentage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRunSpeed", js_JsbTower_EnemyBase_setRunSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setEnemySuccessful", js_JsbTower_EnemyBase_setEnemySuccessful, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVaule", js_JsbTower_EnemyBase_setVaule, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVaule", js_JsbTower_EnemyBase_getVaule, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRunSpeed", js_JsbTower_EnemyBase_getRunSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createAnimation", js_JsbTower_EnemyBase_createAnimation, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPointsVector", js_JsbTower_EnemyBase_setPointsVector, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createAndSetHpBar", js_JsbTower_EnemyBase_createAndSetHpBar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurrHp", js_JsbTower_EnemyBase_setCurrHp, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("enemyExpload", js_JsbTower_EnemyBase_enemyExpload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMaxHp", js_JsbTower_EnemyBase_getMaxHp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("runFllowPoint", js_JsbTower_EnemyBase_runFllowPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMaxHp", js_JsbTower_EnemyBase_setMaxHp, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("changeDirection", js_JsbTower_EnemyBase_changeDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getEnemySuccessful", js_JsbTower_EnemyBase_getEnemySuccessful, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getHpPercentage", js_JsbTower_EnemyBase_getHpPercentage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("currPoint", js_JsbTower_EnemyBase_currPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrHp", js_JsbTower_EnemyBase_getCurrHp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getHpBar", js_JsbTower_EnemyBase_getHpBar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("nextPoint", js_JsbTower_EnemyBase_nextPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPointCounter", js_JsbTower_EnemyBase_getPointCounter, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_EnemyBase_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_EnemyBase_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Sprite_prototype,
		jsb_EnemyBase_class,
		js_JsbTower_EnemyBase_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "EnemyBase", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<EnemyBase> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_EnemyBase_class;
		p->proto = jsb_EnemyBase_prototype;
		p->parentProto = jsb_cocos2d_Sprite_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_TowerBase_class;
JSObject *jsb_TowerBase_prototype;

bool js_JsbTower_TowerBase_getScope(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_getScope : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getScope();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_getScope : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerBase_checkNearestEnemy(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_checkNearestEnemy : Invalid Native Object");
	if (argc == 0) {
		cobj->checkNearestEnemy();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_checkNearestEnemy : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerBase_getTowerValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_getTowerValue : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getTowerValue();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_getTowerValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerBase_setLethality(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_setLethality : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerBase_setLethality : Error processing arguments");
		cobj->setLethality(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_setLethality : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_TowerBase_getLethality(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_getLethality : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getLethality();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_getLethality : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerBase_getRate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_getRate : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getRate();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_getRate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerBase_setRate(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_setRate : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerBase_setRate : Error processing arguments");
		cobj->setRate(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_setRate : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_TowerBase_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerBase_setScope(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_setScope : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerBase_setScope : Error processing arguments");
		cobj->setScope(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_setScope : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_TowerBase_setTowerValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerBase* cobj = (TowerBase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerBase_setTowerValue : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerBase_setTowerValue : Error processing arguments");
		cobj->setTowerValue(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerBase_setTowerValue : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_TowerBase_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		TowerBase* ret = TowerBase::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<TowerBase>(cx, (TowerBase*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_TowerBase_create : wrong number of arguments");
	return false;
}

bool js_JsbTower_TowerBase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    TowerBase* cobj = new TowerBase();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<TowerBase> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "TowerBase");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_TowerBase_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TowerBase)", obj);
}

void js_register_JsbTower_TowerBase(JSContext *cx, JSObject *global) {
	jsb_TowerBase_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_TowerBase_class->name = "TowerBase";
	jsb_TowerBase_class->addProperty = JS_PropertyStub;
	jsb_TowerBase_class->delProperty = JS_DeletePropertyStub;
	jsb_TowerBase_class->getProperty = JS_PropertyStub;
	jsb_TowerBase_class->setProperty = JS_StrictPropertyStub;
	jsb_TowerBase_class->enumerate = JS_EnumerateStub;
	jsb_TowerBase_class->resolve = JS_ResolveStub;
	jsb_TowerBase_class->convert = JS_ConvertStub;
	jsb_TowerBase_class->finalize = js_TowerBase_finalize;
	jsb_TowerBase_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getScope", js_JsbTower_TowerBase_getScope, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("checkNearestEnemy", js_JsbTower_TowerBase_checkNearestEnemy, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTowerValue", js_JsbTower_TowerBase_getTowerValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setLethality", js_JsbTower_TowerBase_setLethality, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLethality", js_JsbTower_TowerBase_getLethality, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRate", js_JsbTower_TowerBase_getRate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRate", js_JsbTower_TowerBase_setRate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_TowerBase_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setScope", js_JsbTower_TowerBase_setScope, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTowerValue", js_JsbTower_TowerBase_setTowerValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_TowerBase_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_TowerBase_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Sprite_prototype,
		jsb_TowerBase_class,
		js_JsbTower_TowerBase_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "TowerBase", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<TowerBase> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_TowerBase_class;
		p->proto = jsb_TowerBase_prototype;
		p->parentProto = jsb_cocos2d_Sprite_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_ArrowTower_class;
JSObject *jsb_ArrowTower_prototype;

bool js_JsbTower_ArrowTower_shoot(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ArrowTower* cobj = (ArrowTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ArrowTower_shoot : Invalid Native Object");
	if (argc == 0) {
		cobj->shoot();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ArrowTower_shoot : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_ArrowTower_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ArrowTower* cobj = (ArrowTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ArrowTower_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ArrowTower_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_ArrowTower_rotateAndShoot(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ArrowTower* cobj = (ArrowTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ArrowTower_rotateAndShoot : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_ArrowTower_rotateAndShoot : Error processing arguments");
		cobj->rotateAndShoot(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ArrowTower_rotateAndShoot : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_ArrowTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ArrowTower* cobj = (ArrowTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ArrowTower_removeBullet : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_ArrowTower_removeBullet : Error processing arguments");
		cobj->removeBullet(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ArrowTower_removeBullet : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_ArrowTower_ArrowTowerBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ArrowTower* cobj = (ArrowTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ArrowTower_ArrowTowerBullet : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Sprite* ret = cobj->ArrowTowerBullet();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ArrowTower_ArrowTowerBullet : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_ArrowTower_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		ArrowTower* ret = ArrowTower::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<ArrowTower>(cx, (ArrowTower*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_ArrowTower_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_TowerBase_prototype;

void js_ArrowTower_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ArrowTower)", obj);
}

void js_register_JsbTower_ArrowTower(JSContext *cx, JSObject *global) {
	jsb_ArrowTower_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ArrowTower_class->name = "ArrowTower";
	jsb_ArrowTower_class->addProperty = JS_PropertyStub;
	jsb_ArrowTower_class->delProperty = JS_DeletePropertyStub;
	jsb_ArrowTower_class->getProperty = JS_PropertyStub;
	jsb_ArrowTower_class->setProperty = JS_StrictPropertyStub;
	jsb_ArrowTower_class->enumerate = JS_EnumerateStub;
	jsb_ArrowTower_class->resolve = JS_ResolveStub;
	jsb_ArrowTower_class->convert = JS_ConvertStub;
	jsb_ArrowTower_class->finalize = js_ArrowTower_finalize;
	jsb_ArrowTower_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("shoot", js_JsbTower_ArrowTower_shoot, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_ArrowTower_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("rotateAndShoot", js_JsbTower_ArrowTower_rotateAndShoot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeBullet", js_JsbTower_ArrowTower_removeBullet, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ArrowTowerBullet", js_JsbTower_ArrowTower_ArrowTowerBullet, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_ArrowTower_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_ArrowTower_prototype = JS_InitClass(
		cx, global,
		jsb_TowerBase_prototype,
		jsb_ArrowTower_class,
		dummy_constructor<ArrowTower>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ArrowTower", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<ArrowTower> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_ArrowTower_class;
		p->proto = jsb_ArrowTower_prototype;
		p->parentProto = jsb_TowerBase_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_DecelerateTower_class;
JSObject *jsb_DecelerateTower_prototype;

bool js_JsbTower_DecelerateTower_shoot(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	DecelerateTower* cobj = (DecelerateTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_DecelerateTower_shoot : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_DecelerateTower_shoot : Error processing arguments");
		cobj->shoot(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_DecelerateTower_shoot : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_DecelerateTower_DecelerateTowerBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	DecelerateTower* cobj = (DecelerateTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_DecelerateTower_DecelerateTowerBullet : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Sprite* ret = cobj->DecelerateTowerBullet();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_DecelerateTower_DecelerateTowerBullet : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_DecelerateTower_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	DecelerateTower* cobj = (DecelerateTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_DecelerateTower_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_DecelerateTower_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_DecelerateTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	DecelerateTower* cobj = (DecelerateTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_DecelerateTower_removeBullet : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_DecelerateTower_removeBullet : Error processing arguments");
		cobj->removeBullet(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_DecelerateTower_removeBullet : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_DecelerateTower_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		DecelerateTower* ret = DecelerateTower::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<DecelerateTower>(cx, (DecelerateTower*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_DecelerateTower_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_TowerBase_prototype;

void js_DecelerateTower_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DecelerateTower)", obj);
}

void js_register_JsbTower_DecelerateTower(JSContext *cx, JSObject *global) {
	jsb_DecelerateTower_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_DecelerateTower_class->name = "DecelerateTower";
	jsb_DecelerateTower_class->addProperty = JS_PropertyStub;
	jsb_DecelerateTower_class->delProperty = JS_DeletePropertyStub;
	jsb_DecelerateTower_class->getProperty = JS_PropertyStub;
	jsb_DecelerateTower_class->setProperty = JS_StrictPropertyStub;
	jsb_DecelerateTower_class->enumerate = JS_EnumerateStub;
	jsb_DecelerateTower_class->resolve = JS_ResolveStub;
	jsb_DecelerateTower_class->convert = JS_ConvertStub;
	jsb_DecelerateTower_class->finalize = js_DecelerateTower_finalize;
	jsb_DecelerateTower_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("shoot", js_JsbTower_DecelerateTower_shoot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("DecelerateTowerBullet", js_JsbTower_DecelerateTower_DecelerateTowerBullet, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_DecelerateTower_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeBullet", js_JsbTower_DecelerateTower_removeBullet, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_DecelerateTower_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_DecelerateTower_prototype = JS_InitClass(
		cx, global,
		jsb_TowerBase_prototype,
		jsb_DecelerateTower_class,
		dummy_constructor<DecelerateTower>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "DecelerateTower", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<DecelerateTower> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_DecelerateTower_class;
		p->proto = jsb_DecelerateTower_prototype;
		p->parentProto = jsb_TowerBase_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_ElectricityTower_class;
JSObject *jsb_ElectricityTower_prototype;

bool js_JsbTower_ElectricityTower_shoot(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ElectricityTower* cobj = (ElectricityTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ElectricityTower_shoot : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_ElectricityTower_shoot : Error processing arguments");
		cobj->shoot(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ElectricityTower_shoot : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_ElectricityTower_ElectricityTowerBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ElectricityTower* cobj = (ElectricityTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ElectricityTower_ElectricityTowerBullet : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Sprite* ret = cobj->ElectricityTowerBullet();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ElectricityTower_ElectricityTowerBullet : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_ElectricityTower_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ElectricityTower* cobj = (ElectricityTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ElectricityTower_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ElectricityTower_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_ElectricityTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ElectricityTower* cobj = (ElectricityTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_ElectricityTower_removeBullet : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_ElectricityTower_removeBullet : Error processing arguments");
		cobj->removeBullet(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_ElectricityTower_removeBullet : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_ElectricityTower_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		ElectricityTower* ret = ElectricityTower::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<ElectricityTower>(cx, (ElectricityTower*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_ElectricityTower_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_TowerBase_prototype;

void js_ElectricityTower_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ElectricityTower)", obj);
}

void js_register_JsbTower_ElectricityTower(JSContext *cx, JSObject *global) {
	jsb_ElectricityTower_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ElectricityTower_class->name = "ElectricityTower";
	jsb_ElectricityTower_class->addProperty = JS_PropertyStub;
	jsb_ElectricityTower_class->delProperty = JS_DeletePropertyStub;
	jsb_ElectricityTower_class->getProperty = JS_PropertyStub;
	jsb_ElectricityTower_class->setProperty = JS_StrictPropertyStub;
	jsb_ElectricityTower_class->enumerate = JS_EnumerateStub;
	jsb_ElectricityTower_class->resolve = JS_ResolveStub;
	jsb_ElectricityTower_class->convert = JS_ConvertStub;
	jsb_ElectricityTower_class->finalize = js_ElectricityTower_finalize;
	jsb_ElectricityTower_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("shoot", js_JsbTower_ElectricityTower_shoot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ElectricityTowerBullet", js_JsbTower_ElectricityTower_ElectricityTowerBullet, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_ElectricityTower_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeBullet", js_JsbTower_ElectricityTower_removeBullet, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_ElectricityTower_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_ElectricityTower_prototype = JS_InitClass(
		cx, global,
		jsb_TowerBase_prototype,
		jsb_ElectricityTower_class,
		dummy_constructor<ElectricityTower>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ElectricityTower", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<ElectricityTower> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_ElectricityTower_class;
		p->proto = jsb_ElectricityTower_prototype;
		p->parentProto = jsb_TowerBase_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_GroupEnemy_class;
JSObject *jsb_GroupEnemy_prototype;

bool js_JsbTower_GroupEnemy_getEnemyTotal(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getEnemyTotal : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getEnemyTotal();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getEnemyTotal : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_getCurrEnemyNum(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getCurrEnemyNum : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getCurrEnemyNum();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getCurrEnemyNum : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_setType2Hp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setType2Hp : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setType2Hp : Error processing arguments");
		cobj->setType2Hp(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setType2Hp : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_getType2Total(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getType2Total : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getType2Total();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getType2Total : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_getRate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getRate : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getRate();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getRate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_setType1Hp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setType1Hp : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setType1Hp : Error processing arguments");
		cobj->setType1Hp(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setType1Hp : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_setType1Total(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setType1Total : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setType1Total : Error processing arguments");
		cobj->setType1Total(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setType1Total : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_setType3Total(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setType3Total : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setType3Total : Error processing arguments");
		cobj->setType3Total(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setType3Total : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_getType3Hp(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getType3Hp : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getType3Hp();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getType3Hp : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_setIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setIsFinishedAddGroup : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setIsFinishedAddGroup : Error processing arguments");
		cobj->setIsFinishedAddGroup(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setIsFinishedAddGroup : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_getType3Total(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getType3Total : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getType3Total();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getType3Total : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_menuCloseCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_menuCloseCallback : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Ref* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_menuCloseCallback : Error processing arguments");
		cobj->menuCloseCallback(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_menuCloseCallback : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_getType2Hp(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getType2Hp : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getType2Hp();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getType2Hp : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_getIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getIsFinishedAddGroup : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->getIsFinishedAddGroup();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getIsFinishedAddGroup : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_initGroupEnemy(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_initGroupEnemy : Invalid Native Object");
	if (argc == 7) {
		int arg0;
		int arg1;
		int arg2;
		int arg3;
		int arg4;
		int arg5;
		double arg6;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
		ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
		ok &= jsval_to_int32(cx, argv[4], (int32_t *)&arg4);
		ok &= jsval_to_int32(cx, argv[5], (int32_t *)&arg5);
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[6]), &arg6);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_initGroupEnemy : Error processing arguments");
		GroupEnemy* ret = cobj->initGroupEnemy(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<GroupEnemy>(cx, (GroupEnemy*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_initGroupEnemy : wrong number of arguments: %d, was expecting %d", argc, 7);
	return false;
}
bool js_JsbTower_GroupEnemy_setType2Total(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setType2Total : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setType2Total : Error processing arguments");
		cobj->setType2Total(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setType2Total : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_getType1Total(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getType1Total : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getType1Total();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getType1Total : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_setEnemyTotal(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setEnemyTotal : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setEnemyTotal : Error processing arguments");
		cobj->setEnemyTotal(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setEnemyTotal : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_setType3Hp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setType3Hp : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setType3Hp : Error processing arguments");
		cobj->setType3Hp(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setType3Hp : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_setCurrEnemyNum(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setCurrEnemyNum : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setCurrEnemyNum : Error processing arguments");
		cobj->setCurrEnemyNum(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setCurrEnemyNum : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_getType1Hp(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_getType1Hp : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getType1Hp();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_getType1Hp : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GroupEnemy_setRate(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GroupEnemy* cobj = (GroupEnemy *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GroupEnemy_setRate : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GroupEnemy_setRate : Error processing arguments");
		cobj->setRate(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GroupEnemy_setRate : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GroupEnemy_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		GroupEnemy* ret = GroupEnemy::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<GroupEnemy>(cx, (GroupEnemy*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_GroupEnemy_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_GroupEnemy_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GroupEnemy)", obj);
}

void js_register_JsbTower_GroupEnemy(JSContext *cx, JSObject *global) {
	jsb_GroupEnemy_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_GroupEnemy_class->name = "GroupEnemy";
	jsb_GroupEnemy_class->addProperty = JS_PropertyStub;
	jsb_GroupEnemy_class->delProperty = JS_DeletePropertyStub;
	jsb_GroupEnemy_class->getProperty = JS_PropertyStub;
	jsb_GroupEnemy_class->setProperty = JS_StrictPropertyStub;
	jsb_GroupEnemy_class->enumerate = JS_EnumerateStub;
	jsb_GroupEnemy_class->resolve = JS_ResolveStub;
	jsb_GroupEnemy_class->convert = JS_ConvertStub;
	jsb_GroupEnemy_class->finalize = js_GroupEnemy_finalize;
	jsb_GroupEnemy_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getEnemyTotal", js_JsbTower_GroupEnemy_getEnemyTotal, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrEnemyNum", js_JsbTower_GroupEnemy_getCurrEnemyNum, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setType2Hp", js_JsbTower_GroupEnemy_setType2Hp, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType2Total", js_JsbTower_GroupEnemy_getType2Total, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRate", js_JsbTower_GroupEnemy_getRate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setType1Hp", js_JsbTower_GroupEnemy_setType1Hp, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setType1Total", js_JsbTower_GroupEnemy_setType1Total, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setType3Total", js_JsbTower_GroupEnemy_setType3Total, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType3Hp", js_JsbTower_GroupEnemy_getType3Hp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setIsFinishedAddGroup", js_JsbTower_GroupEnemy_setIsFinishedAddGroup, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType3Total", js_JsbTower_GroupEnemy_getType3Total, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("menuCloseCallback", js_JsbTower_GroupEnemy_menuCloseCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType2Hp", js_JsbTower_GroupEnemy_getType2Hp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getIsFinishedAddGroup", js_JsbTower_GroupEnemy_getIsFinishedAddGroup, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initGroupEnemy", js_JsbTower_GroupEnemy_initGroupEnemy, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setType2Total", js_JsbTower_GroupEnemy_setType2Total, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType1Total", js_JsbTower_GroupEnemy_getType1Total, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_GroupEnemy_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setEnemyTotal", js_JsbTower_GroupEnemy_setEnemyTotal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setType3Hp", js_JsbTower_GroupEnemy_setType3Hp, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurrEnemyNum", js_JsbTower_GroupEnemy_setCurrEnemyNum, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getType1Hp", js_JsbTower_GroupEnemy_getType1Hp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRate", js_JsbTower_GroupEnemy_setRate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_GroupEnemy_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_GroupEnemy_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Node_prototype,
		jsb_GroupEnemy_class,
		dummy_constructor<GroupEnemy>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "GroupEnemy", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<GroupEnemy> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_GroupEnemy_class;
		p->proto = jsb_GroupEnemy_prototype;
		p->parentProto = jsb_cocos2d_Node_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_MultiDirTower_class;
JSObject *jsb_MultiDirTower_prototype;

bool js_JsbTower_MultiDirTower_shoot(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	MultiDirTower* cobj = (MultiDirTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_MultiDirTower_shoot : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_MultiDirTower_shoot : Error processing arguments");
		cobj->shoot(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_MultiDirTower_shoot : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_MultiDirTower_MultiDirTowerBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	MultiDirTower* cobj = (MultiDirTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_MultiDirTower_MultiDirTowerBullet : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Sprite* ret = cobj->MultiDirTowerBullet();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_MultiDirTower_MultiDirTowerBullet : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_MultiDirTower_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	MultiDirTower* cobj = (MultiDirTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_MultiDirTower_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_MultiDirTower_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_MultiDirTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	MultiDirTower* cobj = (MultiDirTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_MultiDirTower_removeBullet : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_MultiDirTower_removeBullet : Error processing arguments");
		cobj->removeBullet(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_MultiDirTower_removeBullet : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_MultiDirTower_createBullet6(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	MultiDirTower* cobj = (MultiDirTower *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_MultiDirTower_createBullet6 : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_MultiDirTower_createBullet6 : Error processing arguments");
		cobj->createBullet6(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_MultiDirTower_createBullet6 : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_MultiDirTower_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		MultiDirTower* ret = MultiDirTower::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<MultiDirTower>(cx, (MultiDirTower*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_MultiDirTower_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_TowerBase_prototype;

void js_MultiDirTower_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MultiDirTower)", obj);
}

void js_register_JsbTower_MultiDirTower(JSContext *cx, JSObject *global) {
	jsb_MultiDirTower_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_MultiDirTower_class->name = "MultiDirTower";
	jsb_MultiDirTower_class->addProperty = JS_PropertyStub;
	jsb_MultiDirTower_class->delProperty = JS_DeletePropertyStub;
	jsb_MultiDirTower_class->getProperty = JS_PropertyStub;
	jsb_MultiDirTower_class->setProperty = JS_StrictPropertyStub;
	jsb_MultiDirTower_class->enumerate = JS_EnumerateStub;
	jsb_MultiDirTower_class->resolve = JS_ResolveStub;
	jsb_MultiDirTower_class->convert = JS_ConvertStub;
	jsb_MultiDirTower_class->finalize = js_MultiDirTower_finalize;
	jsb_MultiDirTower_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("shoot", js_JsbTower_MultiDirTower_shoot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("MultiDirTowerBullet", js_JsbTower_MultiDirTower_MultiDirTowerBullet, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_MultiDirTower_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeBullet", js_JsbTower_MultiDirTower_removeBullet, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createBullet6", js_JsbTower_MultiDirTower_createBullet6, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_MultiDirTower_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_MultiDirTower_prototype = JS_InitClass(
		cx, global,
		jsb_TowerBase_prototype,
		jsb_MultiDirTower_class,
		dummy_constructor<MultiDirTower>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "MultiDirTower", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<MultiDirTower> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_MultiDirTower_class;
		p->proto = jsb_MultiDirTower_prototype;
		p->parentProto = jsb_TowerBase_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_Thief_class;
JSObject *jsb_Thief_prototype;

bool js_JsbTower_Thief_changeDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Thief* cobj = (Thief *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_Thief_changeDirection : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_Thief_changeDirection : Error processing arguments");
		cobj->changeDirection(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_Thief_changeDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_Thief_enemyExpload(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Thief* cobj = (Thief *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_Thief_enemyExpload : Invalid Native Object");
	if (argc == 0) {
		cobj->enemyExpload();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_Thief_enemyExpload : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_Thief_createThief(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 2) {
		cocos2d::Vector<cocos2d::Node *> arg0;
		int arg1;
		ok &= jsval_to_ccvector(cx, argv[0], &arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_Thief_createThief : Error processing arguments");
		Thief* ret = Thief::createThief(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<Thief>(cx, (Thief*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_Thief_createThief : wrong number of arguments");
	return false;
}


extern JSObject *jsb_EnemyBase_prototype;

void js_Thief_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Thief)", obj);
}

void js_register_JsbTower_Thief(JSContext *cx, JSObject *global) {
	jsb_Thief_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_Thief_class->name = "Thief";
	jsb_Thief_class->addProperty = JS_PropertyStub;
	jsb_Thief_class->delProperty = JS_DeletePropertyStub;
	jsb_Thief_class->getProperty = JS_PropertyStub;
	jsb_Thief_class->setProperty = JS_StrictPropertyStub;
	jsb_Thief_class->enumerate = JS_EnumerateStub;
	jsb_Thief_class->resolve = JS_ResolveStub;
	jsb_Thief_class->convert = JS_ConvertStub;
	jsb_Thief_class->finalize = js_Thief_finalize;
	jsb_Thief_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("changeDirection", js_JsbTower_Thief_changeDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("enemyExpload", js_JsbTower_Thief_enemyExpload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("createThief", js_JsbTower_Thief_createThief, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_Thief_prototype = JS_InitClass(
		cx, global,
		jsb_EnemyBase_prototype,
		jsb_Thief_class,
		dummy_constructor<Thief>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "Thief", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Thief> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_Thief_class;
		p->proto = jsb_Thief_prototype;
		p->parentProto = jsb_EnemyBase_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_TowerPanleLayer_class;
JSObject *jsb_TowerPanleLayer_prototype;

bool js_JsbTower_TowerPanleLayer_setChooseTowerType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerPanleLayer* cobj = (TowerPanleLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerPanleLayer_setChooseTowerType : Invalid Native Object");
	if (argc == 1) {
		TowerType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerPanleLayer_setChooseTowerType : Error processing arguments");
		cobj->setChooseTowerType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerPanleLayer_setChooseTowerType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_TowerPanleLayer_getChooseTowerType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerPanleLayer* cobj = (TowerPanleLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerPanleLayer_getChooseTowerType : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getChooseTowerType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerPanleLayer_getChooseTowerType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerPanleLayer_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerPanleLayer* cobj = (TowerPanleLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerPanleLayer_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerPanleLayer_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_TowerPanleLayer_onTouchEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerPanleLayer* cobj = (TowerPanleLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerPanleLayer_onTouchEnded : Invalid Native Object");
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerPanleLayer_onTouchEnded : Error processing arguments");
		cobj->onTouchEnded(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerPanleLayer_onTouchEnded : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_JsbTower_TowerPanleLayer_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	TowerPanleLayer* cobj = (TowerPanleLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_TowerPanleLayer_onTouchBegan : Invalid Native Object");
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_TowerPanleLayer_onTouchBegan : Error processing arguments");
		bool ret = cobj->onTouchBegan(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_TowerPanleLayer_onTouchBegan : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_JsbTower_TowerPanleLayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		TowerPanleLayer* ret = TowerPanleLayer::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<TowerPanleLayer>(cx, (TowerPanleLayer*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_TowerPanleLayer_create : wrong number of arguments");
	return false;
}



void js_TowerPanleLayer_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TowerPanleLayer)", obj);
}

void js_register_JsbTower_TowerPanleLayer(JSContext *cx, JSObject *global) {
	jsb_TowerPanleLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_TowerPanleLayer_class->name = "TowerPanleLayer";
	jsb_TowerPanleLayer_class->addProperty = JS_PropertyStub;
	jsb_TowerPanleLayer_class->delProperty = JS_DeletePropertyStub;
	jsb_TowerPanleLayer_class->getProperty = JS_PropertyStub;
	jsb_TowerPanleLayer_class->setProperty = JS_StrictPropertyStub;
	jsb_TowerPanleLayer_class->enumerate = JS_EnumerateStub;
	jsb_TowerPanleLayer_class->resolve = JS_ResolveStub;
	jsb_TowerPanleLayer_class->convert = JS_ConvertStub;
	jsb_TowerPanleLayer_class->finalize = js_TowerPanleLayer_finalize;
	jsb_TowerPanleLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setChooseTowerType", js_JsbTower_TowerPanleLayer_setChooseTowerType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getChooseTowerType", js_JsbTower_TowerPanleLayer_getChooseTowerType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_TowerPanleLayer_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("onTouchEnded", js_JsbTower_TowerPanleLayer_onTouchEnded, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("onTouchBegan", js_JsbTower_TowerPanleLayer_onTouchBegan, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_TowerPanleLayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_TowerPanleLayer_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_TowerPanleLayer_class,
		dummy_constructor<TowerPanleLayer>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "TowerPanleLayer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<TowerPanleLayer> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_TowerPanleLayer_class;
		p->proto = jsb_TowerPanleLayer_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_GameManager_class;
JSObject *jsb_GameManager_prototype;

bool js_JsbTower_GameManager_getMoney(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getMoney : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getMoney();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getMoney : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_setCurMapName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setCurMapName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setCurMapName : Error processing arguments");
		cobj->setCurMapName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setCurMapName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_getBlood(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getBlood : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getBlood();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getBlood : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_setNextLevelFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setNextLevelFile : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setNextLevelFile : Error processing arguments");
		cobj->setNextLevelFile(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setNextLevelFile : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_setCurMapID(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setCurMapID : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setCurMapID : Error processing arguments");
		cobj->setCurMapID(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setCurMapID : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_setIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setIsFinishedAddGroup : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setIsFinishedAddGroup : Error processing arguments");
		cobj->setIsFinishedAddGroup(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setIsFinishedAddGroup : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_clear : Invalid Native Object");
	if (argc == 0) {
		cobj->clear();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getCurrLevelFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getCurrLevelFile : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getCurrLevelFile();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getCurrLevelFile : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_setCurBgName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setCurBgName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setCurBgName : Error processing arguments");
		cobj->setCurBgName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setCurBgName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_setCurrLevelFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setCurrLevelFile : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setCurrLevelFile : Error processing arguments");
		cobj->setCurrLevelFile(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setCurrLevelFile : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_setGroupNum(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setGroupNum : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setGroupNum : Error processing arguments");
		cobj->setGroupNum(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setGroupNum : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getGroupNum(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getGroupNum : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getGroupNum();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getGroupNum : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getNextLevelFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getNextLevelFile : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getNextLevelFile();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getNextLevelFile : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_setBlood(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setBlood : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setBlood : Error processing arguments");
		cobj->setBlood(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setBlood : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_setMoney(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_setMoney : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_GameManager_setMoney : Error processing arguments");
		cobj->setMoney(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_setMoney : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_GameManager_getCurMapName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getCurMapName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getCurMapName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getCurMapName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getCurMapID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getCurMapID : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getCurMapID();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getCurMapID : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getCurBgName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getCurBgName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getCurBgName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getCurBgName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	GameManager* cobj = (GameManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_GameManager_getIsFinishedAddGroup : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->getIsFinishedAddGroup();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_GameManager_getIsFinishedAddGroup : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_GameManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		GameManager* ret = GameManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<GameManager>(cx, (GameManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_GameManager_getInstance : wrong number of arguments");
	return false;
}



void js_GameManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GameManager)", obj);
}

void js_register_JsbTower_GameManager(JSContext *cx, JSObject *global) {
	jsb_GameManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_GameManager_class->name = "GameManager";
	jsb_GameManager_class->addProperty = JS_PropertyStub;
	jsb_GameManager_class->delProperty = JS_DeletePropertyStub;
	jsb_GameManager_class->getProperty = JS_PropertyStub;
	jsb_GameManager_class->setProperty = JS_StrictPropertyStub;
	jsb_GameManager_class->enumerate = JS_EnumerateStub;
	jsb_GameManager_class->resolve = JS_ResolveStub;
	jsb_GameManager_class->convert = JS_ConvertStub;
	jsb_GameManager_class->finalize = js_GameManager_finalize;
	jsb_GameManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getMoney", js_JsbTower_GameManager_getMoney, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurMapName", js_JsbTower_GameManager_setCurMapName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getBlood", js_JsbTower_GameManager_getBlood, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setNextLevelFile", js_JsbTower_GameManager_setNextLevelFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurMapID", js_JsbTower_GameManager_setCurMapID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setIsFinishedAddGroup", js_JsbTower_GameManager_setIsFinishedAddGroup, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("clear", js_JsbTower_GameManager_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrLevelFile", js_JsbTower_GameManager_getCurrLevelFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurBgName", js_JsbTower_GameManager_setCurBgName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCurrLevelFile", js_JsbTower_GameManager_setCurrLevelFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGroupNum", js_JsbTower_GameManager_setGroupNum, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_GameManager_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getGroupNum", js_JsbTower_GameManager_getGroupNum, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getNextLevelFile", js_JsbTower_GameManager_getNextLevelFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBlood", js_JsbTower_GameManager_setBlood, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMoney", js_JsbTower_GameManager_setMoney, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurMapName", js_JsbTower_GameManager_getCurMapName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurMapID", js_JsbTower_GameManager_getCurMapID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurBgName", js_JsbTower_GameManager_getCurBgName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getIsFinishedAddGroup", js_JsbTower_GameManager_getIsFinishedAddGroup, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_JsbTower_GameManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_GameManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_GameManager_class,
		dummy_constructor<GameManager>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "GameManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<GameManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_GameManager_class;
		p->proto = jsb_GameManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_PlayLayer_class;
JSObject *jsb_PlayLayer_prototype;

bool js_JsbTower_PlayLayer_logic(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PlayLayer* cobj = (PlayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_PlayLayer_logic : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_PlayLayer_logic : Error processing arguments");
		cobj->logic(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_PlayLayer_logic : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_PlayLayer_update(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PlayLayer* cobj = (PlayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_PlayLayer_update : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_PlayLayer_update : Error processing arguments");
		cobj->update(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_PlayLayer_update : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_JsbTower_PlayLayer_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PlayLayer* cobj = (PlayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_PlayLayer_onTouchBegan : Invalid Native Object");
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_JsbTower_PlayLayer_onTouchBegan : Error processing arguments");
		bool ret = cobj->onTouchBegan(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_PlayLayer_onTouchBegan : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_JsbTower_PlayLayer_nextGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PlayLayer* cobj = (PlayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_PlayLayer_nextGroup : Invalid Native Object");
	if (argc == 0) {
		GroupEnemy* ret = cobj->nextGroup();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<GroupEnemy>(cx, (GroupEnemy*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_PlayLayer_nextGroup : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_PlayLayer_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PlayLayer* cobj = (PlayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_PlayLayer_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_PlayLayer_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_PlayLayer_currentGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	PlayLayer* cobj = (PlayLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_JsbTower_PlayLayer_currentGroup : Invalid Native Object");
	if (argc == 0) {
		GroupEnemy* ret = cobj->currentGroup();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<GroupEnemy>(cx, (GroupEnemy*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_JsbTower_PlayLayer_currentGroup : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_JsbTower_PlayLayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		PlayLayer* ret = PlayLayer::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<PlayLayer>(cx, (PlayLayer*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_PlayLayer_create : wrong number of arguments");
	return false;
}

bool js_JsbTower_PlayLayer_createScene(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::Scene* ret = PlayLayer::createScene();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Scene>(cx, (cocos2d::Scene*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_JsbTower_PlayLayer_createScene : wrong number of arguments");
	return false;
}

bool js_JsbTower_PlayLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    PlayLayer* cobj = new PlayLayer();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<PlayLayer> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "PlayLayer");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_PlayLayer_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PlayLayer)", obj);
}

void js_register_JsbTower_PlayLayer(JSContext *cx, JSObject *global) {
	jsb_PlayLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PlayLayer_class->name = "PlayLayer";
	jsb_PlayLayer_class->addProperty = JS_PropertyStub;
	jsb_PlayLayer_class->delProperty = JS_DeletePropertyStub;
	jsb_PlayLayer_class->getProperty = JS_PropertyStub;
	jsb_PlayLayer_class->setProperty = JS_StrictPropertyStub;
	jsb_PlayLayer_class->enumerate = JS_EnumerateStub;
	jsb_PlayLayer_class->resolve = JS_ResolveStub;
	jsb_PlayLayer_class->convert = JS_ConvertStub;
	jsb_PlayLayer_class->finalize = js_PlayLayer_finalize;
	jsb_PlayLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("logic", js_JsbTower_PlayLayer_logic, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("update", js_JsbTower_PlayLayer_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("onTouchBegan", js_JsbTower_PlayLayer_onTouchBegan, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("nextGroup", js_JsbTower_PlayLayer_nextGroup, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_JsbTower_PlayLayer_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("currentGroup", js_JsbTower_PlayLayer_currentGroup, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_JsbTower_PlayLayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createScene", js_JsbTower_PlayLayer_createScene, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_PlayLayer_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PlayLayer_class,
		js_JsbTower_PlayLayer_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PlayLayer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<PlayLayer> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_PlayLayer_class;
		p->proto = jsb_PlayLayer_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_JsbTower(JSContext* cx, JSObject* obj) {

	js_register_JsbTower_TowerBase(cx, obj);
	js_register_JsbTower_ArrowTower(cx, obj);
	js_register_JsbTower_DecelerateTower(cx, obj);
	js_register_JsbTower_GroupEnemy(cx, obj);
	js_register_JsbTower_PlayLayer(cx, obj);
	js_register_JsbTower_EnemyBase(cx, obj);
	js_register_JsbTower_Thief(cx, obj);
	js_register_JsbTower_GameManager(cx, obj);
	js_register_JsbTower_TowerPanleLayer(cx, obj);
	js_register_JsbTower_ElectricityTower(cx, obj);
	js_register_JsbTower_MultiDirTower(cx, obj);
}

