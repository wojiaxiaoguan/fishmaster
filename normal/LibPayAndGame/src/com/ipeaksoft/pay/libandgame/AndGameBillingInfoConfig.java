package com.ipeaksoft.pay.libandgame;

import android.util.SparseArray;

import com.ipeaksoft.pay.BillingInfoConfig;

/**
 * @author jinjia.peng
 * 
 *         中国游戏基地（和游戏）计费信息配置
 * 
 */
public class AndGameBillingInfoConfig extends BillingInfoConfig<String> {

	private static AndGameBillingInfoConfig mConfig = new AndGameBillingInfoConfig();
	
	public static AndGameBillingInfoConfig getInstance() {
		return mConfig;
	}

	@Override
	protected void initBillingInfo(SparseArray<String> billingInfoConfig) {
		
		billingInfoConfig.put(1001, "001");//5本秘籍
		billingInfoConfig.put(1002, "002");//25只小金鸭
		billingInfoConfig.put(1003, "003");//180只小金鸭
		billingInfoConfig.put(1004, "004");//幸运大礼包
		billingInfoConfig.put(1005, "005"); //新手大礼包
		
		billingInfoConfig.put(1006, "006");//5本秘籍
		billingInfoConfig.put(1007, "007");//25只小金鸭
		billingInfoConfig.put(1008, "008");//180只小金鸭
		billingInfoConfig.put(1009, "009");//幸运大礼包
		billingInfoConfig.put(1010, "010"); //新手大礼包
		
		billingInfoConfig.put(1011, "011");//5本秘籍
		billingInfoConfig.put(1012, "012");//25只小金鸭
		billingInfoConfig.put(1013, "013");//180只小金鸭
		billingInfoConfig.put(1014, "014");//幸运大礼包
		billingInfoConfig.put(1015, "015"); //新手大礼包
	
	}

}
