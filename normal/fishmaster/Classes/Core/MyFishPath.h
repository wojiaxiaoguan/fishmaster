//
//  MyFishPath.h
//  fish
//
//  
//
//

#ifndef __fish__MyFishPath__
#define __fish__MyFishPath__

#include <iostream>
#include "cocos2d.h"
#include "common.h"

USING_NS_CC;


class  CCCircle : public CCActionInterval
{
public:
    bool initWithDuration(float t, CCPoint center,float radius,float start = 0);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    static CCCircle *create(float t, CCPoint center,float radius, float start = 0);
    
protected:
    CCPoint m_center;
    float m_radius;
    float m_start;
};


class CCMoveFromBy : public CCMoveBy
{
public:
    static CCMoveFromBy* create(float duration, const CCPoint& from,const CCPoint& deltaPosition);
    bool initWithDuration(float duration, const CCPoint& from, const CCPoint& deltaPosition);
    virtual void update(float time);
protected:
    CCPoint m_from;
    bool m_started;
};



typedef struct _ccEllipseConfig {
    //中心点坐标
    CCPoint centerPosition;
    float aLength;
    float bLength;
    float angle;
} ccEllipseConfig;


class CCEllipseBy : public CCActionInterval
{
public:
    //用“动作持续时间”和“椭圆控制参数”初始化动作
    bool initWithDuration(float t, const ccEllipseConfig& c);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    //用“动作持续时间”和“椭圆控制参数”创建动作
    static CCEllipseBy *create(float t, const ccEllipseConfig& c);
    
protected:
    ccEllipseConfig m_sConfig;
    CCPoint m_startPosition;
    CCPoint s_startPosition;
    CCPoint m_from;
};


class  CCHelix : public CCActionInterval
{
public:
    bool initWithDuration(float t, CCPoint center,float minRadius,float maxRadius,float start = 0);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    static CCHelix *create(float t, CCPoint center,float minRadius,float maxRadius, float start = 0);
    
protected:
    CCPoint m_center;
    float m_minRadius;
    float m_maxRadius;
    float m_start;
};



#endif /* defined(__fish__MyFishPath__) */
