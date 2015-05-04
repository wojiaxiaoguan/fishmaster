//
//  FishGroup.h
//  fish
//
//  
//
//

#ifndef __fish__FishGroup__
#define __fish__FishGroup__

#include <iostream>
#include "cocos2d.h"
#include "common.h"
#include "GameLayer.h"

class FishGroup{
public:
    enum FishGroupType{
        FishGroupLine = 0,
        FishGroupRand
    };
    static cocos2d::CCArray * createFishGroup(GameLayer *parent,FishGroupType type,Fish::FishType ft = Fish::FISH_NORMAL_TYPEMAX);
    
    static cocos2d::CCArray * createFishLineGroup(GameLayer *parent,Fish::FishType type,int num);
    static cocos2d::CCArray * createFishRandGroup(GameLayer *parent,Fish::FishType type,int num);
};

#endif /* defined(__fish__FishGroup__) */
