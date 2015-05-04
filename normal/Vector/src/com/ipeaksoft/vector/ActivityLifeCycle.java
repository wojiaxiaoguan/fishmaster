package com.ipeaksoft.vector;

import android.content.Intent;

/**
 * @author jinjia.peng
 * 
 *         Activity 生命周期
 * 
 */
public interface ActivityLifeCycle {

	public void resume();

	public void activityResult(int requestCode, int resultCode, Intent data);

	public void pause();
	
}
