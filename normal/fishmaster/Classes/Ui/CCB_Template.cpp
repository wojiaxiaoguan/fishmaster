
#include "CCB_Template.h"
using namespace cocos2d;


CCB_CLASS_NAME:: CCB_CLASS_NAME ()
:CCLayer()
{
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(SceneReplaceTime, CCB_CLASS_NAME ::scene(), ccBLACK));
    

    //cb_menuChests = NULL;

}

CCB_CLASS_NAME:: ~ CCB_CLASS_NAME ()
{
    
   // CC_SAFE_RELEASE(cb_menuChests);

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
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, EPriorityStore, true);
    fillUIElements();

}

bool CCB_CLASS_NAME ::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, CCNode *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cb_menuChests", CCMenu*, this->cb_menuChests);
    
	return true;
}

SEL_MenuHandler CCB_CLASS_NAME::onResolveCCBCCMenuItemSelector(CCObject *pTarget, const char *pSelectorName)
{

 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onExitClicked", CCB_CLASS_NAME::onExitClicked);
    
    
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
    //return cb_menuChests->ccTouchBegan(pTouch, pEvent);
}

void CCB_CLASS_NAME::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //cb_menuChests->ccTouchMoved(pTouch, pEvent);
}
void CCB_CLASS_NAME::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    //cb_menuChests->ccTouchEnded(pTouch, pEvent);
}
void CCB_CLASS_NAME::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    //cb_menuChests->ccTouchCancelled(pTouch, pEvent);
}

void CCB_CLASS_NAME::onExitClicked(CCObject *pSender) {
}

//填充ui元素
void CCB_CLASS_NAME::fillUIElements() {
    
}
