package com.ipeaksoft.pay.libpayunicom3;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;
import com.ipeaksoft.pay.constant.PayChannel;
import com.ipeaksoft.vector.config.AppConfig;
import com.unicom.dcLoader.Utils;
import com.unicom.dcLoader.Utils.UnipayPayResultListener;

/**
 * @author jinjia.peng
 * 
 *         联通（3网）
 * 
 */
public class Unicom3Pay extends Pay {

	private int mId;
	private UnipayPayResultListener mUnipayPayResultListener;
	
	public Unicom3Pay(Context context, OnPayListener onPayListener) {
		super(context, onPayListener);
	}
	
	/**
	 * Application的初始化
	 */
	public static void initSDK(Context pContext)
	{
		System.out.print("initSDK");
		Utils.getInstances().initSDK(pContext, new UnipayPayResultListener() {
			
			@Override
			public void PayResult(String arg0, int arg1, int arg2, String arg3) {
				// TODO Auto-generated method stub
				
			}
		});
	}
	
	@Override
	protected void onInit() {
		
		mUnipayPayResultListener = new UnipayPayResultListener() {
			
			@Override
			public void  PayResult(String payCode, int flag, int flag2, String desc) {
				boolean isSuccess = false;
				String msg = null;
				switch (flag) {
				case 1://success
					//此处放置支付请求已提交的相关处理代码
					isSuccess = true;
					msg = "支付成功, 计费点：" + payCode + ", " + desc;
					break;

				case 2://fail
					//此处放置支付请求失败的相关处理代码
					msg = "支付失败，" + desc;
					break;
					
				case 3://cancel
					//此处放置支付请求被取消的相关处理代码
					msg = "非联通第三方支付, " + desc;
					break;
					
				default:
					break;
				}
				
				mOnPayListener.onPostPay(isSuccess, mId);
				Log.i(AppConfig.TAG, msg);
				Log.i(AppConfig.TAG, "payCode: " + payCode + "; flag: " + flag + "; desc: " + desc);
			}
		};
		
		Utils.getInstances().initSDK(mContext, mUnipayPayResultListener);
	}
	
	@Override
	public void pay(int id) {
		String payCode = Unicom3BillingInfoConfig.getInstance().getBillingInfo(id);
		if (TextUtils.isEmpty(payCode)) {
			Log.e(AppConfig.TAG, "payCode is null.");
		} else {
			mId = id;
			Utils.getInstances().pay(mContext, payCode, mUnipayPayResultListener);
		}
	}

	@Override
	public int getPayChannel() {
		return PayChannel.CHINA_UNICOM_3;
	}

	@Override
	public void query(int id) {
	}

	@Override
	public void destroy() {
	}
	
}
