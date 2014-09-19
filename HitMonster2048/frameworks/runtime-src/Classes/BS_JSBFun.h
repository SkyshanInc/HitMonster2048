//
//  BS_JSBFun.h
//  pokoSanguo
//
//  Created by Shan Shikai on 4/11/14.
//
//

#ifndef __pokoSanguo__BS_JSBFun__
#define __pokoSanguo__BS_JSBFun__

#include <iostream>
#include "cocos2d.h"
using namespace std;

namespace BS {
    class JSBFun: public cocos2d::Ref
    {
    public:
        static cocos2d::Scene* scene();
        
        virtual bool init();
//        CREATE_FUNC(JSBFun);
        static JSBFun* create();
        void js2c(const char *func,const char* param);
        
        std::string JsNativefunc(const char *func,const char* param);
        
        static std::string androidCom_interceptor(const char *func,const char* param);
    };
}

#endif /* defined(__pokoSanguo__BS_JSBFun__) */
