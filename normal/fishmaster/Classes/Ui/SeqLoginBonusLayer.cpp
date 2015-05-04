//
//  SeqLoginBonusLayer.cpp
//  fish
//
//

#include "SeqLoginBonusLayer.h"
#include "GameLayer.h"
#include "Helper.h"
#include "FishUtils.h"
#include "Sound.h"
using namespace cocos2d;

#define DEFAULT_BASE_TAG (1000)

#define CHEST_UNLOCKED_IMAGE ("chestUnlocked.png")
#define CHEST_LOCKED_IMAGE   ("chestLocked.png")
#define GEM_UNLOCKED_IMAGE ("gemUnLocked.png")
#define PEARL_UNLOCKED_IMAGE ("pearlUnLocked.png")

SeqLoginBonusLayer::SeqLoginBonusLayer()
:CCLayer()
{
    cb_menuChests = NULL;
    cb_spCanOpenTip = NULL;
    
//    for (int i = 0; i < MAX_SEQ_LOGIN_DAYS; i++) {
//        cb_lblDayKeys[i] = NULL;
//        cb_lblDayValues[i] = NULL;
//    }
    
    cb_lblFooter = NULL;
    cb_layerRoot = NULL;
    
}


SeqLoginBonusLayer::~SeqLoginBonusLayer()
{
    
    CC_SAFE_RELEASE(cb_menuChests);
    CC_SAFE_RELEASE(cb_spCanOpenTip);
    
//    for (int i = 0; i < MAX_SEQ_LOGIN_DAYS; i++) {
//        CC_SAFE_RELEASE(cb_lblDayKeys[i]);
//        CC_SAFE_RELEASE(cb_lblDayValues[i]);
//    }

    CC_SAFE_RELEASE(cb_lblFooter);
    CC_SAFE_RELEASE(cb_layerRoot);
    
}

CCScene* SeqLoginBonusLayer::scene()
{
    
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("SeqLoginBonusLayer", SeqLoginBonusLayerBuilderLoad::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ios/ccbResources/SeqLoginBonusLayer.ccbi", sc);
	
    ccbReader->release();
    
	if (node) {
        sc->addChild(node);
        
    }
    
	return sc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void SeqLoginBonusLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStore, true);
    manager = SeqLoginBonusManager::sharedSeqLoginBonusManager();
    fillUIElements();

}

#define DAY_KEY_BASE_STR ("cb_lblDayKey")
#define DAY_VAL_BASE_STR ("cb_lblDayValue")
bool SeqLoginBonusLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuChests", CCMenu*, this->cb_menuChests);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_spCanOpenTip", CCSprite*, this->cb_spCanOpenTip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblFooter", CCLabelTTF*, this->cb_lblFooter);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerRoot", CCLayer*, this->cb_layerRoot);
    
//    for (int i = 0; i < MAX_SEQ_LOGIN_DAYS; i++) {
//        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, CCString::createWithFormat("%s%d", DAY_KEY_BASE_STR, i+1)->getCString(), CCLabelTTF*, this->cb_lblDayKeys[i]);
//        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, CCString::createWithFormat("%s%d", DAY_VAL_BASE_STR, i+1)->getCString(), CCLabelTTF*, this->cb_lblDayValues[i]);
//    }
    
	return true;
}

SEL_MenuHandler SeqLoginBonusLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChestClicked", SeqLoginBonusLayer::onChestClicked);
 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onExitClicked", SeqLoginBonusLayer::onExitClicked);
    
    
	return NULL;
}

SEL_CCControlHandler SeqLoginBonusLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void SeqLoginBonusLayer::onEnter()
{
    
	CCLayer::onEnter();
    
}

void SeqLoginBonusLayer::onEnterTransitionDidFinish() {
    CCLayer::onEnterTransitionDidFinish();
    
  //  cb_layerRoot->runAction(CCScaleTo::create(5.f, 1));
}
void SeqLoginBonusLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
    
}

bool SeqLoginBonusLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    
    isTouchInMenu =  cb_menuChests->ccTouchBegan(pTouch, pEvent);
    return true;
}

void SeqLoginBonusLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuChests->ccTouchMoved(pTouch, pEvent);
    }
    
}
void SeqLoginBonusLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        isTouchInMenu = false;
        cb_menuChests->ccTouchEnded(pTouch, pEvent);
    }
    
}
void SeqLoginBonusLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuChests->ccTouchCancelled(pTouch, pEvent);
        isTouchInMenu = false;
    }
    
}



void SeqLoginBonusLayer::onChestClicked(CCObject *pSender) {

    CCMenuItemImage *btn = (CCMenuItemImage*)pSender;
    if (btn == NULL) {
        return;
    }
    
    TInt32 index = btn->getTag();
    index -= DEFAULT_BASE_TAG;
    
    BonusStatus status = manager->bonusStatus(index);
    if (status != StatusCanUnlock) {
        return;
    }
    manager->open(index);
    
    int coins = 0;
    char *unlockImage = NULL;
    if ( index <= 4) {
        Sound::Instance()->playEffect("ffcoin.mp3");
        coins = manager->coins(index);
        coinAnimation( coins, btn->getPosition());
        unlockImage = CHEST_UNLOCKED_IMAGE;
        GameData::getSharedGameData()->changeScore(coins);
    } else {
        Sound::Instance()->playEffect("addYB.mp3");
        if (index == 5) {
            unlockImage = GEM_UNLOCKED_IMAGE;
        } else {
             unlockImage = PEARL_UNLOCKED_IMAGE;
        }
        DiamondType diamond = manager->diamond((SeqLoginDay)index);
        diamondAnimation(diamond, btn->getPosition());
        GameData::getSharedGameData()->addGameDiamond(diamond, 1);
    }
    
    //显示为已经开启过的界面
    btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(unlockImage));
    GameData::getSharedGameData()->setTodayLoginCount(1);
    schedule(schedule_selector(SeqLoginBonusLayer::replaceScene), 2.f);
    
}

void SeqLoginBonusLayer::replaceScene(float ct)
{
    unschedule(schedule_selector(SeqLoginBonusLayer::replaceScene));
    removeSelf();
}

void SeqLoginBonusLayer::onExitClicked(CCObject *pSender) {
}

//填充ui元素
void SeqLoginBonusLayer::fillUIElements() {
    
    const char * dayKeys[MAX_SEQ_LOGIN_DAYS] = {"一", "二", "三", "四", "五", "六", "七"};
    const char * dayValues[MAX_SEQ_LOGIN_DAYS] = {"5000", "8000", "12000", "20000", "30000", "随机宝石", "珍珠"};
    CCMenuItemImage *btn = NULL;
    
    for (int i = 0; i < MAX_SEQ_LOGIN_DAYS; i++) {
//button
        btn = (CCMenuItemImage*)cb_menuChests->getChildByTag(i + DEFAULT_BASE_TAG);
        if (btn == NULL) {
            continue;
        }
        
        BonusStatus status =  manager->bonusStatus(i);
        
        if (status == StatusUnlocked) {
            btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CHEST_UNLOCKED_IMAGE));
            
        } else if (status == StatusCanUnlock ) {
            cb_spCanOpenTip->setPosition(btn->getPosition());
            
            CCScaleTo *zipTo = CCScaleTo::create(0.75, 1);
            CCScaleTo *unzipTo = CCScaleTo::create(0.75, 1.25);
            CCSequence *seqZip = CCSequence::create(CCShow::create(), unzipTo, zipTo, NULL);
            
            CCFadeIn*fadeIn =CCFadeIn::create(0.75f);
            CCFadeOut *fadeOut = CCFadeOut::create(0.75f);
            
            CCSequence *seqFade = CCSequence::create(fadeIn, fadeOut, NULL);
            
            CCSpawn *spawn = CCSpawn::create(seqZip, seqFade, NULL);
            CCRepeatForever *forever = CCRepeatForever::create(spawn);
            
            cb_spCanOpenTip->runAction(forever);
        }
//title
//        cb_lblDayKeys[i]->setFontName("迷你简胖娃");
//        cb_lblDayKeys[i]->setFontSize(18);
//        cb_lblDayKeys[i]->setString(CCString::createWithFormat("第%s天", dayKeys[i])->getCString());

//bonus
//        cb_lblDayValues[i]->setFontName("迷你简胖娃");
//        //cb_lblDayValues[i]->setFontSize(20);
//        cb_lblDayValues[i]->setString(CCString::createWithFormat("%s", dayValues[i])->getCString());
    }
    
}


void SeqLoginBonusLayer::coinAnimation( const int num, const CCPoint &pos) {
    NumSprite *p = NumSprite::create(num);
    animationHelper(p, pos);
}

void SeqLoginBonusLayer::diamondAnimation( DiamondType aType, const CCPoint &pos) {
    //CCSpriteFrame   *spFrame = FishUtils::awardSpriteFrame((GameAwardType)aType);
    //edit by lqg 2015-04-14
    char* fileName = NULL;
    switch (aType) {
        case Diamond_Yellow:
            fileName = "abs4.png";
            break;
        case Diamond_Blue:
            fileName = "abs3.png";
            break;
        case Diamond_Green:
            fileName = "abs1.png";
            break;
        case Diamond_Red:
            fileName = "abs2.png";
            break;
        case Diamond_Pearl:
            fileName = "abs0.png";
            break;
        default:
            break;
    }
    
    CCSpriteFrame* spFrame = NULL;
    if (fileName != NULL) {
        spFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
    }
    
    if (spFrame == NULL) {
        return;
    }
    
    CCSprite *p = CCSprite::create();
    p->initWithSpriteFrame(spFrame);
    animationHelper(p, pos);
    
}
void SeqLoginBonusLayer::animationHelper( CCSprite *p, const CCPoint &pos) {
    if (p == NULL) {
        return;
    }
    
    p->setPosition(pos);
    p->setOpacity(0);
    p->setScale(0.75);
    cb_spCanOpenTip->getParent()->addChild(p);
    
    //CCFadeIn *f1 = CCFadeIn::create(2);
    CCSpawn * sp1 = CCSpawn::createWithTwoActions(CCFadeIn::create(0.15), CCMoveBy::create(0.75, ccp(0,100)));
    CCSpawn * sp2 = CCSpawn::createWithTwoActions(CCFadeOut::create(0.15), CCMoveBy::create(0.75, ccp(0,100)));
    
    CCFiniteTimeAction *removeSpriteFunc = CCCallFunc::create(p, callfunc_selector(NumSprite::removeFromParent));
//    CCFiniteTimeAction *removeSelfFunc = CCCallFunc::create(p, callfunc_selector(SeqLoginBonusLayer::removeSelf));
//    p->runAction(CCSequence::create(sp1, sp2, removeSpriteFunc, removeSelfFunc, NULL));
    p->runAction(CCSequence::create(sp1, sp2, removeSpriteFunc, NULL));
    
    
}

void SeqLoginBonusLayer::removeSelf() {

    CCScaleTo *scaleTo = CCScaleTo::create(0.5f, 0.f);
    CCFadeOut *fadeOut = CCFadeOut::create(0.5f);
    
    CCSpawn *spawn = CCSpawn::create(scaleTo, fadeOut, NULL);
    
    CCFiniteTimeAction *removeFunc = CCCallFunc::create(this, callfunc_selector(SeqLoginBonusLayer::removeFromParent));
    CCCallFunc *VipFunc = CCCallFunc::create(this, callfunc_selector(SeqLoginBonusLayer::isVipReward));
    
    CCSequence *seq = CCSequence::create(spawn, removeFunc,VipFunc, NULL);
    
  //  this ->runAction(seq);
    
    cb_layerRoot->runAction(seq);
    
}
void SeqLoginBonusLayer::isVipReward()
{
    GameData* pData = GameData::getSharedGameData();
    if (pData->getIsHaveVipCard()) {
        Sound::Instance()->playEffect("ffcoin.mp3");
        GameData::getSharedGameData()->changeScore(20000);
    }
}
