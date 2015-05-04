package com.ipeaksoft.agent.taskhandler;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.util.Log;

import com.ipeaksoft.ad.AdListener;
import com.ipeaksoft.ad.IntegralWall.OnExchangeListener;
import com.ipeaksoft.ad.manager.IntegralWallManager;
import com.ipeaksoft.ad.manager.WeightAdManger;
import com.ipeaksoft.agent.GameJNI;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         广告任务处理器
 * 
 */
public class AdTaskHandler {

	private static AdTaskHandler mSingleAdTask;

	/**
	 * 初始化广告任务
	 * 
	 * @param context
	 */
	public static AdTaskHandler init(Context context) {
		if (mSingleAdTask == null) {
			mSingleAdTask = new AdTaskHandler(context);
		}
		return mSingleAdTask;
	}

	/**
	 * 
	 * 获取广告任务实例
	 * 
	 * @return
	 */
	public static AdTaskHandler getInstance() {
		return mSingleAdTask;
	}

//	/**
//	 * 权重广告配置
//	 */
	private static final String AD_CONFIG = "[{'name':'ADList', 'weight':undefined},]";
    private static final String ADB_CONFIG = "";

//	/**
//	 * 积分墙配置
//	 */
//	private static final String INTEGRAL_WALL_CONFIG = "[ { \"name\": \"youmi\"}, { \"name\": \"ad4399\"} ]";

	private Context mContext;
	private OnExchangeListener mExchangeListener;
	private AdListener mAdListener;
	
	private AdTaskHandler(Context context) {
		mContext = context;
		
		mExchangeListener = new OnExchangeListener() {

			@Override
			public void onExchange(int integral) {
				Log.i(AppConfig.TAG, "add integral success, integral: " + integral);
				GameJNI.addCoin(integral);
			}
		};
		
		mAdListener = new AdListener() {
			
			@Override
			public void onShow() {
				Log.i(AppConfig.TAG, "show Ad");
				GameJNI.onShowAd();
			}
			
			@Override
			public void onDismissed() {
				Log.i(AppConfig.TAG, "dismissed Ad");
				GameJNI.onDismissedAd();
			}
		};
	}

	/**
	 * 处理广告任务
	 * 
	 * @param func
	 * @param params
	 */
	public void execAdTask(String func, JSONObject params) {
		if ("showInterstitialAd".equals(func)) { // 打开插屏广告
			
			WeightAdManger.getInstance().show();

		} else if ("openIntegralWall".equals(func)) { // 打开积分墙
			int wallNum = 0;
			try {
				wallNum = params.getInt("wallNum");
			} catch (JSONException e) {
				System.out.println("打开积分墙return了！");
				return;
			}
			System.out.println(wallNum);
			IntegralWallManager.getInstance().show(wallNum-1);
			
		} else if ("syncIntegral".equals(func)) { // 同步积分，兑换金币
			IntegralWallManager.getInstance().exchange();
		} else if ("showBannerAd".equals(func)) { // 打开横幅广告
			
		} else if ("closeBannerAd".equals(func)) { // 关闭横幅广告

		} else if ("initInterstitialAd".equals(func)) { // 初始化插屏广告
			
			System.out.println("初始化插屏广告~"+params.toString());
			//积分墙配置信息
			String AdConfig = "";
			try {
				AdConfig = params.getJSONArray("ADConfig").toString();
				if(params.getJSONArray("ADConfig").length() == 0){
					AdConfig = AD_CONFIG;
				}
			} catch (JSONException e) {
				System.out.println("初始化return了！");
				return;
			}
			System.out.println("Data:"+AdConfig);
			
			WeightAdManger.getInstance().init(mContext, AdConfig);

		} else if ("initInterstitialAdWithCallback".equals(func)) {	//	初始化化插屏广告，带回调
//			WeightAdManger.getInstance().init(mContext, AD_CONFIG, mAdListener);
			
		} else if ("initIntegralWall".equals(func)) { // 初始化积分墙
			System.out.println("初始化积分墙~");
			//积分墙配置信息
			String FreePanelConfig = "";
			try {
				FreePanelConfig = params.getJSONArray("wallConfig").toString();
			} catch (JSONException e) {
				System.out.println("初始化return了！");
				return;
			}
			System.out.println(FreePanelConfig);
			IntegralWallManager.getInstance().init(mContext, FreePanelConfig, mExchangeListener);

		} else if ("initBannerAd".equals(func)) {	//	初始化横幅广告
			
		} else if ("initBannerAdWithCallback".equals(func)) {	//	初始化横幅广告带广告监听器
			
		}
	}

	public void destroy() {
		IntegralWallManager.getInstance().destroy();
		WeightAdManger.getInstance().destroy();
		mSingleAdTask = null;
	}

}
