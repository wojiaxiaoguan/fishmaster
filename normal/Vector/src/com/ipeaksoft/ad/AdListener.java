package com.ipeaksoft.ad;

/**
 * @author jinjia.peng
 * 
 *         广告监听器
 * 
 */
public interface AdListener {

	/**
	 * 广告已经显示
	 */
	public void onShow();
	
	/**
	 * 广告已经关闭
	 */
	public void onDismissed();
	
}
