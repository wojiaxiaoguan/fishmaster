//
//  GameData.cpp
//  fish
//
//  
//
//

#include "GameData.h"
#include "Fish.h"
#include "SceneSelection.h"
//#include "../thirdparty/ThirdPartyFactory.h"
#include "../Ui/GameLayer.h"
#ifdef USING_UMENG
#include "MobClickCpp.h"
#endif
GameCard::GameCard(CardType pType):
m_type(pType)
{
    m_count = 0;
    m_max_count = 5;
    price_red_diamond = 0;
    price_green_diamond = 0;
    price_blue_diamond = 0;
    price_yellow_diamond = 0;
    
    switch (pType) {
            case Card_Denglongyu:
            price_red_diamond = 3;
            price_green_diamond = 3;
            price_blue_diamond = 3;
            price_yellow_diamond = 3;
            break;
            
            case Card_Shenxianyu:
            price_red_diamond = 2;
            price_green_diamond = 2;
            price_blue_diamond = 2;
            price_yellow_diamond = 2;
            break;
            
            case Card_Wuzhe:
            price_yellow_diamond = 2;
            price_green_diamond = 1;
            price_blue_diamond = 3;
            break;
            
            case Card_Shiziyu:
            price_red_diamond = 3;
            price_blue_diamond = 2;
            price_yellow_diamond = 1;
            break;
            
            case Card_Dabaisha:
            price_red_diamond = 3;
            price_green_diamond =3;
            price_blue_diamond = 3;
            price_yellow_diamond = 3;
            break;
            
            case Card_Xiaochouyu:
            price_yellow_diamond = 3;
            price_red_diamond = 1;
            price_green_diamond = 2;
            break;
            
            case Card_LanAli:
            price_blue_diamond = 1;
            price_red_diamond = 2;
            price_green_diamond = 3;
            break;
        default:
            break;
    }
}

GameCard::~GameCard()
{
    
}




GameDiamond::GameDiamond(DiamondType pType):
m_type(pType)
{
    m_cnt = 0;
    
    switch (pType) {
            case Diamond_Green:
            m_min_price = 5000;
            m_max_price = 5000;
            break;
            
            case Diamond_Yellow:
            m_min_price = 5000;
            m_max_price = 5000;
            break;
            

            case Diamond_Blue:
            m_min_price = 5000;
            m_max_price = 5000;
            break;
            

            case Diamond_Red:
            m_min_price = 5000;
            m_max_price = 5000;
            break;
            

            case Diamond_Pearl:
            m_min_price = 7000;
            m_max_price = 7000;
            break;
            
            case Diamond_BlackPearl:
            m_min_price = 30000;
            m_max_price = 30000;
            break;
            
            case Diamond_Diamond:
            m_min_price = 30000;
            m_max_price = 30000;
            break;

        default:
            break;
    }
    int gap = 0;
    if (m_max_price > m_min_price) {
        gap = arc4random() % (m_max_price - m_min_price + 1);
    }
    m_price = m_min_price + gap;
}


GameDiamond::~GameDiamond()
{
    
}


GameTask::GameTask(int pId, int pProgress, int pIn)
{
    m_id = pId;
    m_progress = pProgress;
    m_in = pIn;
    m_time = CConfig::secondNow();
}

GameTask::~GameTask()
{
    
}

////////////////////////////////////////////////////


GameUserExp::GameUserExp(int pLevel, int pBonus, int pExp, char* pDesp):
m_level(pLevel),
m_bonus(pBonus),
m_expForUpgrade(pExp),
m_desp(NULL)
{
    isUnlockCannon = false;
    if (pDesp != NULL) {
        m_desp = pDesp;
    }
}
GameUserExp::GameUserExp(int pLevel, int pBonus, int pExp, char* pDesp,bool pUnlockCannon):
m_level(pLevel),
m_bonus(pBonus),
m_expForUpgrade(pExp),
isUnlockCannon(pUnlockCannon),
m_desp(NULL)
{
    if (pDesp != NULL) {
        m_desp = pDesp;
    }
}



GameUserExp::~GameUserExp()
{
    
}


//////////////////////////////////////////////////////////
bool GameData::_fishLockArray[Fish::FISH_NORMAL_TYPEMAX] = {
    false, //FISH_XIAOGUANGYU,
    false, //    FISH_XIAOCAOYU,
    false, //    FISH_REDAIYU,
    false, //    FISH_DAYANJINYU,
    false, //    FISH_SHUIMU,
    false, //    FISH_SHANWEIYU,
    false, //    FISH_REDAIZIYU,
    false, //    FISH_XIAOCHOUYU,
    false, //    FISH_HETUN,
    false, //    FISH_WUZEI,
    false, //    FISH_SHITOUYU,
    false, //    FISH_SHENXIANYU,
    false, //    FISH_WUGUI,
    false, //    FISH_DENGLONGYU,
    false, //    FISH_SHIBANYU,
    false, //    FISH_HUDIEYU,
    false, //    FISH_LINGDANGYU,
    false, //    FISH_JIANYU,
    false, //    FISH_MOGUIYU,
    true, //    FISH_FEIYU,
    true, //    FISH_LONGXIA,
    true, //    FISH_HAITUN,
    true, //    FISH_DAYINSHA,
    true, //    FISH_LANJING,
//    true, //    FISH_HUANGJINGJINGYU,
//    true, //    FISH_HUANGJINGYU,
//    true, //    FISH_BYMOGUIYU,
//    true, //    FISH_BYWUGUI,
    true, //    FISH_ZHENZHUBEI,
//    true, //    FISH_LANSHA,
    true, //    FISH_XIAOFEIYU,
    true, //    FISH_ALILAN,
//    false, //    FISH_HAIMA,
    true, //    FISH_ZHADANFISH,
    //    FISH_NORMAL_TYPEMAX
};


GameData::GameData():
m_pCards(NULL),
m_pDiamonds(NULL),
m_pUserExp(NULL),
m_pTasks(NULL),
m_pNextLevel(NULL)
{
    m_channel = NULL;
    m_mTaskRecord = new map<int, GameTimesRecord*>();
    m_mReliefRecord = new map<int, GameTimesRecord*>();
    m_mSeaMonsterRecord = new map<int, GameTimesRecord*>();
    
    m_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_score", -1);
    
    if (m_score < 0) {
        m_score = DEFAULT_MONEY;
    }
    
    m_cur_scene = (Scene)CCUserDefault::sharedUserDefault()->getIntegerForKey("m_cur_scene", 0);

    
    m_cur_level = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_cur_level", -1);
    
    if (m_cur_level < 0) {
        m_cur_level = 1;
    }
    
    m_cur_exp = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_cur_exp", -1);
    
    if (m_cur_exp < 0) {
        m_cur_exp = 0;
    }
    
    m_cur_power = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_cur_power", 1980);
    
    if (m_cur_power < 0) {
        m_cur_power = 0;
    }
    
    m_cur_power_count = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_cur_power_count", -1);
    
    if (m_cur_power_count < 0){
        m_cur_power_count = 0;
    }
    
    m_doubleTimeExp = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_doubleTimeExp", -1);
    
    if (m_doubleTimeExp < 0) {
        m_doubleTimeExp = 0;
    }
    
    m_hideBulletCnt = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_hideBulletCnt", -1);
    DF_LOG("*****m_hideBulletCnt = %d",m_hideBulletCnt);
    if (m_hideBulletCnt < 0) {
        m_hideBulletCnt = 0;
    }
    
    m_apBulletCnt = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_apBulletCnt", -1);
    
    if (m_apBulletCnt < 0){
        m_apBulletCnt = 0;
    }
    
    m_isGoldCannon2 = CCUserDefault::sharedUserDefault()->getBoolForKey("m_isGoldCannon2", false);
    m_isGoldCannon3 = CCUserDefault::sharedUserDefault()->getBoolForKey("m_isGoldCannon3", false);
    
    
    _isUnLockMaxConnon = CCUserDefault::sharedUserDefault()->getBoolForKey("m_isUnLockMaxConnon",false);
    _isTodayLoginCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_isTodayLoginCount", 1);
    _isHaveVipCard = CCUserDefault::sharedUserDefault()->getBoolForKey("m_isHaveVipCard",false);
    m_HitPercentage = CCUserDefault::sharedUserDefault()->getIntegerForKey("m_HitPercentage",0);
    
    this->setCards(CCArray::create());
    this->setDiamonds(CCArray::create());
    this->setUserExps(CCArray::create());
    this->setTasks(CCArray::create());
    
    /*init game card*/
    for (int i = Card_Denglongyu ; i <= Card_LanAli; i++) {
        GameCard* pCard = new GameCard((CardType)i);
        CCString* keyName = CCString::createWithFormat("card%d",i);
        int cnt = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName->getCString(), -1);
        if (cnt > 0) {
            pCard->m_count = cnt;
        }
        m_pCards->addObject(pCard);
    }
    
    /*init game diamond*/
    for (int i = Diamond_Yellow ; i <= Diamond_Diamond; i++) {
        GameDiamond* pDiamond = new GameDiamond((DiamondType)i);
        CCString* keyName = CCString::createWithFormat("diamond%d",i);
        int cnt = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName->getCString(), -1);
//        cnt = 19;
        if (cnt > 0) {
            pDiamond->m_cnt = cnt;
        }
        m_pDiamonds->addObject(pDiamond);
    }
    
    /* init game task */
    for (int i = 1; i <= CConfig::sharedConfig()->getTaskSize(); i++)
    {
        GameTask* pTask = new GameTask(i, 0, 0);
        CCString* keyName = CCString::createWithFormat("taskprogress%d", i);
        int pProgress = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName->getCString(), 0);
        if (pProgress > 0)
        {
            pTask->m_progress = pProgress;
        }
        keyName = CCString::createWithFormat("taskin%d", i);
        int pIn = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName->getCString(), 0);
        if (pIn > 0)
        {
            pTask->m_in = pIn;
        }
        keyName = CCString::createWithFormat("tasktime%d", i);
        int pTime = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName->getCString(), 0);
        if (pTime > 0)
        {
            pTask->m_time = pTime;
        }
        m_pTasks->addObject(pTask);
    }
    /* init game task record */
    loadGameRecordInfo(m_mTaskRecord, "task");
    /* init game relief record */
    loadGameRecordInfo(m_mReliefRecord, "relief");
    /* init game sea monster record*/
    loadGameRecordInfo(m_mSeaMonsterRecord, "seamonster");
    m_gameType = GameType_Normal;
    m_seamonster_blood = 0;
    m_seamonster_score = 0;
    m_seamonster_power = 0;
    m_seamonster_power_count = 0;
    m_seamonster_time = 0;
    
    initUserExp();
    
    if (m_cur_level < GameMaxLevel) {
        m_pNextLevel = (GameUserExp*)m_pUserExp->objectAtIndex(m_cur_level + 1);
    }
    
    //init fish lock
    loadlockFish();
    for (int i = 0; i < Fish::FISH_NORMAL_TYPEMAX; i++) {
        Fish::lockFish((Fish::FishType)i, _fishLockArray[i]);
    }
}

void GameData::loadlockFish()
{
    bool isInit = true;
    for (int i = 0; i < Fish::FISH_NORMAL_TYPEMAX; i++) {
        CCString* str = CCString::createWithFormat("m_fish_lock_%d",i);
        int islock = CCUserDefault::sharedUserDefault()->getIntegerForKey(str->getCString(), -1);
        
        if (islock < 0) {
            isInit = false;
            break;
        } else if (islock == 0){
            _fishLockArray[i] = false; //unlock
        } else {
            _fishLockArray[i] = true; //lock
        }
    }
    if (isInit == false) {
        for (int i = 0; i < Fish::FISH_NORMAL_TYPEMAX; i++) {
            CCString* str = CCString::createWithFormat("m_fish_lock_%d",i);
            
            int value = 0; // unlock
            if (_fishLockArray[i]) {
                value = 1; //lock
            }
            CCUserDefault::sharedUserDefault()->setIntegerForKey(str->getCString(), value);
        }
        CCUserDefault::sharedUserDefault()->flush();
    }
}



void GameData::unlockFish(Fish::FishType pIndex)
{
    CCString* str = CCString::createWithFormat("m_fish_lock_%d",pIndex);
    _fishLockArray[pIndex] = false;
   // DF_LOG("unlockFish(%s)",str->getCString());
    CCUserDefault::sharedUserDefault()->setIntegerForKey(str->getCString(), 0);
    CCUserDefault::sharedUserDefault()->flush();
    Fish::lockFish(pIndex, false);
}

void GameData::initUserExp()
{
    GameUserExp* exp = new GameUserExp(1,0,0,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(2,1000,35000,"400炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(3,1500,45000,"大飞鱼");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(4,2000,55000,"500炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(5,2500,65000,"600炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(6,3000,75000,"700炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(7,3500,85000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(8,4000,95000,"800炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(9,4500,105000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(10,5000,115000,"好运鱼圈");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(11,6000,140000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(12,7000,160000,"海豚");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(13,8000,180000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(14,9000,200000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(15,10000,220000,"900炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(16,11000,225000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(17,12000,250000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(18,13000,275000,"定时炸弹");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(19,14000,305000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(20,15000,355000,"1000炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(21,16500,410000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(22,17500,470000,"美人鱼");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(23,19000,535000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(24,20500,605000,"1100炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(25,23000,680000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(26,24500,760000,"双髻鲨");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(27,26000,845000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(28,27500,935000,"1200炮",true);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(29,30000,1025000,NULL);
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(30,33000,1120000,"金龙王");
    m_pUserExp->addObject(exp);
    
    exp = new GameUserExp(31,35000,1325000,NULL);
    m_pUserExp->addObject(exp);
    
    for (int i = 32; i <= GameMaxLevel; i++) {
        int bonus = 0;
        if (i < 40)
        {
            bonus = exp->m_bonus + 2500;
        }
        else if (i < 50)
        {
            bonus = exp->m_bonus + 3000;
        }
        else if (i < 60)
        {
            bonus = exp->m_bonus + 3500;
        }
        else if (i < 70)
        {
            bonus = exp->m_bonus + 4000;
        }
        else if (i < 80)
        {
            bonus = exp->m_bonus + 4500;
        }
        else if (i < 90)
        {
            bonus = exp->m_bonus + 5000;
        }
        else if(i < 100)
        {
            bonus = exp->m_bonus + 5500;
        }
        int expFU = exp->m_expForUpgrade * 1.2;
        exp = new GameUserExp(i,bonus,expFU,NULL);
        m_pUserExp->addObject(exp);
    }
}

GameData::~GameData()
{
    CC_SAFE_RELEASE(m_pCards);
    CC_SAFE_RELEASE(m_pDiamonds);
    CC_SAFE_RELEASE(m_pTasks);
}

void GameData::addGameDiamond(DiamondType pType, uint cnt)
{
    GameDiamond* dia = getGameDiamond(pType);
    dia->m_cnt += cnt;
    saveGameDiamond(dia->m_type);
}

void GameData::addGameTask(unsigned int pTaskId)
{
    saveGameTask(pTaskId, 0, 1, CConfig::secondNow());
}

bool GameData::sellGameDiamond(DiamondType pType, uint cnt)
{
    GameDiamond* dia = getGameDiamond(pType);
    if (dia->m_cnt < cnt) {
        return false;
    }
    dia->m_cnt -= cnt;
    uint total_money = dia->m_price * cnt;
    changeScore(total_money);
    saveGameDiamond(dia->m_type);
    return true;
}


bool GameData::buyGameCard(CardType pType)
{
    GameCard* pCard = getGameCard(pType);
    
    
    if (pCard->m_count >= GameCardMaxNumber) {
        return false;
    }
    
    if (getGameDiamond(Diamond_Red)->m_cnt >= pCard->price_red_diamond
        && getGameDiamond(Diamond_Yellow)->m_cnt >= pCard->price_yellow_diamond
        && getGameDiamond(Diamond_Blue)->m_cnt >= pCard->price_blue_diamond
        && getGameDiamond(Diamond_Green)->m_cnt >= pCard->price_green_diamond)
    {
        getGameDiamond(Diamond_Red)->m_cnt -= pCard->price_red_diamond;
        saveGameDiamond(Diamond_Red);
        getGameDiamond(Diamond_Yellow)->m_cnt -= pCard->price_yellow_diamond;
        saveGameDiamond(Diamond_Yellow);
        getGameDiamond(Diamond_Blue)->m_cnt -= pCard->price_blue_diamond;
        saveGameDiamond(Diamond_Blue);
        getGameDiamond(Diamond_Green)->m_cnt -= pCard->price_green_diamond;
        saveGameDiamond(Diamond_Green);
        
        pCard->m_count++;
        saveGameCard(pCard->m_type);
        return true;
    }
    
    int lack_red = pCard->price_red_diamond - getGameDiamond(Diamond_Red)->m_cnt;
    lack_red = lack_red > 0 ? lack_red : 0;
    
    int lack_yellow = pCard->price_yellow_diamond - getGameDiamond(Diamond_Yellow)->m_cnt;
    lack_yellow = lack_yellow > 0 ? lack_yellow : 0;
    
    int lack_blue = pCard->price_blue_diamond - getGameDiamond(Diamond_Blue)->m_cnt;
    lack_blue = lack_blue > 0 ? lack_blue : 0;
    
    int lack_green = pCard->price_green_diamond - getGameDiamond(Diamond_Green)->m_cnt;
    lack_green = lack_green > 0 ? lack_green : 0;
    
    if (getGameDiamond(Diamond_Pearl)->m_cnt >= (lack_red + lack_green + lack_blue + lack_yellow)) {
        if (lack_red > 0) {
            getGameDiamond(Diamond_Red)->m_cnt = 0;
            getGameDiamond(Diamond_Pearl)->m_cnt -= lack_red;
        } else {
            getGameDiamond(Diamond_Red)->m_cnt -= pCard->price_red_diamond;
        }
        saveGameDiamond(Diamond_Red);
        if (lack_green > 0) {
            getGameDiamond(Diamond_Green)->m_cnt = 0;
            getGameDiamond(Diamond_Pearl)->m_cnt -= lack_green;
        } else {
            getGameDiamond(Diamond_Green)->m_cnt -= pCard->price_green_diamond;
        }
        saveGameDiamond(Diamond_Green);
        if (lack_blue > 0) {
            getGameDiamond(Diamond_Blue)->m_cnt = 0;
            getGameDiamond(Diamond_Pearl)->m_cnt -= lack_blue;
        } else {
            getGameDiamond(Diamond_Blue)->m_cnt -= pCard->price_blue_diamond;
        }
        saveGameDiamond(Diamond_Blue);
        if (lack_yellow > 0) {
            getGameDiamond(Diamond_Yellow)->m_cnt = 0;
            getGameDiamond(Diamond_Pearl)->m_cnt -= lack_yellow;
        } else {
            getGameDiamond(Diamond_Yellow)->m_cnt -= pCard->price_yellow_diamond;
        }
        saveGameDiamond(Diamond_Yellow);
        saveGameDiamond(Diamond_Pearl);
        pCard->m_count++;
        saveGameCard(pCard->m_type);
        return true;
    }
    return false;
}


GameCard* GameData::getGameCard(CardType pType)
{
    GameCard* res = (GameCard*)m_pCards->objectAtIndex(pType - 1);
    return res;
}

GameDiamond* GameData::getGameDiamond(DiamondType pType)
{
    GameDiamond* res = (GameDiamond*)m_pDiamonds->objectAtIndex(pType - 1);
    return res;

}

GameTask* GameData::getGameTask(unsigned int pTaskId)
{
    GameTask* res = (GameTask*)m_pTasks->objectAtIndex(pTaskId - 1);
    return res;
}

GameTask* GameData::getGameTaskIn()
{
    // TODO 需要增加日期和时间判断
    for (int i = 1; i <= CConfig::sharedConfig()->getTaskSize(); i++)
    {
        GameTask* pTemp = getGameTask(i);
        if (pTemp && pTemp->m_in)
        {
            return pTemp;
        }
    }
    return NULL;
}

void GameData::saveGameCard(CardType pType)
{
    CCString* keyName = CCString::createWithFormat("card%d",pType);
    GameCard* pCard = getGameCard(pType);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName->getCString(), pCard->m_count);
    CCUserDefault::sharedUserDefault()->flush();
}

void GameData::saveGameDiamond(DiamondType pType)
{
    CCString* keyName = CCString::createWithFormat("diamond%d",pType);
    GameDiamond* pDiamond = getGameDiamond(pType);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName->getCString(), pDiamond->m_cnt);
    CCUserDefault::sharedUserDefault()->flush();
}

void GameData::saveGameTask(unsigned int pTaskId, unsigned int pProgress, unsigned int pIn, int pTime)
{
    GameTask* task = getGameTask(pTaskId);
    if (task)
    {
        task->m_progress = pProgress;
        task->m_in = pIn;
        task->m_time = pTime;
        
        CCString* keyName = CCString::createWithFormat("taskprogress%d", pTaskId);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName->getCString(), task->m_progress);
        keyName = CCString::createWithFormat("taskin%d", pTaskId);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName->getCString(), task->m_in);
        keyName = CCString::createWithFormat("tasktime%d", pTaskId);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName->getCString(), task->m_time);
        CCUserDefault::sharedUserDefault()->flush();
    }
}

void GameData::checkAddTask(int pDifficulty)
{
    // 根据每日任务完成情况获取可用的任务
    for (int i = 1; i <= CConfig::sharedConfig()->getTaskSize(); i++)
    {
        GameTask* pTemp = getGameTask(i);
        if (pTemp->m_in)
        {
            return;
        }
    }
    // 检查每日任务是否达到上限
    GameTimesRecord* pRecord = getGameRecordInfo(GameRecordType_Task, genDayStamp());
    int pRecordTimes = 0;
    if (!pRecord || pRecord->times < 30000)
    {
        // 根据规则随机 1. 每个难度每天一次 2. 任务等级符合玩家信息
        int pId = 0;
        if (pRecord)
        {
            pRecordTimes = pRecord->times;
            CCLog("当日任务次数%d", pRecordTimes);
            if (pDifficulty != 0)
            {
                // 指定难度
                pId = CConfig::sharedConfig()->getRandomTask(pDifficulty, GameData::getSharedGameData()->currentLevel());
                CCLog("刷新任务 难度=%d  ID=%d", pDifficulty, pId);
            }
            else
            {
                // 查找难度
                for (int i = 0; i < pRecord->ext->size(); i++)
                {
                    if (pRecord->ext->at(i) <= 0)
                    {
                        pId = CConfig::sharedConfig()->getRandomTask(i + 1, GameData::getSharedGameData()->currentLevel());
                        CCLog("刷新任务 难度=%d  ID=%d", i + 1, pId);
                        break;
                    }
                }
            }
        }
        else
        {
            pRecordTimes = 0;
            CCLog("当日任务次数%d", pRecordTimes);
            // 无记录刷新任务 难度 1
            if (pDifficulty != 0)
            {
                pId = CConfig::sharedConfig()->getRandomTask(pDifficulty, GameData::getSharedGameData()->currentLevel());
                CCLog("刷新任务 难度=%d  ID=%d  (无记录)", pDifficulty, pId);
            }
            else
            {
                pId = CConfig::sharedConfig()->getRandomTask(1, GameData::getSharedGameData()->currentLevel());
                CCLog("刷新任务 难度=%d  ID=%d  (无记录)", 1, pId);
            }
        }
        // 找到任务
        const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(pId);
        if (!pTaskCfg)
        {
            CCLog("任务数据有误 ID=%d！ TaskCfg Not Found!", pId);
            return;
        }
        addGameTask(pId);
        vector<int>* pExt = NULL;
        if (pRecord)
        {
            pExt = pRecord->ext;
        }
        if (!pExt)
        {
            pExt = new vector<int>();
            pExt->push_back(0);
            pExt->push_back(0);
            pExt->push_back(0);
        }
        pExt->at(pTaskCfg->difficulty - 1) += 1;
        saveGameRecordInfo(GameRecordType_Task, genDayStamp(),  pRecordTimes + 1, pExt);
    }
}

bool GameData::getTaskSuit(int pTaskId)
{
    const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(pTaskId);
    if (!pTaskCfg)
    {
        return false;
    }
    if (GameData::getSharedGameData()->currentLevel() < pTaskCfg->level)
    {
        return false;
    }
    return true;
}

void GameData::updateTaskProgress(TaskType pType, unsigned int pRequireId, unsigned int pAddProgress)
{
    for (int i = 1; i <= CConfig::sharedConfig()->getTaskSize(); i++)
    {
        GameTask* pTemp = getGameTask(i);
        const TaskCfg* pTaskCfg = CConfig::sharedConfig()->getTask(pTemp->m_id);
        if (pTemp && pTemp->m_in && pTaskCfg)
        {
            int pHave = false;
            if (pTaskCfg->type == pType)
            {
                for (int j = 0; j < pTaskCfg->require.size(); j++)
                {
                    if (pTaskCfg->require.at(j)->id == pRequireId)
                    {
                        pHave = true;
                    }
                }
                if (pHave)
                {
                    pTemp->m_progress += pAddProgress;
                    saveGameTask(pTemp->m_id, pTemp->m_progress, pTemp->m_in, pTemp->m_time);
                    return;
                }
            }
        }
    }
}

//int GameData::getGameReliefInfo(string pDay)
//{
//    map<int, GameTimesRecord*>::iterator it = m_mReliefRecord->find(atoi(pDay.c_str()));
//    if (it != m_mReliefRecord->end())
//    {
//        return it->second->times;
//    }
//    return 0;
//}

//void GameData::saveGameReliefInfo(string pDay, int pTimes)
//{
//    map<int, GameTimesRecord*>::iterator it = m_mReliefRecord->find(atoi(pDay.c_str()));
//    if (it != m_mReliefRecord->end())
//    {
//        it->second->times = pTimes;
//    }
//    else
//    {
//        GameTimesRecord* pTemp = new GameTimesRecord();
//        pTemp->day = atoi(pDay.c_str());
//        pTemp->times = pTimes;
//        m_mReliefRecord->insert(pair<int, GameTimesRecord*>(pTemp->day, pTemp));
//    }
//    //save
//    string pRecord = "";
//    char achTemp[32] = {0};
//    memset(achTemp, 0, sizeof(achTemp));
//    for (it = m_mReliefRecord->begin(); it != m_mReliefRecord->end(); ++it)
//    {
//        sprintf(achTemp, "%d", it->second->day);
//        pRecord.append(achTemp);
//        pRecord.append(CConfig::DELIMIT_COLON);
//        sprintf(achTemp, "%d", it->second->times);
//        pRecord.append(achTemp);
//        pRecord.append(CConfig::DELIMIT_VERTICAL);
//    }
//    CCUserDefault::sharedUserDefault()->setStringForKey("relief", pRecord);
//    CCUserDefault::sharedUserDefault()->flush();
//}

//int GameData::getGameTaskInfo(string pDay)
//{
//    map<int, GameTimesRecord*>::iterator it = m_mTaskRecord->find(atoi(pDay.c_str()));
//    if (it != m_mTaskRecord->end())
//    {
//        return it->second->times;
//    }
//    return 0;
//}

//void GameData::saveGameTaskInfo(string pDay, int pTimes)
//{
//    map<int, GameTimesRecord*>::iterator it = m_mTaskRecord->find(atoi(pDay.c_str()));
//    if (it != m_mTaskRecord->end())
//    {
//        it->second->times = pTimes;
//    }
//    else
//    {
//        GameTimesRecord* pTemp = new GameTimesRecord();
//        pTemp->day = atoi(pDay.c_str());
//        pTemp->times = pTimes;
//        m_mTaskRecord->insert(pair<int, GameTimesRecord*>(pTemp->day, pTemp));
//    }
//    //save
//    string pRecord = "";
//    char achTemp[32] = {0};
//    memset(achTemp, 0, sizeof(achTemp));
//    for (it = m_mTaskRecord->begin(); it != m_mTaskRecord->end(); ++it)
//    {
//        sprintf(achTemp, "%d", it->second->day);
//        pRecord.append(achTemp);
//        pRecord.append(CConfig::DELIMIT_COLON);
//        sprintf(achTemp, "%d", it->second->times);
//        pRecord.append(achTemp);
//        pRecord.append(CConfig::DELIMIT_VERTICAL);
//    }
//    CCUserDefault::sharedUserDefault()->setStringForKey("task", pRecord);
//    CCUserDefault::sharedUserDefault()->flush();
//}

string GameData::genDayStamp()
{
    time_t tt;
    time(&tt);
    struct tm *p;
    p = localtime(&tt);
    char achTemp[32] = {0};
    memset(achTemp, 0, sizeof(achTemp));
    sprintf(achTemp, "%d%d", p->tm_year, p->tm_yday);
    return achTemp;
}

void GameData::loadGameRecordInfo(map<int, GameTimesRecord *> *pRecords, string pKey)
{
    string pRecordStr = CCUserDefault::sharedUserDefault()->getStringForKey(pKey.c_str(), "");
    if (strcmp(pRecordStr.c_str(), "") != 0)
    {
        vector<string>* pRecord = CConfig::sharedConfig()->splitString(pRecordStr.c_str(), CConfig::DELIMIT_VERTICAL);
        for (int i = 0; i < pRecord->size(); i++)
        {
            vector<string>* pDay = CConfig::sharedConfig()->splitString(pRecord->at(i), CConfig::DELIMIT_COLON);
            if (pDay->size() >= 3)
            {
                GameTimesRecord* pTemp = new GameTimesRecord();
                pTemp->day = atoi(pDay->at(0).c_str());
                pTemp->times = atoi(pDay->at(1).c_str());
                pTemp->ext = getGameRecordExtInfo(pDay->at(2));
                pRecords->insert(pair<int, GameTimesRecord*>(pTemp->day, pTemp));
            }
        }
    }
}

GameTimesRecord* GameData::getGameRecordInfo(GameRecordType pType, string pDay)
{
    GameTimesRecord* pRecord = NULL;
    switch (pType)
    {
        case GameRecordType_Task:
            pRecord = getGameRecordInfo(m_mTaskRecord, pDay);
            break;
        case GameRecordType_Relief:
            pRecord = getGameRecordInfo(m_mReliefRecord, pDay);
            break;
        case GameRecordType_SeaMonster:
            pRecord = getGameRecordInfo(m_mSeaMonsterRecord, pDay);
            break;
        default:
            return 0;
    }
    return pRecord;
}

GameTimesRecord* GameData::getGameRecordInfo(map<int, GameTimesRecord *>* pRecords, string pDay)
{
    map<int, GameTimesRecord*>::iterator it = pRecords->find(atoi(pDay.c_str()));
    if (it != pRecords->end())
    {
        return it->second;
    }
    return NULL;
}

void GameData::saveGameRecordInfo(GameRecordType pType, string pDay, int pTimes, vector<int> *pExt)
{
    switch (pType)
    {
        case GameRecordType_Task:
            saveGameRecordInfo(m_mTaskRecord, "task", pDay, pTimes, pExt);
            break;
        case GameRecordType_Relief:
            saveGameRecordInfo(m_mReliefRecord, "relief", pDay, pTimes, pExt);
            break;
        case GameRecordType_SeaMonster:
            saveGameRecordInfo(m_mSeaMonsterRecord, "seamonster", pDay, pTimes, pExt);
            break;
        default:
            break;
    }
}

void GameData::saveGameRecordInfo(map<int, GameTimesRecord *> *pRecords, string pKey, string pDay, int pTimes, vector<int> *pExt)
{
    map<int, GameTimesRecord*>::iterator it = pRecords->find(atoi(pDay.c_str()));
    if (it != pRecords->end())
    {
        it->second->times = pTimes;
        it->second->ext = pExt;
    }
    else
    {
        GameTimesRecord* pTemp = new GameTimesRecord();
        pTemp->day = atoi(pDay.c_str());
        pTemp->times = pTimes;
        pTemp->ext = pExt;
        pRecords->insert(pair<int, GameTimesRecord*>(pTemp->day, pTemp));
    }
    //save
    string pRecord = "";
    char achTemp[32] = {0};
    memset(achTemp, 0, sizeof(achTemp));
    for (it = pRecords->begin(); it != pRecords->end(); ++it)
    {
        sprintf(achTemp, "%d", it->second->day);
        pRecord.append(achTemp);
        pRecord.append(CConfig::DELIMIT_COLON);
        sprintf(achTemp, "%d", it->second->times);
        pRecord.append(achTemp);
        pRecord.append(CConfig::DELIMIT_COLON);
        string pExtStr = "";
        for (int i = 0; i < it->second->ext->size(); i++)
        {
            sprintf(achTemp, "%d", it->second->ext->at(i));
            pExtStr.append(achTemp);
            pExtStr.append(CConfig::DELIMIT_COMMA);
        }
        pRecord.append(pExtStr);
        pRecord.append(CConfig::DELIMIT_VERTICAL);
    }
    CCUserDefault::sharedUserDefault()->setStringForKey(pKey.c_str(), pRecord);
    CCUserDefault::sharedUserDefault()->flush();
}

vector<int>* GameData::getGameRecordExtInfo(string pExtStr)
{
    vector<int>* pExt = new vector<int>();
    vector<string>* pExtInfo = CConfig::sharedConfig()->splitString(pExtStr, CConfig::DELIMIT_COMMA);
    for (int i = 0; i < pExtInfo->size(); i++)
    {
        pExt->push_back(atoi(pExtInfo->at(i).c_str()));
    }
    return pExt;
}

void GameData::setGameType(GameType pGameType)
{
    m_gameType = pGameType;
    switch (pGameType)
    {
        case GameType_Normal:
            m_seamonster_blood = 0;
            m_seamonster_score = 0;
            m_seamonster_power = 0;
            m_seamonster_power_count = 0;
            m_seamonster_time = 0;
            break;
        case GameType_SeaMonster_Normal:
            m_seamonster_blood = 120000;
            m_seamonster_score = 100000;
            m_seamonster_power = 1000;
            m_seamonster_power_count = 0;
            m_seamonster_time = 0;
            break;
        case GameType_SeaMonster_Difficulty:
            m_seamonster_blood = 150000;
            m_seamonster_score = 120000;
            m_seamonster_power = 1000;
            m_seamonster_power_count = 0;
            m_seamonster_time = 180;
            break;
        default:
            break;
    }
}


void GameData::setCurrentScene(Scene pScene)
{
    m_cur_scene = pScene;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_cur_scene", m_cur_scene);
    CCUserDefault::sharedUserDefault()->flush();
}


CCString* GameData::getDespForLevel(int pLevel)
{
    CCString* str = NULL;
    if (pLevel <= GameMaxLevel) {
        GameUserExp* pExp = getGameUserExpFroLevel(pLevel);
        if (pExp->m_desp != NULL) {
            if (!pExp->isUnlockCannon||!GameData::getSharedGameData()->getUnLockMaxConnon()) {
                str = CCString::createWithFormat("当前解锁:  %s",pExp->m_desp);
            }
            else
            {
                str = CCString::createWithFormat("当前解锁:  无");
            }
            
        }
    }
    if (str == NULL) {
        str = CCString::createWithFormat("当前解锁:  无");
    }
    return str;
}

CCString* GameData::getNextDespForLevel(int pLevel)
{
    CCString* str = NULL;
        if (pLevel + 1 < GameMaxLevel) {
                GameUserExp* pExp = getGameUserExpFroLevel(pLevel + 1);
                if (pExp->m_desp != NULL) {
                    if (!pExp->isUnlockCannon||!GameData::getSharedGameData()->getUnLockMaxConnon()) {
                        str = CCString::createWithFormat("下级将解锁:  %s",pExp->m_desp);
                    }
                    else
                    {
                        str = CCString::createWithFormat("下级将解锁:  无");
                    }

                }
            }
    if (str == NULL) {
        str = CCString::createWithFormat("下级将解锁:  无");
    }
    return str;
}



CCString* GameData::getTitleForLevel(int pLevel)
{
    CCString* str = NULL;
    if (pLevel > 0 && pLevel <= 10) {
        str = CCString::create("渔夫");
    } else if (pLevel >= 11 && pLevel <= 19) {
        str = CCString::create("水手");
    } else if (pLevel >= 20 && pLevel <= 29) {
        str = CCString::create("大副");
    } else if (pLevel >= 30 && pLevel <= 39) {
        str = CCString::create("船长");
    } else if (pLevel >= 40 && pLevel <= 49) {
        str = CCString::create("维京人");
    } else if (pLevel >= 50 && pLevel <= 59) {
        str = CCString::create("两栖鱼怪");
    } else if (pLevel >= 60 && pLevel <= 69) {
        str = CCString::create("北海巨妖");
    } else if (pLevel >= 70 && pLevel <= 79) {
        str = CCString::create("海妖塞壬");
    } else if (pLevel >= 80 && pLevel <= 89) {
        str = CCString::create("深海阎王");
    } else if (pLevel >= 90 && pLevel <= 999) {
        str = CCString::create("波塞冬");
    } else {
        str = CCString::create("无");
    }
    return str;
}

CCString* GameData::getPicForLevel(int pLevel)
{
    CCString* str = NULL;
    if (pLevel > 0 && pLevel <= 10) {
        str = CCString::create("cenhao10.png");
    } else if (pLevel >= 11 && pLevel <= 19) {
        str = CCString::create("cenhao19.png");
    } else if (pLevel >= 20 && pLevel <= 29) {
        str = CCString::create("cenhao29.png");
    } else if (pLevel >= 30 && pLevel <= 39) {
        str = CCString::create("cenhao39.png");
    } else if (pLevel >= 40 && pLevel <= 49) {
        str = CCString::create("cenhao49.png");
    } else if (pLevel >= 50 && pLevel <= 59) {
        str = CCString::create("cenhao59.png");
    } else if (pLevel >= 60 && pLevel <= 69) {
        str = CCString::create("cenhao69.png");
    } else if (pLevel >= 70 && pLevel <= 79) {
        str = CCString::create("cenhao79.png");
    } else if (pLevel >= 80 && pLevel <= 89) {
        str = CCString::create("cenhao89.png");
    } else if (pLevel >= 90 && pLevel <= 999) {
        str = CCString::create("cenhao99.png");
    } else {
        str = CCString::create("无");
    }
    return str;
}

GameUserExp* GameData::getGameUserExpFroLevel(int pLevel)
{
    GameUserExp* pExp = NULL;
    if (pLevel <= GameMaxLevel) {
        pExp = (GameUserExp*)m_pUserExp->objectAtIndex(pLevel - 1);
    }
    return pExp;
}


void GameData::upgradeUser()
{
    if (m_cur_level < GameMaxLevel) {
        m_cur_level++;
        m_cur_exp = 0;
        if (m_cur_level < GameMaxLevel) {
            m_pNextLevel = (GameUserExp*)m_pUserExp->objectAtIndex(m_cur_level + 1);
        } else {
            m_pNextLevel = NULL;
        }
        CCUserDefault::sharedUserDefault()->setIntegerForKey("m_cur_level", m_cur_level);
    }
}


bool GameData::addExp(int pExp)
{
    bool isUpgrade = false;
    int addExp = pExp;
    
    //increase with card wuzhe
    GameCard* pCard = getGameCard(Card_Wuzhe);
    if (pCard->m_count > 0) {
        addExp += addExp * pCard->m_count * 3 / 100;
    }
    
    if (m_doubleTimeExp > 0) {
        addExp += addExp;
    }
    int newExp = m_cur_exp + addExp;
    if (m_pNextLevel != NULL) {
        if (newExp > m_pNextLevel->m_expForUpgrade) {
            upgradeUser();
            isUpgrade = true;
        }
    }
    if (isUpgrade == false) {
        m_cur_exp = newExp;
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_cur_exp", m_cur_exp);
    CCUserDefault::sharedUserDefault()->flush();
    return isUpgrade;
}


void GameData::save()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("m_isGoldCannon2", m_isGoldCannon2);
    CCUserDefault::sharedUserDefault()->setBoolForKey("m_isGoldCannon3", m_isGoldCannon3);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_cur_power", m_cur_power);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_cur_power_count", m_cur_power_count);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_score", m_score);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_doubleTimeExp", m_doubleTimeExp);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_hideBulletCnt", m_hideBulletCnt);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_apBulletCnt", m_apBulletCnt);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_HitPercentage", m_HitPercentage);

    CCUserDefault::sharedUserDefault()->flush();
}

GameData* GameData::m_self = NULL;

GameData* GameData::getSharedGameData()
{
    if (m_self == NULL) {
        m_self = new GameData;
    }
    return m_self;
    
}


bool GameData::changeScore(int add)
{
    int newScore = m_score + add;
    if (newScore < 0) {
        return false;
    }
    
    m_score = newScore;
    save();
    //CCNotificationCenter::sharedNotificationCenter()->postNotification("Game_Global_Score_Change");
    GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
    if (pGameLayer)
    {
        pGameLayer->syncScoreUI();
    }
   // DF_LOG("---------changeScore end");
    return true;
}
bool GameData::changeHide(int add)
{
    int newScore = m_hideBulletCnt + add;
    if (newScore < 0) {
        return false;
    }
    
    m_hideBulletCnt = newScore;
    save();
    //CCNotificationCenter::sharedNotificationCenter()->postNotification("Game_Global_Hide_Change");
    GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
    if (pGameLayer)
    {
        pGameLayer->syncHideUI();
    }
    DF_LOG("---------changeHide end");
    return true;
}

bool GameData::setCurrentPowerCount(int count)
{
    if (!isBuyFishKnife())
    {
        m_cur_power_count = 0;
        return false;
    }
    if (count < 0)
    {
        count = 0;
    }
    if (count > GamePowerMaxCount)
    {
        count = GamePowerMaxCount;
        
        return false;
    }
    m_cur_power_count = count;
    return true;
}

bool GameData::addSeaMonsterScore(int addScore)
{
    int newScore = m_seamonster_score + addScore;
    if (newScore < 0)
    {
        return false;
    }
    m_seamonster_score = newScore;
    return true;
}

bool GameData::setSeaMonsterPower(int newPower)
{
    if (newPower < 0)
    {
        newPower = 0;
    }
    m_seamonster_power = newPower;
    return true;
}

bool GameData::setSeaMonsterPowerCount(int newCount)
{
    if (!isBuyFishKnife())
    {
        m_seamonster_power_count = 0;
        return false;
    }
    if (newCount < 0)
    {
        newCount = 0;
    }
    if (newCount > GamePowerMaxCount)
    {
        newCount = GamePowerMaxCount;
        return false;
    }
    m_seamonster_power_count = newCount;
    return true;
}

bool GameData::addSeaMonsterBlood(int addBlood)
{
    int newBlood = m_seamonster_blood + addBlood;
    if (newBlood < 0)
    {
        newBlood = 0;
        return false;
    }
    m_seamonster_blood = newBlood;
    return true;
}

bool GameData::addSeaMonsterTime(int addTime)
{
    int newTime = m_seamonster_time + addTime;
    if (newTime < 0)
    {
        return false;
    }
    m_seamonster_time = newTime;
    return true;
}

#define FIRST_SCENE_INDEX_IN_PRODUCTS (11) //在商品列表中的场景起始索引

int GameData::getProductPrice(ProductType pType)
{
    switch (pType)
    {
        case Product_Coin2:
            return 200;
        case Product_Coin6:
        case Product_Fb_Coin6:
            return 600;
        case Product_Coin10:
        case Product_Fb_Coin10:
            return 1000;
        case Product_Coin15:
            return 1500;
        case Product_Coin18:
            return 1800;
        case Product_Coin40:
            return 4000;
        case Product_Coin78:
            return 7800;
        case Product_Coin128:
            return 12800;
        case Product_Coin388:
            return 38800;
        case Product_Gift12:
            return 1200;
        case Product_Gift18:
            return 1800;
        case Product_Gift25:
            return 2500;
        case Product_Pearl:
            return 200;
        case Product_HideBullet1000:
            return 600;
        case Product_Diamond2:
            return 800;
        case Product_PearlShell:
            return 600;
        case Product_FishKnife:
            return 600;
        case Product_MysticalScene: //神秘海域
        case Product_DreamScene:  //梦幻海域
        case Product_ProfusionScene: //缤纷海域
        case Product_HistoricScene: //古迹海域
            return 2000;
        default:
            break;
    }
}

string GameData::getProductConstId(ProductType pType)
{
    switch (pType)
    {
        case Product_Coin2:
            return "coin2";
        case Product_Coin6:
            return "coin6";
        case Product_Coin10:
            return "coin10";
        case Product_Coin15:
            return "coin15";
        case Product_Coin18:
            return "coin18";
        case Product_Coin40:
            return "coin40";
        case Product_Coin78:
            return "coin78";
        case Product_Coin128:
            return "coin128";
        case Product_Coin388:
            return "coin388";
        case Product_Gift12:
            return "gift12";
        case Product_Gift18:
            return "gift18";
        case Product_Gift25:
            return "gift25";
        case Product_Pearl:
            return "pearls";
        case Product_HideBullet1000:
            return "hb1000";
        case Product_Diamond2:
            return "diamond2";
        case Product_PearlShell:
            return "pearlshell";
        case Product_Fb_Coin6:
            return "fbcoin6";
        case Product_FishKnife:
            return "fishknife";
        case Product_Fb_Coin10:
            return "fbcoin10";
        case Product_MysticalScene: //神秘海域
        case Product_DreamScene:  //梦幻海域
        case Product_ProfusionScene: //缤纷海域
        case Product_HistoricScene: //古迹海域
            return "";
        default:
            break;
    }
}

string GameData::getProductName(ProductType pType)
{
    switch (pType)
    {
        case Product_Coin2:
            return "2000金币";
        case Product_Coin6:
        case Product_Fb_Coin6:
            return "6000金币";
        case Product_Coin10:
        case Product_Fb_Coin10:
            return "10000金币";
        case Product_Coin15:
            return "15000金币";
        case Product_Coin18:
            return "18000金币";
        case Product_Coin40:
            return "40000金币";
        case Product_Coin78:
            return "78000金币";
        case Product_Coin128:
            return "128000金币";
        case Product_Coin388:
            return "388000金币";
        case Product_Gift12:
            return "礼包12";
        case Product_Gift18:
            return "礼包18";
        case Product_Gift25:
            return "礼包25";
        case Product_Pearl:
            return "珍珠";
        case Product_HideBullet1000:
            return "1000发幽灵弹";
        case Product_Diamond2:
            return "海盗的宝石箱";
        case Product_PearlShell:
            return "解锁珍珠贝";
        case Product_FishKnife:
            return "旋风鱼刀+能量存储";
        case Product_MysticalScene: //神秘海域
        case Product_DreamScene:  //梦幻海域
        case Product_ProfusionScene: //缤纷海域
        case Product_HistoricScene: //古迹海域
            return "新的海域";
        default:
            break;
    }
}

string GameData::genOrderId(ProductType pType, int pToken)
{
    char achTemp[128] = {0};
    memset(achTemp, 0, sizeof(achTemp));
    sprintf(achTemp, "%s_%lu_%04d", getProductConstId(pType).c_str(), CConfig::sharedConfig()->secondNow(), pToken);
    return achTemp;
}

void GameData::provideProduct(ProductType pType)
{
    DF_LOG("GameData::provideProduct pType= %d",pType);
    //商品是场景?
    bool isScene = false;
    
    int inc_coins = 0;
    switch (pType)
    {
        case Product_Coin2:
            inc_coins = 20000;
            break;
        case Product_Coin6:
        case Product_Fb_Coin6:
            inc_coins = 70000;
            break;
        case Product_Coin10:
        case Product_Fb_Coin10:
            inc_coins = 130000;
            break;
        case Product_Coin15:
            inc_coins = 200000;
            break;
        case Product_Coin18:
            inc_coins = 350000;
            break;
        case Product_Coin40:
            inc_coins = 740000;
            break;
        case Product_Coin78:
            inc_coins = 1550000;
            break;
        case Product_Coin128:
            inc_coins = 2450000;
            break;
        case Product_Coin388:
            inc_coins = 7250000;
            break;
        case Product_Gift12:
//            unlockFish(Fish::FISH_BYMOGUIYU);
//            unlockFish(Fish::FISH_BYWUGUI);
            inc_coins = 50000;
            break;
        case Product_Gift18:
            m_isGoldCannon2 = true;
            m_isGoldCannon3 = true;
            inc_coins = 100000;
            save();
            break;
        case Product_Gift25:
            addGameDiamond(Diamond_Pearl, 3);
            m_doubleTimeExp += 18000;
            m_hideBulletCnt += 1000;
            break;
        case Product_Pearl:
        {
            inc_coins = 100000;
            addGameDiamond(Diamond_Pearl, 1);
            int ranType = arc4random()%4 + 1;
            addGameDiamond((DiamondType)ranType, 1);
            break;
        }
        case Product_HideBullet1000:
        {
            m_hideBulletCnt += 1000;
            break;
        }
        case Product_Diamond2:
        {
            addGameDiamond(Diamond_Yellow, 2);
            addGameDiamond(Diamond_Green, 2);
            addGameDiamond(Diamond_Red, 2);
            addGameDiamond(Diamond_Blue, 2);
//            addGameDiamond(Diamond_Pearl, 2);
            break;
        }
        case Product_PearlShell:
        {
            DF_LOG("Pay Start Product_PearlShell");
            unlockFish(Fish::FISH_ZHENZHUBEI);
            break;
        }
        case Product_FishKnife:
        {
            setBuyFishKnife(true);
        if(m_cur_power == 2000)
        {
            m_cur_power = 0;
           // m_cur_power_count++;
            if(m_cur_power_count<=0)
            {
                m_cur_power_count =1;
            }
            else
            {
                m_cur_power_count++;
            }
            GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
            if (pGameLayer)
            {
                pGameLayer->updateMinePower(0);
            }
        }
        else
        {
           // m_cur_power_count++;
            if(m_cur_power_count<=0)
                {
                    m_cur_power_count =1;
                }
                else
                {
                    m_cur_power_count++;
                }
                GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
                if (pGameLayer)
                {
                    pGameLayer->updateMinePower(0);
                }
            
            }
            
        }
            break;
        case Product_MysticalScene: //神秘海域
        case Product_DreamScene:  //梦幻海域
        case Product_ProfusionScene: //缤纷海域
        case Product_HistoricScene: //古迹海域
            isScene = true;
            break;
            case Product_UpGradGift:
        {
            inc_coins = 88888;
           // m_hideBulletCnt += 500;
            setHideBulletCount(hideBulletCount()+500);
            //随机添加一只满星宠物
            int rand_pet = CCRANDOM_0_1()*6+1;
            DF_LOG("升级礼包 随机添加一只宠物 id= %d",rand_pet);
            GameCard* pCard = getGameCard((CardType)rand_pet);
            if (pCard->m_count < GameCardMaxNumber)
            {
                //pCard->m_count = GameCardMaxNumber;
                pCard->m_count++;   //改为一只宠物
                saveGameCard(pCard->m_type);
            }
            break;
        }
        case Product_DragonGift:
        {
            inc_coins = m_score;
            break;
        }
            case Product_MermaidGift:
        {
            inc_coins = 1314520;
            addGameDiamond(Diamond_Pearl,9);
            //随机添加一只满星宠物
            int rand_pet = CCRANDOM_0_1()*6+1;
            DF_LOG("美人鱼 随机添加一只宠物 id= %d",rand_pet);
            GameCard* pCard = getGameCard((CardType)rand_pet);
            if (pCard->m_count < GameCardMaxNumber)
            {
                pCard->m_count++;
                saveGameCard(pCard->m_type);
            }

            break;
        }
        case Product_GoodSixGift:
        {
            inc_coins = 66666;
            m_hideBulletCnt += 666;
//            setBuyFishKnife(true);
            /*edit by lqg 2015-04-14
             *
             *
             */

            if(isBuyFishKnife())
            {
                if(m_cur_power_count<=0)
                    m_cur_power_count =1;
                else
                    m_cur_power_count ++;
            }
            else
            {
                m_cur_power = 2000;
            }
                        GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
                        if (pGameLayer)
                        {
                            pGameLayer->updateMinePower(0);
                        }
            break;
        }
        case Product_XihaGift:
        {
            inc_coins =  233333;
            addGameDiamond(Diamond_Pearl, 8);
            
            setDoubleTimeExp( doubleTimeExp() + 7200 );// 加2小时双倍经验时间
            setHitPercentage(getHitPercentage() +1);  //增加1% 命中
//            GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
//            if (pGameLayer)
//            {
//                pGameLayer->onBoughtResultNotify();
//            }
            break;
        }
        default:
            break;
    }
    if (inc_coins > 0) {
        DF_LOG("---------changeScore start");
        changeScore(inc_coins);
    }
    if(m_hideBulletCnt >0)
    {
        DF_LOG("---------changeHide start");
        changeHide(0);
    }
    //首次充值奖励
    if (!isInitRecharged()) {
        doInitRechargedBonus();
        //购买结果通知
       //CCNotificationCenter::sharedNotificationCenter()->postNotification(kInitRechargResultNotification);
        GameLayer* pGameLayer = (GameLayer*)GameData::getSharedGameData()->getDataPoint(DT_Game);
        if (pGameLayer)
        {
            pGameLayer->onBoughtResultNotify();
        }
        changeHide(0);
    }
    DF_LOG("---------end bug");
//    //购买结果通知,本就应是全局通知,但此处只是在首次充值时投递
//    CCNotificationCenter::sharedNotificationCenter()->postNotification(kBoughtResultNotification);
    //商品是场景,投递通知
//    if (isScene) {
//        Scene s = Scene(pType - FIRST_SCENE_INDEX_IN_PRODUCTS);
//        CCNotificationCenter::sharedNotificationCenter()->postNotification(kBoughtSceneResultNotification, (CCObject*)s);
//    }
}


bool GameData::isGoldCannon( int index ) {
    if(index == 2) {
        return m_isGoldCannon2;
    } else if (index == 3 ) {
        return m_isGoldCannon3;
    }
    return false;  // todo
}


#define INIT_RECHARGED_FLAG_STR ("InitRechargedFlagStr")
#define BOOT_FROM_INIT_RECHARGE_FLAG_STR ("BootFromInitRechargeFlagStr")
#define BUY_FISHKNIFE_STR ("buyfishknife")

//首充相关设置
void GameData::setInitRecharged( bool b) {
    
    CCUserDefault::sharedUserDefault()->setBoolForKey(INIT_RECHARGED_FLAG_STR, b);
    CCUserDefault::sharedUserDefault()->flush();
}
bool GameData::isInitRecharged() {
    return CCUserDefault::sharedUserDefault()->getBoolForKey(INIT_RECHARGED_FLAG_STR, false);
}

void GameData::setBootFromInitRecharge(bool b) {
    _isBootFromInitRecharge = b;
}
bool GameData::isBootFromInitRecharge() {
    return _isBootFromInitRecharge;
}

void GameData::setBuyFishKnife(bool b)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(BUY_FISHKNIFE_STR, b);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameData::isBuyFishKnife()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(BUY_FISHKNIFE_STR, false);
}

void GameData::addUnLockMaxConnon(bool status)
{
    _isUnLockMaxConnon = status;
    CCUserDefault::sharedUserDefault()->setBoolForKey("m_isUnLockMaxConnon", status);
    CCUserDefault::sharedUserDefault()->flush();
}
void GameData::addTodayLoginCount()
{
    _isTodayLoginCount++;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_isTodayLoginCount",_isTodayLoginCount );
    CCUserDefault::sharedUserDefault()->flush();
}
void GameData::setTodayLoginCount(int count)
{
    _isTodayLoginCount= count;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_isTodayLoginCount",_isTodayLoginCount );
    CCUserDefault::sharedUserDefault()->flush();
}
void GameData::addVipCard(bool status)
{
    _isHaveVipCard = status;
    CCUserDefault::sharedUserDefault()->setBoolForKey("m_isHaveVipCard",status );
    CCUserDefault::sharedUserDefault()->flush();
}
void GameData::setHitPercentage(int hitPercentage)
{
    m_HitPercentage = hitPercentage;
    if(m_HitPercentage >90)
    {
        m_HitPercentage = 90;
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey("m_HitPercentage",m_HitPercentage );
    CCUserDefault::sharedUserDefault()->flush();
}
//#define INIT_RECHARGE_BONUS_COINS (10000)        // 10w金币
#define INIT_RECHARGE_BONUS_HIDDEN_BULLET (500) // 500隐形炮
#define INIT_RECHARGE_BONUS_X2EXP_TIME (60 * 60 * 3)

void GameData::doInitRechargedBonus() {
    
    //将首次充值标记置空
    setInitRecharged(true);
    
    //加10w金币
//    changeScore( INIT_RECHARGE_BONUS_COINS );
    
    //加500隐形炮
    setHideBulletCount(hideBulletCount() + INIT_RECHARGE_BONUS_HIDDEN_BULLET );
    
    // 加3小时双倍经验时间
    setDoubleTimeExp( doubleTimeExp() + INIT_RECHARGE_BONUS_X2EXP_TIME );
    
    //解锁小飞鱼
    unlockFish(Fish::FISH_XIAOFEIYU);
    
    //增加狮子鱼
    GameCard* pCard = getGameCard(Card_Shiziyu);
    if (pCard->m_count < GameCardMaxNumber)
    {
        pCard->m_count += 1;
        saveGameCard(pCard->m_type);
    }
    //保存更新
    save();
}

void GameData::exitGame()
{
    //del by andy 2015/03/16
//    IThirdParty* pThirdParty = ThirdPartyFactory::Inst()->thirdParty();
//    if (pThirdParty)
//    {
//        pThirdParty->logout();
//    }
    save();
#ifdef USING_UMENG             
    umeng::MobClickCpp::end();
#endif
    CCDirector::sharedDirector()->end();
    
}

void GameData::setDataPoint(Data_Type dataType, void *pData)
{
    if (!pData)
    {
        return;
    }
    erasePoint(dataType);
    m_mapPoint.insert(pair<Data_Type, void*>(dataType, pData));
}

void* GameData::getDataPoint(Data_Type dataType)
{
    map<Data_Type, void*>::iterator iter = m_mapPoint.find(dataType);
    if (iter != m_mapPoint.end())
    {
        return iter->second;
    }
    return NULL;
}

void GameData::erasePoint(Data_Type dataType)
{
    map<Data_Type, void*>::iterator iter = m_mapPoint.find(dataType);
    if (iter != m_mapPoint.end())
    {
        m_mapPoint.erase(iter);
    }
}
void GameData::setChannel(const char *data)
{
    CCString *pstr = CCString::create(data);
    if(!pstr->isEqual(CCString::create("")) && !pstr->isEqual(CCString::create("null"))){
        
        m_channel =pstr;
    }
    else
    {
        if (m_channel !=NULL) {
            delete m_channel;
             m_channel =CCString::createWithFormat("");
        }
        else
        {
            m_channel =CCString::createWithFormat("");
        }
    }

}
void GameData::setAPPKey(const char *data)
{
    CCString *pstr = CCString::create(data);
    if(!pstr->isEqual(CCString::create("")) && !pstr->isEqual(CCString::create("null"))){
        
        m_appkey =pstr;
    }
    else
    {
        if (m_appkey !=NULL) {
            delete m_appkey;
            m_appkey =CCString::createWithFormat("");
        }
        else
        {
            m_appkey =CCString::createWithFormat("");
        }
    }
    
}
