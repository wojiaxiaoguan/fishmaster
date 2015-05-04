package com.ipeaksoft.pay.constant;

/**
 * @author jinjia.peng
 * 
 *         支付渠道
 * 
 */
public interface PayChannel {

	/**
	 * 非法值
	 */
	public static final int INVALID = -1; 
	/**
	 * 支付宝
	 */
	public static final int ALIPAY = 2;
	/**
	 * 网银
	 */
	public static final int INTERNET_BANK = 3;
	/**
	 * 财付通
	 */
	public static final int TENPAY = 4;
	/**
	 * 移动通信
	 */
	public static final int CHINA_MOBILE = 5;
	/**
	 * 联通联信
	 */
	public static final int CHINA_UNICOM = 6;
	/**
	 * 电信通信
	 */
	public static final int CHINA_TELECOM = 7;
	/**
	 * PayPal
	 */
	public static final int PAY_PAL = 8;
	/**
	 * 中国移动——和游戏、游戏基地
	 */
	public static final int CHINA_AND_GAME = 9;
	/**
	 * 安智
	 */
	public static final int ANZHI = 10;
	/**
	 * 奇虎360
	 */
	public static final int QIHOO_360 = 11;
	/**
	 * 中国联通3网
	 */
	public static final int CHINA_UNICOM_3 = 12;
	/**
	 * 中国电信3网
	 */
	public static final int CHINA_TELECOM_3 = 13;
	/**
	 * 手游计费——广告港渞丰
	 */
	public static final int SY = 14;

}
