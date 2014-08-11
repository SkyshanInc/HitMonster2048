//
//  ErroReport.cpp
//  pokoSanguo
//
//  Created by Shan Shikai on 5/26/14.
//
//

#include "ErroReport.h"

string GetTime()
{
    time_t tt = time(NULL);
    tm *tp = localtime(&tt);
	char timeStr[64];
	sprintf(timeStr,"%d/%d/%d:::",tp->tm_mon+1,tp->tm_mday,tp->tm_year+1900);
	return string(timeStr);
}
void PoKoSangGuoLog(const char* log)
{
//    string timeStr = GetTime();
//	string logStr = string(timeStr) + string(log)+"\n\n\n";
//	string writePath = CCFileUtils::getInstance()->getWritablePath();
//	string logFile = writePath + "PoKoSanguoLog.txt";
//	
//	FILE* openFile = fopen(logFile.c_str(),"at+");
//	fwrite(logStr.c_str(),1,logStr.size(),openFile);
//	fclose(openFile);
}

void SendErrorLogFile()
{
    
}

void ReportError(const char* msg)
{
#ifdef DEBUGMODE
    if(msg!=0)
		MessageBox(msg,"速度!截屏!");
	PoKoSangGuoLog(msg);
#endif
    
}

void UncaughtExceptionHandler(const char *exception) {
    
}