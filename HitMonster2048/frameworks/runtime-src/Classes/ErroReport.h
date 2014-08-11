//
//  ErroReport.h
//  pokoSanguo
//
//  Created by Shan Shikai on 5/26/14.
//
//

#ifndef __pokoSanguo__ErroReport__
#define __pokoSanguo__ErroReport__

#include <iostream>
#include "cocos2d.h"
using namespace	std;
using namespace cocos2d;

string GetTime();

void PoKoSangGuoLog(const char* log);

void SendErrorLogFile();

void ReportError(const char* msg);

void UncaughtExceptionHandler(const char *exception);

#endif /* defined(__pokoSanguo__ErroReport__) */
