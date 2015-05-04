package com.ipeaksoft.agent.taskhandler;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.ipeaksoft.agent.GameJNI;
import com.ipeaksoft.agent.util.Utils;
import com.ipeaksoft.pay.OnPayListener;
import com.ipeaksoft.pay.constant.PayPlatformName;
import com.ipeaksoft.pay.manager.PayManager;
import com.ipeaksoft.vector.ActivityLifeCycle;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         支付任务处理器
 * 
 */
public class PayTaskHandler implements ActivityLifeCycle {

	private static PayTaskHandler mSinglePayTask;

	public static String getPayPlatformName(Context context) {
		String payPlatformName = PayPlatformName.TELECOM_3;
//		if (Utils.isChinaMobile(context))
//			payPlatformName = PayPlatformName.AND_GAME;
//		else if (Utils.isChinaTelecom(context))
//			payPlatformName = PayPlatformName.TELECOM;
//		else if (Utils.isChinaUnicom(context))
//			payPlatformName = PayPlatformName.UNICOM;
//		else {
//			return null;
//		}
		return payPlatformName;
	}

	/**
	 * 初始化广告任务
	 * 
	 * @param context
	 */
	public static PayTaskHandler init(Context context) {
		if (mSinglePayTask == null) {
			Log.i(AppConfig.TAG,"PayTaskHandler init");
			mSinglePayTask = new PayTaskHandler(context);
		}

		return mSinglePayTask;
	}

	/**
	 * 
	 * 获取广告任务实例
	 * 
	 * @return
	 */
	public static PayTaskHandler getInstance() {
		return mSinglePayTask;
	}

	private Context mContext;
	private OnPayListener mPayListener;

	private PayTaskHandler(Context context) {
		mContext = context;

		mPayListener = new OnPayListener() {

			@Override
			public void onPostPay(boolean isSuccess, int id) {
				Log.i(AppConfig.TAG, "购买完成，result: " + isSuccess + ", id: "
						+ id);
				GameJNI.postPay(isSuccess, id, PayManager.getInstance()
						.getPayChannel());
			}

			@Override
			public void onPostQuery(boolean isSuccess, int id) {
				Log.i(AppConfig.TAG, "恢复购买查询处理完成，result: " + isSuccess
						+ ", id: " + id);
				GameJNI.postPayQuery(isSuccess, id);
			}
		};
		// String payPlatformName = getPayPlatformName(mContext);
		// if(!payPlatformName.equals(" "))
		Log.i(AppConfig.TAG, "初始化MM");
		{
			PayManager.init(mContext, getPayPlatformName(mContext), mPayListener);
		}
        if(PayManager.getInstance() == null)
        {
        	Log.i(AppConfig.TAG, "new pay not instance!");
        }
        else
        	
        {
        	Log.i(AppConfig.TAG, "new pay instance!");
        }
	}

	/**
	 * 处理内购功能
	 * 
	 * @param func
	 * @param params
	 * @throws JSONException
	 */
	public void execPayTask(String func, JSONObject params)
			throws JSONException {
		if ("initPay".equals(func)) { // 初始化内购功能
			System.out.println("初始化内购~" + getPayPlatformName(mContext));
			// String payPlatformName = params.getString("payPlatformName");
			PayManager.init(mContext, getPayPlatformName(mContext),
					mPayListener);

		} else if ("pay".equals(func)) { // 购买
			int id = params.getInt("id");
			System.out.println("购买id = " + id);
			if (PayManager.getInstance() != null) {
				PayManager.getInstance().pay(id);
			} else {
				System.out.println("支付实例未初始化~" + getPayPlatformName(mContext));
			}

		} else if ("restorePay".equals(func)) { // 恢复购买
			int id = params.getInt("id");

			if (PayManager.getInstance() != null) {
				PayManager.getInstance().query(id);
			} else {
				System.out.println("支付实例未初始化~" + getPayPlatformName(mContext));
			}
		}
	}

	@Override
	public void resume() {
		Object obj = PayManager.getInstance();
		if (obj instanceof ActivityLifeCycle) {
			((ActivityLifeCycle) obj).resume();
		}
	}

	@Override
	public void activityResult(int requestCode, int resultCode, Intent data) {
	}

	@Override
	public void pause() {
		Object obj = PayManager.getInstance();
		if (obj instanceof ActivityLifeCycle) {
			((ActivityLifeCycle) obj).pause();
		}
	}

	public void destroy() {
		PayManager.destroy();
		mSinglePayTask = null;
	}

}
