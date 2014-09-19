//
//  JSB_AUTO.h
//  pokoSanguo
//
//  Created by Shan Shikai on 4/11/14.
//
//

#ifndef __JSBTest__JSB_AUTO__
#define __JSBTest__JSB_AUTO__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass*        jsb_class;
extern JSObject*       jsb_prototype;

void register_all(JSContext* cx, JSObject* obj);

#endif /* defined(__JSBTest__JSB_AUTO__) */
