//
//  FlipCardBonusLayer.cpp
//  fish
//
//  
//
//http://blog.csdn.net/wayne5ning/article/details/8713262

#include "FlipCardBonusLayer.h"
#include "Sound.h"
#include "Helper.h"
#include "GameData.h"


using namespace cocos2d;

#define DEFAULT_BASE_TAG (1000)

FlipCardBonusLayer::FlipCardBonusLayer()
:CCLayer()
{
    cb_menuCards = NULL;
    cb_menuStart = NULL;
    
    cb_layerCardsContainer = NULL;
    cb_layerContainer = NULL;
    cb_layerBegin = NULL;
    cb_layerEnd = NULL;
    cb_layerCards = NULL;
    
    cb_lblCurScore = NULL;
    cb_lblScoreTip = NULL;
    cb_lblEndScoreFG = NULL;
    cb_lblEndScoreBG = NULL;

    spClickPoint = NULL;
}


FlipCardBonusLayer::~FlipCardBonusLayer()
{

    CC_SAFE_RELEASE(cb_menuCards);
    CC_SAFE_RELEASE(cb_menuStart);
    
    CC_SAFE_RELEASE(cb_layerCardsContainer);
    CC_SAFE_RELEASE(cb_layerContainer);
    CC_SAFE_RELEASE(cb_layerBegin);
    CC_SAFE_RELEASE(cb_layerEnd);
    CC_SAFE_RELEASE(cb_layerCards);
    
    CC_SAFE_RELEASE(cb_lblEndScoreFG);
    CC_SAFE_RELEASE(cb_lblEndScoreBG);
    CC_SAFE_RELEASE(cb_lblCurScore);
    CC_SAFE_RELEASE(cb_lblScoreTip);

    CC_SAFE_RELEASE(spClickPoint);
    
    
}


CCScene* FlipCardBonusLayer::scene( BonusTrigger trigger)
{
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("FlipCardBonusLayer", FlipCardBonusLayerBuilderLoad::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ios/ccbResources/FlipCardBonusLayer.ccbi", sc);
	
    ccbReader->release();
    
	if (node) {
        sc->addChild(node);
        FlipCardBonusLayer *layer = (FlipCardBonusLayer*)node;
        layer->manager = FlipCardBonusManager::sharedFlipCardBonusManager();
        layer->manager->setTrigger(trigger);
    }
    
	return sc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void FlipCardBonusLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{

}

bool FlipCardBonusLayer::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuCards", CCMenu*, this->cb_menuCards);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuStart", CCMenu*, this->cb_menuStart);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerCardsContainer", CCLayer*, this->cb_layerCardsContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerContainer", CCLayer*, this->cb_layerContainer);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerBegin", CCLayer*, this->cb_layerBegin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerEnd", CCLayer*, this->cb_layerEnd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_layerCards", CCLayer*, this->cb_layerCards);
    
    

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblEndScoreFG", CCLabelTTF*, this->cb_lblEndScoreFG);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblEndScoreBG", CCLabelTTF*, this->cb_lblEndScoreBG);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblCurScore", CCLabelTTF*, this->cb_lblCurScore);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblScoreTip", CCLabelTTF*, this->cb_lblScoreTip);
    
    
	return true;
}




SEL_MenuHandler FlipCardBonusLayer::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCardClicked", FlipCardBonusLayer::onCardClicked);
 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStartClicked", FlipCardBonusLayer::onStartClicked);
    
    
	return NULL;
}

SEL_CCControlHandler FlipCardBonusLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void FlipCardBonusLayer::update(float dt)
{
}

bool FlipCardBonusLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
//    isTouchInStartMenu = cb_menuStart->ccTouchBegan(pTouch, pEvent);
//
//    if (!isTouchInStartMenu &&!isBeginLayerShow) {
//        isTouchInCardMenu =  cb_menuCards->ccTouchBegan(pTouch, pEvent);
//    }
//
//    isTouchInCardMenu =  cb_menuCards->ccTouchBegan(pTouch, pEvent);
    

    
    if (isBeginLayerShow) {
        isTouchInStartMenu = cb_menuStart->ccTouchBegan(pTouch, pEvent);
        
    } else {
        isTouchInCardMenu =  cb_menuCards->ccTouchBegan(pTouch, pEvent);
    }
    return true;
}

void FlipCardBonusLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInStartMenu) {
        cb_menuStart->ccTouchMoved(pTouch, pEvent);
    }
    if (isTouchInCardMenu) {
        cb_menuCards->ccTouchMoved(pTouch, pEvent);
    }
    
}
void FlipCardBonusLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

    if (isTouchInStartMenu) {
        isTouchInStartMenu = false;
        cb_menuStart->ccTouchEnded(pTouch, pEvent);
    }
    
    if (isTouchInCardMenu) {
        isTouchInCardMenu = false;
        cb_menuCards->ccTouchEnded(pTouch, pEvent);
    }
    
}
void FlipCardBonusLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInStartMenu) {
        cb_menuStart->ccTouchCancelled(pTouch, pEvent);
        isTouchInStartMenu = false;
    }
    
    if (isTouchInCardMenu) {
        cb_menuCards->ccTouchCancelled(pTouch, pEvent);
        isTouchInCardMenu = false;
    }
    
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void FlipCardBonusLayer::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPrioritySubStoreLayer*2, true);
    fillUIElements();
    manager->generate();
    
	CCLayer::onEnter();
    
//    CCMoveTo *moveToY = CCMoveTo::create(0.75, ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
//    cb_layerContainer->runAction(moveToY);

}

void FlipCardBonusLayer::onExit()
{
    
	CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
}


void FlipCardBonusLayer::onCardClicked(CCObject *pSender) {

    
    CCMenuItemImage *btn = (CCMenuItemImage*)pSender;
    if (btn == NULL) {
        return;
    }
    
    flip(btn);
    
}

void FlipCardBonusLayer::onStartClicked(CCObject *pSender) {
    cb_menuCards->setTouchEnabled(true);
    isBeginLayerShow = false;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo *moveToY = CCMoveTo::create(0.75, ccp(size.width/2,
                                                   size.height/2 + size.height));
    cb_layerBegin->runAction(moveToY);
}


//执行翻牌逻辑
void FlipCardBonusLayer::flip(CCMenuItemImage *btn ) {
    
    //  btn->setNormalSpriteFrame(<#cocos2d::CCSpriteFrame *frame#>)
    int index = btn->getTag();
    
    index -= DEFAULT_BASE_TAG;
    
    if ( index < 0 || index >= TOTAL_CARDS) {
        return;
    }
    
    //已经翻牌过,或者游戏已结束
    if (manager->hadFliped(index) || manager->isGameOver()) {
        return;
    }
    
    //翻到bonus牌
    if (manager->isBonus(index)) {
        manager->setGameOver(true);
        
    //翻到2张一样的牌
    } else if ( manager->isSameAsPrevCard(index)) {
        manager->setGameOver(true);
    }
    
    //执行反转动画等操作
    doFlipHelper( btn );
    
    manager->flip(index);
    
//    removeChildByTag(99);
//    
//    NumSprite* sp_num = NumSprite::create(manager->coins(), GameNumberGameLayerGold);
//    sp_num->setPosition(cb_lblCurScore->getPosition());
//    sp_num->setScale(/*cb_lblCurScore->getScale()*/0.5);
//    addChild(sp_num,cb_lblCurScore->getZOrder(),99);
    
    cb_lblCurScore->removeAllChildren();
    CCSize s = cb_lblCurScore->getContentSize();
    NumSprite* sp_num = NumSprite::create(manager->coins(), GameNumberGameLayerGold);
    sp_num->setPosition(ccp(s.width/2,s.height/2));
    sp_num->setAnchorPoint(ccp(0.5,0.5));
//    sp_num->setScale(0.5);
    cb_lblCurScore->addChild(sp_num,1);

    //cb_lblCurScore->setString(CCString::createWithFormat("%d", manager->coins())->getCString());
    if ( manager->isGameOver()) {
        cb_lblEndScoreFG->getParent()->removeChildByTag(124);
        NumSprite* sp_num = NumSprite::create(manager->coins(), GameNumberSotreUp);
        sp_num->setPosition(cb_lblEndScoreFG->getPosition());
        sp_num->setScale(0.8/*cb_lblEndScoreFG->getScale()*/);
        cb_lblEndScoreFG->getParent()->addChild(sp_num,cb_lblEndScoreFG->getZOrder(),124);
        //cb_lblEndScoreFG->setString(CCString::createWithFormat("%d",manager->coins())->getCString());
        //cb_lblEndScoreFG->setColor(FONT_COLOR);
        //cb_lblEndScoreBG->setString(cb_lblEndScoreFG->getString());
        
        CCDelayTime *delay1 = CCDelayTime::create(0.5f);
        CCShow *show = CCShow::create();
        CCFadeIn *fadeIn = CCFadeIn::create(0.25);
        CCScaleTo *unZip = CCScaleTo::create(0.25, 1);
        CCDelayTime *delay2 = CCDelayTime::create(2.f);


        
        CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(FlipCardBonusLayer::removeSelf));
        CCSequence *seq = CCSequence::create(delay1, show,fadeIn, unZip, delay2, callFunc, NULL);

        cb_layerEnd->runAction(seq);
        
        GameData::getSharedGameData()->changeScore( manager->coins() );
        
        //解冻
        bool unFreeze = true;
        CCNotificationCenter::sharedNotificationCenter()->postNotification(kFlipCardBonusNotification, (CCObject*)unFreeze);
        
    }
    
}


void FlipCardBonusLayer::removeSelf() {
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo *moveTo = CCMoveTo::create(0.5f, ccp(size.width/2, size.height + size.height/2));
    
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(FlipCardBonusLayer::removeFromParent));
    
    CCSequence *seq = CCSequence::create(moveTo,callFunc, NULL);

    cb_layerContainer->runAction(seq);
    
   // removeFromParentAndCleanup(true);
}


void FlipCardBonusLayer::fillUIElements() {
    
    removeChildByTag(123);
    
    NumSprite* sp_num = NumSprite::create(manager->base(), GameNumberSotreUp);
    sp_num->setPosition(cb_lblScoreTip->getPosition());
    sp_num->setScale(0.8);
    cb_lblScoreTip->getParent()->addChild(sp_num,cb_lblScoreTip->getZOrder(),123);
    //cb_lblCurScore->setFontName("迷你简胖娃");
  //  cb_lblCurScore->setColor(FONT_COLOR);

    //cb_lblScoreTip->setFontName(cb_lblCurScore->getFontName());
    //cb_lblScoreTip->setString(CCString::createWithFormat("%d", manager->base())->getCString());
   // cb_lblScoreTip->setColor(cb_lblCurScore->getColor());
    
    //cb_lblEndScoreFG->setFontName(cb_lblCurScore->getFontName());
    //cb_lblEndScoreFG->setColor(cb_lblCurScore->getColor());
    
    //cb_lblEndScoreBG->setFontName(cb_lblCurScore->getFontName());
    cb_menuCards->setTouchEnabled(false);
    isBeginLayerShow = true;
    

}


#define FLIP_CARD_EFFECT_ANIMATION_FRAME_NUM (6)
#define FLIP_CARD_EFFECT_ANIMATION_TIME (1.0/(FLIP_CARD_EFFECT_ANIMATION_FRAME_NUM*3))

#define FLIP_CARD_BONUS_ANIMATION_FRAME_NUM (6)
#define FLIP_CARD_BONUS_ANIMATION_TIME (1.0/FLIP_CARD_BONUS_ANIMATION_FRAME_NUM)


#define FLIP_CARD_EFFECT_SOUND (1)
#define FLIP_CARD_BONUS_SOUND (2)


void FlipCardBonusLayer::doFlipHelper(CCMenuItemImage *btn) {
    

    int index = btn->getTag() - DEFAULT_BASE_TAG;
    const char *imageName = manager->cardsImageName( index );
    
    TUint32 soundTag = 0;
    
    //点击动画
    if (manager->isBonus(index)) {
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("flipCardBonusLayer.plist");
        CCArray *arrImages = CCArray::createWithCapacity(FLIP_CARD_BONUS_ANIMATION_FRAME_NUM);
        
        for (int i = 0; i < FLIP_CARD_BONUS_ANIMATION_FRAME_NUM; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("flipCardBonus_%d.png", i)->getCString());
            if(frame != NULL) {
                arrImages->addObject(frame);
            }
        }
        
        CCAnimate  *animBonus = CCAnimate::create( CCAnimation::createWithSpriteFrames(arrImages, FLIP_CARD_BONUS_ANIMATION_TIME));
        CCSequence *seqBonus = CCSequence::create( CCShow::create(), animBonus, CCHide::create(), NULL);
        
        soundTag = FLIP_CARD_BONUS_SOUND;
        
        CCCallFuncND *bonusSoundFunc = CCCallFuncND::create((CCObject*)this, callfuncND_selector(FlipCardBonusLayer::playSound), (void*)soundTag);
        CCSpawn *spawn = CCSpawn::create(seqBonus, bonusSoundFunc, NULL);
        
        CCSprite   *spBonus = CCSprite::createWithSpriteFrameName("flipCardBonus_0.png");
        cb_layerCardsContainer->addChild(spBonus);
        
        spBonus->setPosition(btn->getPosition());
        spBonus->runAction(spawn);


    } else {
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("flipCardBonusLayer.plist");
        CCArray *arrImages = CCArray::createWithCapacity(FLIP_CARD_EFFECT_ANIMATION_FRAME_NUM);
        
        for (int i = 0; i < FLIP_CARD_EFFECT_ANIMATION_FRAME_NUM; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("flipCardEffect_%d.png", i)->getCString());
            if(frame != NULL) {
                arrImages->addObject(frame);
            }
            
        }
        
        soundTag = FLIP_CARD_EFFECT_SOUND;
        
        CCAnimate *animEffect = CCAnimate::create( CCAnimation::createWithSpriteFrames(arrImages, FLIP_CARD_EFFECT_ANIMATION_TIME));
        CCSequence *seqEffect = CCSequence::create( CCShow::create(), animEffect, CCHide::create(), NULL);
        
        CCCallFuncND *effectSoundFunc = CCCallFuncND::create((CCObject*)this, callfuncND_selector(FlipCardBonusLayer::playSound), (void*)soundTag);
        
        CCSpawn *spawnEffect = CCSpawn::create(seqEffect, effectSoundFunc, NULL);
        
        if (spClickPoint == NULL ) {
            spClickPoint = CCSprite::createWithSpriteFrameName("flipCardEffect_0.png");
            spClickPoint->retain();
            
            cb_layerCardsContainer->addChild(spClickPoint);
        }
        
        spClickPoint->setPosition(btn->getPosition());
        spClickPoint->runAction(spawnEffect);

        
        
        //执行高亮本次翻牌获得金币动画
        runHighlightAnimation(manager->base(), btn->getPosition());

    } // end of if (manager->isBonus(index)) {

    
    //切换成正式图片
    btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName));

    
    //翻转
    float scaleTime = 0.2f;
    float scale = btn->getScale();
    CCScaleTo *scaleToNegX = CCScaleTo::create(scaleTime, -scale,scale);
    CCScaleTo *scaleToPosX = CCScaleTo::create(0.0, scale,scale);
    
    CCSequence *seq = CCSequence::create(scaleToNegX, scaleToPosX, NULL);
    btn->runAction(seq);
    
}


#if 0
void FlipCardBonusLayer::runHighlightAnimation( CCLabelTTF *lbl) {
    if (lbl == NULL) {
        return;
        
    }
    
    
    CCShow *show = CCShow::create();
    CCFadeIn *fadeIn = CCFadeIn::create(0.25);
    
    CCScaleTo *unZip = CCScaleTo::create(0.25, 1.5);
    CCDelayTime *delay = CCDelayTime::create(1);
    
    CCFadeOut *fadeOut = CCFadeOut::create(0.25);
    CCHide *hide = CCHide::create();
    CCScaleTo *zip = CCScaleTo::create(0.25, 0.8);
    
    CCSpawn *spawn1 = CCSpawn::create(unZip, fadeIn, NULL);
    CCSpawn *spawn2 = CCSpawn::create(fadeOut, zip, NULL);
    
    CCFiniteTimeAction *seq = CCSequence::create( show, spawn1,  delay,  spawn2, hide, NULL);
    //         CCFiniteTimeAction *seq = CCSequence::create(show, delay,  hide, NULL);
    
    lbl->runAction(seq);
}
#else
void FlipCardBonusLayer::runHighlightAnimation( const int num, const CCPoint &pos) {
    NumSprite *p = NumSprite::create(num);
    p->setPosition(pos);
    p->setOpacity(0);
    p->setScale(0.75);
    cb_layerCardsContainer->addChild(p);
    //CCFadeIn *f1 = CCFadeIn::create(2);
    CCSpawn * sp1 = CCSpawn::createWithTwoActions(CCFadeIn::create(0.15), CCMoveBy::create(0.75, ccp(0,100)));
    CCSpawn * sp2 = CCSpawn::createWithTwoActions(CCFadeOut::create(0.15), CCMoveBy::create(0.75, ccp(0,100)));
    
    CCFiniteTimeAction *callFunc = CCCallFunc::create(p, callfunc_selector(NumSprite::removeFromParent));
    p->runAction(CCSequence::create(sp1,sp2,callFunc,NULL));


}
    
#endif

void FlipCardBonusLayer::playSound(CCNode* sender, void* data) {
    
    TUint8 index = (TUint8)(TUint32)data;
    
    if (index == FLIP_CARD_BONUS_SOUND) {
        Sound::Instance()->playEffect("bonus.mp3");
        
    } else {
        Sound::Instance()->playEffect("ffcoin.mp3");
    }

}


