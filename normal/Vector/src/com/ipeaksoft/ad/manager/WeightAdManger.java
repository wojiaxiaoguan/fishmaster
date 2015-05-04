package com.ipeaksoft.ad.manager;

import java.util.ArrayList;
import java.util.Random;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.ipeaksoft.ad.Ad;
import com.ipeaksoft.ad.AdListener;
import com.ipeaksoft.ad.entity.AdWeight;
import com.ipeaksoft.ad.factory.AdClassMapControler;
import com.ipeaksoft.ad.factory.AdInstanceFactory;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         积分墙管理者
 */
public final class WeightAdManger {
	
	private static final WeightAdManger mWeightAdManager = new WeightAdManger();
	
	/**
	 * 获取权重广告管理器单例
	 * 
	 * @return
	 */
	public static WeightAdManger getInstance() {
		return mWeightAdManager;
	}
	
	private Context mContext;
	private final Random mRandom;
	private final ArrayList<AdWeight> mAdWeightDataList;
	private final ArrayList<Ad> mAdList;
	
	/**
	 * 广告权重总和
	 */
	private int mSumWeight;
	
	/**
	 * 是否已经初始化
	 */
	private boolean mIsInitialized;
	
	private WeightAdManger() {
		mRandom = new Random(System.currentTimeMillis());
		mAdWeightDataList = new ArrayList<AdWeight>();
		mAdList = new ArrayList<Ad>();
		mSumWeight = 0;
		mIsInitialized = false;
	}
	
	/**
	 * 初始化权重广告单例
	 * 
	 * @param context 上下文
	 * @param adConfig 广告配置
	 * @return 
	 */
	public void init(Context context, String adConfig) {
		System.out.println("进来inti");
		if (!mIsInitialized) {
			System.out.println("进来inti");
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
	 * 初始化权重广告单例
	 * 
	 * @param context 上下文
	 * @param adConfig 广告配置
	 * @param adListener 广告监听器
	 * @return
	 */
	public void init(Context context, String adConfig, AdListener adListener) {
		System.out.println("这是初始化判断之前");
		if (mIsInitialized) {
			return;
		}
		System.out.println("这是初始化判断之后");
		mIsInitialized = true;
		mContext = context;
		
		try {
			JSONArray adList = new JSONArray(adConfig);
			System.out.println("解析JSON"+adConfig);
			for (int i = 0; i < adList.length(); ++i) {
				final JSONObject item = adList.getJSONObject(i);
				final String adName = item.getString("name");
				System.out.println("name--------->"+adName);
				final int weight = item.getInt("weight");
				final String fullClassName = AdClassMapControler.getAdFullClassName(adName);	//	获取广告的全类名
				System.out.println("这是实例化判断之前");
				if (!TextUtils.isEmpty(fullClassName) && weight > 0) {	//	存在类名并且权重值大于0
					Ad ad = AdInstanceFactory.newAdInstance(mContext, fullClassName, adListener);
					
					System.out.println("这是实例化判断之前");
					if (ad != null) {	//	实例化成功，添加权广告实例集中，更新总权重值
						System.out.println("这是实例化判断后");
						mAdList.add(ad);
						mSumWeight += weight;
						mAdWeightDataList.add(new AdWeight(adName, weight));
						Log.i(AppConfig.TAG, "add weight ad instance: " + fullClassName);
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

		final int size = mAdWeightDataList.size();
		System.out.println("这是size:" + size);
		final int rand = mRandom.nextInt(mSumWeight);
		int currSumWeight = 0;
		Log.i(AppConfig.TAG, "rand num: " + rand);
		
		for (int i = 0; i < size; ++i) {
			AdWeight adWeight = mAdWeightDataList.get(i);
			
			if (rand >= currSumWeight && rand < (currSumWeight += adWeight.getWeight())) {	//	找到随机数在此区间内
				Log.i(AppConfig.TAG, "Weight Ad Name: " + adWeight.getAdName());
				
				if (mAdList.get(i).show() == false) {	//	此家广告展示失败，使用其它平台的广告展示
					System.out.println("这是show里面的循环");
					int j = (i + 1) % size;
					while (j != i && mAdList.get(j).show() == false) {	//	若广告实例集没有实例可成功展示广告或有广告实例成功展示广告，循环结束
						j = (j + 1) % size;
					}
				}
				break;
			}
		}
	}

	/**
	 * 销毁广告实例集
	 */
	public void destroy() {
		for (Ad ad : mAdList) {
			ad.destroy();
			ad = null;
		}
	}
}
