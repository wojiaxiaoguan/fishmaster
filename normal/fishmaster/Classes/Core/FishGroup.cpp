//
//  FishGroup.cpp
//  fish
//
//  
//
//

#include "FishGroup.h"
#include "FishPath.h"
#include "Fish.h"
USING_NS_CC;



CCArray * FishGroup::createFishGroup(GameLayer* parent,FishGroupType type,Fish::FishType ft)
{
    if(ft == Fish::FISH_NORMAL_TYPEMAX || ft == Fish::FISH_All_TYPEMAX)
    {
        ft = Fish::getRefreshFishType();
    }
    int num = Fish::getRefreshFishNum(ft);

    if( ft == Fish::FISH_XIAOFEIYU ) {
        //xiao fei yu only support line group
        return createFishLineGroup(parent,ft,num);
    }
    switch (type) {
        case FishGroupLine:
            return createFishLineGroup(parent,ft,num);
        case FishGroupRand:
            return createFishRandGroup(parent,ft,num);
        default:
            break;
    }
}

CCArray * FishGroup::createFishLineGroup(GameLayer* parent,Fish::FishType type,int num)
{
    CCArray *pa = CCArray::create();
    Fish *pf = NULL;
    Fish *p = NULL;
    float interval = 0.5;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    for(int i=0; i < num; i++) {
        
        if(pf == NULL) {
            pf = Fish::createSpecificFish(parent,type);
            p = pf;
        } else {
            p = Fish::createSpecificFish(parent,type,false);
            p->m_fishPath = CCArray::createWithArray(pf->m_fishPath);
            
            interval = p->m_speedTime * p->getContentSize().height/visibleSize.width;
//            if(p->m_speedTime > 10)
//                interval = 1.5;
//            else if(p->m_speedTime > 15)
//                interval = 2.0;
            p->m_fishPath->insertObject(CCDelayTime::create(interval*i) , 0);
            p->setPosition(pf->getPosition());
            p->setFlipX(pf->isFlipX());
        }
        
        pa->addObject(p);
    }
    
    return pa;
}

CCArray * FishGroup::createFishRandGroup(GameLayer* parent,Fish::FishType type,int num)
{
    CCArray *pa = CCArray::create();
    for(int i=0; i < num; i++) {
        Fish *p = Fish::createSpecificFish(parent,type,false);
        pa->addObject(p);
    }
    
    FishPathFactory::generateFishesPath(pa);
    
    return pa;
}
