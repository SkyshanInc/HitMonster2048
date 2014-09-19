#ifndef  _GAMECONFIG_H_
#define  _GAMECONFIG_H_

using namespace std;


static const string WELCOME_BG                          = "welcome_bg.png";
static const string WELCOME_LOGO                        = "welcome_logo.png";
static const string WELCOME_BT_QQ_NORALIMAGE            = "welcome_qqbution.png";
static const string WELCOME_BT_QQ_SLECTEDIMAGE          = "welcome_qqbution.png";
static const string MENU_BG                             = "menu.png";
static const string GAMEVIEW_BG                         = "menu.png";


static const string SPRITE_CACHE_PLIST              = "sprite.plist";



static const int TAG_WELCOME_BT          = 1000;
static const int TAG_WELCOME_BT_QQ       = 1001;
static const int TAG_WELCOME_LOADING     = 1002;
static const int TAG_WELCOME_BT_GUEST    = 1003;
 
static const int TAG_GAMELAYER_BT_UP     = 2000;
static const int TAG_GAMELAYER_BT_LEFT   = 2001;
static const int TAG_GAMELAYER_BT_RIGHT  = 2002;
static const int TAG_GAMELAYER_BT_DOWN   = 2003;
static const int TAG_GAMELAYER_STAGE     = 2004;
static const int TAG_GAMELAYER_HOME     = 2005;



enum class EGameState
{
    NONE,
    LOGINERROR,
    LOGINSUCCESS,
    RANDING,
	PLAYING,
    PAUSE,
    RESUME,
	GAMEOVER,
    LOGINOUT
};

enum class EGameScene
{
    WELCOME,
	MENU,
    GAMELAYER,
	GAMEVIEW
};

#endif
