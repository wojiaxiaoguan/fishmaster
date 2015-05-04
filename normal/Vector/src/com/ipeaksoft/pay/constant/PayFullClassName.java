package com.ipeaksoft.pay.constant;

/**
 * @author jinjia.peng
 * 
 *         支付全类名
 * 
 */
public interface PayFullClassName {

	/**
	 * 移动 MM
	 */
	public static final String MM = "com.ipeaksoft.pay.libmmpay.MMPay";
	/**
	 * 奇虎360
	 */
	public static final String QIHOO_360 = "com.ipeaksoft.pay.libpay360.Qihoo360Pay";
	/**
	 * 联通（单网）
	 */
	public static final String UNICOM = "com.ipeaksoft.pay.libpayunicom.UnicomPay";
	/**
	 * 联通（3网）
	 */
	public static final String UNICOM_3 = "com.ipeaksoft.pay.libpayunicom3.Unicom3Pay";
	/**
	 * 电信
	 */
	public static final String TELECOM = "com.ipeaksoft.pay.libpaytelecom.TelecomPay";
	/**
	 * 电信（3网）
	 */
	public static final String TELECOM_3 = "com.ipeaksoft.pay.libpaytelecom3.Telecom3Pay";
	
	/**
	 * 安智
	 */
	public static final String ANZHI= "com.ipeaksoft.pay.libanzhipay.AnzhiPay";
	/**
	 * 中国移动——和游戏、游戏基地
	 */
	public static final String CHINA_AND_GAME = "com.ipeaksoft.pay.libandgame.AndGamePay";
	/**
	 * 手游计费——广洲渞丰
	 */
	public static final String SY = "com.ipeaksoft.pay.libsypay.SyPay";
}
