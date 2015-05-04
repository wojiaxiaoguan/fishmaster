package com.ipeaksoft.ad.manager;

import java.util.HashMap;
import java.util.Map.Entry;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.ipeaksoft.ad.IntegralWall;
import com.ipeaksoft.ad.IntegralWall.OnExchangeListener;
import com.ipeaksoft.ad.factory.AdClassMapControler;
import com.ipeaksoft.ad.factory.AdInstanceFactory;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         积分墙管理器
 */
public final class IntegralWallManager {

	private static final IntegralWallManager mSingleInstance = new IntegralWallManager();
	
	/**
	 * 获取积分墙管理器单例
	 * 
	 * @return
	 */
	public static IntegralWallManager getInstance() {
		return mSingleInstance;
	}
	
	private Context mContext;
	private final HashMap<String, IntegralWall> mIWList;
	
	/**
	 * 是否已经完成初始化
	 */
	private boolean mIsInitialized;
	
	private IntegralWallManager() {
		mIWList = new HashMap<String, IntegralWall>();
		mIsInitialized = false;
	}
	
	/**
	 * 初始化积分墙配置
	 * 
	 * @param context 上下文
	 * @param iwConfig 积分墙配置
	 * @param exchangeListener 积分兑换监听器
	 * @return 
	 */
	public void init(Context context, String integralWallConfig, OnExchangeListener exchangeListener) {
		if (mIsInitialized) {
			return;
		}
		
		mIsInitialized = true;
		mContext = context;
		
		try {
			JSONArray adList = new JSONArray(integralWallConfig);
			
			for (int i = 0; i < adList.length(); ++i) {
				JSONObject item = adList.getJSONObject(i);
				String platformName = item.getString("name");
				String fullClassName = AdClassMapControler.getIWFullClassName(platformName);
				
				if (!TextUtils.isEmpty(fullClassName)) {
					IntegralWall iw = AdInstanceFactory.newIntergralWallInstance(mContext, fullClassName, exchangeListener);
					
					if (iw != null) {
						mIWList.put(platformName, iw);
						Log.i(AppConfig.TAG, "add weight intergral wall instance: " + fullClassName);
					}
				}
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 打开指定积分墙
	 * 
	 * @param platformName 积分墙平台名
	 */
	public void show(String platformName) {
		IntegralWall iw = mIWList.get(platformName);
		if (iw != null) {
			iw.show();
		}
	}
	
	/**
	 * 打开指定的积分墙
	 * 
	 * @param index 积分墙实体集列表某一个
	 */
	public void show(int index) {
		int i = 0;
		for (Entry<String, IntegralWall> entry : mIWList.entrySet()) {
			if (i == index) {
				entry.getValue().show();
				break;
			}
			++i;
		}
	}

	/**
	 * 兑换积分
	 */
	public void exchange() {
		for (Entry<String, IntegralWall> entry : mIWList.entrySet()) {
			entry.getValue().syncIntegral();
		}
	}
	
	/**
	 * 销毁积分墙实体集
	 */
	public void destroy() {
		for (Entry<String, IntegralWall> entry : mIWList.entrySet()) {
			IntegralWall iw = entry.getValue(); 
			iw.destroy();
			iw = null;
		}
	}
}
