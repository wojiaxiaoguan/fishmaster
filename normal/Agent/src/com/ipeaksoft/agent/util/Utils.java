package com.ipeaksoft.agent.util;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.UUID;

import org.apache.commons.io.FileUtils;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Environment;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;

import com.ipeaksoft.agent.activity.WebViewActivity;
import com.ipeaksoft.vector.config.AppConfig;

/**
 * @author jinjia.peng
 * 
 *         瀹���ㄥ伐��烽��
 * 
 */
public final class Utils {

	/**
	 * 缃�缁�涓������ㄦ��绀轰俊���
	 */
	public static final String NETWORK_NOT_AVAILABLE_MSG = "��ㄧ��缃�缁�涓�琛�浜����锛�";
	
	/**
	 * 缃�缁�������������
	 * 
	 * @param context 涓�涓����
	 * @return
	 */
	public static boolean isNetworkAvailable(Context context) {
		ConnectivityManager connMgr = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo netInfo = connMgr.getActiveNetworkInfo();
		return netInfo != null && netInfo.isConnected();
	}
	
	/**
	 * ��ゆ��褰���� SIM ��℃��������涓���界Щ��ㄧЩ��ㄥ��
	 * 
	 * @return
	 */
	public static boolean isChinaMobile(Context context) {
		TelephonyManager telMgr = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
		String operator = telMgr.getSimOperator();
		String ICCID = telMgr.getSimSerialNumber();
		if (ICCID != null && ICCID.trim().length() > 0) {
			ICCID = ICCID.substring(0, 6);
		}
		return ("46000".equals(operator) || "46002".equals(operator) || "46007".equals(operator) || "898600".equals(ICCID));
	}
	
	/**
	 * ��ゆ��褰���� SIM ��℃��������涓���借��������
	 * 
	 * @param context
	 * @return
	 */
	public static boolean isChinaUnicom(Context context) {
		TelephonyManager telMgr = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
		String imsi = telMgr.getSubscriberId();
		return !TextUtils.isEmpty(imsi) && (imsi.startsWith("46001"));
	}
	
	/**
	 * ��ゆ��褰���� SIM ��℃��������涓���界�典俊���
	 * 
	 * @param context
	 * @return
	 */
	public static boolean isChinaTelecom(Context context) {
		TelephonyManager telMgr = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
		String imsi = telMgr.getSubscriberId();
		return !TextUtils.isEmpty(imsi) && (imsi.startsWith("46003"));
	}

	/**
	 * 妫�楠� URL 姝ｅ��琛ㄨ揪寮�
	 */
	private static final String PATTEN_URL = "(http|https):\\/\\/[\\w\\-_]+(\\.[\\w\\-_]+)+([\\w\\-\\.,@?^=%&amp;:/~\\+#]*[\\w\\-\\@?^=%&amp;/~\\+#])?";
	
	/**
	 * ���寮� WebView
	 * 
	 * @param context 涓�涓����
	 * @param url 瑕����寮����缃����
	 */
	public static void openWebView(Context context, String url) {
		if (!isNetworkAvailable(context)) {
			showToast(context, NETWORK_NOT_AVAILABLE_MSG);
			return;
		}

		if (!TextUtils.isEmpty(url) && url.matches(PATTEN_URL)) {
			WebViewActivity.openWebView(context, url);
		} else {
			Log.i(AppConfig.TAG, "-------- url ��煎�����璇� --------");
			Log.i(AppConfig.TAG, "url: " + url);
		}
	}
	
	/**
	 * ���寮� WebView锛�涓������版��杩����
	 * 
	 * @param context 涓�涓����
	 * @param url ���寮����缃����
	 * @param fullClassName ��ㄧ被���锛�杩������板��涓�涓� Activity
	 */
	public static void openWebView(Context context, String url, String fullClassName) {
		if (!isNetworkAvailable(context)) {
			showToast(context, NETWORK_NOT_AVAILABLE_MSG);
			return;
		}

		if (!TextUtils.isEmpty(url) && url.matches(PATTEN_URL)) {
			WebViewActivity.openWebView(context, url, fullClassName);
		} else {
			Log.i(AppConfig.TAG, "-------- url ��煎�����璇� --------");
			Log.i(AppConfig.TAG, "url: " + url);
		}
	}
	
	/**
	 * ���寮� WebView��荤��
	 * 
	 * @param context 涓�涓����
	 * @param url ���寮����缃����
	 * @param fullClassName ��ㄧ被���锛�杩������板��涓�涓� Activity
	 */
	public static void openWebViewRaiders(Context context,String url)
	{
		if(!isNetworkAvailable(context))
		{
			showToast(context, NETWORK_NOT_AVAILABLE_MSG);
			return;
		}
		
		if(!TextUtils.isEmpty(url))
		{
			String urls="file:///android_asset/gameRaiders/"+url+".html";
			WebViewActivity.openWebView(context, urls);
		}
		else
		{
			Log.i(AppConfig.TAG, "-------- url 涓虹┖ --------");
			Log.i(AppConfig.TAG, "url: " + url);
		}
	}
	
	/**
	 * ��剧ず���娑����
	 * 
	 * @param context 涓�涓����
	 * @param msg 娑����
	 */
	public static void showToast(Context context, String msg) {
		Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
	}
	
	/**
	 * ��剧ず��挎�����
	 * 
	 * @param context 涓�涓����
	 * @param msg 娑�������瀹�
	 */
	public static void showLongToast(Context context, String msg) {
		Toast.makeText(context, msg, Toast.LENGTH_LONG).show();
	}
	
	/**
	 * ��峰��璁惧�����
	 * 
	 * @param context
	 * @return
	 */
	public static String getDeviceId(Context context) {
		//	浠����浠堕��璇诲�� device
		SharedPreferences settings = context.getSharedPreferences("deviceId", Context.MODE_PRIVATE);
		String deviceId = settings.getString("deviceId", null);
		
		if (TextUtils.isEmpty(deviceId)) {
			try {
				TelephonyManager tm = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
				deviceId = tm.getDeviceId();
			} catch (Exception e) {
				e.printStackTrace();
			}
			
			if (TextUtils.isEmpty(deviceId)) {
				// ��峰��涓���拌�惧����凤����� UUID 浠ｆ��
				deviceId = UUID.randomUUID().toString().replace("-", "");
			}
			
			// 淇�瀛���伴��缃����浠�(杩���峰��浠ヤ��璇�姣�娆￠�戒�����)
			SharedPreferences.Editor editor = settings.edit();
			editor.putString("deviceId", deviceId);
			editor.commit();
		}

		return deviceId;
	}
	
	/**
	 * ��疯�� assets ���浠跺す涓�������浠跺�� SD ��圭��褰�
	 * 
	 * @param context 涓�涓����
	 * @param srcPath 琛ㄧず assets ���浠跺す涓����婧����浠惰矾寰�
	 */
	public static void copyAssetsFileToSDRootDir(Context context, String srcPath) {
		if (TextUtils.isEmpty(srcPath)) {
			Log.e(AppConfig.TAG, "src path is null.");
			return;
		}
		
		//	��ゆ�� SD ��℃�����瀛����
		boolean isSdCardExist = Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
		if (isSdCardExist) {
			
			//	��� srcPath ��兼�����浠惰矾寰�锛�������浠惰矾寰����������浠跺��
			//	������锛���存�ュ�����浠跺��
			final int index = srcPath.lastIndexOf('/');
			final String destFileName = (index != -1) ? srcPath.substring(index) : srcPath;
			System.out.println("SD���destFileName:" + destFileName);
			try {
				
				InputStream source = context.getAssets().open(srcPath);
				File outFile = new File(Environment.getExternalStorageDirectory(), destFileName);
				FileUtils.copyInputStreamToFile(source, outFile);
			} catch (IOException e) {
				e.printStackTrace();
			}
		} else {
			Log.e(AppConfig.TAG, "SD ��′��瀛����锛�" );
		}
	}
	
	/**
	 * ��峰��浠ｇ�����������
	 */
	public static int getVersionCode(Context mContext) {
		// ��峰��������浠ｇ�����
		int vc = 1;
		try {
			PackageInfo pi = mContext.getPackageManager().getPackageInfo(
					mContext.getPackageName(), 0);
			vc = pi.versionCode;
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			System.out.print("���璇�锛����娉���峰��浠ｇ�����������");
			e.printStackTrace();
		}
		return vc;
	}

	/**
	 * ��峰�����������绉�
	 */
	public static String getVersionName(Context mContext) {
		try {
			PackageInfo pi = mContext.getPackageManager().getPackageInfo(
					mContext.getPackageName(), 0);
			return pi.versionName;
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			System.out.print("���璇�锛����娉���峰��浠ｇ�����������绉�");
			e.printStackTrace();
			return "error version name";
		}
	}

	/**
	 * ��峰��APP娓�������
	 */
	public static String getChannel(Context mContext) {
		ApplicationInfo info;
		try {
			info = mContext.getPackageManager().getApplicationInfo(
					mContext.getPackageName(), PackageManager.GET_META_DATA);
			String msg = info.metaData.getString("APPCHANNLE");
			System.out.println("APPCHANNLE:" + msg);
			return msg;
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "error channel";
	}
	/**
	 * ��峰��Umeng APP娓�������
	 */
	public static String getUmengChannel(Context mContext) {
		ApplicationInfo info;
		try {
			info = mContext.getPackageManager().getApplicationInfo(
					mContext.getPackageName(), PackageManager.GET_META_DATA);
			String msg = info.metaData.getString("UMENG_CHANNEL");
			System.out.println("UMENG_APPKEY:" + msg);
			return msg;
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "error Umeng APP娓�������";
	}
	/**
	 * ��峰��Umeng APPKey
	 */
	public static String getUmengKey(Context mContext) {
		ApplicationInfo info;
		try {
			info = mContext.getPackageManager().getApplicationInfo(
					mContext.getPackageName(), PackageManager.GET_META_DATA);
			String msg = info.metaData.getString("UMENG_APPKEY");
			System.out.println("UMENG_CHANNEL:" + msg);
			return msg;
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "error Umeng APPKey";
	}
	/**
	 * ��峰��APP���灞�KEY
	 */
	public static String getInterstitialKey(Context mContext) {
		ApplicationInfo info;
		try {
			info = mContext.getPackageManager().getApplicationInfo(
					mContext.getPackageName(), PackageManager.GET_META_DATA);
			String msg = info.metaData.getString("APPINTERSTITIAL");
			System.out.println("APPINTERSTITIAL:" + msg);
			return msg;
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "error key";
	}
	
	/**
	 * ��峰��APP妯�骞�KEY
	 */
	public static String getBannerKey(Context mContext) {
		ApplicationInfo info;
		try {
			info = mContext.getPackageManager().getApplicationInfo(
					mContext.getPackageName(), PackageManager.GET_META_DATA);
			String msg = info.metaData.getString("APPBANNER");
			System.out.println("APPBANNER:" + msg);
			return msg;
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return "error key";
	}
	
	/**
	 * 娓�������������缁�澶����
	 */
	public static Boolean isRefusedToURL(Context mContext)
	{
		String pChannel = Utils.getChannel(mContext);
		return pChannel.equals("4399.com") || pChannel.equals("uc.com") || pChannel.equals("meitu.com");
	}

}
