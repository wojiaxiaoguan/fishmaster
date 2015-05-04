package com.ipeaksoft.agent.other;

import java.lang.reflect.InvocationTargetException;

import com.ipeaksoft.other.BaiDuExtension;

import android.app.Activity;
import android.app.Application;
import android.content.Context;

public class BaiDuPropaganda {
	private static BaiDuPropaganda _instance;
	public static BaiDuPropaganda getInstance()
	{
		if(_instance == null)_instance = new BaiDuPropaganda();
		return _instance;
	}
	
	//百度单例
	private Object _rdk;
	private Boolean _bool = true;
	private BaiDuPropaganda()
	{
		Class<?> pClass;
		try {
			pClass = Class.forName("com.ipeaksoft.RDKSingle");
			_rdk = pClass.getMethod("getInstance").invoke(null);
		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			System.out.println("品，Class1"+e1.getMessage());
			e1.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			System.out.println("品，Class2"+e.getMessage());
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			System.out.println("品，Class3"+e.getMessage());
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			System.out.println("品，Class4"+e.getMessage());
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			System.out.println("品，Class5"+e.getMessage());
			e.printStackTrace();
		}
	}
	
	/** 执行退出 */
	public Boolean exit(Activity pActivity,Context pContext)
	{
		if(this.isAvailable()){
			System.out.println("品，调用退出品宣");
			((BaiDuExtension)_rdk).exit(pActivity, pContext);
			return true;
		}
		return false;
	}
	
	/** 执行暂停 */
	public void pause(Activity pActivity,Context pContext)
	{
		if(this.isAvailable()){
			System.out.println("品，暂停处理");
			((BaiDuExtension)_rdk).pause(pActivity, pContext);
		}
	}
	
	/** 执行初始化Application */
	public void initApplication(Application pApplication)
	{
		if(this.isAvailable()){
			System.out.println("品，调用Application品宣INIT");
			((BaiDuExtension)_rdk).onInitApplication(pApplication);
		}
	}
	
	/** 恢复 */
	public void onResume(Context mContext)
	{
		if(this.isAvailable()){
			System.out.println("品，恢复");
			((BaiDuExtension)_rdk).onResume(mContext);
		}
	}
	
	/** 暂停 */
	public void onPause(Context mContext)
	{
		if(this.isAvailable()){
			System.out.println("品，暂停");
			((BaiDuExtension)_rdk).onPause(mContext);
		}
	}
	
	/** 初始化启动页 */
	public void initSplashActivity(Activity pActivity)
	{
		if(this.isAvailable()){
			System.out.println("品，调用启动品宣INIT");
			((BaiDuExtension)_rdk).onInitStage(pActivity);
		}
	}
	
	/** 初始化主页 */
	public void initMainActivity(Activity pActivity)
	{
		if(this.isAvailable()){
			System.out.println("品，调用主页品宣INIT");
			((BaiDuExtension)_rdk).onInitSDK(pActivity);
		}
	}
	
	/** 是否可用 */
	public Boolean isAvailable()
	{
		return _rdk != null && _rdk instanceof BaiDuExtension && _bool;
	}
	
	/** 设置是否可用 */
	public void setAvailable(Boolean bool)
	{
		_bool = bool;
	}
}
