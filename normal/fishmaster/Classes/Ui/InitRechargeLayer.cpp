
#include "InitRechargeLayer.h"
#include "GameStore.h"

using namespace cocos2d;

CCB_CLASS_NAME:: CCB_CLASS_NAME ()
:CCLayer()
{
    cb_lblUnlockKey = NULL;
    
    cb_lblCoinVal = NULL;
    cb_lblPearlVal = NULL;
    cb_lblExpVal = NULL;
    cb_lblUnlockVal = NULL;
    
    cb_lblTip = NULL;
    
    cb_menuRecharge = NULL;
}

CCB_CLASS_NAME:: ~ CCB_CLASS_NAME ()
{
    CC_SAFE_RELEASE(cb_lblUnlockKey);
    
    CC_SAFE_RELEASE(cb_lblCoinVal);
    CC_SAFE_RELEASE(cb_lblPearlVal);
    CC_SAFE_RELEASE(cb_lblExpVal);
    CC_SAFE_RELEASE(cb_lblUnlockVal);
    
    CC_SAFE_RELEASE(cb_lblTip);
    
    CC_SAFE_RELEASE(cb_menuRecharge);
    


}


CCScene* CCB_CLASS_NAME::scene()
{
	CCScene *sc = CCScene::create();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader(XStr(CCB_CLASS_NAME), XConn(CCB_CLASS_NAME, BuilderLoad)::loader());
    
	CCBReader* ccbReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* node = ccbReader->readNodeGraphFromFile("ios/ccbResources/" XStr(CCB_CLASS_NAME ) ".ccbi", sc);
    
    ccbReader->release();
    
	if (node) {
        sc->addChild(node);
    }
    
	return sc;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void CCB_CLASS_NAME ::onNodeLoaded(CCNode *pNode, CCNodeLoader *pCCNodeLoader)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPrioritySubStoreLayer, true);
    fillUIElements();

}

bool CCB_CLASS_NAME ::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblUnlockKey", CCLabelTTF*, this->cb_lblUnlockKey);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblCoinVal", CCLabelTTF*, this->cb_lblCoinVal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblPearlVal", CCLabelTTF*, this->cb_lblPearlVal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblExpVal", CCLabelTTF*, this->cb_lblExpVal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblUnlockVal", CCLabelTTF*, this->cb_lblUnlockVal);
  
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_lblTip", CCLabelTTF*, this->cb_lblTip);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuRecharge", CCMenu*, this->cb_menuRecharge);
    
	return true;
}



SEL_MenuHandler CCB_CLASS_NAME::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{

 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRechargeClicked", CCB_CLASS_NAME::onRechargeClicked);
    
    
	return NULL;
}

SEL_CCControlHandler CCB_CLASS_NAME::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void CCB_CLASS_NAME::onEnter()
{
    
	CCLayer::onEnter();
    
}

void CCB_CLASS_NAME::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
    
}


bool CCB_CLASS_NAME::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    

   isTouchInMenu =  cb_menuRecharge->ccTouchBegan(pTouch, pEvent);
    return true;
}

void CCB_CLASS_NAME::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuRecharge->ccTouchMoved(pTouch, pEvent);
    }

}
void CCB_CLASS_NAME::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        isTouchInMenu = false;
        cb_menuRecharge->ccTouchEnded(pTouch, pEvent);
    }

}
void CCB_CLASS_NAME::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInMenu) {
        cb_menuRecharge->ccTouchCancelled(pTouch, pEvent);
        isTouchInMenu = false;
    }

}


void CCB_CLASS_NAME::onRechargeClicked(CCObject *pSender) {
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(kInitRechargeNotifiction);
    
}

void CCB_CLASS_NAME::fillUIElementsHelper( CCLabelTTF *target, CCLabelTTF *tmpl, const char *text ) {
    if( target == NULL || tmpl == NULL || text == NULL) {
        return;
    }
    target->setFontName(tmpl->getFontName());
    target->setFontSize(tmpl->getFontSize());
    target->setFontFillColor(tmpl->getColor());
    target->setString(text);
    
}

//填充ui元素
void CCB_CLASS_NAME::fillUIElements() {
    
    //template 1
    //cb_lblUnlockKey->setFontName("迷你简胖娃");
    //cb_lblUnlockKey->setFontSize(18);
    //cb_lblUnlockKey->setFontFillColor(ccc3(254, 226, 2));
    //cb_lblUnlockKey->setString("解锁");


    //template2
    //cb_lblCoinVal->setFontName(cb_lblUnlockKey->getFontName());
    //cb_lblCoinVal->setFontSize(cb_lblUnlockKey->getFontSize());
    //cb_lblCoinVal->setString("10万");
    
    
    //fillUIElementsHelper(cb_lblPearlVal, cb_lblCoinVal, "1000");
    //fillUIElementsHelper(cb_lblExpVal, cb_lblCoinVal, "5小时");
    //fillUIElementsHelper(cb_lblUnlockVal, cb_lblCoinVal, "小飞鱼");
    
//    cb_lblTip->setFontName(cb_lblUnlockKey->getFontName());
//    cb_lblTip->setFontSize(22);
//    cb_lblTip->setFontFillColor(ccc3(52, 236, 2));
//    cb_lblTip->setString("首次充值即可获得:");

    
}
