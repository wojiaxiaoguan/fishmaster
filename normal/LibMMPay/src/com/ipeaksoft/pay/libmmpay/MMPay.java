package com.ipeaksoft.pay.libmmpay;

import java.util.HashMap;

import mm.purchasesdk.OnPurchaseListener;
import mm.purchasesdk.Purchase;
import mm.purchasesdk.PurchaseCode;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;

import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.Pay;
import com.ipeaksoft.pay.constant.PayChannel;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         移动 MM 支付
 * 
 */
public class MMPay extends Pay {

	private static final String MM_APPID = "300008993829";
	private static final String MM_APPKEY = "133D63276D87E6921762BBD7B1687872";
	
	public MMPay(Context context, OnPayListener onPayListener) {
		super(context, onPayListener);
		Purchase.getInstance().setAppInfo(MM_APPID, MM_APPKEY);
		Purchase.getInstance().init(context, mOnPurchaseListener);
	}

	private OnPurchaseListener mOnPurchaseListener = new OnPurchaseListener() {

		@Override
		public void onUnsubscribeFinish(int code) {
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onQueryFinish(int code, HashMap obj) {
			String result = "查询成功,该商品已购买";
			boolean isSuccess = false;
			
			if (code != PurchaseCode.QUERY_OK) {
				result = "查询结果：" + Purchase.getReason(code);
			} else {
				String leftDay = (String) obj.get(OnPurchaseListener.LEFTDAY);
				if (leftDay != null && leftDay.trim().length() != 0) {
					result = result + ", 剩余时间 ： " + leftDay;
				}
				
				String orderID =(String) obj.get(OnPurchaseListener.ORDERID);
				if (orderID != null && orderID.trim().length() != 0) {
					result = result + ", OrderID ： " + orderID;
					isSuccess = true;
				}
			}
			
			String payCode = (String) obj.get(OnPurchaseListener.PAYCODE);
			int id = MMBillingInfoConfig.getInstance().getIdByBillingInfo(payCode);
			mOnPayListener.onPostQuery(isSuccess, id);
			Log.i(AppConfig.TAG, result);
		}

		@Override
		public void onInitFinish(int code) {
		}

		@SuppressWarnings("rawtypes")
		@Override
		public void onBillingFinish(int code, HashMap obj) {
			boolean isSuccess = false;
			if (code == PurchaseCode.ORDER_OK || code == PurchaseCode.AUTH_OK || code == PurchaseCode.WEAK_ORDER_OK) {
				isSuccess = true;
			} else {
				Toast.makeText(mContext, "订购结果：" + Purchase.getReason(code), Toast.LENGTH_SHORT).show();
			}
			
			String payCode = (String) obj.get(OnPurchaseListener.PAYCODE);
			int id = MMBillingInfoConfig.getInstance().getIdByBillingInfo(payCode);
			mOnPayListener.onPostPay(isSuccess, id);
		}

		@Override
		public void onBeforeDownload() {
		}

		@Override
		public void onBeforeApply() {
		}

		@Override
		public void onAfterDownload() {
		}

		@Override
		public void onAfterApply() {
		}
	};
	
	@Override
	public int getPayChannel() {
		return PayChannel.CHINA_MOBILE;
	}

	@Override
	public void pay(int id) {
		System.out.println("进入了MM");
		String payCode = MMBillingInfoConfig.getInstance().getBillingInfo(id);
		if (TextUtils.isEmpty(payCode)) {
			Log.e(AppConfig.TAG, "PayCode is null.");
		} else {
			Purchase.getInstance().order(mContext, payCode, mOnPurchaseListener);
		}
	}

	@Override
	public void query(int id) {
		String payCode = MMBillingInfoConfig.getInstance().getBillingInfo(id);
		if (TextUtils.isEmpty(payCode)) {
			Log.e(AppConfig.TAG, "PayCode is null.");
		} else {
			Purchase.getInstance().query(mContext, payCode, mOnPurchaseListener);
		}
	}

	@Override
	public void destroy() {
		
	}

	@Override
	protected void onInit() {
		// TODO Auto-generated method stub
		
	}

}
