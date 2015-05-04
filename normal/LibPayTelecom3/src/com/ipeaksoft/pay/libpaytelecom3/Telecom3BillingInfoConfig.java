package com.ipeaksoft.pay.libpaytelecom3;

import java.util.HashMap;

import android.util.SparseArray;
import cn.egame.terminal.paysdk.EgamePay;

import com.ipeaksoft.pay.BillingInfoConfig;

/**
 * @author jinjia.peng
 * 
 *         中国电信（3网）——计费信息
 * 
 */
public class Telecom3BillingInfoConfig extends BillingInfoConfig<HashMap<String, String>> {

	private static final Telecom3BillingInfoConfig mChinaNetPayInfoConfig = new Telecom3BillingInfoConfig();
	public static Telecom3BillingInfoConfig getInstance() {
		return mChinaNetPayInfoConfig;
	}
	
	@Override
	protected void initBillingInfo(SparseArray<HashMap<String, String>> billingInfoConfig) {
		HashMap<String, String> payInfo1 = new HashMap<String, String>();
		payInfo1.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL1");
		payInfo1.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "金币20000");
		billingInfoConfig.put(1001, payInfo1);

		HashMap<String, String> payInfo2 = new HashMap<String, String>();
		payInfo2.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL2");
		payInfo2.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "金币60000");
		billingInfoConfig.put(1002, payInfo2);

		HashMap<String, String> payInfo3 = new HashMap<String, String>();
		payInfo3.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL3");
		payInfo3.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "金币100000");
		billingInfoConfig.put(1003, payInfo3);

		HashMap<String, String> payInfo4 = new HashMap<String, String>();
		payInfo4.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL4");
		payInfo4.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "1000发幽光弹");
		billingInfoConfig.put(1004, payInfo4);
		
		HashMap<String, String> payInfo5 = new HashMap<String, String>();
		payInfo5.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL5");
		payInfo5.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "海盗宝石箱");
		billingInfoConfig.put(1005, payInfo5); 
		
		HashMap<String, String> payInfo6 = new HashMap<String, String>();
		payInfo6.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL6");
		payInfo6.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "解锁珍珠贝");
		billingInfoConfig.put(1006, payInfo6);

		HashMap<String, String> payInfo7 = new HashMap<String, String>();
		payInfo7.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL7");
		payInfo7.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "金币150000");
		billingInfoConfig.put(1007, payInfo7);

		HashMap<String, String> payInfo8 = new HashMap<String, String>();
		payInfo8.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL8");
		payInfo8.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "激活旋风鱼刀");
		billingInfoConfig.put(1008, payInfo8);

		HashMap<String, String> payInfo9 = new HashMap<String, String>();
		payInfo9.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL9");
		payInfo9.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "能量爆发");
		billingInfoConfig.put(1010, payInfo9);
		
		HashMap<String, String> payInfo10 = new HashMap<String, String>();
		payInfo10.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL10");
		payInfo10.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "渔炮大礼包");
		billingInfoConfig.put(1011, payInfo10); 
		
		HashMap<String, String> payInfo11 = new HashMap<String, String>();
		payInfo11.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL11");
		payInfo11.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "VIP卡");
		billingInfoConfig.put(1012, payInfo11);

		HashMap<String, String> payInfo12 = new HashMap<String, String>();
		payInfo12.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL12");
		payInfo12.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "升级礼包");
		billingInfoConfig.put(1013, payInfo12);

		HashMap<String, String> payInfo13 = new HashMap<String, String>();
		payInfo13.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL13");
		payInfo13.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "人鱼献礼");
		billingInfoConfig.put(1014, payInfo13);

		HashMap<String, String> payInfo14 = new HashMap<String, String>();
		payInfo14.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL14");
		payInfo14.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "军火库");
		billingInfoConfig.put(1015, payInfo14);
		
		HashMap<String, String> payInfo15 = new HashMap<String, String>();
		payInfo15.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "TOOL15");
		payInfo15.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "补充金币");
		billingInfoConfig.put(1009, payInfo15); 
	}

}
