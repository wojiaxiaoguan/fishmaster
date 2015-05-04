package com.ipeaksoft.ad.manager;

import java.util.ArrayList;
import java.util.Random;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.ipeaksoft.ad.AdListener;
import com.ipeaksoft.ad.BannerAd;
import com.ipeaksoft.ad.entity.AdWeight;
import com.ipeaksoft.ad.factory.AdClassMapControler;
import com.ipeaksoft.ad.factory.AdInstanceFactory;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         横幅广告管理器
 * 
 */
public final class BannerAdManager {

	private static final BannerAdManager mBannerManager = new BannerAdManager();
	
	/**
	 * 获取横幅广告管理器单例
	 * 
	 * @return
	 */
	public static BannerAdManager getInstance() {
		return mBannerManager;
	}
	
	private Context mContext;
	private ArrayList<AdWeight> mAdWeightDataList;
	private ArrayList<BannerAd> mAdList;
	private Random mRandom;
	
	/**
	 * 是否已经初始化
	 */
	private boolean mIsInitialized;
	
	/**
	 * 广告权重总和
	 */
	private int mSumWeight;
	
	/**
	 * 当前mAdList 列表显示的BannerAd Index
	 */
	private int mCurrIndex;
	
	private BannerAdManager() {
		mAdWeightDataList = new ArrayList<AdWeight>();
		mAdList = new ArrayList<BannerAd>();
		mRandom = new Random(System.currentTimeMillis());
		mIsInitialized = false;
		mSumWeight = 0;
		mCurrIndex = -1;
	}
	
	/**
	 * 初始化权重广告实例列表
	 * 
	 * @param context 上下文
	 * @param adConfig 广告配置
	 */
	public void init(Context context, String adConfig) {
		if (!mIsInitialized) {
			this.init(context, adConfig, new AdListener() {
				
				@Override
				public void onShow() {
					Log.i(AppConfig.TAG, "adListener.ohShow() is empty!");
				}
				
				@Override
				public void onDismissed() {
					Log.i(AppConfig.TAG, "adListener.onDismissed() is empty!");
				}
			});
		}
	}
	
	/**
	 * 初始化权重广告实例列表
	 * 
	 * @param context 上下文
	 * @param adConfig 广告配置
	 * @param adListener 广告监听器
	 */
	public void init(Context context, String adConfig, AdListener adListener) {
		if (mIsInitialized) {
			return;
		}
		
		mIsInitialized = false;
		mContext = context;
		
		try {
			JSONArray adList = new JSONArray(adConfig);
			
			for (int i = 0; i < adList.length(); ++i) {
				final JSONObject item = adList.getJSONObject(i);
				final String adName = item.getString("name");
				final int weight = item.getInt("weight");
				final String fullClassName = AdClassMapControler.getBannerClassName(adName);	//	获取广告的全类名
				
				if (!TextUtils.isEmpty(fullClassName) && weight > 0) {
					BannerAd ad = AdInstanceFactory.newBannerAdInstance(mContext, fullClassName, adListener);
					
					if (ad != null) {
						mAdList.add(ad);
						mSumWeight += weight;
						mAdWeightDataList.add(new AdWeight(adName, weight));
						Log.i(AppConfig.TAG, "add weight BannerAd instance: " + fullClassName);
					}
				}
			}

		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 产生伪随机数，按权重显示广告
	 */
	public void show() {
		if (mSumWeight <= 0) {
			Log.i(AppConfig.TAG, "sum weight: 0");
			return;
		}
		
		int curSumWeight = 0;
		final int rand = mRandom.nextInt(mSumWeight);
		final int size = mAdWeightDataList.size();
		Log.i(AppConfig.TAG, "rand num: " + rand);
		
		for (int i = 0; i < size; ++i) {
			AdWeight adWeight = mAdWeightDataList.get(i);
			
			if (rand >= curSumWeight && rand < (curSumWeight += adWeight.getWeight())) {	//	找到随机数在此区间内
				Log.i(AppConfig.TAG, "Weight Banner Ad Name: " + adWeight.getAdName());
				
				if (mAdList.get(i).show() == false) {	//	此家广告展示失败，使用其它平台的广告展示
					int j = (i + 1) % size;
					while (j != i && mAdList.get(j).show() == false) {	//	若广告实例集没有实例可成功展示广告或有广告实例成功展示广告，循环结束
						j = (j + 1) % size;
					}
					
					if (j != i) {	//	成功展示横幅广告
						mCurrIndex = j;
					}
				} else {	//	成功展示横幅广告
					mCurrIndex = i;
				}
				
				break;
			}
		}
	}

	/**
	 * 移除横幅广告
	 */
	public void close() {
		if (mCurrIndex >= 0 && mCurrIndex < mAdList.size()) {
			mAdList.get(mCurrIndex).close();
			mCurrIndex = -1;
		}
	}
	
	/**
	 * 销毁广告集
	 */
	public void destroy() {
		for (BannerAd ad : mAdList) {
			ad.destroy();
			ad = null;
		}
	}
}
