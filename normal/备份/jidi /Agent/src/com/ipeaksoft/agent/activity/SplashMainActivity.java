package com.ipeaksoft.agent.activity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import com.ipeaksoft.agent.other.BaiDuPropaganda;
//import com.unicom.dcLoader.welcomeview;

public class SplashMainActivity extends Activity{

private final static int DELAY_MILLIS = 1500;
	
	protected Context mContext;
	
	//默认入口
	
	public static String packageName = null;
	public static String versionName = null;
	public static int versionCode = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		//百度品宣初始化
		BaiDuPropaganda.getInstance().initSplashActivity(this);
	}
	
	
	@Override
	protected void onPause() {
		super.onPause();
	}
	
	 public void runActivity(String pActivity,String pActivityDefault){
	    	//判断入口
	    	String pString = pActivity;//"com.unicom.dcLoader.welcomeview";
	    	Class<?> pClass = null;
			try {
				pClass = Class.forName(pActivityDefault);
			} catch (ClassNotFoundException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
	    	System.out.println("初始化：启动活动");
			try {
				//联通判断入口 cn.cmgame.billing.api.GameOpenActivity com.unicom.dcLoader.welcomeview
				if(Class.forName(pString) != null)
				{
					System.out.println("初始化：进入新活动");
					pClass = Class.forName(pString);
				}
			} catch (ClassNotFoundException e) {
				System.out.println("初始化：活动不存在-" + e.getMessage()+"_"+e.toString());
				e.printStackTrace();
			}

			Intent intent = new Intent(SplashMainActivity.this,pClass);
			startActivity(intent);
			overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out);
			SplashMainActivity.this.finish();
	}
	
	@Override
	protected void onResume() {
		super.onResume();
	}
	
}
