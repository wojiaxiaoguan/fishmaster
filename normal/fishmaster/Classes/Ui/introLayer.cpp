#include "IntroLayer.h"
#include "GameLayer.h"
#include "Sound.h"
#include "../config/CConfig.h"

//#include "SceneSelectionLayer.h"
#include "FishGroup.h"
#include "WaveRippleScene.h"
#include "PlatformHandler.h"

//#include "../thirdparty/IThirdParty.h"
//#include "../thirdparty/ThirdPartyFactory.h"


using namespace cocos2d;


IntroLayer::IntroLayer()
:CCLayer(),
cb_menuActions(NULL),
menuFastEnter_(NULL),
//menuSound_(NULL),
//menuScene_(NULL),
//menuInfo_(NULL),
sp_bg(NULL),
sp_loading(NULL),
sp_title(NULL)
//cb_spWheel(NULL),
//ly_about(NULL),
//ly_seamonster(NULL),
//bmf_normalTimes(NULL),
//bmf_difficultyTimes(NULL),
//m_pMiiSeaMonsterNormal(NULL),
//m_pMiiSeaMonsterDiffculty(NULL)
{
    srand(time(NULL));
//     delaytime = 3.0f;
//     exitcount =0;
//    exitStatus = false;
    isexitInMenu = false;
    isTouchInMenu =false;
    isTouchInWaveRipple =false;
}

IntroLayer::~IntroLayer()
{
    CC_SAFE_RELEASE(cb_menuActions);
    
    CC_SAFE_RELEASE(menuFastEnter_);
//    CC_SAFE_RELEASE(menuSound_);
//    CC_SAFE_RELEASE(menuInfo_);
//    CC_SAFE_RELEASE(menuScene_);
    
    CC_SAFE_RELEASE(sp_bg);
    CC_SAFE_RELEASE(sp_loading);
    CC_SAFE_RELEASE(m_pWaveRipple);
    CC_SAFE_RELEASE(sp_title);
//    CC_SAFE_RELEASE(cb_spWheel);
//    CC_SAFE_RELEASE(ly_about);
//    CC_SAFE_RELEASE(ly_seamonster);
//    CC_SAFE_RELEASE(bmf_normalTimes);
//    CC_SAFE_RELEASE(bmf_difficultyTimes);
//    CC_SAFE_RELEASE(m_pMiiSeaMonsterNormal);
//    CC_SAFE_RELEASE(m_pMiiSeaMonsterDiffculty);
   
}

CCScene* IntroLayer::scene()
{
    DF_LOG("enter IntroLayer::scene");
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("IntroLayer", IntroLayerBuilderLoad::loader());
    //读取IntroLayer
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	IntroLayer* node = (IntroLayer*)ccbReader->readNodeGraphFromFile("ios/ccbResources/IntroLayer.ccbi", sc);
    DF_LOG("IntroLayer::scene() node = %d", node);
    ccbReader->release();
    
	if (node)
    {
		sc->addChild(node);
        node->setKeypadEnabled(true);
    }
    DF_LOG("end IntroLayer::scene node=%x",node);
	return sc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void IntroLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    DF_LOG("enter IntroLayer::onNodeLoaded");
    this->setTouchEnabled(true);
    
    
    m_pWaveRipple =  WaveRippleScene::create();
    m_pWaveRipple->retain();
    sp_bg->addChild(m_pWaveRipple);

    sp_bg->getParent()->reorderChild(sp_bg, -2);
    DF_LOG("enter IntroLayer::onNodeLoaded1");
    this->scheduleUpdate();
    this->schedule(schedule_selector(IntroLayer::updateFish),4.0f);
    
    
//    CCSprite *pc = (CCSprite*)getChildByTag(9999);
//    char str[32];
//    bzero(str,sizeof(str));
//    CCArray *aniframe = CCArray::createWithCapacity(14);
//    
//    for(int i=1;i <15;i++){
//        sprintf(str,"cao_%d.png",i);  //通过下标动态创建精灵
//        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//        aniframe->addObject(frame);
//    }
//    CCAnimation * pa = CCAnimation::createWithSpriteFrames(aniframe,0.2);//通过集合创建动画
//    
//    CCAnimate *animate=CCAnimate::create(pa);
//    
//    CCFiniteTimeAction *action = CCRepeatForever::create(animate);
//    pc->runAction(action);
    
//    if (Sound::Instance()->getIsCloseSound() == false)
//    {
//        menuSound_->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soundno.png"));
//    } else {
//        menuSound_->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soundoff.png"));
//    }
}

bool IntroLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_bg", CCSprite*, this->sp_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_loading", CCSprite*, this->sp_loading);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_title", CCSprite*, this->sp_title);
    
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_spWheel", CCSprite*, this->cb_spWheel);
 
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuActions", CCMenu*, this->cb_menuActions);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuFastEnter_", CCMenuItem*, this->menuFastEnter_);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuSound_", CCMenuItemImage*, this->menuSound_);
   
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuInfo_", CCMenuItem*, this->menuInfo_);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuScene_", CCMenuItem*, this->menuScene_);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_about", CCLayer*, this->ly_about);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ly_seamonster", CCLayer *, this->ly_seamonster);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bmf_normalTimes", CCLabelBMFont *, this->bmf_normalTimes);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bmf_difficultyTimes", CCLabelBMFont *, this->bmf_difficultyTimes);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiSeaMonsterNormal", CCMenuItemImage *, this->m_pMiiSeaMonsterNormal);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMiiSeaMonsterDiffculty", CCMenuItemImage *, this->m_pMiiSeaMonsterDiffculty);
	return true;
}


SEL_MenuHandler IntroLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFastStart", IntroLayer::onFastStart);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFeedback", IntroLayer::onFeedback);
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSceneSelectionClicked", IntroLayer::onSceneSelectionClicked);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onInfo_", IntroLayer::onInfo_);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAboutExit", IntroLayer::onAboutExit);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSeaMonsterCallback", IntroLayer::onSeaMonsterCallback);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSeaMonsterCloseCallback", IntroLayer::onSeaMonsterCloseCallback);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSeaMonsterStartCallback", IntroLayer::onSeaMonsterStartCallback);
	return NULL;
}


SEL_CCControlHandler IntroLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
        return NULL;
}


void IntroLayer::update(float dt)
{
  //  m_pRippleGrid->update(dt);
//    if (exitStatus) {
//        delaytime-=dt;
//        if (delaytime <= 0.0f) {
//            exitStatus =false;
//            exitcount =0;
//            delaytime =3.0f;
//        }
//        else
//        {
//            if (exitcount ==2) {
//#ifdef USING_UMENG
//                umeng::MobClickCpp::end();
//#else
//                 CCDirector::sharedDirector()->end();
//#endif
//                exitStatus = false;
//                exitcount =0;
//                delaytime =3.0f;
//            }
//        }
//    }
}

bool IntroLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//    if (this->getChildByTag(1) && this->getChildByTag(1)->isVisible() ) {
//        this->getChildByTag(1)->setVisible(false);
//        return true;
//    }
    //isTouchInMenu = cb_menuActions->ccTouchBegan(pTouch, pEvent);
    if (isTouchInMenu) {
        return isTouchInMenu;
    }
    
    isTouchInWaveRipple = m_pWaveRipple->ccTouchBegan(pTouch, pEvent);

    
    return isTouchInWaveRipple;
    
}
void IntroLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

    if (isTouchInMenu) {
        cb_menuActions->ccTouchMoved(pTouch, pEvent);
    }
    if (isTouchInWaveRipple) {
        m_pWaveRipple->ccTouchMoved(pTouch, pEvent);
    }
    
}
void IntroLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

    if (isTouchInMenu) {
        cb_menuActions->ccTouchEnded(pTouch, pEvent);
        isTouchInMenu = false;
    }
    
    if (isTouchInWaveRipple) {
        m_pWaveRipple->ccTouchEnded(pTouch, pEvent);
        isTouchInWaveRipple = false;
    }
}
void IntroLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuActions->ccTouchCancelled(pTouch, pEvent);
        isTouchInMenu = false;
    }
    
    if (isTouchInWaveRipple) {
        m_pWaveRipple->ccTouchCancelled(pTouch, pEvent);
        isTouchInWaveRipple = false;
    }
    
    
}

void IntroLayer::keyBackClicked()
{
    //del by andy 2015/03/16
//    IThirdParty* p3rdParty = ThirdPartyFactory::Inst()->thirdParty();
//    if (p3rdParty)
//    {
//        p3rdParty->exitGame();
//    }
//    if (exitcount == 0) {
//        exitStatus =true;
//        exitcount =1;
//    }
//    else if(exitcount == 1)
//    {
//        exitStatus =true;
//        exitcount =2;
//    }
//    else
//    {
//        exitStatus =false;
//        exitcount =0;
//        delaytime =3.0f;
//    }

#ifndef TEST_BAIBAO
    PlatformHandler::getInstance()->exitApp();
#else
   CCDirector::sharedDirector()->end();
#endif
    //CCDirector::sharedDirector()->end();
}

void IntroLayer::onEnterTransitionDidFinish() {
//    wheelIdleAnimation();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void IntroLayer::onEnter()
{
//    Sound::Instance()->stopMusic();
    
    setTouchMode(kCCTouchesOneByOne);
    
	CCLayer::onEnter();
    Sound::Instance()->playMusic("BGMusic0.ogg");
    
    //add fishes
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Fish1.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Fish2.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Fish3.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Fish4.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Fish5.plist");
    
    CConfig::sharedConfig()->loadTask("config/TaskCfg.csv");
    
    CCParticleSystemQuad *emitter = CCParticleSystemQuad::create("Particle/qipao.plist");
    addChild(emitter,1);
    
    schedule(schedule_selector(IntroLayer::playSmallQipao), 8.0f, 10, 0.1f);
}


void IntroLayer::playSmallQipao()
{
    CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("Particle/qipaom.plist");
    emitter1->setPositionX(emitter1->getPositionX()+CCDirector::sharedDirector()->getWinSize().width*7/10);
    emitter1->setAutoRemoveOnFinish(true);
    addChild(emitter1,1);
    
}


void IntroLayer::onExit()
{
    
	CCLayer::onExit();
//     removeFromParentAndCleanup(true);
}



void IntroLayer::wheelIdleAnimation() {
    
//    int rotAngleCW = - (rand() % 2 + 1 )* 360;
//    
//    //转盘动画
//    CCRotateBy *rotByCW4Board = CCRotateBy::create(60, rotAngleCW);
//    CCSequence *seq4Board = CCSequence::create( rotByCW4Board->reverse(),rotByCW4Board, NULL);
//    CCRepeatForever *foreverForBoard = CCRepeatForever::create(seq4Board);
//    cb_spWheel->runAction(foreverForBoard);

    
}
void IntroLayer::onFeedback(CCObject *pSender)
{
    int tag = ((CCMenuItem*)pSender)->getTag();
    switch (tag) {
        case 1:
        {
            if (this->getChildByTag(1) && this->getChildByTag(1)->isVisible()) {
                return ;
            }
#ifndef TEST_BAIBAO
            PlatformHandler::getInstance()->openFeedback();
#else
            DF_LOG("IntroLayer::onFeedback");
#endif
        }
            break;
        case 2:
        {
            if (this->getChildByTag(1) && this->getChildByTag(1)->isVisible()) {
                return ;
            }
            if (this->getChildByTag(1)) {
                this->getChildByTag(1)->setVisible(true);
                
            }
            DF_LOG("IntroLayer::open");
        }
            break;
        case 3:
        {
            if (this->getChildByTag(1)) {
                this->getChildByTag(1)->setVisible(false);
                
            }
            DF_LOG("IntroLayer::close");
        }
            break;
        case 4:
        {
#ifndef TEST_BAIBAO
            PlatformHandler::getInstance()->moreGame();
#else
            DF_LOG("IntroLayer::onFeedback");
#endif
            DF_LOG("IntroLayer::moregame");
            
        }
            break;
        default:
            break;
    }

}
void IntroLayer::onFastStart(CCObject *pSender)
{
    if (this->getChildByTag(1) && this->getChildByTag(1)->isVisible()) {
        return ;
    }
    setKeypadEnabled(false);
    sp_loading->setVisible(true);
    cb_menuActions->setVisible(false);
    if (pSender)
    {
        GameData::getSharedGameData()->setGameType(GameType_Normal);
    }
    Sound::Instance()->playEffect("btn.mp3");
//    cb_spWheel->stopAllActions();
    
//    CCRotateBy *rot = CCRotateBy::create(2, 360*6);
//    CCEaseSineIn *easeRot = CCEaseSineIn::create(rot);
    
//    CCFiniteTimeAction *replaceScene = CCCallFunc::create(this, callfunc_selector(IntroLayer::replaceScene));
//    CCSpawn *spawn = CCSpawn::create(easeRot, replaceScene, NULL);
    
//    cb_spWheel->runAction(spawn );
    scheduleOnce(schedule_selector(IntroLayer::replaceScene), 0.1);
//    replaceScene();
}

//void IntroLayer::onSound(cocos2d::CCObject *pSender)
//{
//    Sound::Instance()->switchSound();
//    if (Sound::Instance()->getIsCloseSound() == false)
//    {
//        menuSound_->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soundno.png"));
//    } else {
//        menuSound_->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soundoff.png"));
//    }
//    Sound::Instance()->playEffect("btn.mp3");
//}

#define FadeIntoGameLayer (2)
void IntroLayer::replaceScene() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(FadeIntoGameLayer, GameLayer::scene(), ccBLACK));

}

void IntroLayer::setButtonStatus( bool b) {
    menuFastEnter_->setVisible(b);
//    menuSound_->setVisible(b);
//    menuInfo_->setVisible(b);
//    menuScene_->setVisible(b);
//    cb_spWheel->setVisible(b);
    
//    if (!b) {
//        cb_spWheel->pauseSchedulerAndActions();
//        
//    } else {
//        cb_spWheel->resumeSchedulerAndActions();
//    }

    
}

//void IntroLayer::onAboutExit(CCObject *pSender)
//{
//    ly_about->setVisible(false);
//    Sound::Instance()->playEffect("btn.mp3");
//}

//void IntroLayer::onSeaMonsterCallback(cocos2d::CCObject *pSender)
//{
//    cb_menuActions->setEnabled(false);
//    updateSeaMonsterTimes();
//    ly_seamonster->setVisible(true);
//    Sound::Instance()->playEffect("btn.mp3");
//}

//void IntroLayer::onSeaMonsterCloseCallback(cocos2d::CCObject *pSender)
//{
//    cb_menuActions->setEnabled(true);
//    ly_seamonster->setVisible(false);
//    Sound::Instance()->playEffect("btn.mp3");
//}

//void IntroLayer::onSeaMonsterStartCallback(cocos2d::CCObject *pSender)
//{
//    // 根据次数判断是否能进入游戏
//    switch ((GameType)((CCNode*)pSender)->getTag()) {
//        case GameType_Normal:
//            GameData::getSharedGameData()->setGameType(GameType_Normal);
//            break;
//        case GameType_SeaMonster_Normal:
//        {
//            // 判断有无次数
//            GameTimesRecord* pRecord = GameData::getSharedGameData()->getGameRecordInfo(GameRecordType_SeaMonster, GameData::getSharedGameData()->genDayStamp());
//            if (!pRecord || pRecord->times < 3)
//            {
//                int pTimes = 0;
//                if (pRecord)
//                {
//                    pTimes = pRecord->times;
//                }
//                vector<int>* pExt = NULL;
//                if (pRecord)
//                {
//                    pExt = pRecord->ext;
//                }
//                if (!pExt)
//                {
//                    pExt = new vector<int>();
//                }
//                GameData::getSharedGameData()->saveGameRecordInfo(GameRecordType_SeaMonster, GameData::getSharedGameData()->genDayStamp(), pTimes + 1, pExt);
//                GameData::getSharedGameData()->setGameType((GameType)((CCNode*)pSender)->getTag());
//                updateSeaMonsterTimes();
//                onFastStart(NULL);
//            }
//            else
//            {
//                // TODO提示 数量达到3次
//                GameData::getSharedGameData()->setGameType((GameType)((CCNode*)pSender)->getTag());
//                updateSeaMonsterTimes();
//                onFastStart(NULL);
//            }
//            break;
//        }
//        case GameType_SeaMonster_Difficulty:
//        {
//            GameDiamond* pDiamond = GameData::getSharedGameData()->getGameDiamond(Diamond_BlackPearl);
//            if (pDiamond->m_cnt > 0)
//            {
//                pDiamond->m_cnt -= 1;
//                GameData::getSharedGameData()->saveGameDiamond(Diamond_BlackPearl);
//                GameData::getSharedGameData()->setGameType((GameType)((CCNode*)pSender)->getTag());
//                updateSeaMonsterTimes();
//                onFastStart(NULL);
//            }
//            else
//            {
//                // TODO提示 黑珍珠不足
//                GameData::getSharedGameData()->saveGameDiamond(Diamond_BlackPearl);
//                GameData::getSharedGameData()->setGameType((GameType)((CCNode*)pSender)->getTag());
//                updateSeaMonsterTimes();
//                onFastStart(NULL);
//            }
//            break;
//        }
//        default:
//            break;
//    }
//}

//void IntroLayer::updateSeaMonsterTimes()
//{
//    // update time
//    char achTemp[32] = {0};
//    bzero(achTemp, sizeof(achTemp));
//    GameTimesRecord* pRecord = GameData::getSharedGameData()->getGameRecordInfo(GameRecordType_SeaMonster, GameData::getSharedGameData()->genDayStamp());
//    int pNormalTimes = 3;
//    if (pRecord)
//    {
//        pNormalTimes = 3 - pRecord->times;
//    }
//    pNormalTimes = pNormalTimes > 0 ? pNormalTimes : 0;
//    sprintf(achTemp, "%d", pNormalTimes);
//    bmf_normalTimes->setString(achTemp);
//    if (pNormalTimes <= 0)
//    {
//        //TODO true - > false
//        m_pMiiSeaMonsterNormal->setEnabled(true);
//    }
//    else
//    {
//        m_pMiiSeaMonsterNormal->setEnabled(true);
//    }
//
//    GameDiamond* pBlackPearl = GameData::getSharedGameData()->getGameDiamond(Diamond_BlackPearl);
//    int pDiffcultyTimes = 0;
//    if (pBlackPearl)
//    {
//        pDiffcultyTimes = pBlackPearl->m_cnt;
//    }
//    sprintf(achTemp, "%d", pDiffcultyTimes);
//    bmf_difficultyTimes->setString(achTemp);
//    if (pDiffcultyTimes <= 0)
//    {
//        m_pMiiSeaMonsterDiffculty->setEnabled(true);
//    }
//    else
//    {
//        m_pMiiSeaMonsterDiffculty->setEnabled(true);
//    }
//}

void IntroLayer::updateFish()
{
/*
    Fish::FishType _ft[] = {Fish::FISH_XIAOGUANGYU,Fish::FISH_XIAOCAOYU,Fish::FISH_XIAOFEIYU};
    Fish::FishType ft = _ft[arc4random()%3];
    CCArray *p = FishGroup::createFishGroup((GameLayer*)this, (arc4random()%2)?FishGroup::FishGroupRand:FishGroup::FishGroupLine,ft);
        
    for(int x=0; x < p->count();x++){
        Fish *pf = (Fish*)(p->objectAtIndex(x));
        sp_bg->getParent()->addChild(pf,-1);
        pf->goFish();
    }
 */
}

void IntroLayer::removeFish(Fish * pf)
{
    
}
