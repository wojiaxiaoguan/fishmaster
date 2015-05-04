package com.ipeaksoft.ad.factory;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import android.content.Context;

import com.ipeaksoft.ad.Ad;
import com.ipeaksoft.ad.AdListener;
import com.ipeaksoft.ad.BannerAd;
import com.ipeaksoft.ad.IntegralWall;
import com.ipeaksoft.ad.IntegralWall.OnExchangeListener;

/**
 * @author jinjia.peng
 * 
 *         广告实例创建工厂
 * 
 */
public class AdInstanceFactory {

	private AdInstanceFactory() {
	}
	
	/**
	 * 获取广告实例
	 * 
	 * @param context 上下文
	 * @param fullClassName 全类名
	 * @return
	 */
	public static Ad newAdInstance(Context context, String fullClassName) {
		Ad ad = null;
		try {
			Class<?> cls = Class.forName(fullClassName);
			Constructor<?>[] cons = cls.getConstructors();
			ad = (Ad) cons[0].newInstance(context);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return ad;
	}

	/**
	 * 获取广告实例
	 * 
	 * @param context 上下文
	 * @param fullClassName 全类名
	 * @param adListener 广告监听器
	 * @return
	 */
	public static Ad newAdInstance(Context context, String fullClassName, AdListener adListener) {
		Ad ad = null;
		try {
			Class<?> cls = Class.forName(fullClassName);
			Constructor<?>[] cons = cls.getConstructors();
			ad = (Ad) cons[1].newInstance(context, adListener);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return ad;
	}
	
	/**
	 * 获取积分墙实例
	 * 
	 * @param context 上下文
	 * @param fullClassName 全类名
	 * @param exchangeListener 积分兑换监听器
	 * @return
	 */
	public static IntegralWall newIntergralWallInstance(Context context, String fullClassName, OnExchangeListener exchangeListener) {
		IntegralWall integrallWall = null;
		try {
			Class<?> cls = Class.forName(fullClassName);
			Constructor<?>[] cons = cls.getConstructors();
			integrallWall = (IntegralWall) cons[0].newInstance(context, exchangeListener);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return integrallWall;
	}
	
	/**
	 * 获取横幅广告实例
	 * 
	 * @param context 上下文
	 * @param fullClassName 横幅广告全类名
	 * @return
	 */
	public static BannerAd newBannerAdInstance(Context context, String fullClassName) {
		BannerAd bannerAd = null;
		try {
			Class<?> cls = Class.forName(fullClassName);
			Constructor<?>[] cons = cls.getConstructors();
			bannerAd = (BannerAd) cons[0].newInstance(context);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return bannerAd;
	}
	
	/**
	 * 获取横幅广告实例
	 * 
	 * @param context 上下文
	 * @param fullClassName 横幅广告全类名
	 * @param adListener
	 * @return
	 */
	public static BannerAd newBannerAdInstance(Context context, String fullClassName, AdListener adListener) {
		BannerAd bannerAd = null;
		try {
			Class<?> cls = Class.forName(fullClassName);
			Constructor<?>[] cons = cls.getConstructors();
			bannerAd = (BannerAd) cons[1].newInstance(context, adListener);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return bannerAd;
	}
}
