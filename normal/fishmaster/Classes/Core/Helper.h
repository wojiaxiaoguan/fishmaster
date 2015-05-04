//
//  Helper.h
//  fish
//
//  
//
//

#ifndef __fish__Helper__
#define __fish__Helper__

#include "cocos2d.h"
#include "common.h"
#include <iostream>

enum NumberType{
    GameNumberGameLayerGold = 1,
    GameNumberStoreLayerGold,
    GameNumberStoreSubLayerGold,
    GameNumberGameLayerTime,
    GameNumberSotreUp,
    GameNumberYingxin
};

class NumSprite : public cocos2d::CCSprite
{
public:
    static NumSprite* create(int num, NumberType pType = GameNumberGameLayerGold);
    virtual void setOpacity(GLubyte opacity);
    
};


class GoldSprite : public cocos2d::CCSprite
{
public:
    static GoldSprite* create(int num);
    virtual void setOpacity(GLubyte opacity);
    void goAnimate();
    void updateGold(cocos2d::CCTime dt);
    int getWidth();
    void stepOver();
private:
    int m_num;
};



class GoldControl : public cocos2d::CCSprite
{
public:
    static GoldControl* create();
    void AddGold(int num);
    GoldControl();
    void updateGolds(cocos2d::CCTime dt);
    void moveGolds(cocos2d::CCTime dt);
private:
    cocos2d::CCArray *m_golds;
};


class CenterRoll : public cocos2d::CCSprite
{
public:
    static CenterRoll* create(int score);
    void generateFrameAnimation();
    void goAnimation();
private:
//    cocos2d::CCAnimation* m_frameAnimation;
    NumSprite *m_pnum;
};



extern bool isCCSpriteInterset(cocos2d::CCSprite* p1, cocos2d::CCSprite* p2);
#endif /* defined(__fish__Helper__) */
