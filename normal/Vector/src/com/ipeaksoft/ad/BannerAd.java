package com.ipeaksoft.ad;

import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

/**
 * @author jinjia.peng
 * 
 *         横幅广告
 */
public abstract class BannerAd extends Ad {

	/**
	 * 广告容器
	 */
	protected RelativeLayout mContainer;

	public BannerAd(Context context) {
		super(context);
	}

	public BannerAd(Context context, AdListener adListener) {
		super(context, adListener);
	}

	@Override
	protected void onInit() {
		mContainer = new RelativeLayout(mContext);
		((Activity) mContext).addContentView(mContainer, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
	}

	/**
	 * 设定子 View 的重心
	 * 
	 * @param gravity
	 */
	public void setAdGravity(int gravity) {
		View view = mContainer.getChildAt(0);
		if (view != null) {
			LayoutParams lp = (LayoutParams) view.getLayoutParams();
			lp.addRule(gravity);
		}
	}
	
	/**
	 * 关闭横幅广告
	 */
	public abstract void close();

	
}
