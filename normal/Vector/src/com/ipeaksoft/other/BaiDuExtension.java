package com.ipeaksoft.other;

import android.app.Activity;
import android.app.Application;
import android.content.Context;

public interface BaiDuExtension {

	/** 百度退出调用 */
	public void exit(Activity mActivity,final Context mContext);
	
	/** 百度暂停调用 */
	public void pause(Activity mActivity,final Context mContext);
	
	/** 百度统计调用 */
	public void onResume(final Context mContext);
	public void onPause(final Context mContext);
	
	/** 初始化调用 */
	public void onInitStage(Activity mActivity);
	public void onInitSDK(Activity mActivity);
	public void onInitApplication(Application mApplication);

}
