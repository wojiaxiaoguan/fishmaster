package com.ipeaksoft.ad;

import android.content.Context;
import android.util.Log;

import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jijia.peng
 * 
 *         广告
 */
public abstract class Ad {

	protected Context mContext;
	protected AdListener mAdListener;
	
	/**
	 * @param context 上下文
	 */
	public Ad(Context context) {
		this(context, new AdListener() {
			
			@Override
			public void onShow() {
				Log.i(AppConfig.TAG, "adListener.ohShow() is empty!");
			}
			
			@Override
			public void onDismissed() {
				Log.i(AppConfig.TAG, "adListener.onDismissed() is empty!");
			}
		});
	}

	/**
	 * @param context 上下文
	 * @param adListener 广告状态监听器
	 */
	public Ad(Context context, AdListener adListener) {
		mContext = context;
		mAdListener = adListener;
		onInit();
	}
	
	/**
	 * 初始化广告
	 */
	protected abstract void onInit();

	/**
	 * 显示广告
	 * 
	 * @return 当成功显示广告，返回 true；广告未加载完成或其它原因未能显示广告，返回 false
	 */
	public abstract boolean show();

	/**
	 * 销毁广告
	 */
	public abstract void destroy();
}
