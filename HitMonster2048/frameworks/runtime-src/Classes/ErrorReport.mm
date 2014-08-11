//
//  ErrorReport.mm
//  pokoSanguo
//
//  Created by 李会群 on 14-4-22.
//
//
#include "ErroReport.h"

#include "HttpClient.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "cocos-ext.h"
#include "storage/local-storage/LocalStorage.h"

using namespace cocos2d::network;


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
	string timeStr = GetTime();
	string logStr = string(timeStr) + string(log)+"\n\n\n";
	string writePath = CCFileUtils::getInstance()->getWritablePath();
	string logFile = writePath + "PoKoSanguoLog.txt";
	
	FILE* openFile = fopen(logFile.c_str(),"at+");
	fwrite(logStr.c_str(),1,logStr.size(),openFile);
	fclose(openFile);
}

void SendErrorLogFile()
{
	CCLOG("=========SendErrorLog=======");
	
	ssize_t bffSize = 0;
	string writePath = CCFileUtils::getInstance()->getWritablePath();
	string logFile = writePath + "PoKoSanguoLog.txt";
	unsigned char* clientData = CCFileUtils::getInstance()->getFileData(logFile.c_str(), "r", &bffSize);
	string logStr = string(clientData,clientData+bffSize);
	string uname = localStorageGetItem("uname");
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Value paramValue;
	paramValue.SetObject();

	doc.AddMember("method","client_log", doc.GetAllocator());
	paramValue.AddMember("device_hash", uname.c_str(), doc.GetAllocator());
	paramValue.AddMember("strlog", logStr.c_str(), doc.GetAllocator());
	doc.AddMember("params",paramValue, doc.GetAllocator());

	rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	
	HttpRequest* request = new HttpRequest();
	//required fields
	string ip = localStorageGetItem("LoginIP");
	if(ip.empty()) 
		ip = "http://117.121.25.155:8345";
	request->setUrl(ip.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setRequestData(buffer.GetString(), buffer.Size());

	//request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
	// optional fields                            
	HttpClient::getInstance()->send(request);
	
	// don't forget to release it, pair to new
	request->release();
	
	//FILE* openFile = fopen(logFile.c_str(),"wb+");
	//fwrite("",1,0,openFile);
	//fclose(openFile);
}

void ReportError(const char* msg)
{
	if(msg!=0)
		MessageBox(msg,"速度!截屏!");
	localStorageSetItem("ErrorReport", "msg");
	PoKoSangGuoLog(msg);
	//NSLog(@"%@ =====",[NSThread callStackSymbols]);
	//NSArray *syms = [NSThread  callStackSymbols]; 
	//NSString *str = [NSString stringWithCString:__PRETTY_FUNCTION__ encoding:NSASCIIStringEncoding];
	//NSLog(@"%@",str);
}

void UncaughtExceptionHandler(NSException *exception) {
    NSArray *arr = [exception callStackSymbols];
    NSString *reason = [exception reason];
    NSString *name = [exception name];
    
    NSString *str = [NSString stringWithFormat:@"=============异常崩溃报告=============\nname:\n%@\nreason:\n%@\ncallStackSymbols:\n%@",
                     name,reason,[arr componentsJoinedByString:@"\n"]];
    
    PoKoSangGuoLog([str UTF8String]);
    //除了可以选择写到应用下的某个文件，通过后续处理将信息发送到服务器等
    //还可以选择调用发送邮件的的程序，发送信息到指定的邮件地址
    //或者调用某个处理程序来处理这个信息
}
