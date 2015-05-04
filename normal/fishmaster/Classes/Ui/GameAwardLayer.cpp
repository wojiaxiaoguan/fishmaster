
#include "GameAwardLayer.h"
using namespace cocos2d;


CCB_CLASS_NAME1:: CCB_CLASS_NAME1 ()
:CCLayer()
{
    sp_desp = NULL;
}

CCB_CLASS_NAME1:: ~ CCB_CLASS_NAME1 ()
{
    CC_SAFE_RELEASE(sp_desp);
}

CCScene* CCB_CLASS_NAME1::scene()
{
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader(XStr(CCB_CLASS_NAME1), XConn(CCB_CLASS_NAME1, BuilderLoad)::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ios/ccbResources/" XStr(CCB_CLASS_NAME1) ".ccbi", sc);
    
	
    ccbReader->release();
    
	if (node) {
        sc->addChild(node,1,DefaultLayerTag);
    }
    
	return sc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void CCB_CLASS_NAME1 ::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStore, true);
    fillUIElements();
    scheduleOnce(schedule_selector(CCB_CLASS_NAME1::exit), 2.5f);
}

bool CCB_CLASS_NAME1 ::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_desp", CCSprite*, this->sp_desp);
	return true;
}

SEL_MenuHandler CCB_CLASS_NAME1::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler CCB_CLASS_NAME1::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void CCB_CLASS_NAME1::onEnter()
{
    
	CCLayer::onEnter();
    
}

void CCB_CLASS_NAME1::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
    
}


bool CCB_CLASS_NAME1::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //return cb_menuChests->ccTouchBegan(pTouch, pEvent);
}

void CCB_CLASS_NAME1::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //cb_menuChests->ccTouchMoved(pTouch, pEvent);
}
void CCB_CLASS_NAME1::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    //cb_menuChests->ccTouchEnded(pTouch, pEvent);
}
void CCB_CLASS_NAME1::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    //cb_menuChests->ccTouchCancelled(pTouch, pEvent);
}


//填充ui元素
void CCB_CLASS_NAME1::fillUIElements() {
    
}


void CCB_CLASS_NAME1::setAwardType(GameAwardType aType)
{
    CCSpriteFrame* spFrame = NULL;
    spFrame = FishUtils::awardSpriteFrame(aType);
    if (spFrame != NULL) {
        //edit by andy 2015-04-14
        ((CCSprite*)sp_desp->getChildByTag(1))->setDisplayFrame(spFrame);
    }
 }


void CCB_CLASS_NAME1::exit()
{
    removeFromParent();
}

