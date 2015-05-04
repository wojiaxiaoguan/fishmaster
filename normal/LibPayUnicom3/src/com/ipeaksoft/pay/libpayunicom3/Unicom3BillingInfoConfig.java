package com.ipeaksoft.pay.libpayunicom3;

import android.util.SparseArray;

import com.ipeaksoft.pay.BillingInfoConfig;

/**
 * @author jinjia.peng
 * 
 * 			联通（3网）——计费信息
 *
 */
public class Unicom3BillingInfoConfig extends BillingInfoConfig<String>{

	private static final Unicom3BillingInfoConfig mConfig = new Unicom3BillingInfoConfig();
	public static Unicom3BillingInfoConfig getInstance() {
		return mConfig;
	}
	
	@Override
	protected void initBillingInfo(SparseArray<String> billingInfoConfig) {
		
				billingInfoConfig.put(1001, "001");//20000
				billingInfoConfig.put(1002, "002");//60000
				billingInfoConfig.put(1003, "003");//100000
				billingInfoConfig.put(1004, "004");//1000幽光弹
				billingInfoConfig.put(1005, "005"); //宝石各两颗
				
				billingInfoConfig.put(1006, "006");//珍珠贝
				billingInfoConfig.put(1007, "007");//150000
				billingInfoConfig.put(1008, "008");//旋风鱼刀

				billingInfoConfig.put(1009, "009");//快速购买100000
				billingInfoConfig.put(1010, "010"); //能量条
				
				billingInfoConfig.put(1011, "011");//解锁最大炮台			               
				billingInfoConfig.put(1012, "012");//VIP
				billingInfoConfig.put(1013, "013");//升级礼包
				billingInfoConfig.put(1014, "014");//嘻哈礼包
				billingInfoConfig.put(1015, "015"); //好6礼包

	}

}
