

#include <iostream>
#include "Bullet.h"
#include "GameLayer.h"
#include "Helper.h"
#include "Sound.h"
#include "GameData.h"

using namespace cocos2d;

void FatherBullet::showTotalScoreAnimate()
{

}

Bullet::Bullet():
m_bAP(false),
isHide(false),
m_pSpriteNet(NULL),
m_reflectTimes(0)
{
    
}

Bullet *Bullet::createWithBulletType(CannonType bulletType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNodeBullet,int pScore, CCPoint pPos, bool pIsAp)
{
    Bullet *pBullet = new Bullet();
    if(pBullet && pBullet->initWithBulletType(bulletType, gameLayer, pBatchNodeBullet,pScore, pPos, pIsAp))
    {
        pBullet->autorelease();
        return pBullet;
    }
    else
    {
        CC_SAFE_DELETE(pBullet);
        return NULL;
    }
}

bool Bullet::initWithBulletType(CannonType bulletType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNodeBullet,int pScore, CCPoint pPos, bool pIsAp)
{
    this->setBulletType(bulletType);
    this->setGameLayer(gameLayer);
//    this->setBatchNodeBullet(pBatchNodeBullet);
//    this->setCannon(cannon);
    m_bAP = pIsAp;
    bullet_score = pScore;
    totalGetScore = 0;
    
    m_speed = GameDefaultBulletSpeed;
    
    int score = GameData::getSharedGameData()->score();
    hit_rate = 50;
    
    if (score < 20000) {
        hit_rate *= 1;
    } else if (score >= 20000 && score < 50000) {
        hit_rate *= 0.95;
    } else if (score >= 50000 && score < 100000) {
        hit_rate *= 0.90;
    } else if (score >= 100000 && score < 200000) {
        hit_rate *= 0.85;
    } else if (score >= 200000 && score < 300000) {
        hit_rate *= 0.80;
    } else if (score >= 300000 && score < 400000) {
        hit_rate *= 0.75;
    } else if (score >= 400000 && score < 500000) {
        hit_rate *= 0.70;
    } else if (score >= 500000 && score < 600000) {
        hit_rate *= 0.65;
    } else if (score >= 600000 && score < 700000) {
        hit_rate *= 0.60;
    } else if (score >= 700000 && score < 1000000) {
        hit_rate *= 0.55;
    } else if (score >= 1000000) {
        hit_rate *= 0.50;
    }
    
    if (bullet_score < 500) {
        hit_rate *= 1;
    } else if (bullet_score >= 500 && bullet_score < 1000) {
        hit_rate *= 0.95;
    } else if (bullet_score >= 1000){
        hit_rate *= 0.9;
    }
    
    GameCard* pCard = GameData::getSharedGameData()->getGameCard(Card_Denglongyu);
    if (pCard->m_count > 0) {
        hit_rate += pCard->m_count;
    }
    
    pCard = GameData::getSharedGameData()->getGameCard(Card_Shenxianyu);
    if (pCard->m_count > 0) {
        bullet_score += bullet_score * pCard->m_count / 100;
    }

    hit_Percentage = GameData::getSharedGameData()->getHitPercentage();
    CCSpriteBatchNode *pBatchNodeNet = NULL;
    char* bullFilename = NULL;
    char* netFilename = NULL;
    float t_scale = 1.0f;
    switch (m_nBulletType) {
            case Red_Cannon2:
            if (m_bAP)
            {
                bullFilename = "piercing01_0.png";
                bulletFile = "piercing01";
                frameCnt = 3;
            }
            else
            {
                bullFilename = "shot01.png";
                bulletFile = "shot01";
                frameCnt = 1;
            }
            netFilename = "net01_0.png";
            netFile = "net01_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            netFrameCnt = 6;
            t_scale = 1.35;
            break;
            
            case Red_Cannon3:
            if (m_bAP)
            {
                bullFilename = "piercing02_0.png";
                bulletFile = "piercing02";
                frameCnt = 3;
            }
            else
            {
                bullFilename = "shot01s.png";
                bulletFile = "shot01s";
                frameCnt = 1;
            }
            netFilename = "net01s_0.png";
            netFile = "net01s_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            netFrameCnt = 6;
            t_scale = 1.35;
            break;
            
            case Red_Cannon4:
            if (m_bAP)
            {
                bullFilename = "piercing03_0.png";
                bulletFile = "piercing03";
                frameCnt = 3;
            }
            else
            {
                bullFilename = "shot01x.png";
                bulletFile = "shot01x";
                frameCnt = 1;
            }
            netFilename = "net01x_0.png";
            netFile = "net01x_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            netFrameCnt = 6;
            t_scale = 1.35;
            break;
            
            case Gold_Cannon2:
            bullFilename = "shot02_0.png";
            netFilename = "net02_0.png";
            bulletFile = "shot02";
            netFile = "net02_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            frameCnt = 3;
            netFrameCnt = 12;
            break;
            
            case Gold_Cannon3:
            bullFilename = "shot02s_0.png";
            netFilename = "net02s_0.png";
            bulletFile = "shot02s";
            netFile = "net02s_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            frameCnt = 3;
            netFrameCnt = 16;
            break;
            
            case Gold_Cannon4:
            //TODO
            bullFilename = "shot02s_0.png";
            netFilename = "net02s_0.png";
            bulletFile = "shot02s";
            netFile = "net02s_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            frameCnt = 3;
            netFrameCnt = 16;
            break;
            
            case Power_Cannon:
            bullFilename = "shot03_0.png";
            netFilename = "net01s_0.png";
            bulletFile = "shot03";
            netFile = "net01s_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            frameCnt = 2;
            netFrameCnt = 6;
            //double score on power cannon
            bullet_score *= 2;
            break;
            
            case Laser_Cannon:
            bullFilename = "shot03s_0.png";
            netFilename = NULL;
            bulletFile = "shot03s";
            netFile = NULL;
            pBatchNodeNet = NULL;
            frameCnt = 6;
            netFrameCnt = 0;
            //100%hit rate increase on laser cannon
            hit_rate *= 2;
            break;
            
            case Knife_Cannon:
            bullFilename = "knife.png";
            netFilename = NULL;
            bulletFile = "knife";
            netFile = NULL;
            pBatchNodeNet = gameLayer->getBatchNodePao();
            frameCnt = 1;
            netFrameCnt = 0;
            hit_rate *= 1.5;
            rotateTime = 0;
            m_speed = 500;
            break;
            
        case Ele_Cannon:
            bullFilename = "ele_0.png";
            netFilename = "ele_0.png";
            bulletFile = "ele";
            netFile = "ele_";
            pBatchNodeNet = gameLayer->getBatchNodePao();
            frameCnt = 1;
            netFrameCnt = 6;
            hit_rate *= 3;
            rotateTime = 0;
            m_speed = 0;
            break;
        default:
            frameCnt = 0;
            break;
    }
    
    
    this->initWithSpriteFrameName(bullFilename);
//    this->setSpriteBullet(CCSprite::createWithSpriteFrameName(bullFilename));
    // CCPoint tPos = getCannon()->getCannonHolePos();
    // gameLayer->getCannon()->getCannonHolePos();
    CCSize s = this->getContentSize();
    if( m_nBulletType != Laser_Cannon && m_nBulletType != Knife_Cannon)
    {
//        NumSprite *p = NumSprite::create(pScore);
//        p->setPosition(ccp(s.width/2,s.height/2));
//        p->setScale(0.5f);
//        p->setAnchorPoint(CCPoint(0.5,0.8));
//        this->addChild(p);
    } else {
//        tPos = gameLayer->getCannon()->getLaserPos();
    }
    this->setPosition(pPos);
    this->setScale(t_scale);
    pBatchNodeBullet->addChild(this);

    if (netFilename != NULL) {
        this->setSpriteNet(CCSprite::createWithSpriteFrameName(netFilename));
        m_pSpriteNet->setVisible(false);
        pBatchNodeNet->addChild(m_pSpriteNet);
    }
    m_pGameLayer->getBullets()->addObject(this);
    
    m_status = Bullet_Fly;
    return true;
}


void Bullet::reflect()
{
    //add reflect code here!!!!!!!!!!
    m_reflectTimes++;
    if (m_reflectTimes >= ApBulletMaxReflect && m_bAP)
    {
        removeSelf();
    }
    
    CCPoint ptFrom = this->getPosition();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //CCLog("(%f,%f)",ptFrom.x,ptFrom.y);
    
    float k = -(ptFrom.y - ptLastStart.y)/(ptFrom.x-ptLastStart.x);
    float b = ptFrom.y-k*ptFrom.x;
    CCPoint target[4];
    CCPoint realTarget;
    CCRect rc;
    rc.setRect(0, 0, size.width, size.height);
    
    //cross with left
    target[0].x = 0;
    target[0].y = b;

    //cross with right
    target[1].x=size.width;
    target[1].y=size.width*k+b;

    //cross with down
    target[2].y = 0;
    target[2].x = -b/k;

    //cross with up
    target[3].y = size.height;
    target[3].x = (size.height-b)/k;

    for (int i=0; i< 4;i++) {
        if( ((int)target[i].x !=(int)ptFrom.x || (int)target[i].y !=(int)ptFrom.y) && rc.containsPoint(target[i])){
            realTarget = target[i];
            break;
        }
    }
    
    float angle = atan2f(realTarget.y - ptFrom.y, realTarget.x - ptFrom.x);
    float rotation = angle / M_PI * 180.0f;
    //edit by andy 2015-03-31
    this->setRotation(90.0f - rotation);
    //this->setRotation(-rotation);
    
//    CCLog("(%f,%f)(%f,%f)(%f,%f)(%f,%f)",target[0].x,target[0].y,target[1].x,target[1].y,target[2].x,target[2].y,target[3].x,target[3].y);
//    CCLog("readTarget (%f,%f)",realTarget.x,realTarget.y);

    float moveSec = getBulletMoveTime(ptFrom,realTarget);
    CCFiniteTimeAction *moveto = CCMoveTo::create(moveSec, realTarget);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::reflect));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, callFunc, NULL);
    this->runAction(sequence);
    ptLastStart = ptFrom;
}

void Bullet::rotate(float delta)
{
    rotateTime += delta;
    this->setRotation(this->getRotation() + 10);
    if (rotateTime > 5)
    {
        removeSelf();
    }
}


float Bullet::getBulletMoveTime(CCPoint startPos, CCPoint endPos)
{
    float dis = sqrtf((startPos.x - endPos.x) * (startPos.x - endPos.x) + (startPos.y - endPos.y) * (startPos.y - endPos.y));
    float sec = dis / m_speed;
    return sec;
}

void Bullet::shootLaser(CCPoint targetDirection)
{
    CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
    
    for(int i=0;i <frameCnt;i++){
        CCString *frameName=CCString::createWithFormat("%s_%d.png",this->bulletFile,i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
    }
    
    m_bulletAnimation = CCAnimation::createWithSpriteFrames(aniframe,0.06);//通过集合创建动画
    CCAnimate *animate=CCAnimate::create(m_bulletAnimation);
    this->runAction(CCRepeat::create(animate, 100));
    
    this->setScaleY(0);
    this->setAnchorPoint(CCPoint(0.5,0));
    
    CCScaleTo* scy = CCScaleTo::create(0.1, 1.5f, 1.2f);
    CCScaleTo* scx = CCScaleTo::create(0.1f, 0,1.0f);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::removeSelf));
    CCSequence* seqB = CCSequence::create(scy,CCDelayTime::create(0.3f),scx,CCHide::create(),callFunc,NULL);
    this->runAction(seqB);
    
}

void Bullet::shootTo(cocos2d::CCPoint targetDirection)
{
    CCPoint ptFrom = this->getPosition();
    CCPoint ptTo = targetDirection;
    float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x);
    float rotation = angle / M_PI * 180.0f;
    //edit by andy 2015-03-31
    this->setRotation(90.0f - rotation);
    //this->setRotation(-rotation);

    if (m_nBulletType == Laser_Cannon) {
        shootLaser(targetDirection);
        return;
    }
    if (isHide) {
        m_pSpriteNet->setPosition(targetDirection);
        showNet();
    }
    
    ptLastStart = ptFrom;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize(); 
    
    //float distance =fmaxf(size.width, size.height);
    //CCPoint targetPt = ccp(ptFrom.x + distance * cosf(angle), ptFrom.y + distance * sinf(angle));
    CCPoint targetPt;
    if(ptTo.x < ptFrom.x){
        //left
        if((ptTo.y-ptFrom.y)/(ptTo.x-ptFrom.x) > (size.height-ptFrom.y)/(0-ptFrom.x)) {
            //real left
            targetPt.x = 0;
            targetPt.y = (ptTo.x*ptFrom.y-ptFrom.x*ptTo.y)/(ptTo.x-ptFrom.x);
        } else {
            //up
            targetPt.y = size.height;
            targetPt.x = (size.height-((ptTo.x*ptFrom.y-ptFrom.x*ptTo.y)/(ptTo.x-ptFrom.x)))/((ptTo.y-ptFrom.y) / (ptTo.x-ptFrom.x));
        }
    } else if(ptTo.x > ptFrom.x) {
        //right
        if((ptTo.y-ptFrom.y)/(ptTo.x-ptFrom.x) < (size.height-ptFrom.y)/(size.width-ptFrom.x)) {
            //real right
            targetPt.x = size.width;
            targetPt.y = size.width*(ptTo.y-ptFrom.y)/(ptTo.x-ptFrom.x)+(ptTo.x*ptFrom.y-ptFrom.x*ptTo.y)/(ptTo.x-ptFrom.x);
        } else {
            //up
            targetPt.y = size.height;
            targetPt.x = (size.height-((ptTo.x*ptFrom.y-ptFrom.x*ptTo.y)/(ptTo.x-ptFrom.x)))/((ptTo.y-ptFrom.y) / (ptTo.x-ptFrom.x));
        }
    } else {
        //mid
        targetPt.x = ptTo.x;
        targetPt.y = size.height;
    }

//    CCLog("(%f,%f)",targetPt.x,targetPt.y);

    float moveSec = getBulletMoveTime(ptFrom, targetPt);
    CCFiniteTimeAction *moveto = CCMoveTo::create(moveSec, targetPt);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::reflect));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, callFunc, NULL);
    this->runAction(sequence);
    if (m_nBulletType == Knife_Cannon)
    {
        this->schedule(schedule_selector(Bullet::rotate));
//        CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
//        
//        pScheduler->scheduleSelector(schedule_selector(Bullet::rotate), this, 1, kCCRepeatForever, 0, true);
    }
    
    if (frameCnt > 1) {
        CCArray *aniframe=CCArray::createWithCapacity(frameCnt);
        
        for(int i=0;i <frameCnt;i++){
            CCString *frameName=CCString::createWithFormat("%s_%d.png",this->bulletFile,i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
            aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
        }
        
        m_bulletAnimation = CCAnimation::createWithSpriteFrames(aniframe,0.1);//通过集合创建动画
        CCAnimate *animate=CCAnimate::create(m_bulletAnimation);
        this->runAction(CCRepeat::create(animate, 100));
    }
}


void Bullet::showNet()
{
 
    if (m_nBulletType == Laser_Cannon || m_nBulletType == Knife_Cannon)
    {
        return;
    }
    
    this->stopAllActions();
    this->setVisible(false);
    m_pSpriteNet->setVisible(true);
    
    m_status = Bullet_Net;
    
    if (isHide == false) {
        m_pSpriteNet->setPosition(this->getPosition());
    }
    
    CCArray *aniframe=CCArray::createWithCapacity(netFrameCnt);
    
    for(int i=0;i <netFrameCnt;i++){
        CCString *frameName=CCString::createWithFormat("%s%d.png",this->netFile,i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        
        aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
    }
    float frameIterval = 0.05f;
    if (m_nBulletType == Ele_Cannon)
    {
        frameIterval = 0.15f;
    }
    m_bulletAnimation = CCAnimation::createWithSpriteFrames(aniframe,frameIterval);//通过集合创建动画
    CCAnimate *animate=CCAnimate::create(m_bulletAnimation);
    m_pSpriteNet->runAction(CCRepeat::create(animate, 1));
    
//    CCParticleSystem *particle = CCParticleSystemQuad::create("growingFlare1.plist");
//    particle->setPosition(m_pSpriteNet->getPosition());
//    particle->setPositionType(kCCPositionTypeGrouped);
//    particle->setAutoRemoveOnFinish(true);
//    m_pGameLayer->addChild(particle, 100);
    
//    CCScaleTo *scale = CCScaleTo::create(0.3f, 2.0f);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(CCDelayTime::create(frameIterval*netFrameCnt), callFunc, NULL);
    m_pSpriteNet->runAction(sequence);
  
    if (m_nBulletType == Ele_Cannon)
    {
        Sound::Instance()->playEffect("ele.mp3");
    }
    else
    {
        Sound::Instance()->playEffect("NetOpen.mp3");
    }
}

void Bullet::removeSelf()
{
//    CCLOG("remove bullet");
    this->unschedule(schedule_selector(Bullet::rotate));
    this->removeFromParentAndCleanup(true);
    if (m_pSpriteNet != NULL) {
        
        m_pSpriteNet->removeFromParentAndCleanup(true);
    }
    m_pGameLayer->getBullets()->removeObject(this);
}

void Bullet::netCatchFish()
{
//    m_status = Bullet_Net;
}