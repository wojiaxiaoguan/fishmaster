package com.ipeaksoft.agent.taskhandler;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

import com.ipeaksoft.agent.GameJNI;
import com.ipeaksoft.agent.other.BaiDuPropaganda;
import com.ipeaksoft.agent.util.Utils;
import com.ipeaksoft.libumeng.UmengAgent;
//import com.ipeaksoft.libumeng.UmengAgent;
import com.ipeaksoft.pay.PayExtraFeatures;
import com.ipeaksoft.pay.manager.PayManager;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         一般任务处理器
 * 
 */
public final class CommonTaskHandler {

	private static CommonTaskHandler mSingleCommonTaskHalder;

	/**
	 * 初始化广告任务
	 * 
	 * @param context
	 */
	public static CommonTaskHandler init(Context context, Activity activity) {
		if (mSingleCommonTaskHalder == null) {
			mSingleCommonTaskHalder = new CommonTaskHandler(context, activity);
		}
		return mSingleCommonTaskHalder;
	}

	/**
	 * 
	 * 获取广告任务实例
	 * 
	 * @return
	 */
	public static CommonTaskHandler getInstance() {
		return mSingleCommonTaskHalder;
	}

	private Context mContext;
	private Activity mActivity;
    
    private long mTime;

	private CommonTaskHandler(Context context, Activity activity) {
		mContext = context;
		mActivity = activity;
	}

	/**
	 * 处理常见的基本任务
	 * 
	 * @param func
	 * @param params
	 * @throws JSONException
	 */
	public void execCommonTask(String func, JSONObject params)
			throws JSONException {
		System.out.println(func);
		if ("openUrl".equals(func)) { // 用本地 WebView 打开链接
			System.out.println("url1");
			final String url = params.getString("value");
			System.out.println("url1:" + url);
			Utils.openWebView(mContext, url);

		} else if ("openUrlWithCallback".equals(func)) { // 用本地 WebView 打开链接，带回调
			System.out.println("url2:");
			final String url = params.getString("value");
			System.out.println("url2:" + url);
			final String beforeActivityClassName = "org.cocos2dx.lib.Cocos2dxActivity.AppActivity";
			Utils.openWebView(mContext, url, beforeActivityClassName);

		} else if ("openFeedback".equals(func)) { // 用户反馈
			UmengAgent.getInstance().openFeedback();
			
		} else if ("showToast".equals(func)) { // 显示 Toast
			final String msg = params.getString("message");
			Utils.showToast(mContext, msg);

		} else if ("showLongToast".equals(func)) {
			final String msg = params.getString("message");
			Utils.showLongToast(mContext, msg);
			    
		} else if ("openUrlWithExternalBrowser".equals(func)) { // 外部浏览器打开Url
			final String url = params.getString("value");
			Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
			mContext.startActivity(intent);

		} else if ("openCommunity".equals(func)) {	//	打开社区
			Log.i(AppConfig.TAG, "社区");
			
		} else if ("copyShareImage".equals(func)) {	//	拷贝分享图片
			System.out.println("这是copyShareImage:" + params.getString("value"));
			final String filePath = params.getString("value");
			Utils.copyAssetsFileToSDRootDir(mContext, filePath);

		}else if ("moreGame".equals(func)) {	//	电信三网专用更多游戏
//			Utils.showLongToast(mContext, "更多游戏");
			
			Object obj = PayManager.getInstance();
			if (obj instanceof PayExtraFeatures) { 
				System.out.println("更多游戏 andy ");
				((PayExtraFeatures) obj).openMoreGame();
			}
			
		}else if ("gameEND".equals(func)) {	//   安卓退出
//            Object obj = PayManager.getInstance();
//            if (!Utils.isRefusedToURL(mContext) && obj instanceof PayExtraFeatures) {
//                ((PayExtraFeatures) obj).exit();
//            }
//            else
//            {
//                long time = System.currentTimeMillis();
//                
//                if(Math.abs(time - mTime) < 3000)
//                {
//                    System.exit(0);
//                }
//                else
//                {
//                    Utils.showLongToast(mContext, "再轻轻按一次退出");
//                    mTime = time;
//                }
//            }
			System.out.println("appExit start");
				appExit();
		}else if ("unReview".equals(func)) {
			System.out.println("java非审核状态");
			BaiDuPropaganda.getInstance().setAvailable(false);
			
		}
	}

	/** 退出统一出口 */
	public void appExit() {
		// 百度品宣的出口调用，如果没有接入百度品宣也不会影响应用运行。
		System.out.println("appExit");
		if (!BaiDuPropaganda.getInstance().exit(mActivity, mContext)) {
			// 支付扩展的接入，如果是拒绝外链的，则不跳入游戏基地这样的返回入口
			Object obj = PayManager.getInstance();
			if (!Utils.isRefusedToURL(mContext)
					&& obj instanceof PayExtraFeatures) {
				((PayExtraFeatures) obj).exit();
			} else {
				long time = System.currentTimeMillis();

				if (Math.abs(time - mTime) < 3000) {
					GameJNI.exitApp();
					System.exit(0);
				} else {
					Utils.showLongToast(mContext, "再轻轻按一次退出");
					mTime = time;
				}
			}
		}
	}


	/** 暂停统一退出 */
	public void appPause() {
		// 百度的暂停调用
		BaiDuPropaganda.getInstance().pause(mActivity, mContext);
	}
	
	/** 非审核入口 */
	public void unReview()
	{
		System.out.println("JAVA：非审核状态");
		// 百度品宣非审核禁用
		BaiDuPropaganda.getInstance().setAvailable(false);
	}

	
	public void destroy() {
		mSingleCommonTaskHalder = null;
	}

}
