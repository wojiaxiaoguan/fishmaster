package com.ipeaksoft.pay;

import android.content.Context;

/**
 * @author jinjia.peng
 * 
 *         支付接口
 */
public abstract class Pay {

	protected Context mContext;
	protected OnPayListener mOnPayListener;
	
	/**
	 * @param context 上下文
	 * @param onPayListener 支付状态监听器
	 */
	public Pay(Context context, OnPayListener onPayListener) {
		mContext = context;
		mOnPayListener = onPayListener;
		onInit();
	}
	
	/**
	 * 初始化
	 */
	protected abstract void onInit();
	
	/**
	 * 获取支付渠道
	 * 
	 * @return
	 */
	public abstract int getPayChannel();

	/**
	 * 根据 Id 购买该商品
	 * 
	 * @param id
	 */
	public abstract void pay(int id);
	
	/**
	 * 恢复购买功能
	 * 
	 * @param id
	 */
	public abstract void query(int id);

	/**
	 * 销毁资源
	 */
	public abstract void destroy();
	
}
