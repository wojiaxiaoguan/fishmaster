//
//  FishPath.h
//  fish
//
//  
//
//

#ifndef __fish__FishPath__
#define __fish__FishPath__

#include <iostream>
#include "cocos2d.h"
#include "common.h"
#include "Fish.h"


class CCFishBezierTo : public cocos2d::CCBezierTo
{
public:
    virtual void update(float time);
    
    static CCFishBezierTo* create(float t, const cocos2d::ccBezierConfig& c);
    
    bool initWithDuration(float t, const cocos2d::ccBezierConfig &c);
    
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
};



class CCFishCardinalSplineTo : public cocos2d::CCCardinalSplineTo
{
public:
    virtual void update(float time);
    //create(时间间隔，点数组，拉力系数)
    static CCFishCardinalSplineTo* create(float duration, cocos2d::CCPointArray* points, float tension);
    
    bool initWithDuration(float duration, cocos2d::CCPointArray* points, float tension);
    //edit by andy 2015/03/16
    /*
     virtual CCObject* copyWithZone(cocos2d::CCZone *pZone);
     */
    virtual CCCardinalSplineTo* copyWithZone(cocos2d::CCZone *pZone);
};


class CCFishLineTo : public cocos2d::CCMoveTo
{
public:
    virtual void update(float time);
    
    static CCFishLineTo* create(float duration, const CCPoint& position);
    
    bool initWithDuration(float duration, const CCPoint& position);
    
    //virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
};


class Fish;

class FishPathFactory {
public:
    enum FishPathType{
        FISH_PATHTYPE_A = 0,
        FISH_PATHTYPE_B,
        FISH_PATHTYPE_C,
        FISH_PATHTYPE_D,
        FISH_PATHTYPE_E,
        FISH_PATHTYPE_STATIC
    };
    static void generateCurveFishPath(Fish * target);
    static void generateBezierFishPath(Fish * target);
    static void generateStaticFishPath(Fish * target);
    static void generateMultiBezierFishPath(Fish *target,cocos2d::CCPoint start,cocos2d::CCPoint end, int num);
    static void createFishPath(Fish* target);
    
    //for requirement
    static void generateFishPathA(Fish *target,cocos2d::CCPoint start=ccp(0,0),cocos2d::CCPoint end=ccp(0,0),bool direction=true);
    static void generateFishPathB(Fish *target,int type=-1,cocos2d::CCPoint start=ccp(0,0),cocos2d::CCPoint end=ccp(0,0));
    static void generateFishPathC(Fish *target);
    static void generateFishPathD(Fish *target);
    static void generateFishPathE(Fish *target);
    
    //for groups
    static void generateFishesPath(cocos2d::CCArray *pfishes);
    static void generateFishesPathA(cocos2d::CCArray *pfishes);
    static void generateFishesPathB(cocos2d::CCArray *pfishes);
    static void generateFishesPathC(cocos2d::CCArray *pfishes);
    static void generateFishesPathD(cocos2d::CCArray *pfishes);
    static void generateFishesPathE(cocos2d::CCArray *pfishes);
    static void generateFishesPathStatic(cocos2d::CCArray *pfishes);
    
    static FishPathType getFishPathType(Fish::FishType type);
    
private:
    
};

#endif /* defined(__fish__FishPath__) */