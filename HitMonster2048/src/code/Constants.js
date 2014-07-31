
var TAG_WinNode      = 10000
var TAG_CloseBtn     = 10001

var ZOrder_Scene = 0
var ZOrder_SceneTop = 1
var ZOrder_Player = 2
var ZOrder_Effect = ZOrder_Player+5
var ZOrder_UIBottom = 8
var ZOrder_MainUI = 9
var ZOrder_UITop = 10
var ZOrder_Max = 11;

// path
var DATA_PATH = "res/data/";
var RES_PATH  = "res";

var LANGUAGE = "cn";
//字体类型
var FONT_TYPE = "FZY4JW--GB1-0";//方正粗圆简

var CURRENCY_TYPE = {GOLD: 0, GEM: 1};
var CURRENCY_ICON = {0: "ico_jinbi.png",
                     1: "ico_zuanshi.png"};

var POWERRECIEVETIMES = 15;//可领取体力的总次数
var MAILVALIDDATE = 30;//邮件的有效天数

/*
	购买金币		1
	购买钻石		2
	购买令牌		3
	购买道具		4
	招贤			5
	升级糖果		6
	付费摇奖机	7
	购买强力开局	8
*/
var SALE_TYPE = {GOLD:1,GEM:2,PVE:3,ITEM:4,GENERAL:5,SODIER:6,SLOT:7,POWERUP:8};

//网络轮询时间
var NETWORK_POLL_TIME = 60;

//是否开启低画质
var LOW_IMAGE_QUALITY = false;
