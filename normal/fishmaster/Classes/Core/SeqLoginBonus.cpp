//
//  LoginBonus.cpp
//  fish
//
//
//

#include "SeqLoginBonus.h"
#include "GameData.h"

#define LAST_LAUNCH_TIME_STR      ("lastLaunchTimeStr")
#define SEQ_LOGIN_FLAG_STR        ("seqLoginFlagStr")
#define SEQ_BONUS_STATUS_FLAG_STR ("seqBonusStatusFlagStr")

SeqLoginBonusManager* SeqLoginBonusManager::sharedManager = NULL;

SeqLoginBonusManager* SeqLoginBonusManager::sharedSeqLoginBonusManager()
{
    if (sharedManager == NULL) {
        
        sharedManager = new SeqLoginBonusManager();
        static Cleaner cleaner;
        
        //取得前一次的启动时间
        sharedManager->loadSettings();
        
        //缓存本次启动时间
        sharedManager->refreshSettings();
        srand(time(NULL));
        
    }
    return sharedManager;
    
}

SeqLoginBonusManager::SeqLoginBonusManager(){
    _isFirstCanUnlock = true;
    _thisDay = 0;
    
}
SeqLoginBonusManager::~SeqLoginBonusManager(){}


//从本地缓存中,读出缓存数据
void SeqLoginBonusManager::loadSettings() {
    
    _lastLaunchTime = CCUserDefault::sharedUserDefault()->getIntegerForKey(LAST_LAUNCH_TIME_STR, 0);
    _seqBonusStatusFlag = CCUserDefault::sharedUserDefault()->getIntegerForKey(SEQ_BONUS_STATUS_FLAG_STR, 0);
    
    //本次调用时间
    time_t tx = time( NULL);
    struct tm* thisTime = localtime(&tx);
    int thisDay = thisTime->tm_mday;
    
    //记录缓存的前一次启动时间
    time_t tempTime = _lastLaunchTime;
    struct tm* lastTime = localtime(&tempTime);
    int lastDay = lastTime->tm_mday;
    
    switch (thisDay - lastDay) {
        case 1:    //本月非第一天之外的任何一天
        case 1-28: //非闰年的2,3月交替
        case 1-29: //闰年的2,3月交替
        case 1-31: //前一月是:1,3,5,7,8,10,12
        case 1-30: //前一月是4，6，9，11
            _isNeighborshipDay = true;
            break;
            
        default:
            _isNeighborshipDay =   false;
    }
    

    _thisLaunchTime = tx;
    
    _isSameDay = ( lastDay == thisDay ? true : false);
    
    //对第一次启动做特殊处理
    if (_lastLaunchTime == 0) {
        _isNeighborshipDay = true;
    }
}


void SeqLoginBonusManager::refreshSettings() {
    
    //更新启动时间
    CCUserDefault::sharedUserDefault()->setIntegerForKey(LAST_LAUNCH_TIME_STR, _thisLaunchTime);
    
    //1.不是同一天且不是紧挨着的两天,即有间断
    //2.连续登录7天
    //  统计状态复位
    if((!_isNeighborshipDay && !_isSameDay) ||((_seqBonusStatusFlag & 0x7F) == 0x7F)) {
        _seqBonusStatusFlag = 0x00;  //默认为全部解锁
        CCUserDefault::sharedUserDefault()->setIntegerForKey(SEQ_BONUS_STATUS_FLAG_STR, _seqBonusStatusFlag);
        CCUserDefault::sharedUserDefault()->flush();
    }
    

}


//是否是新的一天
bool SeqLoginBonusManager::isNeighborshipDay() {
    
    return  _isNeighborshipDay;
}

bool SeqLoginBonusManager::isSameDay(){
    return _isSameDay;
}

BonusStatus SeqLoginBonusManager::bonusStatus( TUint8 index ) {
    if (index < 0 ||index >= 7) {
        return StatusLocked;
    }

    
    BonusStatus status =  BonusStatus((_seqBonusStatusFlag >> index) & 1);

    //如果已经解锁,或者是当天的非第一次登录,直接返回
    if (StatusUnlocked == status || isSameDay() ) {
        return status;
    }
    

    //当天第一次登录,且是第一个非解锁箱子
    if (_isFirstCanUnlock) {
        _isFirstCanUnlock = !_isFirstCanUnlock;
        _thisDay = index;
        
        
    }
    
    //如果是当前可解锁箱子
    if (_thisDay == index) {
        return StatusCanUnlock;
        
    } else {
        return StatusLocked;
    }
    

}

void SeqLoginBonusManager::setBonusStatus(TUint8 index, BonusStatus status){
    if (index < 0 || index >= MAX_SEQ_LOGIN_DAYS ) {
        return;
    }
    
    _seqBonusStatusFlag |= ( 1 << index);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(SEQ_BONUS_STATUS_FLAG_STR, _seqBonusStatusFlag);
    CCUserDefault::sharedUserDefault()->flush();
    
}


int SeqLoginBonusManager::coins(int index) {
    if (index < 0 || index > 5) {
        return 0;
    }
    
    TInt32 coins = 0;
    
    switch (index) {
        case LoginDay1:
            coins = 5000;
            break;
            
        case LoginDay2:
            coins = 8000;
            break;
            
        case LoginDay3:
            coins = 12000;
            break;
            
        case LoginDay4:
            coins = 20000;
            break;
            
        case LoginDay5:
            coins = 30000;
            break;
    }
    
    return coins;

}

DiamondType SeqLoginBonusManager::diamond(SeqLoginDay day) {
    if (day == LoginDay7 ) {
        return Diamond_Pearl;
        
    }
    
    return DiamondType (rand() % 4 + 1);

}

void SeqLoginBonusManager::open(TUint8 index ) {
    if( index < 0 || index >= MAX_SEQ_LOGIN_DAYS ) {
        return;
    }
    
    //修改状态
    setBonusStatus(index);
    
//    //奖励金币 修改到调用层增加物品
//    if (index < 5) {
//        GameData::getSharedGameData()->changeScore( coins(index) );
//    
//    //奖励宝石
//    } else {
//        GameData::getSharedGameData()->addGameDiamond(diamond((SeqLoginDay)index), 1);
//    }
    
}


