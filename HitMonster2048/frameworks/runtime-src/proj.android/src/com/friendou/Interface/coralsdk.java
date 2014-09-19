package com.friendou.Interface;

import java.util.List;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONException;
import org.json.JSONObject;
 



import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.friendou.bn.BattleNetApi;
import com.friendou.bn.BattleNetDataCallback;
import com.friendou.bn.BattleNetRelookCallback;
import com.friendou.bn.gameinfo.GameConfig;
import com.skyshan.hitMonster2048.R;

public class coralsdk
{
	public static final String LOGIN_ACTION = "1"; 
	public static final String GETLOGINSTATUS_ACTION = "2";
	public static final String FINISHGAME_ACTION = "3";
	public static final String SHOWGAMEHOME_ACTION = "4"; 
	public static final String GETPROFILE_ACTION = "5"; 
	public static final String GETMUSICONSTATUS_ACTION = "6"; 
	public static final String GETSOUNDONSTATUS_ACTION = "7"; 
	public static final String HIDESDK_ACTION = "8"; 
	public static final String SETGAMEGOLD_ACTION = "9"; 
	public static final String GETGAMEGOLD_ACTION = "10"; 
	public static final String SHOWSHOPVIEW_ACTION = "11"; 
	public static final String SETGAMEPROPSAVE_ACTION = "12"; 
	public static final String GETGAMEPROP_ACTION = "13"; 
	public static final String GETGAMEDIAMOND_ACTION = "14"; 
	public static final String SETGAMEDIAMOND_ACTION = "15";
	public static final String GETGAMEPOWER_ACTION = "16"; 
	public static final String SETGAMEPOWER_ACTION = "17";
	
	static BattleNetApi bnApi = null;


    private static void setConfig(Activity aContext, PackageInfo pinfo)
    {
         String gamename = pinfo.applicationInfo.loadLabel(aContext.getPackageManager()).toString();
         GameConfig tGameConfig = GameConfig.getInstance();
         tGameConfig.beDebugMode = true; //设置测试模式。注意，若要上线则将此代码注释。
         tGameConfig.appkey = "l6be1eaaa45041c3bc90914a160aa3da";;//设置游戏唯一标识AppKey以及应用名字
         tGameConfig.gamesourcetype = 2;//设置游戏开发平台 (1:Unity3d; 2:Cocos2dx; 3： android原生游戏)
         tGameConfig.appname = gamename; //设置游戏名字
         tGameConfig.gameverion = pinfo.versionName;//设置版本号，版本号格式为x.x.x即三级格式命名方式。
         tGameConfig.screen_orientation = 2;// 设置屏幕方向(1:横屏;2:竖屏)

         tGameConfig.goldhideMode = true;// 设置金币是否显示功能
         tGameConfig.game_bg_img_Rid = R.drawable.menu;;//设置SDK页面的背景
         tGameConfig.challenge_friend_num = 1;//挑战好友人数上限
         tGameConfig.challenge_random_num = 1;//随机挑战人数上限
         tGameConfig.btnvoice_Rid = R.raw.click;// 设置按键声音文件
         bnApi.setMultiplayerMode();//开启多人游戏模式，注释则为单人模式
		 bnApi.initScale();//V1.0.2版本增加
         bnApi.BnLoadWXEngine("wxbe87146c2d642639", String.valueOf(R.drawable.icon), gamename,"你玩过极难贪吃蛇吗？，是极难的贪吃蛇，也许你一分也吃不到！", "http://dev.friendou.com/game_detail/100673");      //微信分享需要的参数分别为 微信APPKEY,游戏icon,应用名称,分享文字说明
    }

	
	
	
	
	
	
	
	
	
	
	
	private static BattleNetDataCallback aBattleNetCallback = new BattleNetDataCallback()
	{

		public void onLogoutNotification()
		{
			bnApi.hideSDK();
			BnLogoutNotification();
		}

		public void onMusicTurnOffAndOn(Boolean isOn)
		{
			BnMusicTurnOffAndOn(isOn);
		}

		public void onSoundTurnOffAndOn(Boolean isOn)
		{
			BnSoundTurnOffAndOn(isOn);
		}

		public void onLoginCallback(int isLogin)
		{
			BnLoginResult(isLogin);
		}

		public void onGameUserSelectedNotification(List userlist)
		{
			BnGameUserSelectedNotification(userlist);
		}

		public void onGameBackNotification()
		{
			BnGameBackNotification();
		}

		@Override
		public void onNetWorkError()
		{
		}

	};

	private static BattleNetRelookCallback aBattleNetRelookCallback = new BattleNetRelookCallback()
	{
		@Override
		public void onGameReplayNotification(List userlist)
		{
			BnGameReplayNotification(userlist);
		}
	};

	public static String ReceiveCocos2dData(String aData)
	{
		if (aData != null && aData.length() > 0)
		{
			try
			{
				Log.e("CallSDK", "aData = " + aData);

				JSONObject tData = new JSONObject(aData);
				String action = tData.getString("action");

				if (action != null)
				{
					if (action.equals(GETLOGINSTATUS_ACTION) || action.equals(GETPROFILE_ACTION)
							|| action.equals(GETMUSICONSTATUS_ACTION) || action.equals(GETSOUNDONSTATUS_ACTION)
							|| action.equals(SETGAMEGOLD_ACTION) || action.equals(GETGAMEGOLD_ACTION)
							|| action.equals(GETGAMEPROP_ACTION) || action.equals(GETGAMEDIAMOND_ACTION) 
							|| action.equals(SETGAMEDIAMOND_ACTION) || action.equals(GETGAMEPOWER_ACTION) 
							|| action.equals(SETGAMEPOWER_ACTION))
					{
						String ret = doaction(aData);
						return ret;
					}
					else
					{
						Message msg = mHandler.obtainMessage();
						msg.what = 0;
						msg.obj = aData;
						mHandler.sendMessage(msg);
					}

				}
			}
			catch (JSONException e)
			{
				e.printStackTrace();
			}

		}
		return "....";
	}

	static Handler mHandler = new Handler()
	{
		public void handleMessage(android.os.Message msg)
		{
			if (msg.what == 0)
			{
				String adata = (String) msg.obj;
				doaction(adata);
			}
		}
	};

	private static String doaction(String aData)
	{

		if (aData != null && aData.length() > 0)
		{
			try
			{
				Log.i("CallSDK", aData);

				JSONObject tData = new JSONObject(aData);
				String action = tData.getString("action");

				if (action != null)
				{
					if (action.equals(LOGIN_ACTION))
					{
						String type = tData.getString("type");
						BnLogin(type);
					}
					else if (action.equals(GETLOGINSTATUS_ACTION))
					{
						String ret = BnGetLoginStatus();;
						return ret;
					}
					else if (action.equals(FINISHGAME_ACTION))
					{
						String score = tData.getString("score");
						String gold = tData.getString("gold");
						String baseStr = tData.getString("baseStr");
						String gamedata = tData.getString("gamedata");
						BnFinishGame(score,gamedata,gold, baseStr);

					}
					else if (action.equals(SHOWGAMEHOME_ACTION))
					{
						BnShowGameHome();
					}
					else if (action.equals(GETPROFILE_ACTION))
					{
						return BnGetProfile();
					}
					else if (action.equals(GETMUSICONSTATUS_ACTION))
					{
						return BnGetMusicOnStatus();
					}
					else if (action.equals(GETSOUNDONSTATUS_ACTION))
					{
						return BnGetSoundOnStatus();
					}
					else if (action.equals(HIDESDK_ACTION))
					{
						BnHideSDK();
					}
					else if (action.equals(SETGAMEGOLD_ACTION))
					{
						String gold = tData.getString("gold");
						return BnSetGameGold(Integer.parseInt(gold));
					}

					else if (action.equals(GETGAMEGOLD_ACTION))
					{
						return BnGetGameGold();
					}
					else if (action.equals(SHOWSHOPVIEW_ACTION))
					{
						String page = tData.getString("page");
						int fpage = Integer.parseInt(page);
						showStoreView(fpage);
					}
					else if (action.equals(SETGAMEPROPSAVE_ACTION))
					{
						String prop = tData.getString("prop");
						BnSetGamePropSave(prop);
					}
					else if (action.equals(GETGAMEPROP_ACTION))
					{
						return BnGetGameProp();
					}
					else if(action.equals(GETGAMEDIAMOND_ACTION))
					{
						return BnGetGameDiamond();
					}
					else if(action.equals(SETGAMEDIAMOND_ACTION))
					{
						String diamond = tData.getString("diamond");
						return BnSetGameDiamond(Integer.parseInt(diamond));
					}
					else if(action.equals(GETGAMEPOWER_ACTION) )
					{
						return BnGetGamePowe();
					}
					else if(action.equals(SETGAMEPOWER_ACTION))
					{
						String power = tData.getString("power");
						return BnSetGamePower(Integer.parseInt(power));
					}
					
					else
					{
						Log.i("error", "Have no this interface !");
					}
				}
				else
				{
					Log.i("CallSDK", "action is null !");
				}

			}
			catch (JSONException e)
			{
				e.printStackTrace();
			}
		}

		return null;
	}

	// 初始化战网
	public static void init(Activity aContext)
	{
		bnApi = BattleNetApi.BnInitEngine(aContext);
		PackageInfo pinfo = null;
		try
		{
			pinfo = aContext.getPackageManager().getPackageInfo(aContext.getPackageName(),
					PackageManager.GET_CONFIGURATIONS);
		}
		catch (NameNotFoundException e)
		{
			e.printStackTrace();
		}
		setConfig(aContext, pinfo);
		bnApi.setBattleNetDataListener(aBattleNetCallback, null);
	}


	// 登陆(type:1 friendou 2 新浪 3腾讯)
	public static void BnLogin(String type)
	{
		int ftype = Integer.parseInt(type);
        bnApi.BnLogin(null, ftype);
//		bnApi.BnLogin(ftype);
	}

	public static String BnGetLoginStatus()
	{
		String loginStr = "";
		Boolean loginstatu = bnApi.BnGetLoginStatus();
		if (loginstatu)
		{
			loginStr = "YES";
		}
		else
		{
			loginStr = "NO";
		}
		return loginStr;
	}

	// 重新打开首页（比如回放之后，重新调这个接口）
	public static void BnShowGameHome()
	{
		bnApi.BnShowGameHome();
	}

	// 隐藏SDK
	public static void BnHideSDK()
	{
		bnApi.hideSDK();
	}

	// 结束游戏
	public static void BnFinishGame(String score, String gamedata, String gold, String baseStr)
	{
		int fscore = Integer.parseInt(score);
		int fgold = Integer.parseInt(gold);
		bnApi.BnFinishGame(fscore, gamedata, fgold, baseStr, "");
	}

	// 结束游戏
	public static void BnGameOver(String score, String gold, String desc1)
	{
		int fscore = Integer.parseInt(score);
		int fgold = Integer.parseInt(gold);
		bnApi.gameOver(fscore, fgold, desc1);
	}

	// 获取用户信息
	public static String BnGetProfile()
	{
		return bnApi.BnGetProfile();
	}

	// 获取音乐开关状态
	public static String BnGetMusicOnStatus()
	{
		String music = "";
		Boolean musicStatus = bnApi.BnGetMusicOnStatus();
		if (musicStatus)
		{
			music = "YES";
		}
		else
		{
			music = "NO";
		}
		return music;
	}

	// 获取音效开关状态
	public static String BnGetSoundOnStatus()
	{
		String sound = "";
		Boolean soundStatus = bnApi.BnGetSoundOnStatus();
		if (soundStatus)
		{
			sound = "YES";
		}
		else
		{
			sound = "NO";
		}
		return sound;
	}

	// 增加或减少金币
	public static String BnSetGameGold(int gold)
	{
		String Result = "";
		boolean result = bnApi.setGameGold(gold);
		if (result)
		{
			Result = "YES";
		}
		else
		{
			Result = "NO";
		}
		return Result;
	}

	public static String BnGetGameGold()
	{
		int GoldNum = bnApi.BnGetGameGold();
		return String.valueOf(GoldNum);
	}

	// page:1、爱心 2、金币 3、钻石
	public static void showStoreView(int page)
	{
		bnApi.BnShowShopView(page);
	}

	// 道具保存
	public static void BnSetGamePropSave(String prop)
	{
		bnApi.setGamePropSave(prop);
	}

	// 获取道具
	public static String BnGetGameProp()
	{
		return bnApi.getGameProp();
	}

	public static String BnGetGameDiamond()
	{
		int Diamond = bnApi.getGameDiamond();
		return String.valueOf(Diamond);
	}

	public static String BnSetGameDiamond(int diamond)
	{
		String Result = "";
		boolean result =  bnApi.setGameDiamond(diamond);
		if (result)
		{
			Result = "YES";
		}
		else
		{
			Result = "NO";
		}
		return Result;
	}

	public static String BnGetGamePowe()
	{
		int GamePowe = bnApi.getGamePowe();
		return String.valueOf(GamePowe);
	}

	public static String BnSetGamePower(int power)
	{
		String Result = "";
		boolean result = bnApi.setGamePower(power);
		if (result)
		{
			Result = "YES";
		}
		else
		{
			Result = "NO";
		}
		return Result;
	}

	// 回调
	// 参加游戏的人员回调,参数userlist数据内容包括:userkey(string),username(string),gamescore(string),gamedata(string)
	public static void BnGameUserSelectedNotification(final List<JSONObject> userlist)
	{
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable()
		{
			@Override
			public void run()
			{
				try
				{
					JSONObject t = new JSONObject();
					t.put("action", "1001");
					// String s = userlist.toString();
					t.put("userlist", userlist);
					SendtoGame(t.toString());
				}
				catch (JSONException e)
				{
					e.printStackTrace();
				}
			}
		});
	}

	// 回放回调（userlist:userkey,username,gamescore,gamedata）
	public static void BnGameReplayNotification(final List<JSONObject> userlist)
	{
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable()
		{
			@Override
			public void run()
			{

				try
				{
					JSONObject t = new JSONObject();
					t.put("action", "1002");
					// String s = userlist.toString();
					t.put("userlist", userlist);
					SendtoGame(t.toString());
				}
				catch (JSONException e)
				{
					e.printStackTrace();
				}
			}
		});
	}

	// 退出登陆通知
	public static void BnLogoutNotification()
	{
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable()
		{
			@Override
			public void run()
			{

				try
				{
					JSONObject t = new JSONObject();
					t.put("action", "1003");
					// String s = userlist.toString();
					SendtoGame(t.toString());
				}
				catch (JSONException e)
				{
					e.printStackTrace();
				}
			}
		});

	}

	// 音乐开关通知
	public static void BnMusicTurnOffAndOn(final boolean isOn)
	{
		try
		{
			JSONObject t = new JSONObject();
			t.put("action", "1004");
			t.put("isOn", isOn);
			SendtoGame(t.toString());
		}
		catch (JSONException e)
		{
			e.printStackTrace();
		}

	}

	// 音效开关通知
	public static void BnSoundTurnOffAndOn(boolean isOn)
	{
		try
		{
			JSONObject t = new JSONObject();
			t.put("action", "1005");
			t.put("isOn", isOn);
			SendtoGame(t.toString());
		}
		catch (JSONException e)
		{
			e.printStackTrace();
		}
	}

	// 登陆回调:1为登陆成功，2为失败，3为取消登录
	public static void BnLoginResult(final int isLogin)
	{
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable()
		{
			@Override
			public void run()
			{
				JSONObject t = new JSONObject();
				try
				{
					t.put("action", "1006");
					t.put("isLogin", isLogin);
					SendtoGame(t.toString());
				}
				catch (JSONException e)
				{
					e.printStackTrace();
				}
			}
		});
	}

	// 游戏结束后返回按键回调
	public static void BnGameBackNotification()
	{
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable()
		{
			@Override
			public void run()
			{
				JSONObject t = new JSONObject();
				try
				{
					t.put("action", "1007");
					SendtoGame(t.toString());
				}
				catch (JSONException e)
				{
					e.printStackTrace();
				}
			}
		});

	}

	// 切到后台回调 1008
	public static void BnApplicationWillResignActive()
	{
		try
		{
			JSONObject t = new JSONObject();
			t.put("action", "1008");
			SendtoGame(t.toString());
		}
		catch (JSONException e)
		{
			e.printStackTrace();
		}
	}

	// Andorid Call Cocos2d 回调
	public static native void SendtoGame(String aInfo); 

}
