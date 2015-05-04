//
//  FlipCardBonus.cpp
//  fish
//
//  
//
//

#include "FlipCardBonus.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>

FlipCardBonusManager* FlipCardBonusManager::sharedManager = NULL;

//获得一个共享的翻翻乐生成器
 FlipCardBonusManager* FlipCardBonusManager::sharedFlipCardBonusManager()
{
    if (sharedManager == NULL) {
        
        srand( time(NULL));
        
        sharedManager = new FlipCardBonusManager();
        static Cleaner cleaner;
    }
    return sharedManager;
    
}

FlipCardBonusManager::FlipCardBonusManager(){}
FlipCardBonusManager::~FlipCardBonusManager(){}


//生成翻翻乐数据,默认为‘缺少金币’
 void FlipCardBonusManager::generate(BonusTrigger theTrigger)
{
    //trigger = theTrigger;
    
    reset();

    shuffle();

    
}

void FlipCardBonusManager::swap(CardTypes* p, CardTypes* q)
{
    CardTypes tmp = *p;
    *p = *q;
    *q = tmp;
}

void FlipCardBonusManager::shuffle()
{
    int i;
    for(i = 0; i < TOTAL_CARDS; i++) {
        int idx = rand() % (i + 1); //选取互换的位置
        swap(&cards[idx], &cards[i]);
    }
    
#ifdef DEBUG_FLIP_CARD
    //生成原始牌型数据
    printf("after shuffle\n");
    
    for (int i = 0; i < 5; i++ ) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", card(i * 5 + j));
        }
        printf("\n");
    }
    
#endif
    
}


//是否翻到bonus牌
bool FlipCardBonusManager::isBonus(TUint8 index)
{
    CardTypes type = card(index);
    
    return (type == CardBonus) ? true : false;
    
}

//是否与前一张牌，牌型相同
bool FlipCardBonusManager::isSameAsPrevCard( TUint8 index)
{
    CardTypes type = card(index);
    
    return  (type == prevCardType) ? true : false;
}

CardTypes FlipCardBonusManager::card(unsigned char index) {
    
    if (index < 0 || index >= TOTAL_CARDS) {
        return CardIllegal; //todo: 索引错误,应单独处理
    }

    
    return cards[index];
}

void FlipCardBonusManager::setCard(unsigned char index, CardTypes type) {
    if (index < 0 || index >= TOTAL_CARDS) {
        return;
    }
    
    if (type < CardIllegal || type >= CardTypeNum) {
        return;
    }
    cards[index] = type;
    
}
//是否已经翻转
bool FlipCardBonusManager::hadFliped(TUint8 index)
{
    CardTypes type = card(index);
    
    //所有不合法,均视为已经反转过, todo .应该细分
    return (type == CardIllegal) ? true : false;
    
}

//获得奖励
TUint32 FlipCardBonusManager::coins() {
    
    return _coins;
    
}

bool FlipCardBonusManager::isGameOver() {
    return _gameOver;
}

void FlipCardBonusManager::setGameOver(bool result) {
    _gameOver = result;
}
void FlipCardBonusManager::reset() {

    static CardTypes tempCardTypes[] = {
        CardCrab,    //螃蟹
        CardShark,   //鲨鱼
        CardTortoise, //乌龟
        CardInkFish,  //乌贼
    };
    
    
    //每种牌型的数量
    static const TUint8 CARDS_NUM_BY_TYPE = 6;
    static const TUint8 CARD_TYPES = 4;

    //生成原始牌型数据
    for (int i = 0; i < CARD_TYPES; i++ ) {
        for (int j = 0; j < CARDS_NUM_BY_TYPE; j++) {
            setCard(i * CARDS_NUM_BY_TYPE + j, tempCardTypes[i] );
            
        }
    }
    
    //加入bonus牌
    setCard(TOTAL_CARDS-1, CardBonus);
    
#ifdef DEBUG_FLIP_CARD
    //生成原始牌型数据
    printf("before shuffle\n");
    
    for (int i = 0; i < 5; i++ ) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", card(i * 5 + j));
        }
        printf("\n");
    }
    
#endif
    
    prevCardType = CardIllegal;
    
    trigger = TriggerIllegal;
    _coins = 0;
    _gameOver = false;
    
}

int FlipCardBonusManager::base() {
    return trigger == ShortageCoins ? SHORTAGE_COINS_FLIP_BONUS : KILL_SEA_HORSE_FLIP_BONUS;
}

void FlipCardBonusManager::flip(TUint8 index ) {
    
    //此牌已经翻过,忽略之
    if (hadFliped(index)) {
        return;
    }
    
    CardTypes type = card(index);
    
    //更新缓存信息
    prevCardType = type;
    setCard(index, CardIllegal);
    
    //加钱
    if (type != CardBonus) {
        _coins += ( trigger == ShortageCoins ? SHORTAGE_COINS_FLIP_BONUS : KILL_SEA_HORSE_FLIP_BONUS );
        
    } else {
        _coins = ( trigger == ShortageCoins ? MAX_SHORTAGE_COINS_FLIP_BONUS : MAX_KILL_SEA_HORSE_FLIP_BONUS);
    }
}

const char* FlipCardBonusManager::cardsImageName(TUint8 index ) {
    
    CardTypes type = card(index);
    
    switch (type) {
            
            //bonus
            case CardBonus:
            {
                return "bonus.png";
            }
            break;
            
            //螃蟹
            case CardCrab:
            {
                return "crab.png";
            }
            break;
            
            //鲨鱼
            case CardShark:
            {
                return "shark.png";
            }
            break;
            
            //乌龟
            case CardTortoise:
            {
                return "tortoise.png";
            }
            break;
            
            //乌贼
            case CardInkFish:
            {
                return "inkfish.png";
            }
            break;
            
        default:

            break;
    }
    return "card_bg.png";  
    
}

