//
//  GameData.h
//  fish
//
//  
//
//

#ifndef __fish__GameData__
#define __fish__GameData__

#include "headerLibrary.h"
#include <iostream>
#include "Fish.h"
#include "SceneSelection.h"
#include "../config/CConfig.h"

#define DEFAULT_MONEY   10000

#define kBoughtResultNotification      ("kBoughtResultNotification")  //购买通知
#define kInitRechargResultNotification ("kInitRechargResultNotification")  //首次充值结果通知
#define kBoughtSceneResultNotification ("kBoughtSceneResultNotification") //购买场景通知

enum GameType
{
    GameType_Normal = 1,
    GameType_SeaMonster_Normal,
    GameType_SeaMonster_Difficulty
};

enum GameRecordType
{
    GameRecordType_Task = 1,
    GameRecordType_Relief,
    GameRecordType_SeaMonster
};

enum CardType{
    Card_Denglongyu = 1,
    Card_Shenxianyu,
    Card_Wuzhe,
    Card_Shiziyu,
    Card_Dabaisha,
    Card_Xiaochouyu,
    Card_LanAli
};

#define GameCardMaxNumber   5
#define GamePowerMaxCount   1

class GameCard : public CCObject
{
public:
    CardType m_type;
    
    int m_count;
    int m_max_count;
    
    int price_red_diamond;
    int price_green_diamond;
    int price_blue_diamond;
    int price_yellow_diamond;
    
    GameCard(CardType pType);
    ~GameCard();
};


enum DiamondType{
    Diamond_Yellow = 1,
    Diamond_Green,
    Diamond_Red,
    Diamond_Blue,
    Diamond_Pearl,      //珍珠
    Diamond_BlackPearl, // 黑珍珠
    Diamond_Diamond     // 钻石
};


class GameDiamond : public CCObject
{
public:
    DiamondType m_type;
    
    int m_price;
    int m_min_price;
    int m_max_price;
    
    int m_cnt;
    
    GameDiamond(DiamondType pType);
    ~GameDiamond();
};


#define GameMaxLevel 99

class GameUserExp : public CCObject
{
public:
    int m_level;
    int m_bonus;
    int m_expForUpgrade;
    bool isUnlockCannon;
    
    char* m_desp;
    
    GameUserExp(int pLevel, int pBonus, int pExp, char* pDesp);
    GameUserExp(int pLevel, int pBonus, int pExp, char* pDesp,bool pUnlockCannon);
    ~GameUserExp();
};

// 游戏任务
class GameTask : public CCObject
{
public:
    unsigned int m_id; // 任务ID
    unsigned int m_progress; // 进度
    unsigned int m_in; // 表示是否正在进行中 0 未 1 进行中
    int m_time; // 任务开始时间
    
    GameTask(int pId, int pProgress, int pIn);
    ~GameTask();
};

typedef struct _GameTimesRecord
{
    int day; // 日期信息  201430 (2014年份 30 这天是2014的第几天)
    int times; // 领取救济的次数 任务完成次数
    vector<int>* ext; // 额外保存的信息
}GameTimesRecord;

#define kInAppPurchaseProductIdCoin2 @"com.corntree.fish.coin2" // 2RMB
#define kInAppPurchaseProductIdCoin6 @"com.corntree.fish.coin6" // 6RMB
#define kInAppPurchaseProductIdCoin10 @"com.corntree.fish.coin10" // 10RMB
#define kInAppPurchaseProductIdCoin18 @"com.corntree.fish.coin18"    //$1.99
#define kInAppPurchaseProductIdCoin40 @"com.corntree.fish.coin40"    //$2.99
#define kInAppPurchaseProductIdCoin78 @"com.corntree.fish.coin78"  //$9.99
#define kInAppPurchaseProductIdCoin128 @"com.corntree.fish.coin128"  //$19.99
#define kInAppPurchaseProductIdCoin388 @"com.corntree.fish.coin388" //$0.99

#define kInAppPurchaseProductIdGift18 @"com.corntree.fish.gift18" //$2.99
#define kInAppPurchaseProductIdGift12 @"com.corntree.fish.gift12" //$1.99
#define kInAppPurchaseProductIdGift25 @"com.corntree.fish.gift25" //$3.99

#define kInAppPurchaseProductIdPearl @"com.corntree.fish.pearls"
#define kInAppPurchaseProductIdHideBullet1000 @"com.corntree.fish.hidebullet1000" // 6RMB
#define kInAppPurchaseProductIdDiamond2 @"com.corntree.fish.diamond2"  // 8RMB
#define kInAppPurchaseProductIdPearlShell @"com.corntree.fish.pearlshell" // 6RMB

enum ProductType{
    
    Product_Coin18 = 1,
    Product_Coin40 ,
    Product_Coin78 ,
    Product_Coin128 ,
    Product_Coin388 ,
    Product_Gift18 ,
    Product_Gift12 ,
    Product_Gift25 ,
    Product_Pearl ,
    
    
    
    Product_Fb_Coin6 , // 新增快速购买6元
    
    
    Product_MysticalScene ,  //神秘海域
    Product_DreamScene ,     //梦幻海域
    Product_ProfusionScene , //缤纷海域
    Product_HistoricScene ,   //古迹海域
    
    Product_Coin2 = 1001,
    Product_Coin6 = 1002,
    Product_Coin10 = 1003,
    Product_HideBullet1000 = 1004,
    Product_Diamond2 = 1005,
    Product_PearlShell = 1006,
    Product_Coin15 = 1007,
    Product_FishKnife = 1008,// 新增旋风鱼刀
    Product_Fb_Coin10 = 1009, // 新增快速购买10元
    
    Product_PowerGift = 1010,    //能量条
    Product_MaxCannonGift = 1011,    //解锁最大炮台
    Product_VIPGift = 1012,  //VIP
    Product_UpGradGift = 1013,   //高手大礼包
    Product_XihaGift   = 1014 , //嘻哈礼包
    Product_GoodSixGift = 1015,    //好6礼包
    
    Product_DragonGift ,   //龙王福利
    Product_MermaidGift,   //美人鱼福利
    ProductID_item6 = -1,//取消(公用)
    
    
};

typedef enum
{
	DT_Shop = 1,
    DT_Game = 2,
}Data_Type;

class GameData{
    
public:
    
    GameData();
    ~GameData();
    
    static GameData* getSharedGameData();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pCards, Cards);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pDiamonds, Diamonds);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pUserExp, UserExps);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pTasks, Tasks);

    void save();
    bool changeScore(int add);

    bool changeHide(int add);
    GameCard* getGameCard(CardType pType);
    GameDiamond* getGameDiamond(DiamondType pType);
    GameTask* getGameTask(unsigned int pTaskId);
    GameTask* getGameTaskIn(); // 获取当前正在进行的任务
    
    bool buyGameCard(CardType pType);
    bool sellGameDiamond(DiamondType pType, uint cnt);
    void addGameDiamond(DiamondType pType, uint cnt);
    
    void saveGameCard(CardType pType);
    void saveGameDiamond(DiamondType pType);
    
    void addGameTask(unsigned int pTaskId);
    void saveGameTask(unsigned int pTaskId, unsigned int pProgress, unsigned int pIn, int pTime);
    void checkAddTask(int pDifficulty); // 检查增加一个任务
    bool getTaskSuit(int pTaskId);
    void updateTaskProgress(TaskType pType, unsigned int pRequireId, unsigned int pAddProgress);
    
//    int getGameReliefInfo(string pDay);
//    void saveGameReliefInfo(string pDay, int pTimes);
    
//    int getGameTaskInfo(string pDay);
//    void saveGameTaskInfo(string pDay, int pTimes);
    
    string genDayStamp();
    void loadGameRecordInfo(map<int, GameTimesRecord*>* pRecords, string pKey);
    GameTimesRecord* getGameRecordInfo(GameRecordType pType, string pDay);
    GameTimesRecord* getGameRecordInfo(map<int, GameTimesRecord*>* pRecords, string pDay);
    void saveGameRecordInfo(GameRecordType pType, string pDay, int pTimes, vector<int>* pExt);
    void saveGameRecordInfo(map<int, GameTimesRecord*>* pRecords, string pKey, string pDay, int pTimes, vector<int>* pExt);
    
    vector<int>* getGameRecordExtInfo(string pExtStr);
    
    GameType getGameType() { return m_gameType; };
    void setGameType(GameType pGameType);
    
    // 获取商品价格（分）
    int getProductPrice(ProductType pType);
    // 获取商品constId
    string getProductConstId(ProductType pType);
    // 获取商品Name
    string getProductName(ProductType pType);
    // 生成订单号
    string genOrderId(ProductType pType, int pToken);
    //支付完成后，提供商品
    void provideProduct(ProductType pType);
    
    //return true if user upgrade
    bool addExp(int pExp);
    
    CCString* getDespForLevel(int pLevel);
    CCString* getNextDespForLevel(int pLevel);
    GameUserExp* getGameUserExpFroLevel(int pLevel);
    
    CCString* getTitleForLevel(int pLevel);
    CCString* getPicForLevel(int pLevel);
    
    void unlockFish(Fish::FishType pIndex);
    void loadlockFish();
    
    void doInitRechargedBonus();
    
    void exitGame();
    
    void setDataPoint(Data_Type dataType, void* pData);
    void* getDataPoint(Data_Type dataType);
    void erasePoint(Data_Type dataType);
//=======================================================
public: //setter && getter
    
    bool isGoldCannon( int index );
    
    int currentLevel() { return m_cur_level; }
    
    GameUserExp* nextLevel() { return m_pNextLevel; }
    
    int score() { return m_score; }
    
    int currentExp() { return m_cur_exp;}
    
    void setCurrentScene(Scene pScene);
    Scene currentScene() { return m_cur_scene; }
    
    int currentPower() { return m_cur_power; }
    void setCurrentPower( int count ) {m_cur_power = count; }
    
    int currentPowerCount() { return m_cur_power_count; }
    bool setCurrentPowerCount(int count);
    
    int doubleTimeExp() { return m_doubleTimeExp; }
    void setDoubleTimeExp(int exp) { m_doubleTimeExp = exp; }
    
    void  setHideBulletCount( int count) { m_hideBulletCnt = count;}
    int hideBulletCount() { return m_hideBulletCnt; }
    
    void setApBulletCount(int count) { m_apBulletCnt = count; }
    int apBulletCount() { return m_apBulletCnt; }
    
    bool addSeaMonsterScore(int addScore);
    int getSeaMonsterScore() { return m_seamonster_score; };
    
    bool setSeaMonsterPower(int newPower);
    int getSeaMonsterPower() { return m_seamonster_power; };
    
    bool setSeaMonsterPowerCount(int newCount);
    int getSeaMonsterPowerCount() { return m_seamonster_power_count; };
    
    bool addSeaMonsterBlood(int addBlood);
    int getSeaMonsterBlood() { return m_seamonster_blood; };
    
    bool addSeaMonsterTime(int addTime);
    int getSeaMonsterTime() { return m_seamonster_time; };

    //首充相关设置
    void setInitRecharged( bool b);
    bool isInitRecharged();
    
    void setBootFromInitRecharge(bool);
    bool isBootFromInitRecharge();

    void setBuyFishKnife(bool b);
    bool isBuyFishKnife();
    
    //add by andy 2015-03-23
    void addUnLockMaxConnon(bool status);
    bool getUnLockMaxConnon() { return _isUnLockMaxConnon; };
    
    void addTodayLoginCount();
    void setTodayLoginCount(int count);
    int getTodayLoginCount() { return _isTodayLoginCount; };
    void addVipCard(bool status);
    bool getIsHaveVipCard() { return _isHaveVipCard; };
    
    void setHitPercentage(int  hitPercentage);
    int  getHitPercentage() { return m_HitPercentage; };
    //add end by andy
    void setChannel(const char * data);
    CCString * getChannel(){return m_channel;};
    void setAPPKey(const char * data);
    CCString * getAPPKey(){return m_appkey;};
private:

    void upgradeUser();
    void initUserExp();
    
    static GameData* m_self;
    static bool _fishLockArray[Fish::FISH_NORMAL_TYPEMAX];
    
    int m_score;
    Scene m_cur_scene;
    int m_cur_level;
    int m_cur_exp;
    int m_cur_power;
    int m_cur_power_count; // 增加保存能量点
    int m_doubleTimeExp;
    int m_hideBulletCnt;
    int m_apBulletCnt;
    
    bool m_isGoldCannon2;
    bool m_isGoldCannon3;
    
    bool _isInitRecharged;
    bool _isBootFromInitRecharge;
    
    //add by andy 2015-03-23
    bool _isUnLockMaxConnon;
    int  _isTodayLoginCount;
    bool _isHaveVipCard;
    //add end by andy
    //add by andy 2015-04-15
    int m_HitPercentage;
    //add end by andy
    
    
    GameUserExp* m_pNextLevel;
    
    map<int, GameTimesRecord*>* m_mTaskRecord;
    map<int, GameTimesRecord*>* m_mReliefRecord;
    map<int, GameTimesRecord*>* m_mSeaMonsterRecord;
    
    GameType m_gameType;
    int     m_seamonster_score; // 海怪模式使用的金币
    int     m_seamonster_power; // 海怪模式使用的能量
    int     m_seamonster_power_count; // 海怪模式使用的能量数量
    int     m_seamonster_blood; // 海怪模式使用的血量
    int     m_seamonster_time; // 海怪模式使用的时间
    
    map<Data_Type, void*>    m_mapPoint;
    CCString* m_channel;
    CCString* m_appkey;
};


#endif /* defined(__fish__GameData__) */
