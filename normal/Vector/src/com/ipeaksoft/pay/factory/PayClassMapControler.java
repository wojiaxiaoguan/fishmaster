package com.ipeaksoft.pay.factory;

import java.util.HashMap;
import java.util.Map;

import com.ipeaksoft.pay.constant.PayFullClassName;
import com.ipeaksoft.pay.constant.PayPlatformName;

/**
 * @author jinjia.peng
 * 
 * 			支付平台名映射类名控制器
 *
 */
public class PayClassMapControler {

	private PayClassMapControler() {
	}
	
	/**
	 * 广告类名映射表
	 */
	private static final Map<String, String> mPayFullClassName;
	static {
		mPayFullClassName = new HashMap<String, String>();
		mPayFullClassName.put(PayPlatformName.MM, PayFullClassName.MM);
		mPayFullClassName.put(PayPlatformName.QIHOO_360, PayFullClassName.QIHOO_360);
		mPayFullClassName.put(PayPlatformName.UNICOM, PayFullClassName.UNICOM);
		mPayFullClassName.put(PayPlatformName.UNICOM_3, PayFullClassName.UNICOM_3);
		mPayFullClassName.put(PayPlatformName.TELECOM, PayFullClassName.TELECOM);
		mPayFullClassName.put(PayPlatformName.TELECOM_3, PayFullClassName.TELECOM_3);
		mPayFullClassName.put(PayPlatformName.ANZHI, PayFullClassName.ANZHI);
		mPayFullClassName.put(PayPlatformName.AND_GAME, PayFullClassName.CHINA_AND_GAME);
		mPayFullClassName.put(PayPlatformName.SY, PayFullClassName.SY);
	}

	/**
	 * 获取支付平台全类名
	 * 
	 * @param payPlatformName 支付平台名
	 * @return
	 */
	public static String getPayFullClassName(String payPlatformName) {
		return mPayFullClassName.get(payPlatformName);
	}
}
