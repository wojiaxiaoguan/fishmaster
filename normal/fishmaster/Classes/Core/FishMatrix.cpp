//
//  FishMatrix.cpp
//  fish
//
//  
//
//

#include "FishMatrix.h"
#include "GameLayer.h"
#include "FishPath.h"
#include "MyFishPath.h"
#include "../Foundation/AppDelegate.h"
USING_NS_CC;



FishMatrix *FishMatrix::create(GameLayer *parent,FishMatrix_Type type)
{
    if(type == FISH_MATRIX_MAX) {
        type = (FishMatrix_Type)(arc4random()%FISH_MATRIX_MAX);
    }
    
    switch (type) {
        case FISH_MATRIX_CIRCLE:
            return FishMatrixCircle::create(parent);
        case FISH_MATRIX_SCATTER:
            return FishMatrixScatter::create(parent);
        case FISH_MATRIX_RANK:
            return FishMatrixRank::create(parent);
        case FISH_MATRIX_ELLIPSE:
            return FishMatrixEllipse::create(parent);
        case FISH_MATRIX_HELIX:
            return FishMatrixHelix::create(parent);
        default:
            break;
    }
    
    return NULL;
}

void FishMatrix::removeFromParent()
{
    //内存泄露  2015-04-24
    m_parent->startFishGenerator(true);
    m_fishes->release();
    m_fishes = NULL;
    CCSprite::removeFromParent();
}


FishMatrixCircle * FishMatrixCircle::create(GameLayer *parent)
{
    FishMatrixCircle *p = new FishMatrixCircle();
    p->init();
    p->m_fishes = CCArray::create();
    p->m_fishes->retain();
    p->m_parent = parent;
    
    Fish *pfc = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
    
    pfc->setPosition(ccp(-500,-500));
    pfc->m_fishPath = new CCArray();
    pfc->m_fishPath->addObject(CCRepeat::create(CCCircle::create(30, ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), 1),40));
    p->m_fishes->addObject(pfc);
    
    //shitouyu
    Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHITOUYU,false);
    CCSize s = pf->getContentSize();
    float duration = 30;
    float radius = 150;
    int num = 2*M_PI*radius/s.height;
    float interval = duration/num;
    for(int i = 0; i < num;i++) {

        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHITOUYU,false);
        pf->setPosition(ccp(-500,-500));

        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        pf->m_fishPath->addObject(CCRepeat::create(CCCircle::create(30, ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes->addObject(pf);
    }
    
    //shitouyu
    pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_DAYANJINYU,false);
    s = pf->getContentSize();
    duration = 30;
    radius = 200;
    num = 2*M_PI*radius/s.height;
    interval = duration/num;
    for(int i = 0; i < num;i++) {
        
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_DAYANJINYU,false);
        pf->setPosition(ccp(-500,-500));
        
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        pf->m_fishPath->addObject(CCRepeat::create(CCCircle::create(30, ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes->addObject(pf);
    }
    
    //redaiyu
    pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIYU,false);
    s = pf->getContentSize();
    duration = 30;
    radius = 250;
    num = 2*M_PI*radius/s.height;
    interval = duration/num;
    for(int i = 0; i < num;i++) {
        
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIYU,false);
        pf->setPosition(ccp(-500,-500));
        
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        pf->m_fishPath->addObject(CCRepeat::create(CCCircle::create(30, ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes->addObject(pf);
    }
    
    //xiaoguangyu
    pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOGUANGYU,false);
    s = pf->getContentSize();
    duration = 30;
    radius = 300;
    num = 2*M_PI*radius/s.height;
    interval = duration/num;
    for(int i = 0; i < num;i++) {
        
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOGUANGYU,false);
        pf->setPosition(ccp(-500,-500));
        
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        pf->m_fishPath->addObject(CCRepeat::create(CCCircle::create(30, ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes->addObject(pf);
    }
    
    return p;
}


void FishMatrixCircle::goFishMatrix()
{
    schedule(schedule_selector(FishMatrixCircle::stop), 10.0f, 6, 30);
}


void FishMatrixCircle::stop()
{
    CCObject* pObj;
    Fish *pt = NULL;
    CCARRAY_FOREACH_REVERSE(m_fishes,pObj)
    {
        Fish* pf=(Fish*)pObj;
        if(pt == NULL) {
            pt = pf;
        }
        
        if(pt->m_fishType == pf->m_fishType) {
            pf->stopAllActions();
            CCPoint last = pf->m_lastPoint;
            CCPoint current = pf->getPosition();
            double angle = atan2((current.y-last.y),(current.x-last.x));
            CCPoint end = ccp(700*cos(angle),700*sin(angle));
            pf->m_fishPath->removeAllObjects();
            pf->m_fishPath->addObject(CCMoveBy::create(10, end));
            
//            if(pf->m_fishType == Fish::FISH_MOGUIYU) {
//                CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(FishMatrixCircle::removeFromParent));
//                pf->m_fishPath->addObject(callFunc);
//            }
        }
    }
    
    CCARRAY_FOREACH_REVERSE(m_fishes,pObj)
    {
        Fish* pf=(Fish*)pObj;
        if(pt->m_fishType == pf->m_fishType) {
            pf->goFish();
            m_fishes->removeObject(pf);
        }
    }
    
    if(m_fishes->count() == 0) {
        //内存泄露  2015-04-24
        removeFromParent();
    }
}


///---------------Implementation of FishMatrixScatter---------------------

FishMatrixScatter* FishMatrixScatter::create(GameLayer *parent)
{
    FishMatrixScatter *p = new FishMatrixScatter();
    p->init();
    p->m_fishes = CCArray::create();
    p->m_fishes->retain();
    p->m_parent = parent;
    
    float interval = 0.1;
    for(int i = 0; i < 300; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOCAOYU,false);
        
        pf->setPosition(ccp(-500,-500));
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        
        //pf->m_fishPath->addObject(callFunc);
        int ag = arc4random()%360;
        float angle = 2*M_PI*ag/360;
        CCPoint to = ccp(700*cos(angle),700*sin(angle));
        pf->setRotation(90-ag);
        pf->m_fishPath->addObject(CCMoveFromBy::create(5,ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), to));
        p->m_fishes->addObject(pf);
    }
    
    return p;
}


void FishMatrixScatter::goFishMatrix()
{
    scheduleOnce(schedule_selector(FishMatrixScatter::stop), 30);
}


void FishMatrixScatter::stop()
{
    //内存泄露  2015-04-24
    removeFromParent();
}




///---------------Implementation of FishMatrixRank---------------------

FishMatrixRank* FishMatrixRank::create(GameLayer *parent)
{
    FishMatrixRank *p = new FishMatrixRank();
    p->init();
    p->m_fishes = CCArray::create();
    p->m_fishes->retain();
    p->m_parent = parent;
    CCSize screen = CCDirector::sharedDirector()->getVisibleSize();
    int blank = 100;
    
    
    
    CCPoint last = ccp(arc4random()%10,-blank);
    float interval = 0.3;
    while(1) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOCAOYU,false);
        int aaa = (arc4random()%10 - 10);
        float lasty = (-blank+aaa);
        last = ccp((last.x+arc4random()%10+10),lasty);
        pf->setPosition(last);
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*(arc4random()%6)));
        
        pf->m_fishPath->addObject(CCMoveBy::create(3, ccp(0,250)));
        
        pf->m_fishPath->addObject(CCDelayTime::create(55));
        pf->m_fishPath->addObject(CCMoveBy::create(6, ccp(0,screen.height+2*blank - 250)));
        p->m_fishes->addObject(pf);
        
        if(last.x > AppDelegate::SCREEN_WIDTH)
            break;
    }
    
    
    last = ccp(arc4random()%10,screen.height+blank);
    interval = 0.3;
    while(1) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOCAOYU,false);
        int aaa = (arc4random()%10 - 10);
        float lasty=screen.height+blank+aaa;
        last = ccp(last.x+arc4random()%10+10,lasty);
        pf->setPosition(last);
        pf->setRotation(180);
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*(arc4random()%6)));
        
        pf->m_fishPath->addObject(CCMoveBy::create(3, ccp(0,-250)));
        pf->m_fishPath->addObject(CCDelayTime::create(55));
        pf->m_fishPath->addObject(CCMoveBy::create(6, ccp(0,-(screen.height+2*blank - 250))));
        p->m_fishes->addObject(pf);
        
        if(last.x > AppDelegate::SCREEN_WIDTH) {
//            CCFiniteTimeAction *callFunc = CCCallFunc::create(p, callfunc_selector(FishMatrixRank::removeFromParent));
//            pf->m_fishPath->addObject(callFunc);
            break;
        }
    }
    
    
    
    
    Fish *tp = Fish::createSpecificFish(p->m_parent, Fish::FISH_DENGLONGYU,false);
    CCSize s = tp->getContentSize();
    tp->release();
    
    for(int i=0; i < 20;i++) {
        Fish *pf;
        if(i < 5) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
        } else if(i < 10) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_WUGUI,false);
        } else if(i < 15) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHENXIANYU,false);
        } else {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU,false);
        }
        pf->setPosition(ccp(-200,300));
        pf->cocos2d::CCNode::setRotation(90);
        
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(5+2*i));
        pf->m_fishPath->addObject(CCMoveBy::create(15, ccp(AppDelegate::SCREEN_WIDTH+2*200,0)));
        p->m_fishes->addObject(pf);
    }
    
    
    
    for(int i=0; i < 20;i++) {
        Fish *pf;
        if(i < 5) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
        } else if(i < 10) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_WUGUI,false);
        } else if(i < 15) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHENXIANYU,false);
        } else {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU,false);
        }
        
        pf->setPosition(ccp(AppDelegate::SCREEN_WIDTH+200,screen.height-300));
        pf->cocos2d::CCNode::setRotation(-90);
        
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(5+2*i));
        pf->m_fishPath->addObject(CCMoveBy::create(15, ccp(-AppDelegate::SCREEN_WIDTH-2*200,0)));
        p->m_fishes->addObject(pf);
    }
    
    return p;
}


void FishMatrixRank::goFishMatrix()
{
    scheduleOnce(schedule_selector(FishMatrixRank::stop), 66);
}


void FishMatrixRank::stop()
{
    removeFromParent();
}



//////


FishMatrixEllipse* FishMatrixEllipse::create(GameLayer *parent)
{
    FishMatrixEllipse *p = new FishMatrixEllipse();
    p->init();
    
    p->m_fishes = CCArray::create();
    p->m_fishes->retain();
    p->m_parent = parent;
    
    float interval = 1;
    
    Fish *pfc = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
    pfc->setPosition(ccp(-500,-500));
    
    pfc->m_fishPath = new CCArray();
    pfc->m_fishPath->addObject(CCRepeat::create(CCCircle::create(20, ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2), 1),40));
    p->m_fishes->addObject(pfc);
    
    for(int i = 0; i < 20; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHUIMU,false);
        
        pf->setPosition(ccp(-500,-500));
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        
        //pf->m_fishPath->addObject(callFunc);
        //int ag = arc4random()%360;
        //float angle = 2*M_PI*ag/360;
        //CCPoint to = ccp(700*cos(angle),700*sin(angle));
        //pf->setRotation(90-ag);
        ccEllipseConfig c;
        c.centerPosition = ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2);
        c.aLength = 100;
        c.bLength = 300;
        c.angle = 0;
        pf->m_fishPath->addObject(CCRepeat::create(CCEllipseBy::create(20,c),40));
        p->m_fishes->addObject(pf);
    }

    for(int i = 0; i < 20; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHUIMU,false);
        
        pf->setPosition(ccp(-500,-500));
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        
        //pf->m_fishPath->addObject(callFunc);
        //int ag = arc4random()%360;
        //float angle = 2*M_PI*ag/360;
        //CCPoint to = ccp(700*cos(angle),700*sin(angle));
        //pf->setRotation(90-ag);
        ccEllipseConfig c;
        c.centerPosition = ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2);
        c.aLength = 100;
        c.bLength = 300;
        c.angle = 2*M_PI/3;
        pf->m_fishPath->addObject(CCRepeat::create(CCEllipseBy::create(20,c),40));
        p->m_fishes->addObject(pf);
    }
    
    for(int i = 0; i < 20; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHUIMU,false);
        
        pf->setPosition(ccp(-500,-500));
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        
        //pf->m_fishPath->addObject(callFunc);
        //int ag = arc4random()%360;
        //float angle = 2*M_PI*ag/360;
        //CCPoint to = ccp(700*cos(angle),700*sin(angle));
        //pf->setRotation(90-ag);
        ccEllipseConfig c;
        c.centerPosition = ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2);
        c.aLength = 100;
        c.bLength = 300;
        c.angle = 4*M_PI/3;
        pf->m_fishPath->addObject(CCRepeat::create(CCEllipseBy::create(20,c),40));
        p->m_fishes->addObject(pf);
    }
    
    return p;
}



void FishMatrixEllipse::goFishMatrix()
{
    //scheduleOnce(schedule_selector(FishMatrixEllipse::stop), 60);
    schedule(schedule_selector(FishMatrixEllipse::stop), 10.0f, 2, 40);
}


void FishMatrixEllipse::stop()
{
    
    CCObject* pObj;
    Fish *pt = NULL;
    CCARRAY_FOREACH_REVERSE(m_fishes,pObj)
    {
        Fish* pf=(Fish*)pObj;
        if(pt == NULL) {
            pt = pf;
        }
        
        if(pt->m_fishType == pf->m_fishType) {
            pf->stopAllActions();
            CCPoint last = pf->m_lastPoint;
            CCPoint current = pf->getPosition();
            double angle = atan2((current.y-last.y),(current.x-last.x));
            CCPoint end = ccp(700*cos(angle),700*sin(angle));
            pf->m_fishPath->removeAllObjects();
            pf->m_fishPath->addObject(CCMoveBy::create(10, end));
            
//            if(pf->m_fishType == Fish::FISH_MOGUIYU) {
//                CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(FishMatrixCircle::removeFromParent));
//                pf->m_fishPath->addObject(callFunc);
//            }
        }
    }
    
    CCARRAY_FOREACH_REVERSE(m_fishes,pObj)
    {
        Fish* pf=(Fish*)pObj;
        if(pt->m_fishType == pf->m_fishType) {
            pf->goFish();
            m_fishes->removeObject(pf);
        }
    }
    
    if(m_fishes->count() == 0) {
        removeFromParent();
    }
}



///////



FishMatrixHelix* FishMatrixHelix::create(GameLayer *parent)
{
    FishMatrixHelix *p = new FishMatrixHelix();
    p->init();
    
    p->m_fishes = CCArray::create();
    p->m_fishes->retain();
    p->m_parent = parent;
    
    float interval = 1;
    Fish *pf = NULL;
    
    for(int i = 0; i < 30; i++) {
        pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_DENGLONGYU,false);
        
        pf->setPosition(ccp(-500,-500));
        pf->m_fishPath = new CCArray();
        pf->m_fishPath->addObject(CCDelayTime::create(interval*i));
        
        pf->m_fishPath->addObject(CCRepeat::create(CCHelix::create(30,ccp(AppDelegate::SCREEN_WIDTH / 2,AppDelegate::SCREEN_HEIGHT / 2),100,AppDelegate::SCREEN_WIDTH / 2),1));
        p->m_fishes->addObject(pf);
    }

    //CCFiniteTimeAction *callFunc = CCCallFunc::create(p, callfunc_selector(FishMatrixHelix::removeFromParent));
    //pf->m_fishPath->addObject(callFunc);
    return p;
}



void FishMatrixHelix::goFishMatrix()
{
    scheduleOnce(schedule_selector(FishMatrixHelix::stop), 60);
    //schedule(schedule_selector(FishMatrixCircle::stop), 10.0f, 2, 50);
}


void FishMatrixHelix::stop()
{
    removeFromParent();
}

