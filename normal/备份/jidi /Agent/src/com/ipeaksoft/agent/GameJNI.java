package com.ipeaksoft.agent;

/**
 * @author jinjia.peng
 * 
 *         游戏 JNI 层
 * 
 */
public class GameJNI {

	/**
	 * 添加金币
	 * 
	 * @param value
	 */
	public static native void addCoin(int value);

	/**
	 * @param isSuccess 是否购买成功
	 * @param id 商品Id
	 * @param channelId 支付渠道
	 */
	public static native void postPay(boolean isSuccess, int id, int channelId);
	
	/**
	 * 不可重复购买商品查询完成
	 *
	 * @param isSuccess 是否查询成功
	 * @param id 商品Id
	 */
	public static native void postPayQuery(boolean isSuccess, int id);
	
	/**
	 * 显示广告
	 */
	public static native void onShowAd();
	
	/**
	 * 关闭广告
	 */
	public static native void onDismissedAd();
	
	/**
	 * 设置音效状态
	 */
	public static native void setMusicEnabled(boolean isOpen);
	
	
	public static native void setChannel(String channel,int version);
	
}
