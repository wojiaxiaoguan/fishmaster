#include "AppDelegate.h"
#include "introLayer.h"
#include "Sound.h"
#include "GameData.h"
#ifdef USING_UMENG
#include "MobClickCpp.h"
#endif
USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    CCSize szFrame = CCEGLView::sharedOpenGLView()->getFrameSize();
//    int t_x = 1136;
//    int t_y = 640;
//    if (szFrame.width == 2048 ||szFrame.width == 1024) {
//        t_x = 1024;
//        t_y = 768;
//    }
//    if (szFrame.width == 960 || szFrame.width == 480) {
//        t_x = 960;
//        t_y = 640;
//    }
//    if (szFrame.width == 1136) {
//        t_x = 1136;
//        t_y = 640;
//    }
//    if (szFrame.width == 1280 ) {
//        t_x = 1024;
//        t_y = 768;
//    }
//    if (szFrame.height == 1080) {
//        t_x = 1024;
//        t_y = 768;
//    }
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, kResolutionFixedWidth);
	
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    Sound::Instance()->initSound();
    
    
    CCFileUtils::sharedFileUtils()->addSearchPath("ios");
    CCFileUtils::sharedFileUtils()->addSearchPath("music/fish");
    CCFileUtils::sharedFileUtils()->addSearchPath("music/music");
    CCFileUtils::sharedFileUtils()->addSearchPath("music/sound");
    CCFileUtils::sharedFileUtils()->addSearchPath("fonts");
    CCFileUtils::sharedFileUtils()->addSearchPath("config");
    CCFileUtils::sharedFileUtils()->addSearchPath("Particle");

    // create a scene. it's an autorelease object
//    CCScene *pScene = IntroLayer::scene();

    CCScene *pScene = IntroLayer::scene();
    DF_LOG("AppDelegate::applicationDidFinishLaunching  pScene = %d",pScene);
    // run
    pDirector->runWithScene(pScene);
//    std::string str =
//#ifndef TEST_BAIBAO
        const char* str =GameData::getSharedGameData()->getChannel()->getCString();
        const char* appkey =GameData::getSharedGameData()->getAPPKey()->getCString();
    DF_LOG("getChannel %s   appkey  %s",str,appkey);
#ifdef USING_UMENG
 MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL(appkey, str);
#endif
    
//#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
//    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    Sound::Instance()->pauseMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
#ifdef USING_UMENG
    umeng::MobClickCpp::applicationDidEnterBackground();
#endif
    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
//    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    DF_LOG("applicationWillEnterForeground");
    Sound::Instance()->resumeMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
#ifdef USING_UMENG
    umeng::MobClickCpp::applicationWillEnterForeground();
#endif
    
}



