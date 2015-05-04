//
//  ios.h
//  paigow-ipad
//
//  
//
//

#ifndef __paigow_ipad__platform__
#define __paigow_ipad__platform__

#include "cocos2d.h"
#include "common.h"
#include "typeDef.h"
//#include "storePackHelper.h"
//#include "foundation.h"

using namespace cocos2d;

//第三方登录相关
//==============================================================
#define REMIND_IN (@"remind_in")
#define EXPIRES_IN (@"expires_in")
#define UID (@"uid")

#define ACCESS_TOKEN  (@"access_token")

//sns类型
typedef enum {
    INVALID_AUTH_TYPE,
    AUTH_TYPE_SINA,
    AUTH_TYPE_FB,
    AUTH_TYPE_TENCENT,
    AUTH_TYPE_TWITTER,
    AUTH_TYPE_NUM
}OAuthType;



//商城类型
typedef enum tagStoreType {
    STORE_ILLEGAL,        //非法类型
    STORE_FREE,           //免费商城
    STORE_NORMAL,         //商城
    STORE_VALUE_PACK,     //超值礼包
    STORE_TYPE_NUM
}StoreType;


typedef struct tagRawGoodsInfo {
    TUint8  gameID;               //所属游戏
    TUint8  platformID;          //平台id
//    TUint8  ID[NAME_LEN+1];
//    
//    //礼品相关
//    TUint16 giftID;      //礼品id
//    TUint32 score;       //积分
//    TUint32 gold ;       //金条
//    
//    TUint32 bonusScore;  //赠送的筹码
//    TUint32 bonusGold;   //赠送的金条
//    
//    //价格相关
//    TUint16 price;       //原价
//    TUint8  unit;        //单位
//    
//    TUint8 attribue;                //商品属性:一次性商品等
//    TUint32 reserved1;              //保留字段
//    TUint32 reserved2;
//    TUint8 title[TITLE_LEN+1];             //商品名
//    TUint8 viceTitle[VICE_TITLE_LEN+1];    //商品子标题
//    TUint8 desc[DESC_LEN + 1];             //商品简介
    
}RawGoodsInfo;

//商品节点
typedef struct tagGoodsInfo : public CCObject
{
    RawGoodsInfo goodsInfo;
    
    //已经购买过
    bool hadBoughtIt;
    
}GoodsInfo;




#define MAX_ACCESSTOKEN_LEN (1024)
#define SUB_GP_LOGON_THIRDPARTY (32)

//请求确认或注册一新帐号
struct CMD_GP_LogonByThirdParty
{
    TUint32 dwAuthType;
    TUint8  accessToken[MAX_ACCESSTOKEN_LEN];
};

#define SUB_GP_LOGON_THIRDPARTY_TENCENT (37)
#define OPENID_LEN (32)

struct CMD_GP_LogonByThirdParty_Tencent
{
    TUint32 dwAuthType;
    TUint8  openID[OPENID_LEN];
    
    TUint8  accessToken[MAX_ACCESSTOKEN_LEN];
};

// 返回的新帐号
struct CMD_GP_GetOAuthAccountSCS
{
//    TInt8 szAccount[NAME_LEN];
//    TInt8 szPassword[PASS_LEN];
};

//==============================================================


//加载完成
#define kNotificationLoadFinished "kNotificationLoadFinished"

//使用默认头像
#define kNotificationUseDefaultAvatar "kNotificationUseDefaultAvatar"

//获得了appStore的响应
#define kNotificationReceivedResponseFromAppStore "kNotificationReceivedResponseFromAppStore"

//因为默认头像从0开始,所以为了避免冲突在用用户id命名时,将添加此基址
#define  FACE_ID_INDEX_BASE ( 200)

class IPlatform {
public:
    
public:
    IPlatform(){};
    virtual  ~IPlatform(){};
    
public:
    // 联网方式
    virtual bool startReachability(){
        return true;
    }

    // 获取电量信息
    virtual float getCurMonitoring(){
        return 1;
    }

    //投递加载完成通知
    virtual void postLoadingFinishedNotification() {
        CCLog("Please overload  this API (postLoadingFinishedNotification) when u need");
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(kNotificationLoadFinished, NULL);
    }
    
	// 请求服务器购买验证
    virtual void sendIapReciept2Server(void *data) {
        CCLog("Please overload  this API (sendIapReciept2Server) when u need");
    };
    
	// 根据第三方类型登陆
    virtual void loginWithSNSType (int shareType) {
        CCLog("Please overload  this API (loginWithSNSType) when u need");
    }

	// 购买完成后操作
//    virtual void finishPaymentTransaction( const DBR_GB_Purchase &recp) {
//         CCLog("Please overload  this API (finishPaymentTransaction) when u need");
//    }
    
    //第三方登录
    virtual void loginWithOAuth(OAuthType authType, const char *accessToken, const char *openId){
        CCLog("Please overload  this API (loginWithOAuth) when u need");
    }

	// 开始购买
    virtual  void beginPurchase(int productType) {
        CCLog("Please overload  this API (beginPurchase) when u need");  
    }
    
	// 分享微博
    virtual void sendWeibo( int snsType, int oneTimeType) {
        CCLog("Please overload  this API (beginPurchase) when u need");          
    }
    
	// 更改头像
    virtual void changeAvatar() {
        CCLog("Please overload  this API (changeAvatar) when u need");             
    }
    
	// 获取自定义头像路径根据ID
    virtual const char* getCustomAvatarAbsPathById( int faceId ) {
        CCLog("Please overload  this API (getCustomAvatarAbsPathById) when u need");     
        return NULL;
    }

    virtual bool fileExistsAtPath( const char *path) {
        CCLog("Please overload  this API (fileExistsAtPath) when u need");
        return false;
    }

	// 同步头像
    virtual void syncAvatarWithServer( const char *path) {
         CCLog("Please overload  this API (syncAvatarWithServer) when u need");         
    }
    
    virtual void eventClicked( const char *event) {
            CCLog("Please overload  this API (eventClicked) when u need");
    }
	
    virtual void feedback(int id, const char *name ) {
        CCLog("Please overload  this API (feedback) when u need");        
    }
    
    virtual void spawnAppWithID( const char *name ) {
        CCLog("Please overload  this API (spawnAppWithName) when u need");            
    }
    
    virtual TargetPlatform platform() {
        CCLog("Please overload  this API (platform) when u need");
        return  TargetPlatform(-1);
    }
    
    virtual void cancelAuthWithType( int type) {
        CCLog("Please overload  this API (cancelAuthWithType) when u need");        
    }
    
    virtual const char *getOpenUdid() {
        CCLog("Please overload  this API (getOpenUdid) when u need");
//		return FoundationBase::Instance()->GetMacAdress();
    }
    
    //当前输入模式,默认为英文
    virtual bool isEnInputMode() {
        CCLog("Please overload  this API (isEnInputMode) when u need");
        return true;
    }
    
    //兑奖开关
    virtual bool isGiftOpen()
    {
        CCLog("Please overload  this API (isGiftOpen) when u need");
        return true;
    }
    
    virtual bool isLoadingTipOpen()
    {
        CCLog("Please overload  this API isLoadingTipOpen when u need");
        return true;
    }
    
    
    virtual bool isAdSendOpen() {
        CCLog("Please overload  this API isAdSendOpen when u need");
        return false;
    }
    
    //取的登陆服务器ip地址
    virtual const char* getHallIp() {
        CCLog("Please overload  this API (getHallIp) when u need");
		return "";
	}

    // 更新版本
    virtual void checkNewVersion()
    {
        CCLog("Please overload  this API (checkNewVersion) when u need");
    }

    // 打开Appstore
    virtual void openAppStrore()
    {
        CCLog("Please overload  this API (openAppStrore) when u need");
    }
    
    // 恢复购买
    virtual void restoreIap()
    {
        CCLog("Please overload  this API (restoreIap) when u need");
    }
    
    // 显示广告
    virtual void showFloatAd()
    {
        CCLog("Please overload  this API (showFloatAd) when u need");
    }
    // 显示广告
    virtual void showListAd()
    {
        CCLog("Please overload  this API (showListAd) when u need");
    }
    
    // 隐藏广告
    virtual void removeListAd()
    {
        CCLog("Please overload  this API (removeListAd) when u need");
    }
    
    virtual const char* valueForJSONKey( const char *rawJSONText, const char *key ) {
        CCLog("Please overload  this API (valueForJSONKey) when u need");
        return NULL;
    }
    
    virtual const char* dirDocumentPath(){
        CCLog("Please overload  this API (dirDocumentPath) when u need");
        return NULL;
    }

    virtual void prepareTrophyImage() {
        CCLog("Please overload  this API (prepareTrophyImage) when u need");
    }


    virtual void saveGoodsForStoreType(CCDictionary *dictGoods, CCArray *arrKey, StoreType type ) {
        CCLog("Please overload  this API (saveGoodsForType) when u need");
    }
    
    virtual RawGoodsInfo* goodsForStoreType (StoreType type, int *num ) {
        CCLog("Please overload  this API (goodsForStoreType) when u need");
        return NULL;
    }
    
    virtual char** arrayWithJSONKey( const char *rawJSONText, const char *key,  int *num ){
        return NULL;
    }
    
};



#endif /* defined(__paigow_ipad__platform__) */
