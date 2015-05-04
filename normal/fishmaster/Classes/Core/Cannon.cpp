//
//  Cannon.cpp
//
//  
//
//

#include "Cannon.h"
#include "Bullet.h"
#include "GameLayer.h"
#include "GameData.h"
#include "Helper.h"
#include "../Foundation/Sound.h"

using namespace cocos2d;

Cannon* Cannon::createWithCannonType(GameLayer *pGameLayer, cocos2d::CCSpriteBatchNode *pBatchNode,CCSprite* pCannonSprite){
    Cannon* pCannon = new Cannon(pGameLayer,pBatchNode,pCannonSprite);
    
    if (pCannon == NULL) {
        CC_SAFE_DELETE(pCannon);
        return NULL;
    }
    
    if(pCannon->initWithCannonType(pCannon->m_nCannonType)){
        pCannon->autorelease();//放入内存池管理，调用方需要使用retain操作，才能避免被释放，参考[C1]
        
    }
    return pCannon;
}

Cannon::Cannon(GameLayer *gameLayer,CCSpriteBatchNode *pBatchNode,CCSprite* pCannonSprite):
m_pGameLayer(gameLayer),
m_pBatchNode(pBatchNode),
m_pSprite(pCannonSprite),
m_fRotation(0.0f),
isHideBullet(false),
isSepcailCannon(false),
cannon_score_max(300),
isCooldown(true),
cannonName(NULL),
SpecLeftTime(0),
m_lLastAddAp(0)
{
    //尽量使用初始列表，参考：[C3]
    cannon_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("cannon_score", -1);
    
    if (cannon_score < 0)
    {
        cannon_score = 100;
    }
    
    if (cannon_score > 0 && cannon_score < 500)
    {
        m_nCannonType = Red_Cannon2;
    }
    else if (cannon_score >= 500 && cannon_score < 900)
    {
        m_nCannonType = Red_Cannon3;
    }
    else
    {
        m_nCannonType = Red_Cannon4;
    }
    normal_cannonType = m_nCannonType;
}

Cannon::~Cannon(){
}

int Cannon::getConnonType(){
    return this->m_nCannonType;
}


void Cannon::startSpecCannon(CannonType cannonType)
{
    if (isSepcailCannon) {
        if (cannonType == m_nCannonType) {
            //SpecLeftTime += 12;
            return;
        }
    } else {
        normal_cannonType = m_nCannonType;
    }
    SpecLeftTime = CannonSpecDuringTime;
    initWithCannonType(cannonType);
}

void Cannon::endSpecCannon()
{
    m_pSprite->stopAllActions();
    initWithCannonType(normal_cannonType);
}


bool Cannon::incCannonScore()
{
    int incScore = 100;
//    if (cannon_score >= 500) {
//        incScore = 100;
//    }
    int new_cannon_score = cannon_score + incScore;
    if (new_cannon_score > cannon_score_max) {
        new_cannon_score = 100;
    }
    if (((cannon_score >= 500 && new_cannon_score < 500 ) ||
    (cannon_score < 500 && new_cannon_score >= 500 ) || (cannon_score >= 900 && new_cannon_score < 900) || (cannon_score < 900 && new_cannon_score >= 900))
        && isSepcailCannon == false)
    {
        if (new_cannon_score < 500)
        {
            m_nCannonType = Red_Cannon2;
        }
        else if (new_cannon_score < 900)
        {
            m_nCannonType = Red_Cannon3;
        }
        else
        {
            m_nCannonType = Red_Cannon4;
        }
        initWithCannonType(m_nCannonType);
    }
    cannon_score = new_cannon_score;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("cannon_score", cannon_score);
    CCUserDefault::sharedUserDefault()->flush();
    return true;
}


bool Cannon::decCannonScore()
{
    int decScore = 100;
//    if (cannon_score >= 600) {
//        decScore = 100;
//    }
    int new_cannon_score = cannon_score - decScore;
    
    if (new_cannon_score <= 0) {
        new_cannon_score = cannon_score_max;
    }
    if (((cannon_score >= 500 && new_cannon_score < 500 ) ||
         (cannon_score < 500 && new_cannon_score >= 500 ) || (cannon_score >= 900 && new_cannon_score < 900 ) ||
         (cannon_score < 900 && new_cannon_score >= 900 ))
        && isSepcailCannon == false)
    {
        if (new_cannon_score < 500)
        {
            m_nCannonType = Red_Cannon2;
        }
        else if (new_cannon_score < 900)
        {
            m_nCannonType = Red_Cannon3;
        }
        else
        {
            m_nCannonType = Red_Cannon4;
        }
        initWithCannonType(m_nCannonType);
    }
    cannon_score = new_cannon_score;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("cannon_score", cannon_score);
    CCUserDefault::sharedUserDefault()->flush();
    return false;
    
}


bool Cannon::initWithCannonType(CannonType pCannonType){
    //根据炮台类型 组装 炮台对于的图片名称，炮台的具体名称可从cannon.plist中找到
    char* fireName = NULL;
    
    if (pCannonType == Red_Cannon2 && GameData::getSharedGameData()->isGoldCannon(2))
    {
        pCannonType = Gold_Cannon2;
    }
    
    if (pCannonType == Red_Cannon3 && GameData::getSharedGameData()->isGoldCannon(3))
    {
        pCannonType = Gold_Cannon3;
    }
    
    if (pCannonType == Red_Cannon4 && GameData::getSharedGameData()->isGoldCannon(4))
    {
        pCannonType = Gold_Cannon4;
    }
    
    if (isSepcailCannon == false) {
        normal_cannonType = m_nCannonType;
    }
    
    switch (pCannonType) {
            case Red_Cannon2:
                cannonName="Pao01";
                fireName = "PaoFire_01.png";
                isSepcailCannon = false;
            break;
            case Red_Cannon3:
                cannonName="Pao01s";
                fireName = "PaoFire_01.png";
                isSepcailCannon = false;
            break;
            case Red_Cannon4:
                cannonName = "Pao01x";
                fireName = "PaoFire_01.png";
                isSepcailCannon = false;
            break;
            case Gold_Cannon2:
                cannonName="Pao02";
                fireName = "PaoFire_02.png";
                isSepcailCannon = false;
            break;
            case Gold_Cannon3:
                cannonName="Pao02s";
                fireName = "PaoFire_02s.png";
                isSepcailCannon = false;
            break;
            case Gold_Cannon4:
                //TODO
            break;
            case Power_Cannon:
                cannonName="Pao03";
                fireName = "PaoFire_03.png";
                isSepcailCannon = true;
            break;
            
            case Laser_Cannon:
                cannonName="laser";
                isSepcailCannon = true;
            break;
            
//            case Knife_Cannon: // 非特殊炮塔 不需要设置
//                cannonName="Pao01";
//                fireName = "PaoFire_01.png";
//                isSepcailCannon = false;
            break;
            
        default:
            cannon_score = 0;
            return false;
            break;
    }
    m_nCannonType = pCannonType;
    
    CCSprite* sp_fire = (CCSprite*)m_pSprite->getChildByTag(CannonFireTag);
    if (fireName != NULL) {
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fireName);
        sp_fire->setDisplayFrame(pFrame);
    }
   
    //根据炮台名称创建炮台精灵frame，此API将从CCSpriteFrameCache对象中查找指定对象
    CCString* filename = CCString::createWithFormat("%s_0.png",cannonName);
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
    m_pSprite->setDisplayFrame(pFrame);
    
    CCArray *aniframe=CCArray::createWithCapacity(3);
    
    for(int i=1;i <=5;i++){
        CCString *frameName=CCString::createWithFormat("qipao2_%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
    }
    
    CCAnimation* tAnimation = CCAnimation::createWithSpriteFrames(aniframe,0.08);//通过集合创建动画
    CCAnimate *animate=CCAnimate::create(tAnimation);
    CCSprite* sp = CCSprite::createWithSpriteFrameName("qipao2_1.png");
    sp->setPosition(CCPoint(m_pSprite->getContentSize().width/2, m_pSprite->getContentSize().height/2));
    sp->setAnchorPoint(CCPoint(0.5,0.4));
    m_pSprite->addChild(sp,1,CannonSwitchTag);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Cannon::removeSwEffect));
    CCSequence* seqSw = CCSequence::create(animate, CCHide::create(),callFunc,NULL);
    sp->runAction(seqSw);
    
    cooldown();
    
//    if (m_nCannonType == Laser_Cannon) {
//        CCArray *aniframe=CCArray::createWithCapacity(3);
//        
//        for(int i=1;i <=4;i++){
//            CCString *frameName=CCString::createWithFormat("laser_%d.png",i);
//            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
//            aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
//        }
//        
//        CCAnimation* tAnimation = CCAnimation::createWithSpriteFrames(aniframe,0.06);//通过集合创建动画
//        CCAnimate *animate=CCAnimate::create(tAnimation);
//        CCSequence* seq = CCSequence::create(CCDelayTime::create(0.2f), CCRepeat::create(animate, 100),NULL);
//        m_pSprite->runAction(seq);
//
//    }
    
    return true;
}

void Cannon::removeSwEffect()
{
    m_pSprite->removeChildByTag(CannonSwitchTag, true);
}

bool Cannon::rotationAndFire(cocos2d::CCPoint ptTo)
{
    GameData* gd = GameData::getSharedGameData();
    bool haveMoney = false;
    if (gd->getGameType() == GameType_Normal)
    {
        haveMoney = gd->score() >= cannon_score ? true : false;
    }
    else
    {
        haveMoney = gd->getSeaMonsterScore() >= cannon_score ? true : false;
    }
    
    if (haveMoney == false) {
        Sound::Instance()->playEffect("coinshort.mp3");
        return false;
    }
    
    if (isCooldown == false) {
        return false;
    } else {
        isCooldown = false;
    }

    //取得炮台的位置，再与ptTo连线构造三角形，便于下一步从炮台出发的角度计算
    CCPoint ptFrom=m_pSprite->getPosition();
    //计算预备要转到的角度值 atan2f函数 返回 弧度值
    float angle=atan2f(ptTo.y-ptFrom.y,ptTo.x-ptFrom.x)/M_PI * 180.0f;
    //存储炮台准备转向的角度值（方向）
    m_fRotation=90 - angle;
    //计算从当前炮台的角度转向指定的方向经过的绝对角度值
    float absf_rotation=fabsf(m_fRotation-this->m_pSprite->getRotation());
    //计算转向需要的时间预设0.2ms转1弧度
    float duration=absf_rotation/180.0f*0.2f;
    //构造旋转动作对象 参考:[C4]
    CCFiniteTimeAction *pAction = CCRotateTo::create(duration, m_fRotation);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Cannon::doFire));
    CCFiniteTimeAction *cooldown = CCCallFunc::create(this, callfunc_selector(Cannon::cooldown));
    CCFiniteTimeAction *sequence = CCSequence::create(pAction,CCDelayTime::create(0.05f), callFunc,CCDelayTime::create(0.1f),cooldown, NULL);
    //触发转向动作
    this->m_pSprite->runAction(sequence);
    //保持用户的触摸点
    this->m_pDirection= ptTo;
    
    
    int fireFrameCnt = 3;
    if (m_nCannonType != Laser_Cannon) {
        
        CCSequence* fireSeq = CCSequence::create(CCDelayTime::create(0.1f),CCBlink::create(0.2f, 2),CCHide::create(),NULL);
        CCSprite* sp_fire = (CCSprite*)m_pSprite->getChildByTag(CannonFireTag);
        sp_fire->setAnchorPoint(m_pSprite->getChildByTag(CannonFireTag)->getAnchorPoint());
        sp_fire->setPosition(m_pSprite->getChildByTag(CannonFireTag)->getPosition());
        sp_fire->runAction(fireSeq);
        
        fireFrameCnt = 2;
    }
    
    fireFrameCnt += 1;
    CCArray *aniframe=CCArray::createWithCapacity(fireFrameCnt);
    
    for(int i=0;i < fireFrameCnt;i++){
        int cnt = i;
        if (i == fireFrameCnt - 1) {
            cnt = 0;
        }
        CCString *frameName=CCString::createWithFormat("%s_%d.png",cannonName,cnt);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
    }
    
    CCAnimation* tAnimation = CCAnimation::createWithSpriteFrames(aniframe,0.2/fireFrameCnt);//通过集合创建动画
    CCAnimate *animate=CCAnimate::create(tAnimation);
    m_pSprite->runAction(CCRepeat::create(animate, 1));
    
    return true;
}


CCPoint Cannon::getLaserPos()
{
    CCPoint res;
    int leng = m_pSprite->getContentSize().height/18;
    int newx = m_pSprite->getPositionX() + leng * sinf(m_pSprite->getRotation() * M_PI / 180.0f) + 24 * cosf(m_pSprite->getRotation() * M_PI / 180.0f);
    int newy = m_pSprite->getPositionY() + leng * cosf(m_pSprite->getRotation() * M_PI / 180.0f) - 24 * sinf(m_pSprite->getRotation() * M_PI / 180.0f);
    
    return CCPoint(newx,newy);
}



CCPoint Cannon::getCannonHolePos()
{
    CCPoint res;
    int leng = m_pSprite->getContentSize().height/4;
    int newx = m_pSprite->getPositionX() + leng * sinf(m_pSprite->getRotation() * M_PI / 180.0f);
    int newy = m_pSprite->getPositionY() + leng * cosf(m_pSprite->getRotation() * M_PI / 180.0f);
    
    return CCPoint(newx,newy);
}


void Cannon::cooldown()
{
    isCooldown = true;
}

void Cannon::doFire()
{
    GameData* gd = GameData::getSharedGameData();
    // 新增宠物效果
    GameCard* pCard = gd->getGameCard(Card_LanAli);
    Bullet *pBullet;
    bool pAddAp = false;
    if (m_nCannonType != Laser_Cannon || m_nCannonType != Knife_Cannon)
    {
        // 概率新增穿透弹
        int pRate = pCard->m_count * 2;
        pAddAp = (arc4random() % 100 < pRate) && (m_nCannonType != Power_Cannon) && ((CConfig::secondNow() - 1) > m_lLastAddAp) && (gd->hideBulletCount() <= 0);
        if (pAddAp)
        {
            m_lLastAddAp = CConfig::secondNow();
        }
        pBullet = Bullet::createWithBulletType(m_nCannonType, this->m_pGameLayer, this->m_pBatchNode,cannon_score, getCannonHolePos(), pAddAp);
    }
    else
    {
        pBullet = Bullet::createWithBulletType(m_nCannonType, this->m_pGameLayer, this->m_pBatchNode,cannon_score, getLaserPos());
    }
    //DF_LOG("m_nCannonType =%d,Power_Cannon=%d,m_nCannonType=%d,Laser_Cannon=%d",m_nCannonType ,Power_Cannon , m_nCannonType ,Laser_Cannon);
    if (gd->hideBulletCount()<= 0) {
        isHideBullet = false;
        gd->setHideBulletCount(0);
    } else if(m_nCannonType != Power_Cannon && m_nCannonType != Laser_Cannon){
        if (!pAddAp)
        {
            isHideBullet = true;
            gd->setHideBulletCount(gd->hideBulletCount()-1);
        }
        else
        {
            isHideBullet = false;
        }
    }
    
    pBullet->isHide = isHideBullet;
    pBullet->shootTo(this->m_pDirection);
}



