package com.ipeaksoft.pay;

import android.text.TextUtils;
import android.util.SparseArray;

/**
 * @author jinjia.peng
 * 
 *         计费信息配置
 * @param <E> 具体类
 * 
 */
public abstract class BillingInfoConfig<E> {

	private final SparseArray<E> mBillingInfoConfig;
	
	public BillingInfoConfig() {
		mBillingInfoConfig = new SparseArray<E>();
		initBillingInfo(mBillingInfoConfig);
	}
	
	/**
	 * 初始化支付信息，添加计费点
	 */
	protected abstract void initBillingInfo(SparseArray<E> billingInfoConfig);

	/**
	 * 根据商品 id 值获取计费信息
	 * 
	 * @param id
	 * @return
	 */
	public E getBillingInfo(int id) {
		return mBillingInfoConfig.get(id);
	}

	/**
	 * 根据计费信息获取商品 id
	 * 
	 * @param billingInfo
	 * @return
	 */
	public int getIdByBillingInfo(E billingInfo) {
		int id = GoodsId.INVALID;
		
		for (int i = 0; i < mBillingInfoConfig.size(); ++i) {
			E value = mBillingInfoConfig.valueAt(i);

			if (billingInfo instanceof String) {
				if (TextUtils.equals((String) billingInfo, (String) value)) { // 比较字符串内容
					id = mBillingInfoConfig.keyAt(i);
					break;
				}
			} else {
				if (value == billingInfo) { // 比较是否引用同一对象
					id = mBillingInfoConfig.keyAt(i);
					break;
				}
			}
		}
		
		return id;
	}
}
