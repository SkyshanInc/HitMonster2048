#import "coralsdk.h"
#import "XcodeCallback.h"
#import <BattleWorkLibrary/FDBNApp.h>
#import <BattleWorkLibrary/BNJSONSerializer.h>


@implementation BnInterfaceForIOS

+(NSString *) DictionaryToString:(NSDictionary *)dic
{
	NSError *error = nil;
	NSData *jsonData = [[BNJSONSerializer serializer] serializeDictionary:dic error:&error];
    NSString *str = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
	return str;
}

@end

USING_NS_CC;

//设置游戏配置
void BnSetConfig(void *__glView)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //设置服务器为测试服务器,若游戏需上线则讲此行代码注释，链接到正式服务器
    //[FDBNApp setDebugMode];
    //挑战好友人数上限(默认1个)
    [FDBNApp setChallengeFriendNum:1];
    //随机挑战人数上限(默认1个)
    [FDBNApp setChallengeRanDomNun:1];
    //设置按键声音（VoiceName声音文件名）
    [FDBNApp setButtonVoice:@"onclick.wav"];
    //设置版本号
    [FDBNApp setGameVerion:@"1.0.0"];
    //设置SDK其他页面的背景
    [FDBNApp setBNEngineBackgroundImage:[UIImage imageNamed:@"menu.png"]];
    
    
    
    
    //设置游戏唯一标识gameid 以及应用名字
    [FDBNApp setGameId:@"l6be1eaaa45041c3bc90914a160aa3da" gameName:@"HitMonster2048"];
    //微信分享调用的,微信APPKEY，自己应用ICON，应用名字，分享文字，应用连接地址
    [FDBNApp loadWXEngine:@"wxbe87146c2d642639" icon:[UIImage imageNamed:@"Icon"] title:@"HitMonster" message:@"打怪兽！" url:@"http://dev.friendou.com/game_detail/100673"];
    
    
//    //设置游戏唯一标识gameid 以及应用名字
//    [FDBNApp setGameId:@"f6583e55ba29c09c35b41332168321be" gameName:@"极难贪吃蛇"];
//    //微信分享调用的,微信APPKEY，自己应用ICON，应用名字，分享文字，应用连接地址
//    [FDBNApp loadWXEngine:@"wxbe87146c2d642639" icon:[UIImage imageNamed:@"Icon"] title:@"极难贪吃蛇" message:@"你玩过极难贪吃蛇吗？，是极难的贪吃蛇，也许你一分也吃不到！" url:@"http://dev.friendou.com/game_detail/100673"];
    
    
    
    //开启多人游戏模式，注释则为单人模式
    [FDBNApp setMultiplayerMode];
    //设置游戏按键穿透
    [FDBNApp setGameView:(UIView*)__glView];
    //设置屏幕方向(YES: 横屏。NO:竖屏)
    [FDBNApp setScreenOrientation:NO];
    //设置是否有回放功能，NO：无回放，YES：有回放
    [FDBNApp setReplayStatus:NO];
    //设置SDK不显示金币
    [FDBNApp setGoldHideMode];
#endif
}

void IOSLogin(int type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [FDBNApp login:type];
#endif

}

bool IOSGetLoginStatus()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isLogin = [FDBNApp getloginstatus];
    NSLog(@"GetLoginStatus === %i",isLogin);
    return isLogin;
#endif

}

void IOSShowGameHome()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [FDBNApp showGameHome];
#endif
    
}

//隐藏SDK
void IOSBnHideSDK()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [FDBNApp hideSDK];
#endif
}

void IOSGameOver(int score, int gold, const char* baseStr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	NSString *Score = [NSString stringWithFormat:@"%i",score];
	NSString *Gold = [NSString stringWithFormat:@"%i",gold];
	NSString *BaseStr = [NSString stringWithUTF8String:baseStr];
	//NSString *ArchieveStr = [NSString stringWithUTF8String:archieveStr];
    
    [FDBNApp gameOver:Score gameGold:Gold baseScoreStr:BaseStr];
#endif

}

void IOSFinishGame(int score, const char* gameData, int gold, const char* baseStr)
{

	NSString *Score = [NSString stringWithFormat:@"%i",score];
	NSString *GameData = [NSString stringWithUTF8String:gameData];
	//NSString *Data = [NSString stringWithUTF8String:data];
	NSString *Gold = [NSString stringWithFormat:@"%i",gold];
	NSString *BaseStr = [NSString stringWithUTF8String:baseStr];
	NSData* xmlData = [GameData dataUsingEncoding:NSUTF8StringEncoding];
    
    [FDBNApp finishGame:Score gameData:xmlData gameGold:Gold baseScoreStr:BaseStr];
    
}


const char *IOSGetProfile()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    char *buf = new char[512];
    memset(buf, 0, 512);
    NSDictionary *UserData = [FDBNApp getUser];
    if(UserData == NULL)
    {
        NSLog(@"UserData is null !");
        return NULL;
    }
    NSString *str = [BnInterfaceForIOS DictionaryToString:UserData];
    
    NSLog(@"user === %@",UserData);
    
    if (UserData != nil)
    {
        const char *name = [str UTF8String];
        strcpy(buf, name);
        [str release];
    }
    else
    {
        strcpy(buf, "");
    }
    return buf;
    
#endif
    
}

bool IOSGetMusicOnStatus()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isOn = [FDBNApp getMusicOnStatus];
    NSLog(@"BnGetMusicOnStatus === %i",isOn);
    return isOn;
#endif

}

bool IOSGetSoundOnStatus()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isOn = [FDBNApp getSoundOnStatus];
    NSLog(@"BnGetSoundOnStatus === %i",isOn);
    return isOn;
#endif

}

//增加或减少金币
bool IOSBnSetGameGold(int gold)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [FDBNApp setGameGold:gold];
    CCLOG("IOSBnSetGameGold=====gold = %d",gold);
#endif
}

//获取金币
int IOSBnGetGameGold()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [FDBNApp getGameGold];
#endif
}

//page:1、爱心 2、金币 3、钻石
void IOSBnShowStoreView(int page)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    [FDBNApp showStoreView:page];
    CCLOG("IOSBnShowShopView");
    
#endif
}

//道具保存
void IOSBnSetGamePropSave(const char *prop)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSString *GameProp = [NSString stringWithUTF8String:prop];
    [FDBNApp setGamePropSave:GameProp];
#endif
}

//获取道具
const char *IOSBnGetGameProp()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    char *buf = new char[1024];
    memset(buf, 0, 1024);
    NSString *GameProp = [FDBNApp getGameProp];
    if (GameProp != nil)
    {
        NSLog(@"GameProp == %@",GameProp);
        const char *Prop = [GameProp UTF8String];
        strcpy(buf, Prop);
    }
    else
    {
        NSLog(@"Game prop is null !");
        strcpy(buf, "");
    }
    return buf;
    
#endif
}
//获取钻石数量
int IOSBnGetGameDiamond()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [FDBNApp getGameDiamond];
#endif
}
    
//增加或减少钻石
bool IOSBnSetGameDiamond(int DiamondNum)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [FDBNApp setGameDiamond:DiamondNum];
#endif
}
    
//获取爱心数量
int IOSBnGetGamePower()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [FDBNApp getGamePower];
#endif
}
    
//增加或减少爱心
bool IOSBnSetGamePower(int PowerNum)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [FDBNApp setGamePower:PowerNum];
#endif
}



