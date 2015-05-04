package com.ipeaksoft.vector;

import android.app.Application;

/**
 * @author jinjia.peng
 * 
 *         Application 控制器
 * 
 */
public class AppControler extends Application {

	private static AppControler mSingleton;
	
	public static AppControler getInstance() {
		return mSingleton;
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		mSingleton = this;
	}
	
}
