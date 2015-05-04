//
//  Coin.h
//  fish
//
//  
//
//

#ifndef __fish__Coin__
#define __fish__Coin__

#include "cocos2d.h"
#include "common.h"
#include <iostream>

class Coin : public cocos2d::CCSprite
{
public:
    enum CoinType{
        COIN_TYPE_GOLDSMALL,
        COIN_TYPE_GOLDBIG
    };
    static Coin* create(CoinType type);
    Coin(CoinType type);
    void addLinePathTo(float duration, cocos2d::CCPoint p);
    void goCoin();
    
    void coinStopCBK();
    void coinStepCBK();
    ~Coin(){};
    
protected:
    void generateFrameAnimation();
    
    CoinType m_coinType;
    cocos2d::CCAnimation* m_animation;
    cocos2d::CCArray * m_coinPath;
    int m_coinPathStep;
    float m_frameDelay;
    int m_frameCount;
};

#endif /* defined(__fish__Coin__) */
