//
//  FishPath.cpp
//  fish
//
//  
//
//

#include "FishPath.h"
#include "Fish.h"

USING_NS_CC;


void CCFishBezierTo::update(float time)
{
    
    CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
    CCPoint current = this->getTarget()->getPosition();
    
    double angle = atan2((current.y-last.y),(current.x-last.x));
    this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
    
    ((Fish*)this->getTarget())->m_lastPoint = current;
    return CCBezierTo::update(time);
};

CCFishBezierTo* CCFishBezierTo::create(float t, const ccBezierConfig& c)
{
    CCFishBezierTo * n = new CCFishBezierTo();
    n->initWithDuration(t, c);
    n->autorelease();
    
    return n;
}


bool CCFishBezierTo::initWithDuration(float t, const cocos2d::ccBezierConfig &c)
{
    return CCBezierTo::initWithDuration(t, c);
}

CCObject* CCFishBezierTo::copyWithZone(cocos2d::CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFishBezierTo* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CCFishBezierTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCFishBezierTo();
        pZone = pNewZone = new CCZone(pRet);
    }
    
    CCBezierTo::copyWithZone(pZone);
    
    pRet->initWithDuration(this->getDuration(),this->m_sToConfig);
    
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}


void CCFishLineTo::update(float time)
{
    
    CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
    CCPoint current = this->getTarget()->getPosition();
    
    double angle = atan2((current.y-last.y),(current.x-last.x));
    this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
    
    ((Fish*)this->getTarget())->m_lastPoint = current;
    return CCMoveTo::update(time);
};

CCFishLineTo* CCFishLineTo::create(float duration, const cocos2d::CCPoint &position)
{
    CCFishLineTo * n = new CCFishLineTo();
    n->initWithDuration(duration, position);
    n->autorelease();
    
    return n;
}


bool CCFishLineTo::initWithDuration(float duration, const cocos2d::CCPoint &position)
{
    return CCMoveTo::initWithDuration(duration, position);
}

//CCObject* CCFishLineTo::copyWithZone(cocos2d::CCZone *pZone)
//{
//    CCZone* pNewZone = NULL;
//    CCFishBezierTo* pRet = NULL;
//    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
//    {
//        pRet = (CCFishBezierTo*)(pZone->m_pCopyObject);
//    }
//    else
//    {
//        pRet = new CCFishBezierTo();
//        pZone = pNewZone = new CCZone(pRet);
//    }
//    
//    CCFishLineTo::copyWithZone(pZone);
//    
//    pRet->initWithDuration(this->getDuration(),this->m_sToConfig);
//    
//    CC_SAFE_DELETE(pNewZone);
//    return pRet;
//}





CCFishCardinalSplineTo* CCFishCardinalSplineTo::create(float duration, cocos2d::CCPointArray *points, float tension)
{
    CCFishCardinalSplineTo * n = new CCFishCardinalSplineTo();
    n->initWithDuration(duration, points,tension);
    n->autorelease();
    
    return n;
}


bool CCFishCardinalSplineTo::initWithDuration(float duration, cocos2d::CCPointArray *points, float tension)
{
    return CCCardinalSplineTo::initWithDuration(duration,points,tension);
}


void CCFishCardinalSplineTo::update(float time)
{
    
    CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
    CCPoint current = this->getTarget()->getPosition();
    
    double angle = atan2((current.y-last.y),(current.x-last.x));
    this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
    
    ((Fish*)this->getTarget())->m_lastPoint = current;
    return CCCardinalSplineTo::update(time);
};
//edit by andy 2015/03/16
/*
 CCObject* CCFishCardinalSplineTo::copyWithZone(cocos2d::CCZone *pZone)
 */
CCCardinalSplineTo* CCFishCardinalSplineTo::copyWithZone(cocos2d::CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFishCardinalSplineTo* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CCFishCardinalSplineTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCFishCardinalSplineTo();
        pZone = pNewZone = new CCZone(pRet);
    }
    
    CCCardinalSplineTo::copyWithZone(pZone);
    
    pRet->initWithDuration(this->getDuration(), this->m_pPoints, this->m_fTension);
    
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}




CCPoint getMDCurvePoint(CCPoint start, CCPoint end, int distance,bool plus)
{
    float angle = atan2f(start.y - end.y, start.x - end.x);
    
    if(plus)
        angle += M_PI/2;
    else
        angle -= M_PI/2;
    
    int x = distance*cosf(angle);
    int y = distance*sinf(angle);
    
    return (start+end)/2 + ccp(x,y);
}


CCPoint getMDCurvePointRate(CCPoint start, CCPoint end, float rate,bool plus)
{
    float angle = atan2f(start.y - end.y, start.x - end.x);
    
    if(plus)
        angle += M_PI/2;
    else
        angle -= M_PI/2;
    
    int distance = rate * sqrt((start.x-end.x)*(start.x-end.x) + (start.y-end.y)*(start.y-end.y))/2;
    
    int x = distance*cosf(angle);
    int y = distance*sinf(angle);
    
    return (start+end)/2 + ccp(x,y);
}

CCPoint genRandMDPoint(cocos2d::CCPoint & start, cocos2d::CCPoint &end)
{
    switch (arc4random()%3){
        case 0:
            return (end-start)/3+start;
        case 2:
            return (end-start)/3*2+start;
        case 1:
        default:
            return (end-start)/2+start;
    }
}

//CCPoint getReflectPoint(CCPoint start, CCPoint origin)
//{
//    return origin+(origin-start);
//}

CCPoint getReflectPoint(CCPoint start, CCPoint origin,float rate = 1)
{
    return origin+(origin-start)*rate;
}


CCFishBezierTo* generateBezierPath(CCPoint start, CCPoint c1, CCPoint c2, CCPoint end,float t)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = c1;
    bezier.controlPoint_2 = c2;
    bezier.endPosition = end;
    
    CCFishBezierTo * p = CCFishBezierTo::create(t,bezier);
    
    return p;
}


void FishPathFactory::generateStaticFishPath(Fish * target)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    target->m_fishPath = new CCArray();
    
    CCSize s = target->getContentSize();
    
    target->setPosition(ccp(arc4random()%(int)visibleSize.width, arc4random()%(int)visibleSize.height ));
    target->m_fishPath->addObject(CCMoveBy::create(60, ccp(0,0)));
}


void FishPathFactory::generateCurveFishPath(Fish * target)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    target->m_fishPath = new CCArray();
    
    
    //For big fish, only one path
    CCPoint start,c1,c2,end;
    float t1 = 15;
    int t2 = 10;
    CCSize s = target->getContentSize();
    int limit = 200;
    //int distance = 200;
    
    if(arc4random()%2) {
        start = ccp(-s.width,arc4random()%((int)visibleSize.height));
        end = ccp(visibleSize.width+s.width,arc4random()%((int)visibleSize.height));
    } else {
        target->setFlipX(true);
        start = ccp(visibleSize.width+s.width,arc4random()%((int)visibleSize.height));
        end = ccp(-s.width,arc4random()%((int)visibleSize.height));
    }
    
    if(start.y < limit && end.y < visibleSize.height/2)
        end.y+=(int)(visibleSize.height/2);
    if(end.y < limit && start.y < visibleSize.height/2)
        start.y += (int)(visibleSize.height/2);
    //c2 =ccp(0,(float)(arc4random()%200)+200);
    c1 = getMDCurvePoint(start,end,200,(arc4random()%2)?true:false);
    if(c1.y < 300) {
        c1.y += 300;
    }
    CCPointArray * array = CCPointArray::create(20);
    array->addControlPoint(start);
    array->addControlPoint(c1);
    array->addControlPoint(end);
    target->m_fishPath->addObject(CCFishCardinalSplineTo::create(arc4random()%t2+t1, array, 0));
    target->setPosition(start);
}


void FishPathFactory::generateBezierFishPath(Fish * target)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    target->m_fishPath = new CCArray();
    
    CCSize spriteSize = target->getContentSize();
    //For big fish, only one path
    CCPoint start,c1,c2,end;
    float t1 = 15;
    int t2 = 10;
    int blank = 100;
    
    switch(arc4random()%4) {
        case 0:
            start = ccp(-spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            end = ccp(visibleSize.width+spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            c1 = ccp((end.x - start.x)/4,visibleSize.height);
            c2 = ccp((end.x - start.x)/4*3,visibleSize.height);
            target->setPosition(start);
            target->m_fishPath->addObject(generateBezierPath(start, c1, c2, end, target->m_speedTime));
            break;
        case 1:
            target->setFlipX(true);
            start = ccp(-spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            end = ccp(visibleSize.width+spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            c1 = ccp((end.x - start.x)/4,visibleSize.height);
            c2 = ccp((end.x - start.x)/4*3,visibleSize.height);
            target->setPosition(end);
            target->m_fishPath->addObject(generateBezierPath(end, c2, c1, start, target->m_speedTime));
            break;
        case 2:
            start = ccp(-spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            end = ccp(visibleSize.width+spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            c1 = ccp((end.x - start.x)/4,MIN(end.y,start.y));
            c2 = ccp((end.x - start.x)/4*3,MIN(end.y,start.y));
            target->setPosition(start);
            target->m_fishPath->addObject(generateBezierPath(start, c1, c2, end, target->m_speedTime));
            break;
        case 3:
            target->setFlipX(true);
            start = ccp(-spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            end = ccp(visibleSize.width+spriteSize.width,arc4random()%((int)visibleSize.height-blank)+blank);
            c1 = ccp((end.x - start.x)/4,MIN(end.y,start.y));
            c2 = ccp((end.x - start.x)/4*3,MIN(end.y,start.y));
            target->setPosition(end);
            target->m_fishPath->addObject(generateBezierPath(end, c2, c1, start, target->m_speedTime));
            break;
    }
}



void FishPathFactory::generateMultiBezierFishPath(Fish *target, CCPoint start, CCPoint end,int num)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    target->m_fishPath = new CCArray();
    
    CCPoint c1,c2;
    CCPoint md,c21,c22;

    CCSize s = target->getContentSize();
    int blank = 100;
    
    if(start.x == 0 && start.y == 0) {
        start = ccp(-s.width,arc4random()%((int)visibleSize.height-blank)+blank);
        end = ccp(visibleSize.width+s.width,arc4random()%((int)visibleSize.height-blank)+blank);
    }
    
    if(num == -1)
        num = arc4random()%4;
    
    switch(num) {
        case 0:
            md = genRandMDPoint(start,end);
            c1 = ccp((md.x-start.x)/4+start.x,MAX(start.y,md.y));
            c2 = ccp((md.x - start.x)/4*3+start.x,MAX(start.y,md.y));
            c21 = ccp((end.x - md.x)/4+md.x,MIN(end.y,md.y));
            c22 = ccp((end.x - md.x)/4*3+md.x,MIN(end.y,md.y));
            
            target->m_fishPath->addObject(generateBezierPath(start, c1, c2, md, target->m_speedTime/2));
            target->m_fishPath->addObject(generateBezierPath(md, c21, c22, end, target->m_speedTime/2));
            target->setPosition(start);
            break;
        case 1:
            target->setFlipX(true);
            md = genRandMDPoint(start,end);
            c1 = ccp((md.x-start.x)/4+start.x,MAX(start.y,md.y));
            c2 = ccp((md.x - start.x)/4*3+start.x,MAX(start.y,md.y));
            c21 = ccp((end.x - md.x)/4+md.x,MIN(end.y,md.y));
            c22 = ccp((end.x - md.x)/4*3+md.x,MIN(end.y,md.y));
            
            target->m_fishPath->addObject(generateBezierPath(end, c22, c21, md, target->m_speedTime/2));
            target->m_fishPath->addObject(generateBezierPath(md, c2, c1, start, target->m_speedTime/2));
            target->setPosition(end);
            break;
        case 2:
            md = genRandMDPoint(start,end);
            c1 = ccp((md.x-start.x)/4+start.x,MIN(start.y,md.y));
            c2 = ccp((md.x - start.x)/4*3+start.x,MIN(start.y,md.y));
            c21 = ccp((end.x - md.x)/4+md.x,MAX(end.y,md.y));
            c22 = ccp((end.x - md.x)/4*3+md.x,MAX(end.y,md.y));
            
            target->m_fishPath->addObject(generateBezierPath(start, c1, c2, md, target->m_speedTime/2));
            target->m_fishPath->addObject(generateBezierPath(md, c21, c22, end, target->m_speedTime/2));
            target->setPosition(start);
            break;
        case 3:
            target->setFlipX(true);
            md = genRandMDPoint(start,end);
            c1 = ccp((md.x-start.x)/4+start.x,MIN(start.y,md.y));
            c2 = ccp((md.x - start.x)/4*3+start.x,MIN(start.y,md.y));
            c21 = ccp((end.x - md.x)/4+md.x,MAX(end.y,md.y));
            c22 = ccp((end.x - md.x)/4*3+md.x,MAX(end.y,md.y));
            
            target->m_fishPath->addObject(generateBezierPath(end, c22, c21, md, target->m_speedTime/2));
            target->m_fishPath->addObject(generateBezierPath(md, c2, c1, start, target->m_speedTime/2));
            target->setPosition(end);
            break;
        }
}


void FishPathFactory::generateFishPathA(Fish *target,CCPoint start,CCPoint end,bool direction)
{
    target->m_fishPath = new CCArray();
    
    //++++++mine
    //target->m_fishPath->addObject(generateBezierPath(ccp(200,0), ccp(500,0), ccp(500,500), ccp(200,500), 2));
    //target->m_fishPath->addObject(generateBezierPath(ccp(200,500), ccp(0,500), ccp(0,700), ccp(200,700), 2));
    //target->m_fishPath->addObject(generateBezierPath(ccp(200,700), ccp(800,700), ccp(900,500), ccp(700,300), 2));
    //target->m_fishPath->addObject(generateBezierPath(ccp(700,300),ccp(500,100), ccp(600,0), ccp(800,0), 2));
    //target->setPosition(ccp(200,0));
    
    //++++his
//    target->m_fishPath->addObject(generateBezierPath(ccp(0,440),ccp(68,471),ccp(68,471), ccp(82,403),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(82,403), ccp(121,215), ccp(121,215), ccp(193,329),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(193,329), ccp(274,472), ccp(274,472), ccp(317,391),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(317,391), ccp(361,314),ccp(542,330), ccp(473,400),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(473,400) ,ccp(406,471),ccp(406,471), ccp(563,496),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(563,496) ,ccp(703,536),ccp(703,536) ,ccp(707,449),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(707,449) ,ccp(779,296) ,ccp(929,310) ,ccp(944,488),1));
//    target->m_fishPath->addObject(generateBezierPath(ccp(944,488),ccp(954,555),ccp(954,555) ,ccp(1024,455),1));
//    target->setPosition(ccp(0,440));
    
    CCSize s = target->getContentSize();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if(start.x == 0 && start.y == 0) {
        start = ccp(-s.width,arc4random()%((int)visibleSize.height));
        end = ccp(visibleSize.width+s.width,arc4random()%((int)visibleSize.height));
    }
    //start = ccp(0,visibleSize.height/2);
    //end = ccp(visibleSize.width,visibleSize.height/2);
    
    CCPointArray *pp = CCPointArray::create(30);
    CCPointArray *np = CCPointArray::create(30);
    pp->addControlPoint(start);
    pp->addControlPoint(end);
    
    
    CCPoint a,b,n;
    for(int i=0; i < pp->count()-1;i++) {
        a = pp->getControlPointAtIndex(i);
        b = pp->getControlPointAtIndex(i+1);
        n = getMDCurvePointRate(a,b,0.3,false);
        np->addControlPoint(a);
        np->addControlPoint(n);
        //np->addControlPoint(b);
    }
    np->addControlPoint(b);
/*    
    pp = np;
    np = CCPointArray::create(30);
    
    for(int i=0; i < pp->count()-1;i++) {
        a = pp->getControlPointAtIndex(i);
        b = pp->getControlPointAtIndex(i+1);
        n = getMDCurvePointRate(a,b,0.3,arc4random()%2);
        np->addControlPoint(a);
        np->addControlPoint(n);
        //np->addControlPoint(b);
    }
    np->addControlPoint(b);
    
    
    pp = np;
    np = CCPointArray::create(30);
    
    for(int i=0; i < pp->count()-1;i++) {
        a = pp->getControlPointAtIndex(i);
        b = pp->getControlPointAtIndex(i+1);
        n = getMDCurvePointRate(a,b,0.3,arc4random()%2);
        np->addControlPoint(a);
        np->addControlPoint(n);
        //np->addControlPoint(b);
    }
    np->addControlPoint(b);
*/  
    
    //target->m_fishPath->addObject(CCFishCardinalSplineTo::create(5, np, 0));
    
    CCPoint fc = getMDCurvePointRate(np->getControlPointAtIndex(0),np->getControlPointAtIndex(1),0.4,direction);
    fc = fc + ccp(arc4random()%100,arc4random()%100);
    target->m_fishPath->addObject(generateBezierPath(np->getControlPointAtIndex(0), fc, fc, np->getControlPointAtIndex(1), target->m_speedTime/2));
    for(int i=1; i < np->count()-1;i++) {
        CCPoint s = np->getControlPointAtIndex(i);
        CCPoint c1 = getReflectPoint(fc, s,0.7);
        CCPoint e = np->getControlPointAtIndex(i+1);
        
        target->m_fishPath->addObject(generateBezierPath(s, c1, c1, e, target->m_speedTime/2));
        fc = c1;
    }
    target->setPosition(start);
}


void FishPathFactory::generateFishesPathA(cocos2d::CCArray *pfishes)
{
    CCPoint start,end;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if(pfishes == NULL || pfishes->count() == 0)
        return;
    CCSize s = ((Fish*)pfishes->objectAtIndex(0))->getContentSize();
    
    start = ccp(-s.height*3,arc4random()%((int)visibleSize.height));
    end = ccp(visibleSize.width+s.height*3,arc4random()%((int)visibleSize.height));
    int r = sqrt(s.width*s.width+s.height*s.height);
    float angle = (arc4random()%(int)((2*M_PI)*1000))/1000;
    bool direction = arc4random()%2;

    
    for(int i=0; i < pfishes->count(); i++) {
        Fish *p = (Fish *)pfishes->objectAtIndex(i);
        float rs = r+arc4random()%r;
        float re = r+arc4random()%r;
        angle += (arc4random()%(int)((M_PI/12)*1000))/1000;
        generateFishPathA(p,start+ccp(rs*cos(angle),rs*sin(angle)),end+ccp(re*cos(angle),re*sin(angle)),direction);
        angle += M_PI/6;
    }
}

void FishPathFactory::generateFishesPathB(cocos2d::CCArray *pfishes)
{
    CCPoint start,end;
    int blank = 100;
    int type = arc4random()%4;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if(pfishes == NULL || pfishes->count() == 0)
        return;
    CCSize s = ((Fish*)pfishes->objectAtIndex(0))->getContentSize();
    
    start = ccp(-s.height*3,arc4random()%((int)visibleSize.height-blank)+blank);
    end = ccp(visibleSize.width+s.height*3,arc4random()%((int)visibleSize.height-blank)+blank);
    
    int r = sqrt(s.width*s.width+s.height*s.height);
    float angle = M_PI/6;
    
    for(int i=0; i < pfishes->count(); i++) {
        Fish *p = (Fish *)pfishes->objectAtIndex(i);
        float rs = r+arc4random()%r;
        float re = r+arc4random()%r;
        angle += (arc4random()%(int)((M_PI/12)*1000))/1000;        
        generateFishPathB(p,type,start+ccp(rs*cos(angle),rs*sin(angle)),end+ccp(re*cos(angle),re*sin(angle)));
        angle += M_PI/6;
    }
    
    return;
}

void FishPathFactory::generateFishesPathC(cocos2d::CCArray *pfishes)
{
    for(int i=0; i < pfishes->count(); i++) {
        Fish *p = (Fish *)pfishes->objectAtIndex(i);
        generateFishPathC(p);
    }
}

void FishPathFactory::generateFishesPathD(cocos2d::CCArray *pfishes)
{
    for(int i=0; i < pfishes->count(); i++) {
        Fish *p = (Fish *)pfishes->objectAtIndex(i);
        generateFishPathD(p);
    }
}

void FishPathFactory::generateFishesPathE(cocos2d::CCArray *pfishes)
{
    for(int i=0; i < pfishes->count(); i++) {
        Fish *p = (Fish *)pfishes->objectAtIndex(i);
        generateFishPathE(p);
    }
}


void FishPathFactory::generateFishesPathStatic(cocos2d::CCArray *pfishes)
{
    for(int i=0; i < pfishes->count(); i++) {
        Fish *p = (Fish *)pfishes->objectAtIndex(i);
        createFishPath(p);
    }
}

void FishPathFactory::generateFishPathB(Fish *target,int type,CCPoint start,CCPoint end)
{
    return generateMultiBezierFishPath(target,start,end,type);
}

void FishPathFactory::generateFishPathC(Fish *target)
{
    return generateBezierFishPath(target);
}


void FishPathFactory::generateFishPathD(Fish *target)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    target->m_fishPath = new CCArray();
    
    CCSize spriteSize = target->getContentSize();
    CCPoint start,end;
    switch(arc4random()%4) {
        case 0:
            start = ccp(-spriteSize.width,-spriteSize.height);
            end = ccp(visibleSize.width+spriteSize.width,visibleSize.height+spriteSize.height);
            break;
        case 1:
            start = ccp(visibleSize.width+spriteSize.width,visibleSize.height+spriteSize.height);
            end = ccp(-spriteSize.width,-spriteSize.height);
            break;
        case 2:
            start = ccp(-spriteSize.width,visibleSize.height+spriteSize.height);
            end = ccp(visibleSize.width+spriteSize.width,-spriteSize.height);
            break;
        case 3:
            start = ccp(visibleSize.width+spriteSize.width,-spriteSize.height);
            end = ccp(-spriteSize.width,visibleSize.height+spriteSize.height);
            break;
    }
    target->setPosition(start);
    target->m_fishPath->addObject(CCFishLineTo::create(target->m_speedTime,end));
}


void FishPathFactory::generateFishPathE(Fish *target)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    target->m_fishPath = new CCArray();
    
    CCSize spriteSize = target->getContentSize();
    CCPoint start,end;
    float t1 = 15;
    int t2 = 10;
    
    if(arc4random()%2){
        start = ccp(-spriteSize.width,arc4random()%((int)visibleSize.height-400)+300);
        end = ccp(visibleSize.width+spriteSize.width,start.y);
    } else {
        start = ccp(visibleSize.width+spriteSize.width,arc4random()%((int)visibleSize.height-400)+300);
        end = ccp(-spriteSize.width,start.y);
        target->setFlipX(true);
    }
    
    target->setPosition(start);
    target->m_fishPath->addObject(generateBezierPath(start, (start+end)/2, (start+end)/2, end, target->m_speedTime));
}


FishPathFactory::FishPathType FishPathFactory::getFishPathType(Fish::FishType type)
{
    switch (type) {
        case Fish::FISH_XIAOGUANGYU:
        case Fish::FISH_XIAOCAOYU:
        case Fish::FISH_XIAOHUANGCI:
        case Fish::FISH_LANGUANGYU:
            // A\B
            if(arc4random()%2) {
                return FISH_PATHTYPE_A;
            } else {
                return FISH_PATHTYPE_B;
            }
        case Fish::FISH_REDAIYU:
        case Fish::FISH_DAYANJINYU:
        case Fish::FISH_SHUIMU:
        case Fish::FISH_SHANWEIYU:
        case Fish::FISH_REDAIZIYU:
        case Fish::FISH_XIAOCHOUYU:
        case Fish::FISH_HETUN:
        case Fish::FISH_WUZEI:
        case Fish::FISH_SHITOUYU:
        case Fish::FISH_SHENXIANYU:
        case Fish::FISH_WUGUI:
        case Fish::FISH_DENGLONGYU:
        case Fish::FISH_SHIBANYU:
        case Fish::FISH_HUDIEYU:
        case Fish::FISH_LINGDANGYU:
        case Fish::FISH_QICAIYU:
        case Fish::FISH_YINGWULUO:
        case Fish::FISH_TIAOWENYU:
            // B\C
            if(arc4random()%2){
                return FISH_PATHTYPE_B;
            }else{
                return FISH_PATHTYPE_C;
            }
        case Fish::FISH_JIANYU:
        case Fish::FISH_MOGUIYU:
        case Fish::FISH_FEIYU:
        case Fish::FISH_LONGXIA:
        case Fish::FISH_HAITUN:
//        case Fish::FISH_BYMOGUIYU:
        case Fish::FISH_GANGKUIYU:
            // C\D\E
            switch(arc4random()%3){
                case 0:
                    return FISH_PATHTYPE_C;
                case 1:
                    return FISH_PATHTYPE_D;
                case 2:
                    return FISH_PATHTYPE_E;
            }
        case Fish::FISH_DAYINSHA:
        case Fish::FISH_LANJING:
//        case Fish::FISH_HUANGJINGJINGYU:
//        case Fish::FISH_LANSHA:
        case Fish::FISH_HAIGUAI:
            // D\E
            if(arc4random()%2) {
                return FISH_PATHTYPE_D;
            } else {
                return FISH_PATHTYPE_E;
            }
//        case Fish::FISH_HUANGJINGYU:
//        case Fish::FISH_BYWUGUI:
        case Fish::FISH_ALILAN:
            // B
            return FISH_PATHTYPE_B;
        case Fish::FISH_XIAOFEIYU:
            // C
            return FISH_PATHTYPE_C;
        case Fish::FISH_ZHENZHUBEI:
            return FISH_PATHTYPE_E;
//            return FISH_PATHTYPE_STATIC;
//        case Fish::FISH_HAIMA:
        case Fish::FISH_ZHADANFISH:
        case Fish::FISH_HGZHADAN:
            return FISH_PATHTYPE_E;
        default:
            return FISH_PATHTYPE_C;
    }
}

void FishPathFactory::createFishPath(Fish * target)
{
    FishPathType t = getFishPathType(target->m_fishType);
    switch(t){
        case FISH_PATHTYPE_A:
            return generateFishPathA(target);
        case FISH_PATHTYPE_B:
            return generateFishPathB(target);
        case FISH_PATHTYPE_C:
            return generateFishPathC(target);
        case FISH_PATHTYPE_D:
            return generateFishPathD(target);
        case FISH_PATHTYPE_E:
            return generateFishPathE(target);
        case FISH_PATHTYPE_STATIC:
            return generateStaticFishPath(target);
    }
}


void FishPathFactory::generateFishesPath(cocos2d::CCArray *pfishes)
{
    if(pfishes == NULL || pfishes->count() == 0)
        return;
    Fish::FishType ft = ((Fish*)pfishes->objectAtIndex(0))->m_fishType;
    FishPathType t = getFishPathType(ft);
    
    switch(t){
        case FISH_PATHTYPE_A:
            return generateFishesPathA(pfishes);
        case FISH_PATHTYPE_B:
            return generateFishesPathB(pfishes);
        case FISH_PATHTYPE_C:
            return generateFishesPathB(pfishes);
        case FISH_PATHTYPE_D:
            return generateFishesPathD(pfishes);
        case FISH_PATHTYPE_E:
            return generateFishesPathE(pfishes);
        case FISH_PATHTYPE_STATIC:
            return generateFishesPathStatic(pfishes);
            break;
    }
}
