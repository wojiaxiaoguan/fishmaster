//
//  Coin.cpp
//  fish
//
//  
//
//

#include "Coin.h"
USING_NS_CC;

Coin* Coin::create(CoinType type)
{
    Coin * n = new Coin(type);
    //n->initWithDuration(t, c);
    n->init();
    n->generateFrameAnimation();
    n->autorelease();
    
    return n;
}

Coin::Coin(CoinType type):m_coinType(type),m_coinPathStep(0)
{
    m_coinPath = new CCArray();
    m_frameDelay = 0.02;
    switch(type){
        case COIN_TYPE_GOLDSMALL:
            m_frameCount = 12;
            break;
        case COIN_TYPE_GOLDBIG:
            m_frameCount = 12;
            break;
    }
}


void Coin::generateFrameAnimation()
{
    char str[32];
    const char *fmt = NULL;
    
    bzero(str,sizeof(str));
    CCArray *aniframe = CCArray::createWithCapacity(m_frameCount);
    
    switch(m_coinType){
        case COIN_TYPE_GOLDSMALL:
//            fmt = "yb_%d.png";
//            break;
        case COIN_TYPE_GOLDBIG:
            fmt = "jb_d%d.png";
            break;
    }
    
    for(int i=0;i <m_frameCount;i++){
        sprintf(str,fmt,i);  //通过下标动态创建精灵
        //CCSpriteFrame *frame =CCSpriteFrame::create(str,CCRectMake(0,0,64,128));
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        
        if(i==0){//默认添加第一帧图到界面上
            initWithSpriteFrame(frame);
            //setPosition(ccp(0,0));
        }
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
        
        m_animation = CCAnimation::createWithSpriteFrames(aniframe,m_frameDelay);//通过集合创建动画
        m_animation->retain();
    }
}

void Coin::addLinePathTo(float duration, cocos2d::CCPoint p)
{
    CCMoveTo *moveto = CCMoveTo::create(duration, p);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Coin::coinStepCBK));
    m_coinPath->addObject(CCEaseExponentialIn::create(moveto));
    m_coinPath->addObject(callFunc);
    if(m_coinPath->count() == 1) {
        m_coinPath->addObject(CCEaseExponentialIn::create(CCMoveTo::create(1,p)));
        //m_coinPath->addObject(callFunc);
    }
}

void Coin::goCoin()
{
    CCAnimate *animate=CCAnimate::create(m_animation);
    
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Coin::coinStopCBK));
    m_coinPath->addObject(callFunc);
    
    CCSpawn*  coinaction = CCSpawn::createWithTwoActions(CCRepeat::create(animate,3),CCSequence::create(m_coinPath));
    CCFiniteTimeAction *callFunc2 = CCCallFunc::create(this, callfunc_selector(Coin::removeFromParent));
    runAction(CCSequence::create(coinaction,callFunc2,NULL));
}

void Coin::coinStopCBK()
{
    // step control: how to use?
//    CCLog("step ");
    switch (m_coinPathStep) {
        case 0:
            
            break;
        case 1:
            break;
    }
}

void Coin::coinStepCBK()
{
    
}