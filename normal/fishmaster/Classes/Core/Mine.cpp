//
//  Mine.cpp
//  fish
//
//  
//
//

#include "Mine.h"
#include "GameData.h"
#include "../Foundation/AppDelegate.h"
#include "../config/CConfig.h"
#include "../Ui/GameLayer.h"

Mine* Mine::create(cocos2d::CCSpriteBatchNode *pBatchNode)
{
    Mine* pMine = new Mine();
    pMine->m_batchNode = pBatchNode;
    return pMine;
}


Mine::Mine():
m_status(Mine_Start),
m_batchNode(NULL),
m_gameLayer(NULL)
{
    bullet_score = 500;
    
    GameCard* pCard = GameData::getSharedGameData()->getGameCard(Card_Xiaochouyu);
    if (pCard->m_count > 0) {
        bullet_score += pCard->m_count * 100;
    }

    updatePowerMax();
}


Mine::~Mine()
{
    
}


void Mine::updatePowerMax()
{
    //int level = GameData::getSharedGameData()->currentLevel();
//    if (level <= 10) {
//        m_power_max = 150000;
//    } else if (level >= 11 && level <= 20) {
//        m_power_max = 210000;
//    } else if (level >= 21 && level <= 50) {
//        m_power_max = 300000;
//    } else {
//        m_power_max = 420000;
//    }
    m_power_max = 2000;//5000;
}

void Mine::addPower(int pAdd)
{
    int new_power = 0;
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        new_power = GameData::getSharedGameData()->currentPower() + pAdd;
        if (new_power > m_power_max)
        {
            bool pAddSuccess = GameData::getSharedGameData()->setCurrentPowerCount(GameData::getSharedGameData()->currentPowerCount() + 1);
            if (pAddSuccess)
            {
                new_power -= m_power_max;
            }
            else
            {
                new_power = m_power_max;
            }
        }
        GameData::getSharedGameData()->setCurrentPower(new_power);
        GameData::getSharedGameData()->save();
    }
    else
    {
        new_power = GameData::getSharedGameData()->getSeaMonsterPower() + pAdd;
        if (new_power > m_power_max)
        {
            bool pAddSuccess = GameData::getSharedGameData()->setSeaMonsterPowerCount(GameData::getSharedGameData()->getSeaMonsterPowerCount() + 1);
            if (pAddSuccess)
            {
                new_power -= m_power_max;
            }
            else
            {
                new_power = m_power_max;
            }
        }
        GameData::getSharedGameData()->setSeaMonsterPower(new_power);
    }
}


void Mine::mineReady()
{
    m_status = Mine_Ready;
    
    int frameCnt = 3;
        CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
        
        for(int i=0;i <frameCnt;i++){
            CCString *frameName=CCString::createWithFormat("slei_%d.png",i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
            aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
        }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(aniframe,0.16);//通过集合创建动画
    CCAnimate *animate=CCAnimate::create(animation);
    m_sprite->runAction(CCRepeat::create(animate, 1000));
}


void Mine::start(CCPoint pPoint,CCLayer* pGameLayer)
{
    const char* frameFile = "slei_0.png";
//    CCSpriteFrame* spFram = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameFile);
//    m_sprite->setDisplayFrame(spFram);
    
    m_sprite = CCSprite::createWithSpriteFrameName(frameFile);
    m_sprite->setPosition(pPoint);
    m_sprite->setOpacity(0);
    pGameLayer->addChild(m_sprite);
    
    totalGetScore = 0;
    
    
    CCFiniteTimeAction *readyFunc = CCCallFunc::create(this, callfunc_selector(Mine::mineReady));
        CCFiniteTimeAction *fin = CCFadeIn::create(0.5f);
        CCFiniteTimeAction *fout = CCFadeOut::create(0.5f);
        CCSequence* newSeq = CCSequence::create(fin,fout,fin,fout,fin,readyFunc,NULL);
        m_sprite->runAction(newSeq);
    
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        bool pSubSuccess = GameData::getSharedGameData()->setCurrentPowerCount(GameData::getSharedGameData()->currentPowerCount() - 1);
        if (!pSubSuccess)
        {
            GameData::getSharedGameData()->setCurrentPower(0);
        }
        
    }
    else
    {
        bool pSubSuccess = GameData::getSharedGameData()->setSeaMonsterPowerCount(GameData::getSharedGameData()->getSeaMonsterPowerCount() - 1);
        if (!pSubSuccess)
        {
            GameData::getSharedGameData()->setSeaMonsterPower(0);
        }
        
    }
    updatePowerMax();
    GameData::getSharedGameData()->save();
}

void Mine::startKnife(cocos2d::CCPoint pPoint, cocos2d::CCLayer *pGameLayer)
{
    // 出现两把飞刀
    totalGetScore = 0;
    
    GameData* gd = GameData::getSharedGameData();
    Bullet *pBulletOne = Bullet::createWithBulletType(Knife_Cannon, (GameLayer*)pGameLayer, m_batchNode, bullet_score, CCPoint(AppDelegate::SCREEN_WIDTH / 2, 0));
    if (gd->hideBulletCount()<= 0)
    {
        gd->setHideBulletCount(0);
    }
    pBulletOne->isHide = false;
    pBulletOne->shootTo(CCPoint(0, AppDelegate::SCREEN_HEIGHT / 2));
    
    Bullet *pBulletTwo = Bullet::createWithBulletType(Knife_Cannon, (GameLayer*)pGameLayer, m_batchNode, bullet_score, CCPoint(AppDelegate::SCREEN_WIDTH / 2, 0));
    if (gd->hideBulletCount()<= 0)
    {
        gd->setHideBulletCount(0);
    }
    pBulletTwo->isHide = false;
    pBulletTwo->shootTo(CCPoint(AppDelegate::SCREEN_WIDTH, AppDelegate::SCREEN_HEIGHT / 2));
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        bool pSubSuccess = GameData::getSharedGameData()->setCurrentPowerCount(GameData::getSharedGameData()->currentPowerCount() - 1);
        if (!pSubSuccess)
        {
                if(GameData::getSharedGameData()->currentPower() >= m_power_max)
                {
                    GameData::getSharedGameData()->setCurrentPowerCount(1);
                }
                GameData::getSharedGameData()->setCurrentPower(0);
        }
        else
        {
            GameData::getSharedGameData()->setCurrentPower( GameData::getSharedGameData()->currentPower()+1);
        }
        GameData::getSharedGameData()->save();
    }
    else
    {
        bool pSubSuccess = GameData::getSharedGameData()->setSeaMonsterPowerCount(GameData::getSharedGameData()->getSeaMonsterPowerCount() - 1);
        if (!pSubSuccess)
        {
            if(GameData::getSharedGameData()->currentPower() >= m_power_max)
            {
                GameData::getSharedGameData()->setSeaMonsterPowerCount(1);
            }
            GameData::getSharedGameData()->setSeaMonsterPower(0);
        }
        else
        {
            GameData::getSharedGameData()->setSeaMonsterPower( GameData::getSharedGameData()->getSeaMonsterPower()+1);        }
        }
    updatePowerMax();
    GameData::getSharedGameData()->save();
}

void Mine::startEle(cocos2d::CCLayer *pGameLayer)
{
    // 出现电磁风暴
    totalGetScore = 0;
    m_gameLayer = (GameLayer*)pGameLayer;
    m_gameLayer->startEle();
    //
    if (GameData::getSharedGameData()->getGameType() == GameType_Normal)
    {
        bool pSubSuccess = GameData::getSharedGameData()->setCurrentPowerCount(GameData::getSharedGameData()->currentPowerCount() - 1);
        if (!pSubSuccess)
        {
                        GameData::getSharedGameData()->setCurrentPower(0);
        }
        else
        {
            GameData::getSharedGameData()->setCurrentPower( GameData::getSharedGameData()->currentPower()+1);
        }
        GameData::getSharedGameData()->save();
    }
    else
    {
        bool pSubSuccess = GameData::getSharedGameData()->setSeaMonsterPowerCount(GameData::getSharedGameData()->getSeaMonsterPowerCount() - 1);
        if (!pSubSuccess)
        {
            if(GameData::getSharedGameData()->currentPower() >= m_power_max)
            {
                GameData::getSharedGameData()->setSeaMonsterPowerCount(1);
            }
            GameData::getSharedGameData()->setSeaMonsterPower(0);
        }
        else
        {
            GameData::getSharedGameData()->setSeaMonsterPower( GameData::getSharedGameData()->getSeaMonsterPower()+1);
        }
    }
    updatePowerMax();
    GameData::getSharedGameData()->save();
}

void Mine::addEle()
{
    Bullet* pEle = Bullet::createWithBulletType(Ele_Cannon, m_gameLayer, m_batchNode, bullet_score, CCPoint(arc4random() % AppDelegate::SCREEN_WIDTH, arc4random() % AppDelegate::SCREEN_HEIGHT));
    pEle->showNet();
}

void Mine::remove()
{
    m_status = Mine_End;
    
    m_sprite->removeFromParentAndCleanup(true);
}


void Mine::startBomb()
{
    this->scheduleOnce(schedule_selector(Mine::bomb), 0.5f);
}

void Mine::bomb()
{
    int frameCnt = 10;
    float frameInterval = 0.08;
    CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
    
    m_sprite->stopAllActions();
    
    for(int i=0;i <frameCnt;i++){
        CCString *frameName=CCString::createWithFormat("sleitx_%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(aniframe,frameInterval);//通过集合创建动画
    CCAnimate *animate=CCAnimate::create(animation);
    m_sprite->runAction(animate);
    
    CCFiniteTimeAction *removeFunc = CCCallFunc::create(this, callfunc_selector(Mine::remove));
    CCSequence* newSeq = CCSequence::create(CCDelayTime::create(frameInterval*frameCnt),removeFunc,NULL);
    m_sprite->runAction(newSeq);
    
    m_status = Mine_Bomb;
}

