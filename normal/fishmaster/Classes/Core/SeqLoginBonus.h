//
//  LoginBonus.h
//  fish
//
//
//

#ifndef __fish__LoginBonus__
#define __fish__LoginBonus__
#include "Typedef.h"
#include "headerLibrary.h"
#include "GameData.h"

enum BonusStatus {
    StatusLocked,
    StatusUnlocked,
    StatusCanUnlock,
    StatusNum
};

typedef enum enSeqLoginDay{
    LoginDay1,
    LoginDay2,
    LoginDay3,
    LoginDay4,
    LoginDay5,
    LoginDay6,
    LoginDay7,
}SeqLoginDay;

#define MAX_SEQ_LOGIN_DAYS (7)  //最多连续7天登录

//连续登录奖励管理器
class SeqLoginBonusManager  {

public:
    ~SeqLoginBonusManager();
    
    //获得一个共享的连续登录奖励管理器
    static SeqLoginBonusManager* sharedSeqLoginBonusManager();
    
    //上一次启动时间
    TUint32 lastLaunchTime();
    
    //奖励状态
    BonusStatus bonusStatus( TUint8 index );
    
    //开奖
    void open(TUint8 index );
    
    //是否是同一天
    bool isSameDay();
    void setIsSameDay( bool bSameDay = true) {
        _isSameDay = bSameDay;
    }
    //本次打开可获得的金币数
    int coins(int index );

    DiamondType diamond( SeqLoginDay index );
    
private:
    SeqLoginBonusManager();
    
private:

    //将指定bonus状态更新,默认为解锁
    void setBonusStatus(TUint8 index, BonusStatus status = StatusUnlocked);

    //刷新配置
    void refreshSettings();
    
    //加载配置
    void loadSettings();
    
    //是否是上次启动后的,紧挨的新一天
    bool isNeighborshipDay();
    

    
    
private:
    class Cleaner
    {
    public:
        Cleaner(){}
        ~Cleaner()
        {
            if(SeqLoginBonusManager::sharedSeqLoginBonusManager() != NULL) {
                delete SeqLoginBonusManager::sharedSeqLoginBonusManager();
            }
        }
    };
    
    
    
private:
    static SeqLoginBonusManager *sharedManager;
    
    //是否是紧埃的两天
    bool _isNeighborshipDay;
    
    //是否是同一天
    bool _isSameDay;
    
    //是否是每天第一次登录,碰到的第一个可解锁按钮
    bool _isFirstCanUnlock;
    
    TUint8 _seqBonusStatusFlag;
    TUint8 _thisDay;
    
    //本地缓存的前一次启动的时间
    TUint32 _lastLaunchTime;
    
    //本次启动时间
    TUint32 _thisLaunchTime;
};



#endif /* defined(__fish__LoginBonus__) */
