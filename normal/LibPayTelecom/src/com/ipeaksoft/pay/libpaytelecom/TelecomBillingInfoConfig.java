package com.ipeaksoft.pay.libpaytelecom;

import java.util.HashMap;

import android.util.SparseArray;
import cn.egame.terminal.paysdk.EgamePay;

import com.ipeaksoft.pay.BillingInfoConfig;

/**
 * @author jinjia.peng
 * 
 *         中国电信计费信息
 * 
 */
public class TelecomBillingInfoConfig extends BillingInfoConfig<HashMap<String, String>> {

	private static final TelecomBillingInfoConfig mChinaNetPayInfoConfig = new TelecomBillingInfoConfig();
	public static TelecomBillingInfoConfig getInstance() {
		return mChinaNetPayInfoConfig;
	}
	
	@Override
	protected void initBillingInfo(SparseArray<HashMap<String, String>> billingInfoConfig) {
		HashMap<String, String> payInfo1 = new HashMap<String, String>();
		payInfo1.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "5165724");
		payInfo1.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "一堆过关秘籍");
		billingInfoConfig.put(101, payInfo1);

		HashMap<String, String> payInfo2 = new HashMap<String, String>();
		payInfo2.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "5165722");
		payInfo2.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "少量小金鸭");
		billingInfoConfig.put(102, payInfo2);

		HashMap<String, String> payInfo3 = new HashMap<String, String>();
		payInfo3.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "5165723");
		payInfo3.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "大量小金鸭");
		billingInfoConfig.put(103, payInfo3);

		HashMap<String, String> payInfo4 = new HashMap<String, String>();
		payInfo4.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "5165726");
		payInfo4.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "幸运大礼包");
		billingInfoConfig.put(104, payInfo4);
		
		HashMap<String, String> payInfo5 = new HashMap<String, String>();
		payInfo5.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, "5165725");
		payInfo5.put(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC, "新手大礼包");
		billingInfoConfig.put(105, payInfo5); 
		
	}

}
