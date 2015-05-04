package com.ipeaksoft.pay;

/**
 * @author jinjia.peng
 * 
 * 
 *         支付监听器
 */
public interface OnPayListener {

	/**
	 * 购买完成回调
	 * 
	 * @param isSuccess 购买成功
	 * @param id 商品id
	 */
	public void onPostPay(boolean isSuccess, int id);

	/**
	 * 不可重复购买回调
	 * 
	 * @param isSuccess 查询成功 
	 * @param id 商品id
	 */
	public void onPostQuery(boolean isSuccess, int id);
}
