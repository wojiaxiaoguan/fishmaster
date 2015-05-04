package com.ipeaksoft.pay.libandgame;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.widget.Toast;
import cn.cmgame.billing.api.BillingResult;
import cn.cmgame.billing.api.GameInterface;
import cn.cmgame.billing.api.GameInterface.GameExitCallback;
import cn.cmgame.billing.api.GameInterface.IPayCallback;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;
import com.ipeaksoft.pay.PayExtraFeatures;
import com.ipeaksoft.pay.constant.PayChannel;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         中国游戏基地（和游戏）
 * 
 */
public class AndGamePay extends Pay implements PayExtraFeatures {
	
	private IPayCallback mPayCallback;
	
	public AndGamePay(Context context, OnPayListener onPayListener) {
		super(context, onPayListener);
	}

	@Override
	protected void onInit() {
		Activity activity = (Activity) mContext;
		GameInterface.initializeApp(activity);
		
		mPayCallback = new GameInterface.IPayCallback() {
			@Override
			public void onResult(int resultCode, String billingIndex, Object obj) {
				boolean isSuccess = false;
				String result = null;
				
				switch (resultCode) {
				case BillingResult.SUCCESS:
					isSuccess = true;
					result = "购买道具：[" + billingIndex + "] 成功！";
					Log.i(AppConfig.TAG, result);
					break;
					
				case BillingResult.FAILED:
					result = "购买道具：[" + billingIndex + "] 失败！";
					Toast.makeText(mContext, result, Toast.LENGTH_SHORT).show();
					break;
					
				default:
					result = "购买道具：[" + billingIndex + "] 取消！";
					Log.i(AppConfig.TAG, result);
					break;
				}
				
				final int id = AndGameBillingInfoConfig.getInstance().getIdByBillingInfo(billingIndex);
				mOnPayListener.onPostPay(isSuccess, id);
			}
		};
	}
	
	public void pay(int id) {
		String billingIndex = AndGameBillingInfoConfig.getInstance().getBillingInfo(id);
		boolean isRepeated = (id != 1010 && id != 1012 && id != 1013 && id != 1014);
		
		if (!isRepeated) {
			//	是否已经购买过该商品（非消耗品）
			boolean isActivate = GameInterface.getActivateFlag(billingIndex);
			if (isActivate) {
				mOnPayListener.onPostQuery(true, id);
			} else {
				GameInterface.doBilling(mContext, true, isRepeated, billingIndex, null, mPayCallback);
			}
		} else {
			GameInterface.doBilling(mContext, true, isRepeated, billingIndex, null, mPayCallback);
		}
	}
	
	@Override
	public int getPayChannel() {
		return PayChannel.CHINA_AND_GAME;
	}

	@Override
	public void query(int id) {
		String billingIndex = AndGameBillingInfoConfig.getInstance().getBillingInfo(id);
		boolean isActivate = GameInterface.getActivateFlag(billingIndex);
		if (isActivate) {
			mOnPayListener.onPostQuery(true, id);
		} else {
			mOnPayListener.onPostQuery(false, id);
		}
	}

	@Override
	public void destroy() {
	}

	@Override
	public void openMoreGame() {
		Log.i(AppConfig.TAG, "no processing!");
	}
	
	@Override
	public void exit() {
		GameInterface.exit(mContext, new GameExitCallback() {
			
			@Override
			public void onConfirmExit() {
				((Activity) mContext).finish();
				System.exit(0);
			}
			
			@Override
			public void onCancelExit() {
			}
		});
	}

}
