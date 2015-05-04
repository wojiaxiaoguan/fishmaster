package com.ipeaksoft.fishmaster;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

import com.ipeaksoft.agent.activity.SplashMainActivity;
import com.ipeaksoft.agent.taskhandler.PayTaskHandler;
import com.ipeaksoft.pay.constant.PayPlatformName;
import com.ipeaksoft.fishmaster.R;





public class SplashActivity extends SplashMainActivity {
	
	private final static int DELAY_MILLIS = 1500;
	
	private Context mContext;
	
	public static String packageName = null;
	public static String versionName = null;
	public static int versionCode = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		this.mContext = this;
		// 设置无标题
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		// 设置全屏
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		setContentView(R.layout.activity_splash);
		
		//更新在线配置
		
//		//友盟推送
//		PushAgent mPushAgent = PushAgent.getInstance(mContext);
//		mPushAgent.setDebugMode(false);
//		mPushAgent.enable();
//		Log.d("umeng_device_token", "======================" + UmengRegistrar.getRegistrationId(mContext));
		
//		// 统计应用启动数据
//		PushAgent.getInstance(mContext).onAppStart();
		
		//JPush推送
//		JPushInterface.setDebugMode(false);
//        JPushInterface.init(this);
		
		try {
			PackageInfo info = mContext.getPackageManager().getPackageInfo(mContext.getPackageName(), 0);
			packageName = info.packageName;
			versionName =  info.versionName;
			versionCode = info.versionCode;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			packageName = "com.ipeaksoft.pitDadGame2";
			versionName = "2.0.01";
		}
	}
	
	@Override
	protected void onPause() {
		super.onPause();
//		JPushInterface.onPause(this);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
//		JPushInterface.onResume(this);
//		JPushInterface.onResume(this);
		
		//定时任务，三秒后跳转
		TimerTask task = new TimerTask(){
		    public void run(){
		    	String pString = PayTaskHandler.getPayPlatformName(mContext);
		    	String pActivity = "com.ipeaksoft.fishmaster.fishmaster";
		    	if(pString == PayPlatformName.UNICOM || pString == PayPlatformName.UNICOM_3)
		    	{
					((SplashActivity)mContext).runActivity("com.unicom.dcLoader.welcomeview", pActivity);
		    	}
		    	else if(pString == PayPlatformName.AND_GAME)
		    	{
					((SplashActivity)mContext).runActivity("cn.cmgame.billing.api.GameOpenActivity", pActivity);
		    	}
		    	else
		    	{
		    		((SplashActivity)mContext).runActivity(pActivity, pActivity);
		    	}

		    }
		}; 
		Timer timer = new Timer(); 
		timer.schedule(task, DELAY_MILLIS); 
		
	}

}
