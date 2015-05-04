package com.ipeaksoft.pay.libpaytelecom3;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;
import cn.egame.terminal.paysdk.EgamePay;
import cn.egame.terminal.paysdk.EgamePayListener;
import cn.egame.terminal.sdk.log.EgameAgent;
import cn.play.dserv.CheckTool;
import cn.play.dserv.ExitCallBack;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;
import com.ipeaksoft.pay.PayExtraFeatures;
import com.ipeaksoft.pay.constant.PayChannel;
import com.ipeaksoft.vector.ActivityLifeCycle;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         中国电信3网
 * 
 */
public class Telecom3Pay extends Pay implements PayExtraFeatures, ActivityLifeCycle {

	private EgamePayListener mEgamePayListener;
	
	public Telecom3Pay(Context context, OnPayListener onPayListener) {
		super(context, onPayListener);
	}

	@Override
	protected void onInit() {
		System.out.println("Telecom3Pay oninit");
		EgamePay.init(mContext);
		System.out.println("Telecom3Pay oninit  end ");
		mEgamePayListener = new EgamePayListener() {
			
			@Override
			public void paySuccess(Map<String, String> params) {
				int id = Telecom3BillingInfoConfig.getInstance().getIdByBillingInfo((HashMap<String, String>) params);
				mOnPayListener.onPostPay(true, id);
				
				String msg = "道具" + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC) + "支付成功";
				msg += "\nalias: " + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
				Log.i(AppConfig.TAG, msg);
			}
			
			@Override
			public void payFailed(Map<String, String> params, int error) {
				int id = Telecom3BillingInfoConfig.getInstance().getIdByBillingInfo((HashMap<String, String>) params);
				mOnPayListener.onPostPay(false, id);
				
				String msg = "道具" + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC) + "支付失败：错误代码：" + error;
				
				Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
				msg += "\nalias: " + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
				Log.i(AppConfig.TAG, msg);
			}
			
			@Override
			public void payCancel(Map<String, String> params) {
				String msg = "道具"+params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_DESC) + "支付已取消";
				
				Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
				msg += "\nalias: " + params.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
				Log.i(AppConfig.TAG, msg);
			}
		};
		Log.i(AppConfig.TAG, "ChinaNetPay init!");
	}
	
	@Override
	public int getPayChannel() {
		return PayChannel.CHINA_TELECOM_3;
	}

	@Override
	public void pay(int id) {
		Log.i(AppConfig.TAG, "goods id: " + id);
		
		HashMap<String, String> billingInfo = Telecom3BillingInfoConfig.getInstance().getBillingInfo(id);
		if (billingInfo != null) {
			Log.i(AppConfig.TAG, "payCode: " + billingInfo.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS));
			EgamePay.pay(mContext, billingInfo, mEgamePayListener);
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
	public void openMoreGame() {
		//String msg = "更多游戏";
		
		//Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
		CheckTool.more(mContext);
		//msg = "更多游戏 结束了";
		
		//Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
	}

	@Override
	public void exit() {
		CheckTool.exit(mContext, new ExitCallBack() {
			
			@Override
			public void exit() {
				((Activity) mContext).finish();
				System.exit(0);
			}
			
			@Override
			public void cancel() {
			}
		});
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
