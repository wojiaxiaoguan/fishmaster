package com.ipeaksoft.agent.activity;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ProgressBar;

import com.ipeaksoft.agent.R;

/**
 * @author jinjia.peng
 * 
 *         WebView 页面
 * 
 */
public class WebViewActivity extends Activity {

	/**
	 * 需要打开Url键名
	 */
	public static final String KEY_URL = "url";
	/**
	 * 全类名键名
	 */
	public static final String KEY_FULL_CLASSNAME = "fullClassName";
	/**
	 * 请求码
	 */
	public static final int KEY_REQUEST_CODE = 0x20;
	/**
	 * 结果码
	 */
	public static final int KEY_RESULT_CODE = 0x3231;
	
	
	/**
	 * 返回前一个 Activity 的前类名
	 */
	private String mFullClassName;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.vector_activity_web);
		
		//	加载网页
		Intent intent = getIntent();
		final String url = intent.getStringExtra(KEY_URL);
		final WebView webView = (WebView) findViewById(R.id.web);
		webView.loadUrl(url);
		webView.setWebViewClient(new WebViewClient() {
			@Override
			public boolean shouldOverrideUrlLoading(WebView view, String url) {
				view.loadUrl(url);
				return true;
			}
		});
		
		//	返回父页面
		findViewById(R.id.backImgBtn).setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				back();
			}
		});
		
		//	处理进度条更新
		final ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
		webView.setWebChromeClient(new WebChromeClient() {
			@Override
			public void onProgressChanged(WebView view, int newProgress) {
				if (newProgress == 100) {
					progressBar.setVisibility(View.GONE);
				}
				super.onProgressChanged(view, newProgress);
			}
		});
		
		mFullClassName = intent.getStringExtra(KEY_FULL_CLASSNAME);
	}

	/**
	 * 打开 WebView 页面
	 * 
	 * @param context
	 * @param url
	 */
	public static void openWebView(Context context, String url) {
		Intent intent = new Intent(context, WebViewActivity.class);
		intent.putExtra(KEY_URL, url);
		context.startActivity(intent);
	}
	
	/**
	 * 打开 WebView 带回调
	 * 
	 * @param context
	 * @param url
	 * @param fullClassName 返回到 activity 的全类名
	 */
	public static void openWebView(Context context, String url, String fullClassName) {
		Intent intent = new Intent(context, WebViewActivity.class);
		intent.putExtra(KEY_URL, url);
		intent.putExtra(KEY_FULL_CLASSNAME, fullClassName);
		((Activity) context).startActivityForResult(intent, KEY_REQUEST_CODE);
	}
	
	@Override
	public void onBackPressed() {
		back();
	}
	
	/**
	 * 返回父页面需要处理的逻辑
	 */
	private void back() {
		if (!TextUtils.isEmpty(mFullClassName)) {	//	有结果返回前一个 Activity
			Intent intent = new Intent();
			ComponentName componentName = new ComponentName(this, mFullClassName);
			intent.setComponent(componentName);
			setResult(KEY_RESULT_CODE, intent);
		}
		finish();
	}
}
