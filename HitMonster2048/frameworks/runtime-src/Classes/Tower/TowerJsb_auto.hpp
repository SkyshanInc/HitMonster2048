#ifndef __JsbTower_h__
#define __JsbTower_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_EnemyBase_class;
extern JSObject *jsb_EnemyBase_prototype;

bool js_JsbTower_EnemyBase_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_EnemyBase_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_EnemyBase(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_EnemyBase_decelerate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setHpPercentage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setRunSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setEnemySuccessful(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setVaule(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getVaule(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getRunSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_createAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setPointsVector(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_createAndSetHpBar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setCurrHp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_enemyExpload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getMaxHp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_runFllowPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_setMaxHp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_changeDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getEnemySuccessful(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getHpPercentage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_currPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getCurrHp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getHpBar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_nextPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_getPointCounter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_EnemyBase_EnemyBase(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_TowerBase_class;
extern JSObject *jsb_TowerBase_prototype;

bool js_JsbTower_TowerBase_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_TowerBase_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_TowerBase(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_TowerBase_getScope(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_checkNearestEnemy(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_getTowerValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_setLethality(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_getLethality(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_getRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_setRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_setScope(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_setTowerValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerBase_TowerBase(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ArrowTower_class;
extern JSObject *jsb_ArrowTower_prototype;

bool js_JsbTower_ArrowTower_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_ArrowTower_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_ArrowTower(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_ArrowTower_shoot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ArrowTower_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ArrowTower_rotateAndShoot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ArrowTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ArrowTower_ArrowTowerBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ArrowTower_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_DecelerateTower_class;
extern JSObject *jsb_DecelerateTower_prototype;

bool js_JsbTower_DecelerateTower_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_DecelerateTower_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_DecelerateTower(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_DecelerateTower_shoot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_DecelerateTower_DecelerateTowerBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_DecelerateTower_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_DecelerateTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_DecelerateTower_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ElectricityTower_class;
extern JSObject *jsb_ElectricityTower_prototype;

bool js_JsbTower_ElectricityTower_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_ElectricityTower_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_ElectricityTower(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_ElectricityTower_shoot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ElectricityTower_ElectricityTowerBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ElectricityTower_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ElectricityTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_ElectricityTower_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GroupEnemy_class;
extern JSObject *jsb_GroupEnemy_prototype;

bool js_JsbTower_GroupEnemy_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_GroupEnemy_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_GroupEnemy(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_GroupEnemy_getEnemyTotal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getCurrEnemyNum(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setType2Hp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getType2Total(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setType1Hp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setType1Total(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setType3Total(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getType3Hp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getType3Total(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_menuCloseCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getType2Hp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_initGroupEnemy(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setType2Total(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getType1Total(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setEnemyTotal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setType3Hp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setCurrEnemyNum(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_getType1Hp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_setRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GroupEnemy_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_MultiDirTower_class;
extern JSObject *jsb_MultiDirTower_prototype;

bool js_JsbTower_MultiDirTower_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_MultiDirTower_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_MultiDirTower(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_MultiDirTower_shoot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_MultiDirTower_MultiDirTowerBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_MultiDirTower_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_MultiDirTower_removeBullet(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_MultiDirTower_createBullet6(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_MultiDirTower_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_Thief_class;
extern JSObject *jsb_Thief_prototype;

bool js_JsbTower_Thief_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_Thief_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_Thief(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_Thief_changeDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_Thief_enemyExpload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_Thief_createThief(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_TowerPanleLayer_class;
extern JSObject *jsb_TowerPanleLayer_prototype;

bool js_JsbTower_TowerPanleLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_TowerPanleLayer_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_TowerPanleLayer(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_TowerPanleLayer_setChooseTowerType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerPanleLayer_getChooseTowerType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerPanleLayer_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerPanleLayer_onTouchEnded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerPanleLayer_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_TowerPanleLayer_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GameManager_class;
extern JSObject *jsb_GameManager_prototype;

bool js_JsbTower_GameManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_GameManager_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_GameManager(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_GameManager_getMoney(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setCurMapName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getBlood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setNextLevelFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setCurMapID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getCurrLevelFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setCurBgName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setCurrLevelFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setGroupNum(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getGroupNum(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getNextLevelFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setBlood(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_setMoney(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getCurMapName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getCurMapID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getCurBgName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getIsFinishedAddGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_GameManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_PlayLayer_class;
extern JSObject *jsb_PlayLayer_prototype;

bool js_JsbTower_PlayLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_JsbTower_PlayLayer_finalize(JSContext *cx, JSObject *obj);
void js_register_JsbTower_PlayLayer(JSContext *cx, JSObject *global);
void register_all_JsbTower(JSContext* cx, JSObject* obj);
bool js_JsbTower_PlayLayer_logic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_nextGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_currentGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_createScene(JSContext *cx, uint32_t argc, jsval *vp);
bool js_JsbTower_PlayLayer_PlayLayer(JSContext *cx, uint32_t argc, jsval *vp);
#endif

