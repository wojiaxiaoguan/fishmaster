package com.ipeaksoft.agent.activity;

import java.lang.reflect.InvocationTargetException;

import android.app.Application;
import android.content.Context;

import com.ipeaksoft.agent.other.BaiDuPropaganda;
import com.ipeaksoft.agent.taskhandler.PayTaskHandler;
import com.ipeaksoft.pay.constant.PayPlatformName;

/**
 * @author jinjia.peng
 * 
 *         Game Application
 * 
 */
public class GameApplication extends Application {
	
	public void onCreate() {
		super.onCreate();
		
		Context pContext = this;
		
		//初始化百度品宣
		BaiDuPropaganda.getInstance().initApplication(this);
		
		System.out.println("初始化 Application");
		try {
			if(PayTaskHandler.getPayPlatformName(this) == PayPlatformName.AND_GAME)
			{
				System.out.println("初始化AndGame Application");
				System.loadLibrary("megjb");
			}
			
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			if(Class.forName("com.unicom.dcLoader.welcomeview") != null)
			{
				if(PayTaskHandler.getPayPlatformName(this) == PayPlatformName.UNICOM)
				{
					System.out.println("初始化Unicom Application");
					Class<?> pClass = Class.forName("com.ipeaksoft.pay.libpayunicom.UnicomPay");
					pClass.getMethod("initSDK",Context.class).invoke(null,pContext);
				}
				else if(PayTaskHandler.getPayPlatformName(this) == PayPlatformName.UNICOM_3)
				{
					System.out.println("初始化Unicom3 Application");
					System.loadLibrary("megjb");
					Class<?> pClass = Class.forName("com.ipeaksoft.pay.libpayunicom3.Unicom3Pay");
					pClass.getMethod("initSDK",Context.class).invoke(null, pContext);
				}
			}
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			System.out.println("初始化错误:"+e.getMessage()+"_"+e.toString());
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			System.out.println("初始化错误:"+e.getMessage()+"_"+e.toString());
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			System.out.println("初始化错误:"+e.getMessage()+"_"+e.toString());
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			System.out.println("初始化错误:"+e.getMessage()+"_"+e.toString());
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			System.out.println("初始化错误:"+e.getMessage()+"_"+e.toString());
			e.printStackTrace();
		}
		System.out.println("初始化结束");
	}

}
