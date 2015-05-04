//
//  FlipCardBonus.h
//  fish
//
//  
//
//

#ifndef __fish__FlipCardBonus__
#define __fish__FlipCardBonus__

#include <cstddef>
#include "Typedef.h"

#define  DEBUG_FLIP_CARD (0)

//牌型种类
typedef enum enCardTypes {
    CardIllegal, //非法牌型
    CardBonus,   //奖励
    CardCrab,    //螃蟹
    CardShark,   //鲨鱼
    CardTortoise, //乌龟
    CardInkFish,  //乌贼
    CardTypeNum,
    
}CardTypes;



//5*5
const TUint8 CARDS_IN_ROW = 5;
const TUint8 CARDS_IN_COL = 5;
const TUint8 TOTAL_CARDS  = CARDS_IN_ROW * CARDS_IN_COL;


//已经翻过标记
const TInt8 CARD_HAD_FLIPED_FLAG  = -1;

//缺少金币,每次点击可获得1k
const TInt32 SHORTAGE_COINS_FLIP_BONUS = 1000;
const TInt32 MIN_CONIS = 50;

//击杀海马,每次点击可获得5k
const TInt32 KILL_SEA_HORSE_FLIP_BONUS = 5000;

//击杀海马,最多可获得奖励数据
const TUint32 MAX_KILL_SEA_HORSE_FLIP_BONUS = (KILL_SEA_HORSE_FLIP_BONUS * TOTAL_CARDS);

//缺少金币,最多可获得奖励数据
const TUint32 MAX_SHORTAGE_COINS_FLIP_BONUS = (SHORTAGE_COINS_FLIP_BONUS * TOTAL_CARDS);

//触发翻翻乐的原因
enum BonusTrigger{
    TriggerIllegal,   //非法原因
    ShortageCoins,    //缺少金币
    KillSeaHorse,     //击杀海马
    BonusTriggerNum,
};




//翻翻乐版型生成器
class FlipCardBonusManager  {
    

public:

    ~FlipCardBonusManager();
    
    //获得一个共享的翻翻乐生成器
    static FlipCardBonusManager* sharedFlipCardBonusManager();
    
    //生成翻翻乐数据,默认为‘缺少金币’
    void generate(BonusTrigger trigger = ShortageCoins);
    
    //是否翻到bonus牌
    bool isBonus(TUint8 index);
    
    //是否与前一张牌，牌型相同
    bool isSameAsPrevCard( TUint8 index);
    
    //是否已经翻转
    bool hadFliped(TUint8 index);
    
    //获得奖励
    TUint32 coins();
    
    //翻牌
    void flip(TUint8 index );
    
    //此索引所对应的牌的图像文件名,默认为背景文件
    const char* cardsImageName(TUint8 index);
    
    //每张牌的分值
    int base();
    
    void setTrigger(BonusTrigger theTrigger) { trigger = theTrigger;}
    
    bool isGameOver();
    void setGameOver( bool result);
    
private:
    FlipCardBonusManager();
    
private:

    void reset();
    void shuffle();
    
    CardTypes card( TUint8 index);
    void setCard( TUint8 index, CardTypes type);
    
    void swap(CardTypes* p, CardTypes* q);
    
    
private:
    class Cleaner
    {
    public:
        Cleaner(){}
        ~Cleaner()
        {
            if(FlipCardBonusManager::sharedFlipCardBonusManager() != NULL) {
                delete FlipCardBonusManager::sharedFlipCardBonusManager();
            }
        }
    };
    

    
private:
    
    //牌型数据缓存
    CardTypes cards[TOTAL_CARDS];
                                     
    //前一次所翻的牌型
    CardTypes prevCardType;
    
    //触发翻翻乐的原因
    BonusTrigger trigger;
    
    //当前获得的金币数
    TUint32 _coins;
    
    bool _gameOver;
    
    static FlipCardBonusManager *sharedManager;
};

#endif /* defined(__fish__FlipCardBonus__) */
