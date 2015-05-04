package com.ipeaksoft.pay.factory;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import android.content.Context;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;

/**
 * @author jinjia.peng
 * 
 * 			支付实例创建工厂
 *
 */
public class PayInstanceFactory {
	
	private PayInstanceFactory() {
	}

	/**
	 * 获取支付实例
	 * 
	 * @param context
	 * @param fullClassName
	 * @return
	 */
	public static Pay newPayInstance(Context context, String payPlatformName, OnPayListener onPayListener) {
		Pay ad = null;
		
		try {
			System.out.println("这是newPayInstance");
			String fullClassName = PayClassMapControler.getPayFullClassName(payPlatformName);
			System.out.println("PayInstance:"+fullClassName);
			Class<?> cls = Class.forName(fullClassName);
			Constructor<?>[] cons = cls.getConstructors();
			ad = (Pay) cons[0].newInstance(context, onPayListener);
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
}
