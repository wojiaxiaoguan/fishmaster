//
//  JniUtil.cpp
//  CheatGame
//
//  
//
//

#include "JniUtil.h"
#include "GameData.h"
#include "GameLayer.h"
#include "GameStore.h"
#include "Sound.h"
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

#define CALL_JAVA_JSON_STRING "{ \"func\": \"%s\", \"param\": {%s} }"
#define JAVA_PLATFORM_TAG "---- JniUtil ----  ||  "

#define CALL_JAVA_JSON_VOID "{ \"group\": \"%s\", \"func\": \"%s\", \"param\": {%s} }"
#define CALL_JAVA_JSON_BOOLEAN "{ \"func\": \"%s\", \"param\": {%s} }"
#define CALL_JAVA_JSON_STRING "{ \"func\": \"%s\", \"param\": {%s} }"

void JniUtil::callJni(const char *data){
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    const char * jniClass = "com/ipeaksoft/pitDadGame/GameSceneActivity";
    bool isHave = JniHelper::getStaticMethodInfo(minfo,jniClass,"callJni","(Ljava/lang/String;)V");
    if (!isHave) {
        CCLog("jni->%s/callJni:此函数不存在", jniClass);
    }else{
        CCLog("jni->%s/callJni:此函数存在", jniClass);
        jstring jdata = minfo.env->NewStringUTF(data);
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jdata);
    }
    CCLog("jni-java函数执行完毕");
}

void JniUtil::callStaticVoidMethod(const char *pGroup, const char *pFunc, const char *pParam) {
    
    JniMethodInfo minfo;
    const char* pClassName = "com/ipeaksoft/agent/GameAgent";
    const char* pMethodName = "execTask";
    const char* pSignature = "(Ljava/lang/String;)V";
    bool isExistsMethod = JniHelper::getStaticMethodInfo(minfo, pClassName, pMethodName, pSignature);
    
    if (isExistsMethod) {
        CCLOG("%s开始执行：%s", JAVA_PLATFORM_TAG, pMethodName);
        const char* pJsonData = CCString::createWithFormat((char*) CALL_JAVA_JSON_VOID, pGroup, pFunc, pParam)->getCString();
        jstring jdata = minfo.env->NewStringUTF(pJsonData);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jdata);
        CCLOG("%s结束执行：%s", JAVA_PLATFORM_TAG, pMethodName);
    } else {
        CCLOG("%s方法不存在：%s", JAVA_PLATFORM_TAG, pMethodName);
    }
}

void JniUtil::callStaticVoidMethod(const char *pGroup, const char *pFunc) {
    callStaticVoidMethod(pGroup, pFunc, "");
}

//int JniUtil::getMyIsMute4Effect(){
//    int v = 0;
//    JniMethodInfo minfo;//定义Jni函数信息结构体
//    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
//    const char * jniClass = "com/ipeaksoft/pitDadGame/GameSceneActivity";
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,jniClass,"getIsMute4Effect","()I");
//    if (!isHave) {
//        CCLog("jni->%s/callJni:此函数不存在", jniClass);
//    }else{
//        CCLog("jni->%s/callJni:此函数存在", jniClass);
//        //调用此函数
//        v = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
//    }
//    CCLog("jni-java函数执行完毕");
//    return v;
//}

char* JniUtil::jstringToChar(JNIEnv *env, jstring jstr)
{
    char * rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("UTF-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte * ba = env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen > 0)
    {
        rtn = (char*)malloc(alen+1); //new char[alen+1];
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);
    
    return rtn;
}

const char* JniUtil::callStaticStringMethod(const char* pFunc, const char* pParam) {
    string result;
    JniMethodInfo minfo;
    const char* pClassName = "com/ipeaksoft/agent/GameAgent";
    const char* pMethodName = "execStringTask";
    const char* pSignature = "(Ljava/lang/String;)Ljava/lang/String;";
    bool isExistsMethod = JniHelper::getStaticMethodInfo(minfo, pClassName, pMethodName, pSignature);
    
    if (isExistsMethod) {
        CCLOG("%s开始执行：%s", JAVA_PLATFORM_TAG, pMethodName);
        const char* pJsonData = CCString::createWithFormat((char*) CALL_JAVA_JSON_STRING, pFunc, pParam)->getCString();
        jstring jsonData = minfo.env->NewStringUTF(pJsonData);
        jstring jresult = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, jsonData);
        result = minfo.env->GetStringUTFChars(jresult, 0);
        CCLOG("%s结束执行：%s", JAVA_PLATFORM_TAG, pMethodName);
    } else {
        CCLOG("%s方法不存在：%s", JAVA_PLATFORM_TAG, pMethodName);
    }
    return result.empty() ? NULL : result.c_str();
}

const char* JniUtil::callStaticStringMethod(const char* pFunc) {
    return callStaticStringMethod(pFunc, "");
}

bool JniUtil::callStaticBooleanMethod(const char *pFunc, const char *pParam) {
    jboolean result = JNI_FALSE;
    JniMethodInfo minfo;
    const char* pClassName = "com/ipeaksoft/agent/GameAgent";
    const char* pMethodName = "execBooleanTask";
    const char* pSignature = "(Ljava/lang/String;)Z";
    
    bool isExistsMethod = JniHelper::getStaticMethodInfo(minfo, pClassName, pMethodName, pSignature);
    if (isExistsMethod) {
        CCLOG("%s开始执行：%s", JAVA_PLATFORM_TAG, pMethodName);
        const char* pJsonData = CCString::createWithFormat((char*) CALL_JAVA_JSON_STRING, pFunc, pParam)->getCString();
        jstring jsonData = minfo.env->NewStringUTF(pJsonData);
        result = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, jsonData);
        CCLOG("%s结束执行：%s", JAVA_PLATFORM_TAG, pMethodName);
    } else {
        CCLOG("%s方法不存在：%s", JAVA_PLATFORM_TAG, pMethodName);
    }
    return result == JNI_TRUE;
}

bool JniUtil::callStaticBooleanMethod(const char *pFunc) {
    return callStaticBooleanMethod(pFunc, "");
}

extern "C"
{
    void Java_com_ipeaksoft_agent_GameJNI_postPay(JNIEnv*  env, jobject thiz, jboolean isSuccess,jint id,jint channelID)
    {
        //这里java调用postPay;，这里就会被调用。jint a = 1
        CCLOG("java call c++....   postPay");
        DF_LOG("----------isSuccess =%d ",isSuccess);
        if(isSuccess)
        {
            DF_LOG("id = %d" , id);
            int m_id = id>=1010?2:1;
            switch (m_id) {
                case 1:
                {
                    GameData* pData = GameData::getSharedGameData();
                    pData->provideProduct((ProductType)id);
                    GameStoreLayer* pGameStoreLayer = (GameStoreLayer*)GameData::getSharedGameData()->getDataPoint(DT_Shop);
                    if (pGameStoreLayer)
                    {
                        if(id == 1009)
                        {
                           pGameStoreLayer->fastCloseCallback(NULL);
                        }
                        else
                            
                        {
                           pGameStoreLayer->setFastBuyVisible(false);
                        }
                        
                    }
                    
                    
                }
                    break;
                case 2:
                {
                    DF_LOG("----------   start");
                    //                CCNotificationCenter::sharedNotificationCenter()->postNotification("Game_Task_Buy_Info",CCInteger::create(id));
                    GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
                    if (pGameLayer)
                    {
                        pGameLayer->buyTaskSuccess((ProductType)id);
                    }
                    DF_LOG("----------   end");
                }
                    break;
                    
                default:
                    break;
            }
        }
        else
        {
            DF_LOG("支付失败 id=%d" , id);
        }
        
        
        
    }
    void Java_com_ipeaksoft_agent_GameJNI_onShowAd(JNIEnv*  env, jobject thiz)
    {
        //这里java调用onShowAd;，这里就会被调用。jint a = 1
        CCLOG("java call c++....   onShowAd");
        
    }
    void Java_com_ipeaksoft_agent_GameJNI_setChannel(JNIEnv*  env, jobject thiz,jstring channel,jint version)
    {
        //这里java调用setChannel;，这里就会被调用。jint a = 1
        CCLOG("java call c++....   setChannel");
        const char *c_str = NULL;
        jboolean isCopy;    // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
        c_str = JniUtil::jstringToChar(env, channel);
        if(c_str == NULL)
        {
            return ;
        }
        DF_LOG("C_str: %s \n", c_str);
        //GameData::getSharedGameData()->setChannel(c_str);

    }
    void Java_com_ipeaksoft_agent_GameJNI_setUmengChannel(JNIEnv*  env, jobject thiz,jstring appKey,jstring channel)
       {
           //这里java调用setChannel;，这里就会被调用。jint a = 1
           CCLOG("java call c++....   setUmengChannel");
           const char *c_str = NULL;
           jboolean isCopy;    // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
           c_str = JniUtil::jstringToChar(env, channel);
           if(c_str == NULL)
           {
               return ;
           }
           DF_LOG("Chanle =: %s \n", c_str);
           GameData::getSharedGameData()->setChannel(c_str);
           c_str = JniUtil::jstringToChar(env, appKey);
           if(c_str == NULL)
           {
               return ;
           }
           DF_LOG("Chanle =: %s \n", c_str);
           GameData::getSharedGameData()->setAPPKey(c_str);
       }
   
    void Java_com_ipeaksoft_agent_GameJNI_setMusicEnabled(JNIEnv*  env, jobject thiz,jboolean isOpen)
    {
        //这里java调用setChannel;，这里就会被调用。jint a = 1
        CCLOG("java call c++....   setMusicEnabled isOpen =%d",isOpen);
        Sound::Instance()->setCloseSound(!isOpen);
        
    }
    void Java_com_ipeaksoft_agent_GameJNI_exitApp(JNIEnv*  env, jobject thiz)
    {
        //这里java调用exitApp;，这里就会被调用。jint a = 1
        CCLOG("java call c++....   exitApp ");
        GameData::getSharedGameData()->exitGame();
        
    }

}

#endif