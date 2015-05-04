/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.ipeaksoft.agent.activity;

import java.lang.reflect.InvocationTargetException;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Intent;
import android.os.Bundle;

import com.ipeaksoft.agent.GameAgent;
import com.ipeaksoft.agent.GameJNI;
import com.ipeaksoft.agent.other.BaiDuPropaganda;
import com.ipeaksoft.agent.taskhandler.PayTaskHandler;
//import com.ipeaksoft.libumeng.UmengAgent;
import com.ipeaksoft.pay.constant.PayPlatformName;

public class MainActivity extends Cocos2dxActivity {
	
	public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
        
        return glSurfaceView;
    }
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		//百度品宣初始化
		BaiDuPropaganda.getInstance().initMainActivity(this);
		
		GameAgent.init(this, MainActivity.this);
		overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out);

		System.out.println("初始化agent");
		//游戏基地音效控制
		Class<?> pClass;
		try {
			pClass = Class.forName("cn.cmgame.billing.api.GameInterface");
			if(pClass != null && PayTaskHandler.getPayPlatformName(MainActivity.this) == PayPlatformName.AND_GAME)
			{
				for(int i=0;i< pClass.getMethods().length;i++)
				{
					System.out.println("游戏" +pClass.getMethods()[i].getName());
				}
				
				Boolean pBool = (Boolean)pClass.getMethod("isMusicEnabled").invoke(null);
				if(pBool){
					GameJNI.setMusicEnabled(true);
					System.out.println("声音开！");
				}else{
					GameJNI.setMusicEnabled(false);
					System.out.println("声音关！");
				}
			}
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Main初始化");
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//		UmengAgent.getInstance().onActivityResult(requestCode, resultCode, data);
		super.onActivityResult(requestCode, resultCode, data);
	}
	
	@Override
	protected void onDestroy() {
		GameAgent.getInstance().destroy();
		super.onDestroy();
	}
	
	@Override
	protected void onResume() {
		GameAgent.getInstance().resume();
		super.onResume();
	}
	
	@Override
	protected void onPause() {
		GameAgent.getInstance().pause();
		super.onPause();
	}
	
}

