//
//  JniUtil.h
//  CheatGame
//
//  
//
//

#ifndef __CheatGame__JniUtil__
#define __CheatGame__JniUtil__

#include <iostream>
#include "cocos2d.h"
#include "common.h"

USING_NS_CC;
using namespace std;

//调用Jni时传递的数据

#define JNI_JSON "{\"group\":\"%s\", \"func\":\"%s\", \"attr\":{%s}}"

#define CALL_JNI(__GROUP__, __FUNC__, __ATTR__) JniUtil::callJni(CCString::createWithFormat(JNI_JSON, __GROUP__,__FUNC__, __ATTR__)->getCString());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

class JniUtil : public cocos2d::CCObject{
    
public:
    
    static void callJni(const char * data);
    
    static char* jstringToChar(JNIEnv *env, jstring jstr);
    
    /**
     * 调用 Java 静态 Void 方法
     *
     * @param pGroup 组
     * @param pFunc 方法
     * @param pParams 参数
     */
    static void callStaticVoidMethod(const char* pGroup, const char* pFunc, const char* pParams);
    
    /**
     * 调用 Java 静态空方法
     *
     * @param pGroup 组
     * @param pFunc 方法
     */
    static void callStaticVoidMethod(const char* pGroup, const char* pFunc);
    
//    static int getMyIsMute4Effect();
    /**
     * 调用 Java 静态 String 方法
     *
     * @param pFunc 方法
     * @param pParams 参数
     */
    static const char* callStaticStringMethod(const char* pFunc, const char* pParams);
    
    /**
     * 调用 Java 静态 String 方法
     *
     * @param pFunc 方法
     */
    static const char* callStaticStringMethod(const char* pFunc);
    
    /**
     * 调用 Java 静态 Boolean 方法
     *
     * @param pFunc 方法
     * @param pParams 参数
     */
    static bool callStaticBooleanMethod(const char* pFunc, const char* pParams);
    
    /**
     * 调用 Java 静态 Boolean 方法
     *
     * @param pFunc 方法
     */
    static bool callStaticBooleanMethod(const char* pFunc);
};

#endif

#endif /* defined(__CheatGame__JniUtil__) */
