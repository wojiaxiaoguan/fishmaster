package com.ipeaksoft.ad.entity;

/**
 * @author jinjia.peng
 * 
 * 
 *         广告权重实体类
 */
public class AdWeight {

	/**
	 * 广告名
	 */
	private String mAdName;
	/**
	 * 显示权重
	 */
	private int mWeight;

	public AdWeight() {
	}
	
	public AdWeight(String adName, int weight) {
		mAdName = adName;
		mWeight = weight;
	}

	public String getAdName() {
		return mAdName;
	}

	public void setAdName(String mAdName) {
		this.mAdName = mAdName;
	}

	public int getWeight() {
		return mWeight;
	}

	public void setWeight(int weight) {
		this.mWeight = weight;
	}

}
