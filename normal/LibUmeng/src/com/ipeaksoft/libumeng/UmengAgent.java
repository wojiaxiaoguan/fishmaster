package com.ipeaksoft.libumeng;

import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

import com.ipeaksoft.vector.config.AppConfig;
import com.umeng.fb.FeedbackAgent;
import com.umeng.fb.model.Conversation;
import com.umeng.fb.model.DevReply;
import com.umeng.fb.model.Reply;
import com.umeng.mobclickcpp.MobClickCppHelper;

/**
 * @author jinjia.peng
 * 
 *         友盟游戏统计
 * 
 */
public class UmengAgent {

	private static UmengAgent mUmengAgent;
	
	private static final String TAG = UmengAgent.class.getName();
	private Context mContext;
//	private PushAgent mPushAgent;
	private FeedbackAgent mFeedback;

	private UmengAgent(Context context) {
		mContext = context;
		System.out.print("初始化UMeng-A");
		//initPush();
		initMobClick();
		initFeedback();
		//initSocial();
	}
	
	public static UmengAgent init(Context context) {
		if (mUmengAgent == null) {
			mUmengAgent = new UmengAgent(context);
		}
		return mUmengAgent;
	}
	
	public static UmengAgent getInstance() {
		return mUmengAgent;
	}

	/**
	 * 初始化用户反馈
	 */
	private void initFeedback() {
		mFeedback = new FeedbackAgent(mContext);
		mFeedback.sync(); // 友盟意见反馈的回复检测

		// 开发者对用户的反馈进行回复，通知用户
		mFeedback.getDefaultConversation().sync(new Conversation.SyncListener() {

					@Override
					public void onSendUserReply(List<Reply> arg0) {
						Log.i(AppConfig.TAG, "发送消息 Umeng ");
					}

					@Override
					public void onReceiveDevReply(List<DevReply> arg0) {
						// TODO Auto-generated method stub
						if (arg0 != null && arg0.size() > 0) {
							String msg = "已有开发者对你的反馈进行了回复";
							Toast.makeText(mContext, msg, Toast.LENGTH_SHORT)
									.show();
							mFeedback.startFeedbackActivity();
						}
					}
				});
	}

	/**
	 * 打开用户反馈
	 */
	public void openFeedback() {
		Log.i(AppConfig.TAG, "openFeedback ------------ ");
		mFeedback.startFeedbackActivity();
	}

	/**
	 * 初始化友盟推送
	 */
	private void initPush() {
//		// 开启友盟推送服务
//		mPushAgent = PushAgent.getInstance(mContext);
//		mPushAgent.onAppStart();
//		mPushAgent.enable();
//		mPushAgent.setDebugMode(AppConfig.IS_DEBUG);

//		// 可用于测试友盟消息服务后台
//		String deviceToken = UmengRegistrar.getRegistrationId(mContext);
//		Log.i(TAG, "Device Token: " + deviceToken);
	}

	/**
	 * 初始化友盟游戏统计分析
	 */
	private void initMobClick() {
		System.out.print("初始化UMeng");
		MobClickCppHelper.init(mContext);
	}
	
	/**
	 * 初始化社会组件
	 */
	private void initSocial() {
//		CCUMSocialController.initSocialSDK((Activity) mContext, "com.umeng.social.share");
		
	}
	
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
//		CCUMSocialController.onActivityResult(requestCode, resultCode, data);
	}
}
