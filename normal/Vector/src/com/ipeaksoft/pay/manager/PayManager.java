package com.ipeaksoft.pay.manager;

import android.content.Context;
import android.util.Log;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;
import com.ipeaksoft.pay.factory.PayInstanceFactory;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         支付管理器
 * 
 */
public final class PayManager {

	private static Pay mPay;

	/**
	 * 根据支付平台获取支付实体
	 * 
	 * @param context 上下文
	 * @param payPlatformName 支付平台
	 * @param onPayListener 支付状态监听器
	 * @return
	 */
	public static Pay init(Context context, String payPlatformName, OnPayListener onPayListener) {
		if (mPay == null) {
			mPay = PayInstanceFactory.newPayInstance(context, payPlatformName, onPayListener);
			Log.i(AppConfig.TAG, "new pay instance!");
		}
		return mPay;
	}

	/**
	 * 获取支付实例
	 * 
	 * @return
	 */
	public static Pay getInstance() {
		return mPay;
	}
	
	/**
	 * 销毁资源
	 */
	public static void destroy() {
		if (mPay != null) {
			mPay.destroy();
			mPay = null;
		}
	}
	
}