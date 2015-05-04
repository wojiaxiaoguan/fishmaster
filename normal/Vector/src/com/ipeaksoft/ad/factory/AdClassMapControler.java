package com.ipeaksoft.ad.factory;

import java.util.HashMap;
import java.util.Map;

import com.ipeaksoft.ad.constant.AdFullClassName;
import com.ipeaksoft.ad.constant.AdPlatformName;

/**
 * @author jinjia.peng
 * 
 *         广告类名映射器
 */
public class AdClassMapControler {
	
	/**
	 * 广告类名映射表
	 */
	private static final Map<String, String> mAdFullClassName;
	static {
		mAdFullClassName = new HashMap<String, String>();
		mAdFullClassName.put(AdPlatformName.BAIDU, AdFullClassName.AD_BAIDU);
		mAdFullClassName.put(AdPlatformName.DOMOB, AdFullClassName.AD_DOMOB);
		mAdFullClassName.put(AdPlatformName.WANDOUJIA, AdFullClassName.AD_WANDOUJIA);
		mAdFullClassName.put(AdPlatformName.GDT, AdFullClassName.AD_GDT);
		mAdFullClassName.put(AdPlatformName.ANWO, AdFullClassName.AD_ANWO);
		mAdFullClassName.put(AdPlatformName.AD_4399, AdFullClassName.AD_4399);
		mAdFullClassName.put(AdPlatformName.FEIWO, AdFullClassName.AD_FEIWO);
		mAdFullClassName.put(AdPlatformName.YOUMI, AdFullClassName.AD_YOUMI);
		mAdFullClassName.put(AdPlatformName.AD_360, AdFullClassName.AD_360);
		mAdFullClassName.put(AdPlatformName.WAPS, AdFullClassName.AD_WAPS);
		mAdFullClassName.put(AdPlatformName.MUMAYI, AdFullClassName.AD_MUMAYI);
		mAdFullClassName.put(AdPlatformName.MV, AdFullClassName.AD_MV);
		mAdFullClassName.put(AdPlatformName.ADSMOGO, AdFullClassName.AD_ADSMOGO);
		mAdFullClassName.put(AdPlatformName.AD_COCOA, AdFullClassName.AD_ADCOCOA);
		mAdFullClassName.put(AdPlatformName.BAYI, AdFullClassName.BAYI);
        mAdFullClassName.put(AdPlatformName.CHANCE, AdFullClassName.IW_AD_CHANCE);
        mAdFullClassName.put(AdPlatformName.SAGE, AdFullClassName.AD_SAGE);
	}
	
	/**
	 * 积分墙广告类名映射表
	 */
	private static final Map<String, String> mIWFullClassName;
	static {
		mIWFullClassName = new HashMap<String, String>();
		mIWFullClassName.put(AdPlatformName.AD_360, AdFullClassName.IW_360);
		mIWFullClassName.put(AdPlatformName.AD_4399, AdFullClassName.IW_4399);
		mIWFullClassName.put(AdPlatformName.AD_91, AdFullClassName.IW_91_DIANJIN);
		mIWFullClassName.put(AdPlatformName.ANWO, AdFullClassName.IW_ANWO);
		mIWFullClassName.put(AdPlatformName.DOMOB, AdFullClassName.IW_DOMOB);
		mIWFullClassName.put(AdPlatformName.YOUMI, AdFullClassName.IW_YOUMI);
		mIWFullClassName.put(AdPlatformName.YQB, AdFullClassName.IW_YQB);
		mIWFullClassName.put(AdPlatformName.WAPS, AdFullClassName.IW_WAPS);
		mIWFullClassName.put(AdPlatformName.MUMAYI, AdFullClassName.IW_MUMAYI);
		mIWFullClassName.put(AdPlatformName.MOBILE7, AdFullClassName.IW_MOBILE7);
		mIWFullClassName.put(AdPlatformName.AD_COCOA, AdFullClassName.IW_AD_COCOA);
	}

	/**
	 * 横幅广告类名映射表
	 */
	private static final Map<String, String> mBannerAdFullClassName;
	static {
		mBannerAdFullClassName = new HashMap<String, String>();
		mBannerAdFullClassName.put(AdPlatformName.YOUMI, AdFullClassName.BANNER_YOUMI);
	}
	
	private AdClassMapControler() {
	}

	/**
	 * 获取广告类名
	 * 
	 * @param adPlatformName 广告平台名
	 * @return
	 */
	public static String getAdFullClassName(String adPlatformName) {
		return mAdFullClassName.get(adPlatformName);
	}

	/**
	 * 获取积分墙类名
	 * 
	 * @param adPlatfromName 广告平台名
	 * @return
	 */
	public static String getIWFullClassName(String adPlatfromName) {
		return mIWFullClassName.get(adPlatfromName);
	}
	
	/**
	 * 获取横幅广告实例
	 * 
	 * @param adPlatfromName 广告平台名
	 * @return
	 */
	public static String getBannerClassName(String adPlatfromName) {
		return mBannerAdFullClassName.get(adPlatfromName);
	}
}
