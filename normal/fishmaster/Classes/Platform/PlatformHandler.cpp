#include "PlatformHandler.h"
#include "JniUtil.h"
#include "GameData.h"
#include "cocos2d.h"

#define NO_NETWORK_TOAST \
if(!isNetworkAvailable()){\
toast(NO_NETWORK_MSG);\
return;\
}//提示无网络//


#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
template <typename TYPE, void (TYPE::*_RunThread)()>
void* _thread_t(void* param)
{
    TYPE* This = (TYPE*)param;
    This->_RunThread();
    return NULL;
}
#endif

PlatformHandler* PlatformHandler::_pSingleInstance = NULL;
PlatformHandler* PlatformHandler::getInstance() {
    if (_pSingleInstance == NULL) {
        _pSingleInstance = new PlatformHandler();
    }
    return _pSingleInstance;
}

void PlatformHandler::destroy() {
    if (_pSingleInstance != NULL) {
        _pSingleInstance = NULL;
    }
}

PlatformHandler::PlatformHandler()
{

    postCode = 0;

    
}
PlatformHandler::~PlatformHandler()
{
  
}
void PlatformHandler::initPay()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    DF_LOG("init android pay");
    string pParam = cocos2d::CCString::createWithFormat((char*) "\"payPlatformName\": MM")->getCString();
    JniUtil::callStaticVoidMethod("pay", "initPay",pParam.c_str());
#endif
}
void PlatformHandler::pay(ProductType id) {
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    DF_LOG("PlatformHandler::pay(%d)",id);
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    DF_LOG("PlatformHandler::pay(%d)",id);
    
    if (GameData::getSharedGameData()->isBuyFishKnife() && (id == Product_FishKnife ))
    {
        //判断旋风鱼刀是否已经解锁
        string pParam = CCString::createWithFormat((char*) "\"message\": \"%s\"", "您已解锁旋风鱼刀")->getCString();
        JniUtil::callStaticVoidMethod("common", "showToast", pParam.c_str());
        postPay(false, Product_FishKnife, DEFAULT);
        return;
    }
    DF_LOG("Product_PearlShell : ",Product_PearlShell);
    if(id == Product_PearlShell)
    {
        
        CCString* str = CCString::createWithFormat("m_fish_lock_24");
        int islock = CCUserDefault::sharedUserDefault()->getIntegerForKey(str->getCString(), -1);
        DF_LOG("Product_PearlShell : islock =%d",islock);
        if(islock == 0)
        {
            //判断珍珠贝是否解锁
            string pParam = CCString::createWithFormat((char*) "\"message\": \"%s\"", "您已解锁珍珠贝")->getCString();
            JniUtil::callStaticVoidMethod("common", "showToast", pParam.c_str());
            postPay(false, Product_PearlShell, DEFAULT);
            return;
        }
    }
    
    
    string pParam = CCString::createWithFormat((char*) "\"id\": %d", (int) id)->getCString();
    JniUtil::callStaticVoidMethod("pay", "pay", pParam.c_str());
    DF_LOG("PlatformHandler::pay end");

#endif
}
void PlatformHandler::postPay(bool isSuccess, ProductType goodsId, PayChannelId payChannelId) {
    
    
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    //  TODO
    CCLOG("postPay test");
    if (!isSuccess) {
        CCLOG("faile  call back");
        
//        Director::getInstance()->getScheduler()->schedule(schedule_selector(PlatformHandler::buyWithoutNetCallback), this, 0, 0, 1, false);
        return;
    }
    
    CCLOG("goodsId----->%d",goodsId);
    CCLOG("payChannelId----->%d",payChannelId);
    GameData::getSharedGameData()->provideProduct( goodsId);
    
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    
#endif
}
void PlatformHandler::postPay(ProductType goodsId, PayChannelId payChannelId) {
    CCLOG("post pay by ttt: %d, %d", goodsId, payChannelId);
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    
   
    GameData::getSharedGameData()->provideProduct(goodsId);
    
#endif
}
void PlatformHandler::postPayScheduleCallBack(float t,void * data,std::string name)
{
    
}
void PlatformHandler::postPayCallBack(float dt){
   
}
void PlatformHandler::buyWithoutNetCallback(float dt)
{
   }
//恢复购买
void PlatformHandler::restorePurchase()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#endif
    
}
void PlatformHandler::exitApp()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    DF_LOG("PlatformHandler::exitApp");
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    DF_LOG("PlatformHandler::exitApp");
    string pParam = CCString::createWithFormat((char*) "\"message\": \"%s\"", "exitapp")->getCString();
    JniUtil::callStaticVoidMethod("common", "gameEND", pParam.c_str());
    DF_LOG("PlatformHandler::exitApp end");
    
#endif

}
void PlatformHandler::openFeedback()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    DF_LOG("PlatformHandler::openFeedback");
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    DF_LOG("PlatformHandler::openFeedback");
    string pParam = CCString::createWithFormat((char*) "\"message\": \"%s\"", "openFeedback")->getCString();
    JniUtil::callStaticVoidMethod("common", "openFeedback", pParam.c_str());
    DF_LOG("PlatformHandler::exitApp end");
    
#endif
    
}
void PlatformHandler::moreGame()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    DF_LOG("PlatformHandler::moreGame");
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    DF_LOG("PlatformHandler::moreGame");
    string pParam = CCString::createWithFormat((char*) "\"message\": \"%s\"", "moreGame")->getCString();
    JniUtil::callStaticVoidMethod("common", "moreGame", pParam.c_str());
    DF_LOG("PlatformHandler::moreGame end");
    
#endif
    
}
void PlatformHandler::toast(const char *message){
    
    CCLOG("---------------PlatformUtil::toast()");
    
#if MC_IS_IOS
#elif MC_IS_ANDROID
    //    CCString *data = CCString::createWithFormat("\"message\":\"%s\"", message);
    //    CALL_JNI("common", "toast", data->getCString());
#endif
}
