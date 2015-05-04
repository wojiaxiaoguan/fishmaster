package com.ipeaksoft.pay.libpaytelecom;

import java.util.HashMap;
import java.util.Map;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;
import cn.egame.terminal.paysdk.EgamePay;
import cn.egame.terminal.paysdk.EgamePayListener;
import cn.egame.terminal.sdk.log.EgameAgent;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;
import com.ipeaksoft.pay.constant.PayChannel;
import com.ipeaksoft.vector.ActivityLifeCycle;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         中国电信
 * 
 */
public class TelecomPay extends Pay implements ActivityLifeCycle {

	private EgamePayListener mEgamePayListener;
	
	public TelecomPay(Context context, OnPayListener onPayListener) {
		super(context, onPayListener);
	}

	@Override
	protected void onInit() {
		
		System.out.println("电信单网的购买id：");
		EgamePay.init(mContext);
		mEgamePayListener = new EgamePayListener() {
			
			@Override
			public void paySuccess(Map<String, String> params) {
				int id = TelecomBillingInfoConfig.getInstance().getIdByBillingInfo((HashMap<String, String>) params);
				mOnPayListener.onPostPay(true, id);
				
				String msg = "道具" + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC) + "支付成功";
				msg += "\nalias: " + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
				Log.i(AppConfig.TAG, msg);
			}
			
			@Override
			public void payFailed(Map<String, String> params, int error) {
				int id = TelecomBillingInfoConfig.getInstance().getIdByBillingInfo((HashMap<String, String>) params);
				mOnPayListener.onPostPay(false, id);
				
				String msg = "道具" + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC) + "支付失败：错误代码：" + error;
				msg += "\nalias: " + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
				Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
				Log.i(AppConfig.TAG, msg);
			}
			
			@Override
			public void payCancel(Map<String, String> params) {
				String msg = "道具"+params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC)+"支付已取消";
				msg += "\nalias: " + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
				Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
				Log.i(AppConfig.TAG, msg);
			}
		};
		Log.i(AppConfig.TAG, "ChinaNetPay init!");
	}
	
	@Override
	public int getPayChannel() {
		return PayChannel.CHINA_TELECOM;
	}

	@Override
	public void pay(int id) {
		Log.i(AppConfig.TAG, "goods id: " + id);
		
		HashMap<String, String> billingInfo = TelecomBillingInfoConfig.getInstance().getBillingInfo(id);
		if (billingInfo != null) {
			Log.i(AppConfig.TAG, "payCode: " + billingInfo.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS));
			EgamePay.pay(mContext, billingInfo, mEgamePayListener);
			System.out.println("这是电信单网的支付pay");
		} else {
			Log.e(AppConfig.TAG, "billing info is null.");
		}
	}

	@Override
	public void query(int id) {
	}

	@Override
	public void destroy() {
	}

	@Override
	public void resume() {
		EgameAgent.onResume(mContext);
	}

	@Override
	public void activityResult(int requestCode, int resultCode, Intent data) {
	}

	@Override
	public void pause() {
		EgameAgent.onPause(mContext);
	}

}
