//
//  Utils.h
//  fish
//
//  
//
//

#ifndef __fish__Utils__
#define __fish__Utils__

#include "headerLibrary.h"

enum GameAwardType{
    GameAwardOneDiamondYellow = 1,
    GameAwardOneDiamondGreen,
    GameAwardOneDiamondRed,
    GameAwardOneDiamondBlue,
    GameAwardOneDiamondPearl,
    
//    GameAwardOneMine,
//    GameAwardHideBullet,
//    GameAwardCoin15000,
//    GameAwardCoin30000,
//    GameAwardCoin50000,
//    GameAwardDoubleExp
};

struct FishUtils {
    static CCSpriteFrame *awardSpriteFrame( GameAwardType aType );
};


#endif /* defined(__fish__Utils__) */
