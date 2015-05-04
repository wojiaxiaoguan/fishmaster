package com.ipeaksoft.pay.libmmpay;

import android.util.SparseArray;

import com.ipeaksoft.pay.BillingInfoConfig;

/**
 * @author jinjia.peng
 * 
 *         MM 计费信息配置
 * 
 */
public class MMBillingInfoConfig extends BillingInfoConfig<String> {
	
	private static MMBillingInfoConfig mMMBillingInfoConfig = new MMBillingInfoConfig();
	public static MMBillingInfoConfig getInstance() {
		return mMMBillingInfoConfig;
	}

	@Override
	protected void initBillingInfo(SparseArray<String> billingInfoConfig) {
		
		System.out.println("进入计费信息配置方法");
		billingInfoConfig.put(1001, "30000899382901");//20000
		billingInfoConfig.put(1002, "30000899382902");//60000
		billingInfoConfig.put(1003, "30000899382903");//100000
		billingInfoConfig.put(1004, "30000899382904");//1000幽光弹
		billingInfoConfig.put(1005, "30000899382905"); //宝石各两颗
		
		billingInfoConfig.put(1006, "30000899382906");//珍珠贝
		billingInfoConfig.put(1007, "30000899382907");//150000
		billingInfoConfig.put(1008, "30000899382908");//旋风鱼刀

		billingInfoConfig.put(1009, "30000899382915");//快速购买100000
		billingInfoConfig.put(1010, "30000899382909"); //能量条
		
		billingInfoConfig.put(1011, "30000899382910");//解锁最大炮台			               
		billingInfoConfig.put(1012, "30000899382911");//VIP
		billingInfoConfig.put(1013, "30000899382912");//升级礼包
		billingInfoConfig.put(1014, "30000899382913");//人鱼献礼
		billingInfoConfig.put(1015, "30000899382914"); //军火库
		

	}

}
