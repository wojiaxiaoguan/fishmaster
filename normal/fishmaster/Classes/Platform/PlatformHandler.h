//
//  PlatformHandler.h
//  Platform
//
//  
//
//

#ifndef __Platform__PlatformHandler__
#define __Platform__PlatformHandler__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "common.h"
#include "GameData.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#endif
USING_NS_CC;
using namespace extension;


/** 支付渠道Id */
enum  PayChannelId {
    DEFAULT = 0,
    APP_STORE,      //  App Store
    ALIPAY,         //  支付宝
    NET_BANK,       //  网银
    TENPAY,         //  财付通
    CHINA_MOBILE,   //  中国移动
    CHINA_UNICOM,   //  中国联通
    CHINA_NET,      //  中国电信
    PAY_PAL,        //  PayPal
};

/** 分享类型 ID */
enum  ShareID {
    INVALID = 0,            //  无效值
    WEIXI_CIRCLES_SHARE = 1,    //  微信朋友圈——分享
    WEIXI_CIRCLES_HELP = 2,     //  微信朋友圈——求助
    WEIXI_IN_FRIEND_COIN = 3,    //  向好友索取金币
    WEIXI_IN_FRIEND_LIFE = 4,   //  向好友索取体力
};



class PlatformHandler 
{
private:
    static PlatformHandler* _pSingleInstance;
    PlatformHandler();
    virtual ~PlatformHandler();
    
    
public:
    
    //  当前选择的分享 ID
    CC_SYNTHESIZE(ShareID, _currShareID, CurrSharedID);
    
public:
    /**
     * 获取 PlatformHandler 单例
     */
    static PlatformHandler* getInstance();
    
    /**
     * 销毁 PlatformHandler 单例
     */
    static void destroy();
    /**
     *初始化支付
     *
     */
    void initPay();
    /**
     * 支付
     */
    void pay(ProductType id);
    
    /**
     * 支付完成
     */
    void postPay(bool isSuccess, ProductType goodsId, PayChannelId payChannelId);
    
    /**
     * 支付完成
     */
    int postCode;
    void postPay(ProductType goodsId, PayChannelId payChannelId);
    void postPayScheduleCallBack(float t,void * data,std::string name);
    void postPayCallBack(float dt);
    
    /**
     * 支付失败
     */
    void buyWithoutNetCallback(float dt);
    
    void restorePurchase();//恢复购买
    void toast(const char *message);//弹出框
    void exitApp();
    
    void openFeedback();//反馈
    void moreGame();//更多游戏

};

#endif /* defined(__Platform__PlatformHandler__) */
