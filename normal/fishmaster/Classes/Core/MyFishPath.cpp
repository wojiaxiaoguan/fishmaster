//
//  MyFishPath.cpp
//  fish
//
//  
//
//

#include "MyFishPath.h"
#include "Fish.h"


bool CCCircle::initWithDuration(float t, CCPoint center,float radius,float start)
{
    if (CCActionInterval::initWithDuration(t))
    {
        m_center = center;
        m_radius = radius;
        m_start = start;
        return true;
    }
    
    return false;
}


CCCircle* CCCircle::create(float t, CCPoint center, float radius, float start)
{
    CCCircle *pc = new CCCircle();
    pc->initWithDuration(t, center,radius,start);
    pc->autorelease();
    
    return pc;
}


void CCCircle::update(float time)
{
    if (m_pTarget)
    {
        
        CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
        CCPoint current = this->getTarget()->getPosition();
        
        if(last.x != -500 || last.y != -500) {
            double angle = atan2((current.y-last.y),(current.x-last.x));
            this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
        }
        ((Fish*)this->getTarget())->m_lastPoint = current;
        m_pTarget->setPosition(m_center + ccp(m_radius*cos(m_start + (2*M_PI)*time),m_radius*sin(m_start + (2*M_PI)*time)));
    }
}


CCMoveFromBy * CCMoveFromBy::create(float duration, const cocos2d::CCPoint &from, const cocos2d::CCPoint &deltaPosition)
{
    CCMoveFromBy * pn = new CCMoveFromBy;
    pn->initWithDuration(duration, from, deltaPosition);
    
    return pn;
}

bool CCMoveFromBy::initWithDuration(float duration, const CCPoint& from, const CCPoint& deltaPosition)
{
    m_from = from;
    m_started = false;
    return CCMoveBy::initWithDuration(duration, deltaPosition);
}

void CCMoveFromBy::update(float time)
{
    if(!m_started && getTarget()) {
        getTarget()->setPosition(m_from);
        m_started = true;
    }
    
    return CCMoveBy::update(time);
}






//++++++++++++++++++++++++++++++


//static inline float tuoyuanXat( float a, float bx, float c, float t )//返回X坐标
//{
//    //参数方程
//    //return -a*cos(2*M_PI*t)+a;
//    //float x = -a*cos(2*M_PI*t)+a;
//    return a*cos(2*M_PI*t);
//}
//static inline float tuoyuanYat( float a, float by, float c, float t )//返回Y坐标
//{
//    float b = sqrt(powf(a, 2) - powf(c, 2));//因为之前定义的参数是焦距c而不是短半轴b，所以需要计算出b
//    //参数方程
//    return b*sin(2*M_PI*t);
//}

CCPoint getEllipsePos(float a, float b,float angle,float t)
{
    float x = a*cos(2*M_PI*t);
    float y = b*sin(2*M_PI*t);
    
    float u = x*cos(angle)+y*sin(angle);
    float v = x*sin(angle)-y*cos(angle);
    
    return ccp(u,v);
}


CCEllipseBy* CCEllipseBy::create(float t, const ccEllipseConfig& c)//利用之前定义的椭圆的三个参数初始化椭圆
{
    CCEllipseBy *pTuoyuanBy = new CCEllipseBy();
    pTuoyuanBy->initWithDuration(t, c);
    pTuoyuanBy->autorelease();
    
    return pTuoyuanBy;
}

bool CCEllipseBy::initWithDuration(float t, const ccEllipseConfig& c)
{
    if (CCActionInterval::initWithDuration(t))
    {
        m_sConfig = c;
        return true;
    }
    
    return false;
}
void CCEllipseBy::update(float time)
{
    if (m_pTarget)
    {
        //rotate
        CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
        CCPoint current = this->getTarget()->getPosition();
        
        if(last.x != -500 || last.y != -500) {
            double angle = atan2((current.y-last.y),(current.x-last.x));
            this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
        }
        ((Fish*)this->getTarget())->m_lastPoint = current;
        
        //
        CCPoint s_startPosition =m_sConfig.centerPosition;//中心点坐标
        float a = m_sConfig.aLength;
        float b = m_sConfig.bLength;
        float angle = m_sConfig.angle;
        m_pTarget->setPosition(ccpAdd(s_startPosition, getEllipsePos(a,b,angle,time)));//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标
    }
}




bool CCHelix::initWithDuration(float t, CCPoint center,float minRadius,float maxRadius,float start)
{
    if (CCActionInterval::initWithDuration(t))
    {
        m_center = center;
        m_minRadius = minRadius;
        m_maxRadius = maxRadius;
        m_start = start;
        return true;
    }
    
    return false;
}


CCHelix* CCHelix::create(float t, CCPoint center,float minRadius,float maxRadius,float start)
{
    CCHelix *pc = new CCHelix();
    pc->initWithDuration(t, center,minRadius,maxRadius,start);
    pc->autorelease();
    
    return pc;
}


void CCHelix::update(float time)
{
    if (m_pTarget)
    {
        
        CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
        CCPoint current = this->getTarget()->getPosition();
        
        if(last.x != -500 || last.y != -500) {
            double angle = atan2((current.y-last.y),(current.x-last.x));
            this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
        }
        ((Fish*)this->getTarget())->m_lastPoint = current;
        m_pTarget->setPosition(m_center + ccp(((m_maxRadius-m_minRadius)*time+m_minRadius)*cos(m_start + (6*M_PI)*time),((m_maxRadius-m_minRadius)*time+m_minRadius)*sin(m_start + (6*M_PI)*time)));
    }
}