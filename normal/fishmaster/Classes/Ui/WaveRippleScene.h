#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "common.h"
#include "CCRippleSprite.h"


class WaveRippleScene : public cocos2d::CCLayer
{
public:
    
    WaveRippleScene(){}
    ~WaveRippleScene(){}
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(WaveRippleScene);
    
    void autoRipples();
    
    void update(float dt);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
private:
    pgeRippleSprite *rippleSprite;
};

#endif // __HELLOWORLD_SCENE_H__
