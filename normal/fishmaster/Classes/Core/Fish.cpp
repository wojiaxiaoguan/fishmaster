//
//  Fish.cpp
//  MyGame
//
//  
//
//

#include "Fish.h"
#include "GameLayer.h"
#include "Coin.h"
#include "Helper.h"
#include "Sound.h"
#include "GameData.h"
#include "FishPath.h"
//#include "FlipCardBonusLayer.h"
USING_NS_CC;


int Fish::_freshRateArray[Fish::FISH_All_TYPEMAX] = {
    100,// FISH_XIAOGUANGYU = 0,
    90,// FISH_XIAOCAOYU,
    90,// FISH_REDAIYU,
    80,// FISH_DAYANJINYU,
    80,// FISH_SHUIMU,
    70,// FISH_SHANWEIYU,
    70,// FISH_REDAIZIYU,
    60,// FISH_XIAOCHOUYU,
    60,// FISH_HETUN,
    50,// FISH_WUZEI,
    50,// FISH_SHITOUYU,
    45,// FISH_SHENXIANYU,
    45,// FISH_WUGUI,
    40,// FISH_DENGLONGYU,
    40,// FISH_SHIBANYU,
    35,// FISH_HUDIEYU,
    35,// FISH_LINGDANGYU,
    35,// FISH_JIANYU,
    30,// FISH_MOGUIYU,
    30,// FISH_FEIYU,
    30,// FISH_LONGXIA,
    25,// FISH_HAITUN,
    25,// FISH_DAYINSHA,
    25,// FISH_LANJING,
//    25,// FISH_HUANGJINGJINGYU,
//    40,// FISH_HUANGJINGYU,
//    30,// FISH_BYMOGUIYU,
//    30,// FISH_BYWUGUI,
    30,// FISH_ZHENZHUBEI,
//    40,// FISH_LANSHA,
    30,// FISH_XIAOFEIYU,
    50,// FISH_ALILAN,
//    20,// FISH_HAIMA,
    0,// FISH_ZHADANFISH,
    0,// FISH_NORMAL_TYPEMAX (NO USE)
    80,// FISH_XIAOHUANGCI
    80,// FISH_LANGUANGYU
    60,// FISH_QICAIYU
    50,// FISH_YINGWULUO
    50,// FISH_TIAOWENYU
    40,// FISH_GANGKUIYU
    0,// FISH_HAIGUAI
    0// FISH_HGZHADAN
};
//    ,0 //zhadan
//    ,0 //max



bool Fish::_fishLockArray[Fish::FISH_All_TYPEMAX] = {
    false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false
};

bool Fish::_fishRingLockArray[Fish::SPEC_NONE] = {
    false,false,false,false,false,false
};


#define SPEED_TIME_A 6
#define SPEED_TIME_B 8
#define SPEED_TIME_C 12
#define SPEED_TIME_D 18
#define SPEED_TIME_E 22
#define SPEED_TIME_F 30




Fish::Fish(FishType type):m_fishType(type),m_spec(SPEC_NONE),m_specSprite(NULL)
{
    m_activeFrameDelay = 0.15;
    m_deadFrameDelay = 0.15;
    m_originColor = getColor();
    switch(m_fishType){
        case FISH_XIAOGUANGYU:
            m_activeFrameCount = 5;    //8
            m_deadFrameCount = 2;
            m_scoreRate = 0.25;
            m_attackRate = 150;
            m_activeFrameDelay = 0.06;
            m_speedTime = 10;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_XIAOCAOYU:
            m_activeFrameCount = 8;
            m_deadFrameCount = 3;
            m_scoreRate = 0.5;
            m_attackRate = 120;
            m_activeFrameDelay = 0.08;
            m_speedTime = 11;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_REDAIYU:
            m_activeFrameCount = 4;   //7
            m_deadFrameCount = 3;
            m_scoreRate = 1;
            m_attackRate = 100;
            m_activeFrameDelay = 0.08;
            m_speedTime = 12;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_DAYANJINYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;  //3
            m_scoreRate = 2;
            m_attackRate = 80;
            m_speedTime = 14;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_SHUIMU:
            m_activeFrameCount = 9;   //10
            m_deadFrameCount = 5;  //6
            m_scoreRate = 3;
            m_attackRate = 50;
            m_speedTime = 18;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_SHANWEIYU:
            m_activeFrameCount = 8;   //
            m_deadFrameCount = 2;     //4
            m_scoreRate = 4;
            m_attackRate = 18;
            m_speedTime = 15;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_REDAIZIYU:
            m_activeFrameCount = 7;
            m_deadFrameCount = 3;
            m_scoreRate = 5;
            m_attackRate = 16;
            m_speedTime = 13;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_XIAOCHOUYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;
            m_scoreRate = 6;
            m_attackRate = 14;
            m_activeFrameDelay = 0.1;
            m_speedTime = 17;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_HETUN:
            m_activeFrameCount = 6;  //10
            m_deadFrameCount = 3;
            m_scoreRate = 7;
            m_attackRate = 12;
            m_speedTime = 17;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_WUZEI:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;
            m_scoreRate = 8;
            m_attackRate = 12;
            m_speedTime = 8;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_SHITOUYU:
            m_activeFrameCount = 5;    //6
            m_deadFrameCount = 3;
            m_scoreRate = 9;
            m_attackRate = 10;
            m_activeFrameDelay = 0.06;
            m_speedTime = 16;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_SHENXIANYU:
            m_activeFrameCount = 6;   //7
            m_deadFrameCount = 3;    //4
            m_scoreRate = 10;
            m_attackRate = 10;
            m_activeFrameDelay = 0.08;
            m_speedTime = 14;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_WUGUI:
            m_activeFrameCount = 5;
            m_deadFrameCount = 4;
            m_scoreRate = 12;
            m_attackRate = 11;
            m_speedTime = 16;
            m_genCornNum = 21;
            m_fishCD = 0;
            break;
        case FISH_DENGLONGYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 4;
            m_scoreRate = 15;
            m_attackRate = 10;
            m_activeFrameDelay = 0.12;
            m_speedTime = 17;
            m_genCornNum = 21;
            m_fishCD = 0;
            break;
        case FISH_SHIBANYU:
            //edit by lqg 2015-04-09
            //m_activeFrameCount = 7;
            m_activeFrameCount = 4;
            m_deadFrameCount = 4;
            m_scoreRate = 18;
            m_attackRate = 9;
            m_speedTime = 15;
            m_genCornNum = 21;
            m_fishCD = 0;
            break;
        case FISH_HUDIEYU:
            m_activeFrameCount = 4;//6
            m_deadFrameCount = 3;
            m_scoreRate = 20;
            m_attackRate = 8;
            m_speedTime = 14;
            m_genCornNum = 22;
            m_fishCD = 0;
            break;
        case FISH_LINGDANGYU:
            m_activeFrameCount = 4;//
            m_deadFrameCount = 3;
            m_scoreRate = 25;
            m_attackRate = 7;
            m_speedTime = 16;
            m_genCornNum = 22;
            m_fishCD = 0;
            break;
        case FISH_JIANYU:
            m_activeFrameCount = 4;//6
            m_deadFrameCount = 3;
            m_scoreRate = 30;
            m_attackRate = 6;
            m_speedTime = 13;
            m_genCornNum = 22;
            m_fishCD = 5;
            break;
        case FISH_MOGUIYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;
            m_scoreRate = 35;
            m_attackRate = 5;
            m_speedTime = 15;
            m_genCornNum = 23;
            m_fishCD = 0;
            break;
        case FISH_FEIYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;
            m_scoreRate = 40;
            m_attackRate = 4;
            m_activeFrameDelay = 0.1;
            m_speedTime = 17;
            m_genCornNum = 23;
            m_fishCD = 5;
            break;
        case FISH_LONGXIA:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;
            m_scoreRate = 50;
            m_attackRate = 3;
            m_activeFrameDelay = 0.1;
            m_speedTime = 18;
            m_genCornNum = 23;
            m_fishCD = 5;
            break;
        case FISH_HAITUN:
            m_activeFrameCount = 8;
            m_deadFrameCount = 4;
            m_scoreRate = arc4random() % 10 + 60;
            m_attackRate = 3;
            m_speedTime = 15;
            m_genCornNum = 24;
            m_fishCD = 5;
            break;
        case FISH_DAYINSHA:
            m_activeFrameCount = 8;
            m_deadFrameCount = 4;
            m_scoreRate = arc4random() % 10 + 80;
            m_attackRate = 2;
            m_speedTime = 18;
            m_genCornNum = 24;
            m_fishCD = 5;
            break;
        case FISH_LANJING:
            m_activeFrameCount = 8;  //6
            m_deadFrameCount = 3;
            m_scoreRate = 100;
            m_attackRate = 2;
            m_activeFrameDelay = 0.2;
            m_speedTime = 20;
            m_genCornNum = 24;
            m_fishCD = 5;
            break;
//        case FISH_HUANGJINGJINGYU:
//            m_activeFrameCount = 10;
//            m_deadFrameCount = 4;
//            m_scoreRate = arc4random()%21+180;
//            m_attackRate = 1;
//            m_activeFrameDelay = 0.2;
//            m_speedTime = 22;
//            m_genCornNum = 25;
//            m_fishCD = 30;
//            break;
//        case FISH_HUANGJINGYU:
//            m_activeFrameCount = 13;
//            m_deadFrameCount = 4;
//            m_scoreRate = 75;
//            m_attackRate = 2;
//            m_speedTime = 18;
//            m_genCornNum = 23;
//            m_fishCD = 30;
//            break;
//        case FISH_BYMOGUIYU:
//            m_activeFrameCount = 11;
//            m_deadFrameCount = 3;
//            m_scoreRate = 35;
//            m_attackRate = 3;
//            m_speedTime = 14;
//            m_genCornNum = 23;
//            m_fishCD = 30;
//            break;
//        case FISH_BYWUGUI:
//            m_activeFrameCount = 10;
//            m_deadFrameCount = 6;
//            m_scoreRate = 18;
//            m_attackRate = 4;
//            m_speedTime = 15;
//            m_genCornNum = 21;
//            m_fishCD = 30;
//            break;
        case FISH_ZHENZHUBEI:
            m_activeFrameCount = 4;  //6
            m_deadFrameCount = 3;   //2
            m_scoreRate = 10;
            m_attackRate = 12;
            m_speedTime = 20;
            m_genCornNum = 1;
            m_fishCD = 30;
            break;
//        case FISH_LANSHA:
//            m_activeFrameCount = 13;
//            m_deadFrameCount = 6;
//            m_scoreRate = 90;
//            m_attackRate = 2;
//            m_speedTime = 14;
//            m_genCornNum = 24;
//            m_fishCD = 30;
//            break;
        case FISH_XIAOFEIYU:
            m_activeFrameCount = 3;   //7
            m_deadFrameCount = 1;    //3
            m_scoreRate = arc4random()%5+1;
            m_attackRate = 30;
            m_speedTime = 14;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_ALILAN:
            m_activeFrameCount = 8;
            m_deadFrameCount = 6;
            m_scoreRate = arc4random()%5+6;
            m_attackRate = 20;
            m_speedTime = 16;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
//        case FISH_HAIMA:
//            m_activeFrameCount = 11;
//            m_deadFrameCount = 4;
//            m_scoreRate = 0;
//            m_attackRate = 5;
//            m_speedTime = 20;
//            m_genCornNum = 0;
//            m_fishCD = 30;
//            break;
        case FISH_ZHADANFISH:
            m_activeFrameCount = 3;    //5
            m_deadFrameCount = 2;   //6
            m_scoreRate = 0;
            m_attackRate = 2;
            m_speedTime = 22;
            m_genCornNum = 0;
            m_fishCD = 0;
            break;
        case FISH_XIAOHUANGCI:
            m_activeFrameCount = 15;
            m_deadFrameCount = 5;
            m_scoreRate = 1;
            m_attackRate = 60;
            m_activeFrameDelay = 0.06;
            m_speedTime = 11;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_LANGUANGYU:
            m_activeFrameCount = 15;
            m_deadFrameCount = 6;
            m_scoreRate = 2;
            m_attackRate = 50;
            m_activeFrameDelay = 0.06;
            m_speedTime = 13;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_QICAIYU:
            m_activeFrameCount = 15;
            m_deadFrameCount = 6;
            m_scoreRate = 3;
            m_attackRate = 40;
            m_speedTime = 15;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_YINGWULUO:
            m_activeFrameCount = 8;
            m_deadFrameCount = 3;
            m_scoreRate = 5;
            m_attackRate = 30;
            m_speedTime = 17;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_TIAOWENYU:
            m_activeFrameCount = 8;
            m_deadFrameCount = 4;
            m_scoreRate = 8;
            m_attackRate = 20;
            m_activeFrameDelay = 0.1;
            m_speedTime = 16;
            m_genCornNum = 1;
            m_fishCD = 0;
            break;
        case FISH_GANGKUIYU:
            m_activeFrameCount = 9;
            m_deadFrameCount = 4;
            m_scoreRate = 12;
            m_attackRate = 10;
            m_speedTime = 18;
            m_genCornNum = 23;
            m_fishCD = 0;
            break;
        case FISH_HAIGUAI:
            m_activeFrameCount = 14;
            m_deadFrameCount = 4;
            m_scoreRate = 0;
            m_attackRate = 0;
            m_activeFrameDelay = 0.2;
            m_speedTime = 21;
            m_genCornNum = 24;
            m_fishCD = 2;
            break;
        case FISH_HGZHADAN:
            m_activeFrameCount = 9;
            m_deadFrameCount = 11;
            m_scoreRate = 0;
            m_attackRate = 20;
            m_speedTime = 20;
            m_genCornNum = 0;
            m_fishCD = 0;
            break;
        case FISH_NORMAL_TYPEMAX:
        case FISH_All_TYPEMAX:
            break;
    }
    
    if(m_fishCD !=0) {
        if(_fishLockArray[m_fishType] == false){
            lockFish(m_fishType, true);
        }
    }
}


Fish::~Fish()
{
//    CCLog("free fish %d",m_fishType);
    //if(m_fishType == FISH_HAIMA) {
    //    lockFish(FISH_HAIMA, false);
    //}
        

    
}


void Fish::lockFish(FishType type,bool lck)
{
    if(type >= FISH_NORMAL_TYPEMAX)
        return;
    _fishLockArray[type] = lck;
}

void Fish::lockFishRing(SpecialAttr type, bool lck)
{
    if(type >= sizeof(_fishRingLockArray))
        return;
    _fishRingLockArray[type] = lck;
}

#if 0
Fish* Fish::create(GameLayer *parent)
{
    static int freshRateTotal = 0;
    int i;
    if(freshRateTotal == 0) {
        for(i=0; i < FISH_TYPEMAX; i++) {
            if(_fishLockArray[i] == false)
                freshRateTotal += _freshRateArray[i];
        }
    }
    
    int t = arc4random() % freshRateTotal;
    for(i=0; i < FISH_TYPEMAX; i++) {
        if(_fishLockArray[i])
            continue;
        if(t < _freshRateArray[i])
            break;
        t -= _freshRateArray[i];
    }
    
    return createSpecificFish(parent,(FishType)i);
    //return createSpecificFish(parent,Fish::FISH_HUANGJINGJINGYU);
}
#endif

Fish::FishType Fish::getRefreshFishType()
{
    int freshRateTotal = 0;
    int i = 0;
    
    freshRateTotal = 0;
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        //? FISH_NORMAL_TYPEMAX-1
        for(i=0; i < FISH_NORMAL_TYPEMAX-1; i++) {
            if(_fishLockArray[i] == false)
                freshRateTotal += _freshRateArray[i];
        }
        int t = arc4random() % freshRateTotal;
        for(i=0; i < FISH_NORMAL_TYPEMAX-1; i++) {
            if(_fishLockArray[i]){
                //t -= _freshRateArray[i];
                continue;
            }
            if(t < _freshRateArray[i])
                break;
            t -= _freshRateArray[i];
        }
        if (i >= FISH_NORMAL_TYPEMAX)
        {
            i = FISH_NORMAL_TYPEMAX - 1;
        }
        return (FishType)i;
    }
    else
    {
        for (i = FISH_XIAOHUANGCI; i < FISH_HAIGUAI; i++)
        {
            freshRateTotal += _freshRateArray[i];
        }
        int t = arc4random() % freshRateTotal;
        for (i = FISH_XIAOHUANGCI; i < FISH_HAIGUAI; i++)
        {
            if (t < _freshRateArray[i])
            {
                break;
            }
            t -= _freshRateArray[i];
        }
        if (i >= FISH_HAIGUAI)
        {
            i = FISH_HAIGUAI - 1;
        }
        return (FishType)i;
    }
}

int Fish::getRefreshFishNum(FishType type)
{
    switch(type){
        case FISH_XIAOGUANGYU:
            return arc4random()%4+4;
            break;
        case FISH_XIAOCAOYU:
            return arc4random()%3+4;
        case FISH_REDAIYU:
            return arc4random()%3+2;
        case FISH_DAYANJINYU:
        case FISH_ALILAN:
            return arc4random()%2+3;
        case FISH_SHUIMU:
        case FISH_SHENXIANYU:
        case FISH_WUZEI:
        case FISH_XIAOCHOUYU:
            return arc4random()%2+2;
        case FISH_SHANWEIYU:
        case FISH_REDAIZIYU:
        case FISH_HETUN:
        case FISH_WUGUI:
        case FISH_DENGLONGYU:
        case FISH_HUDIEYU:
        case FISH_LINGDANGYU:
        case FISH_SHIBANYU:
            return arc4random()%2+1;
        case FISH_SHITOUYU:
            return arc4random()%3+1;
        case FISH_XIAOFEIYU:
            return 6;
        case FISH_JIANYU:
        case FISH_FEIYU:
        case FISH_LONGXIA:
            return 1;
        case FISH_HAITUN:
            return 0;
        case FISH_DAYINSHA:
        case FISH_LANJING:
//        case FISH_HUANGJINGJINGYU:
//        case FISH_HUANGJINGYU:
//        case FISH_LANSHA:
//        case FISH_BYMOGUIYU:
//        case FISH_BYWUGUI:
        case FISH_ZHENZHUBEI:
//        case FISH_HAIMA:
            return 1;
        // 刷新鱼的数量
        case FISH_XIAOHUANGCI:
            return arc4random() % 2 + 6;
        case FISH_LANGUANGYU:
            return arc4random() % 1 + 5;
        case FISH_QICAIYU:
            return arc4random() % 2 + 3;
        case FISH_YINGWULUO:
        case FISH_TIAOWENYU:
            return arc4random() % 1 + 1;
        case FISH_GANGKUIYU:
        case FISH_HAIGUAI:
            return 1;
        default:
            return 1;
    }
}

Fish* Fish::createSpecFish(GameLayer *parent)
{
    FishType specArray[] = {
        FISH_REDAIZIYU,
        FISH_XIAOCHOUYU,
        FISH_HETUN,
        FISH_SHITOUYU,
        FISH_DENGLONGYU,
        FISH_SHENXIANYU,
        FISH_WUGUI,
        FISH_HUDIEYU
    };
    
    int j = arc4random()%(sizeof(specArray)/sizeof(specArray[0]));
    Fish *p =NULL;
    
    
    int n = 0;
    for(int _j = 0; _j < sizeof(_fishRingLockArray); _j++) {
        if(_fishRingLockArray[_j] == false)
            n++;
    }
    if(n != 0) {
        int t = arc4random()%n;
        int i =0;
        for( i = 0; i < sizeof(_fishRingLockArray);i++) {
            if(_fishRingLockArray[i])
                continue;
            if(t == 0)
                break;
            t--;
        }
        
        if(arc4random()%10<5)
        {
             p= createSpecificFish(parent,FISH_HAITUN);
            p->setSpec(SPEC_YWYQ);
        }
        else
        {
            if ((Fish::SpecialAttr)i == SPEC_YWYQ) {
                p= createSpecificFish(parent,FISH_HAITUN);
            }
            else
            {
                p = createSpecificFish(parent,specArray[j]);
            }
            p->setSpec((Fish::SpecialAttr)i);
        }
        
        
    }
    
    switch(p->m_spec){
        case SPEC_HLYQ:
        case SPEC_DASIXI:
        case SPEC_TLYQ:
            switch(p->m_fishType) {
                case FISH_REDAIZIYU:
                case FISH_XIAOCHOUYU:
                    p->m_attackRate = 5;
                    break;
                case FISH_HETUN:
                case FISH_SHITOUYU:
                    p->m_attackRate = 4;
                    break;
                case FISH_DENGLONGYU:
                case FISH_SHENXIANYU:
                    p->m_attackRate = 3;
                    break;
                case FISH_WUGUI:
                case FISH_HUDIEYU:
                    p->m_attackRate = 2;
                    break;
            }
            break;
        case SPEC_HYLL:
            switch(p->m_fishType) {
                case FISH_REDAIZIYU:
                case FISH_XIAOCHOUYU:
                case FISH_HETUN:
                case FISH_SHITOUYU:
                    p->m_attackRate = 5;
                    break;
                case FISH_DENGLONGYU:
                case FISH_SHENXIANYU:
                case FISH_WUGUI:
                case FISH_HUDIEYU:
                    p->m_attackRate = 4;
                    break;
            }
            break;
        case SPEC_ZDYQ:
        case SPEC_YWYQ:
            switch(p->m_fishType) {
                case FISH_REDAIZIYU:
                case FISH_XIAOCHOUYU:
                case FISH_HETUN:
                    p->m_attackRate = 1;  //5
                    break;
                case FISH_SHITOUYU:
                case FISH_DENGLONGYU:
                case FISH_SHENXIANYU:
                    p->m_attackRate = 1;//4
                    break;
                case FISH_WUGUI:
                case FISH_HUDIEYU:
                    p->m_attackRate = 1;//3
                    break;
                    default:
                    p->m_attackRate = 1;
                    break;
            }
            break;
    }
    //special fish remains 18
    p->m_speedTime = 18;
    return p;
}


Fish* Fish::createSpecificFish(GameLayer *parent,FishType type,bool withPath)
{
    Fish * n = new Fish(type);
    n->init();
    n->generateFrameAnimation();
    if(withPath)
        n->generateFishPath();
    n->autorelease();
    n->m_parent = parent;
    n->m_parent->retain();
    /*
    if(type == FISH_ZHENZHUBEI) {
        return SpecialFish::create(parent,type);
    } if( type < 6) {
        return SmallFish::create(parent,type);
    } else {
        return BigFish::create(parent,type);
    }
     */
    
    return n;
}

void Fish::generateFishPath()
{
    FishPathFactory::createFishPath(this);
}

void Fish::goFish()
{
    CCAction*  fishaction = NULL;
    CCAnimate *animate=CCAnimate::create(m_activeFrameAnimation);
    
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::fishStopCBK));
    if(m_fishPath != NULL) {
        m_fishPath->addObject(callFunc);
        fishaction = CCSpawn::createWithTwoActions(CCRepeat::create(animate,100),CCSequence::create(m_fishPath));
        m_fishPath->removeObject(callFunc);
    } else {
        fishaction = CCSequence::create(CCRepeat::create(animate,100),callFunc,NULL);
    }
    runAction(fishaction);
}

int Fish::dealWithTLYQ()
{
    CCObject * pFishObj = NULL;
    int score = 0;
    CCARRAY_FOREACH(m_parent->getFishes(), pFishObj)
    {
        Fish *pFish = (Fish *)pFishObj;

        if(pFish->m_fishType == m_fishType && pFish != this) {
            //score += pFish->killFish(m_attackBullet);
            score += pFish->attackFish(m_attackBullet,1);
        }
    }
    
    return score;
}


void Fish::setOpacity(GLubyte opacity)
{
    CCObject *pcd = NULL;
    CCArray *n = getChildren();
    CCARRAY_FOREACH(n,pcd) {
        ((CCSprite*)pcd)->setOpacity(opacity);
    }
    CCSprite::setOpacity(opacity);
}

void Fish::setColor(const ccColor3B& color3)
{
    CCObject *pcd = NULL;
    CCArray *n = getChildren();
    CCARRAY_FOREACH(n,pcd) {
        ((CCSprite*)pcd)->setColor(color3);
    }
    CCSprite::setColor(color3);
}

int Fish::dealWithZhadanFish()
{
    CCObject * pFishObj = NULL;
    int score = 0;
    CCARRAY_FOREACH(m_parent->getFishes(), pFishObj)
    {
        Fish *pFish = (Fish *)pFishObj;
        
        if (pFish == NULL || pFish == this || pFish->m_fishType == FISH_ZHADANFISH || pFish->m_fishType == FISH_HGZHADAN || pFish->m_spec != SPEC_NONE || pFish->m_fishType == FISH_HAIGUAI) {
            continue;
        }
        if (m_fishType == FISH_HGZHADAN)
        {
            score += pFish->attackFish(m_attackBullet, 1);
        }
        else
        {
            score += pFish->attackFish(m_attackBullet, 0.5);
        }
    }
    
    return score;

}

int Fish::dealWithHLYQ()
{
    float rate = 0;
    int score;
    switch(m_fishType ) {
        case FISH_REDAIZIYU:
        case FISH_XIAOCHOUYU:
            rate = 0.05;
            break;
        case FISH_HETUN:
        case FISH_SHITOUYU:
            rate = 0.06;
            break;
        case FISH_SHENXIANYU:
            rate = 0.07;
            break;
        case FISH_WUGUI:
            rate = 0.08;
            break;
        case FISH_DENGLONGYU:
            rate = 0.09;
            break;
        case FISH_HUDIEYU:
            rate = 0.1;
            break;
        default:
            break;
    }
    score = GameData::getSharedGameData()->score() * rate;
    if(score < 1000)
        score = 1000;
    if(score > 1000000)
        score = 1000000;
    return score;
}


extern CCRect shrinkRect(CCRect rc, float xr, float yr);


int Fish::dealWithZDYQ()
{
    CCObject * pFishObj = NULL;
    int score = 0;
    float rate = 0;
    CCARRAY_FOREACH(m_parent->getFishes(), pFishObj)
    {
        Fish *pFish = (Fish *)pFishObj;
        
        if (pFish == NULL || pFish == this || pFish->m_spec != SPEC_NONE) {
            continue;
        }
        
        CCRect hittestRect = shrinkRect(pFish->boundingBox(), 3.0f, 3.0f);
        //CCRect hittestRect = pFish->boundingBox();
        
        if(hittestRect.intersectsRect(boundingBox()))
        {
            switch(pFish->m_fishType ) {
                case FISH_REDAIZIYU:
                case FISH_XIAOCHOUYU:
                    rate = 0.45;
                    break;
                case FISH_HETUN:
                case FISH_SHITOUYU:
                    rate = 0.55;
                    break;
                case FISH_SHENXIANYU:
                case FISH_WUGUI:
                    rate = 0.65;
                    break;
                case FISH_DENGLONGYU:
                case FISH_HUDIEYU:
                    rate = 0.75;
                    break;
                default:
                    break;
            }
            score += pFish->attackFish(m_attackBullet,rate);
        }
    }
    
    return score;
}

int Fish::dealWithYWYQ()
{
   // CCObject * pFishObj = NULL;
    //int score = this->attackFish(m_attackBullet,1);
    
    //int num = 0;
    m_parent->fishdeadCallBack(m_lastPoint);
    /*    del by andy 2015-04-15
    CCARRAY_FOREACH(m_parent->getFishes(), pFishObj)
    {
        Fish *pFish = (Fish *)pFishObj;
        
        if(pFish->m_fishType == m_fishType && pFish != this && m_spec == SPEC_NONE) {
            //score += pFish->killFish(m_attackBullet);
            score += pFish->attackFish(m_attackBullet,1);
            num ++;
            if(num == 8){
                break;
            }
        }
    }
    
    if(num < 8) {
        CCARRAY_FOREACH(m_parent->getFishes(), pFishObj)
        {
            Fish *pFish = (Fish *)pFishObj;
            
            if(pFish->m_scoreRate <= m_scoreRate && pFish != this && pFish->m_spec == SPEC_NONE) {
                //score += pFish->killFish(m_attackBullet);
                score += pFish->attackFish(m_attackBullet,1);
                num ++;
                if(num == 8){
                    break;
                }
            }
        }
    }
    */
    return 0;
}


//int Fish::dealWithYWYQ()
//{
//    int rate = 0;
//    switch(m_fishType ) {
//        case FISH_REDAIZIYU:
//        case FISH_XIAOCHOUYU:
//        case FISH_HETUN:
//        case FISH_SHITOUYU:
//            rate = arc4random()%10 + 11;
//            break;
//        case FISH_SHENXIANYU:
//        case FISH_WUGUI:
//            rate = arc4random()%10 + 21;
//            break;
//        case FISH_DENGLONGYU:
//        case FISH_HUDIEYU:
//            rate = arc4random()%10 + 31;
//            break;
//        default:
//            break;
//    }
//    
//    return m_attackBullet->bullet_score * rate;
//}

int Fish::killFish(FatherBullet *pBullet)
{
    if(pBullet) {
        m_attackBullet = pBullet;
        m_attackBullet->retain();
    }
    
    //first remove from parent m_pFishes to avoid multi-attack
    m_parent->getFishes()->removeObject(this);
    
    stopAllActions();
    if(m_spec == SPEC_ZDYQ) {
        char str[32];
        
        
        bzero(str,sizeof(str));
        CCArray *aniframe = CCArray::createWithCapacity(10);
        
        
        for(int i=0;i <10;i++){
            sprintf(str,"quan06_%d.png",i);  //通过下标动态创建精灵
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
            
            aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
        }
        CCAnimate *animate = CCAnimate::create(CCAnimation::createWithSpriteFrames(aniframe,0.1f));//通过集合创建动画
        
        
        CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::fishDeadCBK));
        m_fishAction = CCSequence::create(CCRepeat::create(animate,1), callFunc, NULL);
        //m_fishAction->retain();
        runAction(m_fishAction);
        Sound::Instance()->playEffect("bomb1.mp3");
    }
    else {
        CCAnimate *animate = CCAnimate::create(m_deadFrameAnimation);
        CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::fishDeadCBK));
        m_fishAction = CCSequence::create(CCRepeat::create(animate,1), callFunc, NULL);
        //m_fishAction->retain();
        runAction(m_fishAction);
    }
    //shake the hole screen
    if ( m_fishType == FISH_ZHADANFISH || m_fishType == FISH_HGZHADAN) {
        CCSequence *p = CCSequence::create(CCMoveBy::create(0.05,ccp(0,20)),
                                           CCMoveBy::create(0.05,ccp(0,-20)),
                                           CCMoveBy::create(0.05,ccp(0,-20)),
                                           CCMoveBy::create(0.05,ccp(0,20)),
                                           CCMoveBy::create(0.05,ccp(0,15)),
                                           CCMoveBy::create(0.05,ccp(0,-15)),
                                           CCMoveBy::create(0.05,ccp(0,-15)),
                                           CCMoveBy::create(0.05,ccp(0,15)),
                                           CCMoveBy::create(0.05,ccp(0,10)),
                                           CCMoveBy::create(0.05,ccp(0,-10)),
                                           CCMoveBy::create(0.05,ccp(0,-10)),
                                           CCMoveBy::create(0.05,ccp(0,10)),
                                           CCMoveBy::create(0.05,ccp(0,5)),
                                           CCMoveBy::create(0.05,ccp(0,-5)),
                                           CCMoveBy::create(0.05,ccp(0,-5)),
                                           CCMoveBy::create(0.05,ccp(0,5)),NULL);
        
        m_parent->runAction(p);
    }
    
    playDeadSound();
    int gemRate,canonRate;
    gemRate = canonRate = 0;
    //del by andy 2015-04-27
    // 更新任务 捕捉到鱼
    //GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_CATCHFISH, (int)m_fishType, 1);
    // 更新任务 鱼倍数相关
   // GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_CATCHMULTIFISH, m_scoreRate, 1);
   // GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_CATCHMULTIFISHUP, m_scoreRate, 1);
   // GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_CATCHMULTIFISHDOWN, m_scoreRate, 1);
    // 更新任务 捕捉到指定渔圈
    //GameData::getSharedGameData()->updateTaskProgress(TASK_TYPE_CATCHFISHCIRCLE, (int)m_spec, 1);
    //del by andy 2015-04-27 end
    if (GameData::getSharedGameData()->getSeaMonsterTime() < 45 && GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty)
    {
        // 困难模式杀死鱼增加倍数时间
        GameData::getSharedGameData()->addSeaMonsterTime(m_scoreRate);
    }
    
    switch(m_fishType) {
//        case FISH_XIAOGUANGYU:
//            m_parent->startLaser(true);
//            canonRate = 100;
//            gemRate = 0;
//            break;
        case FISH_REDAIZIYU:
        case FISH_XIAOCHOUYU:
        case FISH_HETUN:
        case FISH_WUZEI:
            canonRate = 1;
            gemRate = 0;
            break;
        case FISH_SHITOUYU:
        case FISH_DENGLONGYU:
        case FISH_SHENXIANYU:
            canonRate = 2;
            gemRate = 0;
            break;
        case FISH_WUGUI:
        case FISH_SHIBANYU:
            canonRate = 3;
            gemRate = 3;
            break;
        case FISH_HUDIEYU:
        case FISH_LINGDANGYU:
            canonRate = 4;
            gemRate = 5;
            break;
        case FISH_JIANYU:
        case FISH_MOGUIYU:
            canonRate = 5;
            gemRate = 7;
            break;
        case FISH_FEIYU:
        case FISH_LONGXIA:
            canonRate = 6;
            gemRate = 10;
            break;
        case FISH_HAITUN:
        case FISH_DAYINSHA:
            canonRate = 7;
            gemRate = 12;
            break;
        case FISH_LANJING:
            canonRate = 8;
            gemRate = 12;
            break;
//        case FISH_HUANGJINGJINGYU:
//            canonRate = 8;
//            gemRate = 15;
//            break;
//        case FISH_HUANGJINGYU:
//            m_parent->startPower(true);
//            break;
//        case FISH_LANSHA:
//            m_parent->startLaser(true);
//            break;
        case FISH_ZHENZHUBEI:
            m_parent->dropGemstone(Diamond_Pearl);
            break;
//        case FISH_BYMOGUIYU:
//        case FISH_BYWUGUI:
//            gemRate = 100;
//            canonRate = 0;
//            break;
//        case FISH_HAIMA:
//            //冻结炮弹的计时器
//            m_parent->setFreezeing(true);
//            CCDirector::sharedDirector()->getRunningScene()->addChild(FlipCardBonusLayer::scene());
//            break;
        case FISH_ZHADANFISH:
            //TODO 杀死鱼之后的效果
            break;
        case FISH_XIAOHUANGCI:
            break;
        case FISH_LANGUANGYU:
            break;
        case FISH_QICAIYU:
            break;
        case FISH_YINGWULUO:
            break;
        case FISH_TIAOWENYU:
            break;
        case FISH_GANGKUIYU:
            break;
        case FISH_HAIGUAI:
            break;
        case FISH_HGZHADAN:
            break;
        default:
            canonRate = 0;
            gemRate = 0;
            break;
    }
    
    if(arc4random()%100 < gemRate) {
        m_parent->dropGemstone((DiamondType)(arc4random()%4+1));
    }
    
    if(arc4random()%100 < canonRate) {
//        arc4random()%2 ? m_parent->startPower(false) : m_parent->startLaser(false);
        m_parent->startPower(false);
    }
    if (m_spec == SPEC_YWYQ) {
        return 0;
    }
    return m_attackBullet->bullet_score * m_scoreRate;
}

int Fish::attackFish(FatherBullet *pBullet, float rate)
{
    int originScore = 0;
    int extraScore = 0;
    int bombScore = 0;
    if(pBullet) {
        m_attackBullet = pBullet;
        m_attackBullet->retain();
    }
    
    // 判断是否是海怪模式
    if (GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Difficulty || GameData::getSharedGameData()->getGameType() == GameType_SeaMonster_Normal)
    {
        if (m_fishType == FISH_HAIGUAI)
        {
            float p = arc4random() % 5 + 95;
            p = p / 100;
            int pSeaMonsterDamage = (int)(p * pBullet->bullet_score * -1);
            GameData::getSharedGameData()->addSeaMonsterBlood(pSeaMonsterDamage);
            SeaMonsterInterface* si = dynamic_cast<SeaMonsterInterface*>(m_parent);
            si->onGetDamage();
//            CCLog(" hit seamonster %d", pSeaMonsterDamage);
        }
    }
    
    if(!willDead(rate)){
        //take a shine
        schedule(schedule_selector(Fish::updateShine), 0.1f, 5, 0);
        //ccColor3B c1 = getColor();
        //CCLog("%f %f %f",c1.r,c1.g,c1.b);
        return 0;
    }
    
    //kill current fish first
    originScore = killFish(pBullet);
    
    //zhadan fish?
    if (m_fishType == FISH_ZHADANFISH || m_fishType == FISH_HGZHADAN)
    {
        bombScore = dealWithZhadanFish();
    }
    
    //special fish?
    switch(m_spec) {
        case SPEC_DASIXI:
            extraScore = originScore * 3;
            break;
        case SPEC_HLYQ:
            extraScore = dealWithHLYQ();
            break;
        case SPEC_HYLL:
            m_parent->startRollLottery();
            break;
        case SPEC_TLYQ:
            extraScore = dealWithTLYQ();
            break;
        case SPEC_ZDYQ:
            dealWithZDYQ();
            break;
        case SPEC_YWYQ:
            dealWithYWYQ();
            break;
        case SPEC_NONE:
        default:
            break;
    }
    
    if((extraScore+originScore) > 0) {
        generateCoin(m_genCornNum);
        generateNum(extraScore + originScore);
    }
    
    return extraScore + originScore + bombScore;
}

void Fish::updateShine(cocos2d::CCTime dt)
{
    ccColor3B c1 = getColor();
    if(c1.r != 125){
        setColor(ccc3(125,0,0));
    }else{
        setColor(m_originColor);
    }
}

void Fish::unLockAndRelease()
{
    lockFish(m_fishType,false);
    removeFromParentAndCleanup(true);
}

void Fish::fishDeadCBK()
{
    
    if(_fishLockArray[m_fishType] == true){
        //locked by CD, we will unlock it when cd out.
        setVisible(false);
        CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::unLockAndRelease));
        runAction(CCSequence::create(CCDelayTime::create(m_fishCD),callFunc,NULL));
    } else {
        removeFromParentAndCleanup(true);
    }
    if( m_attackBullet) {
        m_attackBullet->release();
        m_attackBullet = NULL;
    }
}

void Fish::fishStopCBK()
{
//    CCLog("fish stop %d",m_fishType);
    FishInterface *pl = dynamic_cast<FishInterface*>(m_parent);
    pl->removeFish(this);
    
    if(_fishLockArray[m_fishType] == true){
        //locked by CD, we will unlock it when cd out.
        setVisible(false);
        CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::unLockAndRelease));
        runAction(CCSequence::create(CCDelayTime::create(m_fishCD),callFunc,NULL));
    } else {
        removeFromParentAndCleanup(true);
    }
}


const char * Fish::getFishFilePrefix(FishType type)
{
    switch (type) {
        case FISH_XIAOGUANGYU:
            return "xiaoguangyu";
        case FISH_XIAOCAOYU:
            return "xiaocaoyu";
        case FISH_REDAIYU:
            return "redaiyu";
        case FISH_DAYANJINYU:
            return "dayanjinyu";
        case FISH_SHUIMU:
            return "shuimu";
        case FISH_SHANWEIYU:
            return "shanweiyu";
        case FISH_REDAIZIYU:
            return "redaiziyu";
        case FISH_XIAOCHOUYU:
            return "xiaochouyu";
        case FISH_HETUN:
            return "hetun";
        case FISH_WUZEI:
            return "wuzei";
        case FISH_SHITOUYU:
            return "shitouyu";
        case FISH_SHENXIANYU:
            return "shenxianyu";
        case FISH_WUGUI:
            return "wugui";
        case FISH_DENGLONGYU:
            return "denglongyu";
        case FISH_SHIBANYU:
            return "shibanyu";
        case FISH_HUDIEYU:
            return "hudieyu";
        case FISH_LINGDANGYU:
            return "lingdangyu";
        case FISH_JIANYU:
            return "jianyu";
        case FISH_MOGUIYU:
            return "moguiyu";
        case FISH_FEIYU:
            return "feiyu";
        case FISH_LONGXIA:
            return "longxia";
        case FISH_HAITUN:
            return "haitun";
        case FISH_DAYINSHA:
            return "dayinsha";
        case FISH_LANJING:
            return "lanjing";
//        case FISH_HUANGJINGJINGYU:
//            return "huangjingjingyu";
//        case FISH_HUANGJINGYU:
//            return "huangjingyu";
//        case FISH_BYMOGUIYU:
//            return "bymoguiyu";
//        case FISH_BYWUGUI:
//            return "bywugui";
        case FISH_ZHENZHUBEI:
            return "zhenzhubei";
//        case FISH_LANSHA:
//            return "lansha";
        case FISH_XIAOFEIYU:
            return "xiaofeiyu";
        case FISH_ALILAN:
            return "alilan";
//        case FISH_HAIMA:
//            return "haima";
        case FISH_ZHADANFISH:
            return "zhadan";
        case FISH_XIAOHUANGCI:
            return "xiaohuangci";
        case FISH_LANGUANGYU:
            return "languangyu";
        case FISH_QICAIYU:
            return "qicaiyu";
        case FISH_YINGWULUO:
            return "yingwuluo";
        case FISH_TIAOWENYU:
            return "tiaowenyu";
        case FISH_GANGKUIYU:
            return "gangguiyu";
        case FISH_HAIGUAI:
            return "haiguai";
        case FISH_HGZHADAN:
            return "hgzhadan";
        default:
            return "";
    }
}


void Fish::generateFrameAnimation()
{
    char str[32];
    

    bzero(str,sizeof(str));
    CCArray *aniframe = CCArray::createWithCapacity(m_activeFrameCount);
    
    
    for(int i=0;i <m_activeFrameCount;i++){
        sprintf(str,"%s_%d.png",getFishFilePrefix(m_fishType),i);  //通过下标动态创建精灵
        //CCSpriteFrame *frame =CCSpriteFrame::create(str,CCRectMake(0,0,64,128));        
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        
        if(i==0){//默认添加第一帧图到界面上
            initWithSpriteFrame(frame);
            //setPosition(ccp(0,0));
        }
        //add by lqg 2015-04-12
        if (!frame) {
            DF_LOG("generateFrameAnimation frame =%s ",str);
        }
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
    
    }
    m_activeFrameAnimation = CCAnimation::createWithSpriteFrames(aniframe,m_activeFrameDelay);//通过集合创建动画
    m_activeFrameAnimation->retain();

    

    bzero(str,sizeof(str));
    CCArray *aniframe2 = CCArray::createWithCapacity(m_deadFrameCount);
    
    for(int i=0;i <m_deadFrameCount;i++){
        if (m_fishType == FISH_HGZHADAN)
        {
            sprintf(str, "%s_d%d.png", getFishFilePrefix(FISH_ZHADANFISH), i);
        }
        else
        {
            sprintf(str,"%s_d%d.png",getFishFilePrefix(m_fishType),i);  //通过下标动态创建精灵
        }
        //CCSpriteFrame *frame =CCSpriteFrame::create(str,CCRectMake(0,0,64,128));
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        
        if(i==0){//默认添加第一帧图到界面上
            //initWithSpriteFrame(frame);
            //setPosition(ccp(0,0));
        }
        //add by lqg 2015-04-12
        if (!frame) {
            DF_LOG("generateFrameAnimation frame =%s ",str);
        }
        aniframe2->addObject(frame);//将每一帧精灵动画添加到集合里面
    }
    
    m_deadFrameAnimation = CCAnimation::createWithSpriteFrames(aniframe2,m_deadFrameDelay);//通过集合创建动画
    m_deadFrameAnimation->retain();
    
}

CCFishBezierTo* Fish::generateBezierPath(CCPoint start, CCPoint c1, CCPoint c2, CCPoint end,float t)
{
    setPosition(start);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = c1;
    bezier.controlPoint_2 = c2;
    bezier.endPosition = end;
    
    CCFishBezierTo * p = CCFishBezierTo::create(t,bezier);
    p->startWithTarget(this);
    return p;
}

void Fish::generateCoin(int onum)
{
    Coin * pc[10] = {0};
    float tangle;
    float step;
    CCPoint pt = getPosition();
    int type = onum/10;
    int num = onum%10;
    if( num <= 0 || num > 10) {
        return;
    }
    
    if(num == 1) {
        tangle = 0;
        step = tangle;
    } else if(num == 2) {
        tangle = M_PI/6;
        step = tangle;
    } else if(num == 3) {
        tangle = M_PI/3;
        step = tangle/(num-1);
    } else {
        tangle = M_PI/2;
        step = tangle/(num-1);
    }
    
    for(int i=0; i < num ;i++) {
        float angle;
        if(num %2 == 1) {
            angle = M_PI/2+pow(-1.0,i)*step*(floor((i+1)/2));
        } else {
            angle = (M_PI/2 - tangle/2)+(step*i);
        }
        pc[i] = Coin::create(type?(Coin::COIN_TYPE_GOLDBIG):(Coin::COIN_TYPE_GOLDSMALL));
        pc[i]->setPosition(pt);
        pc[i]->addLinePathTo(0.2, ccp(pt.x+100*cos(angle),pt.y+100*sin(angle)));
        pc[i]->addLinePathTo(1, ccp(65,50));
        m_parent->getBatchNodeCoin()->addChild(pc[i]);
        pc[i]->goCoin();
    }
    
    Sound::Instance()->playEffect("Coin.mp3");
}

void Fish::generateNum(int num)
{
    NumSprite *p = NumSprite::create(num);
    p->setPosition(getPosition());
    p->setScale(0.8);
    m_parent->getBatchNodeCoin()->addChild(p);
    
    CCSpawn * sp2 = CCSpawn::createWithTwoActions(CCFadeOut::create(2), CCMoveBy::create(2, ccp(0,100)));
    
    CCFiniteTimeAction *callFunc = CCCallFunc::create(p, callfunc_selector(NumSprite::removeFromParent));
    p->runAction(CCSequence::create(CCMoveBy::create(0.05,ccp(0,20)),sp2,callFunc,NULL));
}

void Fish::playDeadSound()
{
    const char *p = NULL;
    switch(m_fishType){
        case FISH_SHENXIANYU:
//            p = "fish01.mp3";
            break;
//        case FISH_BYWUGUI:
//            p = "fish02.mp3";
//            break;
        case FISH_HUDIEYU:
            p = "fish04.mp3";
            break;
        case FISH_LINGDANGYU:
            p = "fish05.mp3";
            break;
        case FISH_MOGUIYU:
//        case FISH_BYMOGUIYU:
            p = "fish06.mp3";
            break;
        case FISH_LONGXIA:
            p = "fish07.mp3";
            break;
        case FISH_HAITUN:
            p = "fish08.mp3";
            break;
        case FISH_DAYINSHA:
            p = "fish09.mp3";
            break;
        case FISH_LANJING:
            p = "fish10.mp3";
            break;
//        case FISH_HUANGJINGJINGYU:
//            p = "fish11.mp3";
//            break;
//        case FISH_HAIMA:
//            p = "fish03.mp3";
//            break;
        case FISH_ZHADANFISH:
        case FISH_HGZHADAN:
            p = "bomb1.mp3";
            break;
//        case FISH_LANSHA:
//            p = "fish01.mp3";
//            break;
        case FISH_JIANYU:
        case FISH_FEIYU:
//        case FISH_HUANGJINGYU:
            p = "fish00.mp3";
            break;
        default:
            p = NULL;
            break;
    }
    
    if( p!= NULL) {
        Sound::Instance()->playEffect(p);
    }
}

bool Fish::willDead(float rate)
{
    if(rate == 0) {
        int t_rate = m_attackRate * m_attackBullet->hit_rate;
        if (m_spec == SPEC_YWYQ) {
            return   arc4random()%1500<400;
        }
        return arc4random()%(10000-100*m_attackBullet->hit_Percentage) < t_rate;
    }else {
        return arc4random()%100 < rate*100;
    }
}

void Fish::setSpec(SpecialAttr spec)
{
    
    const char* pstr = NULL;
    switch(spec) {
        case SPEC_DASIXI:
            pstr = "dasixi.png";
            break;
        case SPEC_HLYQ:
            pstr = "hlyq.png";
            break;
        case SPEC_TLYQ:
            pstr = "tlyq.png";
            break;
        case SPEC_HYLL:
            pstr = "hyll.png";
            break;
        case SPEC_ZDYQ:
            pstr = "zdyq.png";
            break;
        case SPEC_YWYQ:
            pstr = "bjyq.png";
        default:
            break;
    }
    
    if(pstr) {
        m_spec = spec;
        if(m_specSprite) {
            m_specSprite->release();
            m_specSprite = NULL;
        }

        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pstr);
        m_specSprite = CCSprite::createWithSpriteFrame(frame);
        m_specSprite->retain();
        addChild(m_specSprite,-1);
        CCSize a = getContentSize();
        CCSize b = m_specSprite->getContentSize();
//        m_specSprite->setAnchorPoint(CCPointZero);
        m_specSprite->setPosition(ccp(a.width/2,a.height/2));
        m_specSprite->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 150)));
        
    }
    
}

bool Fish::isFishLocked(FishType type)
{
    return _fishLockArray[type];
}
