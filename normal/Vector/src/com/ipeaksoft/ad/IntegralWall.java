package com.ipeaksoft.ad;

import android.content.Context;

/**
 * @author jinjia.peng
 * 
 *         积分墙
 */
public abstract class IntegralWall extends Ad {

	/**
	 * @author jinjia.peng
	 * 
	 *         积分兑换监听器
	 */
	public interface OnExchangeListener {

		/**
		 * 积分兑换回调函数
		 * 
		 * @param integral 积分
		 * 
		 */
		public void onExchange(int integral);

	}

	/**
	 * 积分兑换监听器
	 */
	protected OnExchangeListener mExchangeListener;

	/**
	 * 积分构造方法
	 * 
	 * @param context
	 *            上下文件
	 * @param exchangeListener
	 *            积分兑换监听器
	 */
	public IntegralWall(Context context, OnExchangeListener exchangeListener) {
		super(context);
		mExchangeListener = exchangeListener;
	}

	/**
	 * 同步积分墙积分
	 */
	public abstract void syncIntegral();

}
