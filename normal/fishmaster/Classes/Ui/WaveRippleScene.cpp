#include "WaveRippleScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* WaveRippleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    WaveRippleScene *layer = WaveRippleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WaveRippleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
   
    
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("introBg.plist");
    rippleSprite = pgeRippleSprite::create("log.jpg");
 //   rippleSprite->retain();
//    rippleSprite->setPosition(ccp(160,240));
//    rippleSprite->setScale(0.5);
    //rippleSprite->setScale(480.0 / 320);
    this->addChild(rippleSprite);
    
//    rippleSprite->setRotation(20);

    this->scheduleUpdate();

    return true;
}



void WaveRippleScene::update(float dt)
{
    rippleSprite->update(dt);
    
}

#pragma mark - touch events

bool WaveRippleScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return rippleSprite->ccTouchBegan(pTouch, pEvent);
}



void WaveRippleScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return rippleSprite->ccTouchMoved(pTouch, pEvent);
}


void WaveRippleScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return rippleSprite->ccTouchCancelled(pTouch, pEvent);
}


void WaveRippleScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return rippleSprite->ccTouchEnded(pTouch, pEvent);
}

