//
//  Utils.cpp
//  fish
//
//  
//
//

#include "FishUtils.h"


CCSpriteFrame *FishUtils::awardSpriteFrame( GameAwardType aType ) {
    char* fileName = NULL;
    //edit by andy  2015-04-14
    switch (aType) {
        case GameAwardOneDiamondBlue:
            fileName = "pack_10008.png";
            break;
        case GameAwardOneDiamondGreen:
            fileName = "pack_10006.png";
            break;
        case GameAwardOneDiamondRed:
            fileName = "pack_10009.png";
            break;
        case GameAwardOneDiamondYellow:
            fileName = "pack_10007.png";
            break;
        case GameAwardOneDiamondPearl:
            fileName = "pack_85.png";
            break;
//        case GameAwardOneMine:
//            fileName = "1mine.png";
//            break;
//        case GameAwardHideBullet:
//            fileName = "1Stealthgun.png";
//            break;
//        case GameAwardCoin15000 :
//            fileName = "15000coin.png";
//            break;
//        case GameAwardCoin30000:
//            fileName = "30000coin.png";
//            break;
//        case GameAwardCoin50000:
//            fileName = "50000coin.png";
//            break;
//        case GameAwardDoubleExp:
//            fileName = "expx2.png";
//            break;
        default:
            break;
    }
    
    CCSpriteFrame* spFrame = NULL;
    if (fileName != NULL) {
        spFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
    }
    
    return spFrame;
    
}

